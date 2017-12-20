#include "qjsonrpcclient.h"
#include <QtWebSockets>

Q_LOGGING_CATEGORY(MODULES_QJSONRPC_CLIENT, "modules.qjsonrpc.client", QtWarningMsg)

#ifdef QDISCOVERYSERVICE_USED
    #include "qdiscoveryservice.h"
#endif

class QJsonRpcClient::PrivateData
{
public:
    QWebSocket socket;
    QMap<QString, QJsonObject> pendingResults;
    bool binary;
    bool async;
    QTimer callTimeout;
    bool connected;

    //sync calls
    QMap<QString, QEventLoop*> syncEventLoops;

#ifdef QDISCOVERYSERVICE_USED
    QDiscoveryService remoteService;
#endif
};

QJsonRpcClient::QJsonRpcClient(QObject *parent) : QObject(parent)
  ,d_data(new PrivateData)
{
    d_data->connected = false;
    d_data->binary = true;
    d_data->async = false;

    QObject::connect(&d_data->socket, &QWebSocket::stateChanged, [this](QAbstractSocket::SocketState state){
        setConnected(state == QAbstractSocket::ConnectedState);
    });



    QObject::connect(&d_data->socket, &QWebSocket::textMessageReceived, [this](const QString& message) {
        QJsonParseError error;
        const QJsonObject messageObject = QJsonDocument::fromJson(message.toUtf8(), &error).object();
        if(error.error != QJsonParseError::NoError) {
            qCWarning(MODULES_QJSONRPC_CLIENT) << "Invalid JSON message received. Parsing error" << error.errorString() << "in Message:" << message;
            return;
        }

        onNewMessageReceived(messageObject);
    });

    QObject::connect(&d_data->socket, &QWebSocket::binaryMessageReceived, [this](const QByteArray& message) {
        const QJsonObject messageObject = QJsonDocument::fromBinaryData(message).object();
        if(messageObject.isEmpty()) {
            qCWarning(MODULES_QJSONRPC_CLIENT) << "Invalid binary JSON message received: " << message;
            return;
        }

        onNewMessageReceived(messageObject);
    });

    QObject::connect(&d_data->callTimeout, &QTimer::timeout, [this]() {
        if(d_data->pendingResults.isEmpty()) return;

        QDateTime now = QDateTime::currentDateTime();
        foreach(QString id, d_data->pendingResults.keys()) {
            QJsonObject pendingResult = d_data->pendingResults.value(id);
            QDateTime sent = QDateTime::fromString(pendingResult.value(QStringLiteral("sent")).toString(), "yyyyMMdd-hh:mm:ss.zzz");
            QDateTime deadline = sent.addMSecs(pendingResult.value(QStringLiteral("timeout")).toInt());

            if(now < deadline) continue;

            qCWarning(MODULES_QJSONRPC_CLIENT) << "Method call (" << pendingResult.value(QStringLiteral("method")).toString() << ") timed out.";

            //create an error object
            QJsonObject errorObject;
            errorObject.insert(QStringLiteral("code"), ErrorCodeTimeout);
            errorObject.insert(QStringLiteral("message"), QStringLiteral("Method call timed out."));
            pendingResult.insert(QStringLiteral("error"),errorObject);

            //forward the error 'reply' to the onNewMessageReceived() function
            onNewMessageReceived(pendingResult);
        }
    });
    d_data->callTimeout.start(250);

#ifdef QDISCOVERYSERVICE_USED
    QObject::connect(&d_data->remoteService, &QDiscoveryService::serviceInfoChanged, [this](QJsonObject serviceInfo) {
        if(d_data->socket.state() != QAbstractSocket::UnconnectedState) return;

        QString remoteAddress = serviceInfo.value("_metaData").toObject().value("remoteAddress").toString();
        quint16 port = serviceInfo.value("port").toInt();

        qCDebug(MODULES_QJSONRPC_CLIENT) << "Service discovered. Trying to connect to" << remoteAddress << "on port" << QString::number(port);
        d_data->socket.open(QString("ws://") + remoteAddress + ":" + QString::number(port));
    });
#endif
}

QJsonRpcClient::~QJsonRpcClient()
{
    close();
}

bool QJsonRpcClient::isConnected() const
{
    return d_data->socket.state() == QAbstractSocket::ConnectedState;
}

void QJsonRpcClient::setConnected(bool arg)
{
    if(d_data->connected == arg) return;

    d_data->connected = arg;
    emit connectedChanged(arg);
}

bool QJsonRpcClient::isBinary() const
{
    return d_data->binary;
}

void QJsonRpcClient::setBinary(bool arg)
{
    if(d_data->binary == arg) return;

    d_data->binary = arg;
    emit binaryChanged(arg);
}

bool QJsonRpcClient::isAsync() const
{
    return d_data->async;
}

void QJsonRpcClient::setAsync(bool arg)
{
    if(d_data->async == arg) return;

    d_data->async = arg;
    emit asyncChanged(arg);
}

void QJsonRpcClient::sendMessage(const QJsonObject &messageObject)
{

    // Roboter-Gruppe erwartet Strings
    /*
    if(d_data->binary)
        d_data->socket.sendBinaryMessage(QJsonDocument(messageObject).toBinaryData());
    else
        d_data->socket.sendTextMessage(QString::fromUtf8(QJsonDocument(messageObject).toJson()));
        */

    d_data->socket.sendTextMessage(QString::fromUtf8(QJsonDocument(messageObject).toJson()));
    d_data->socket.flush();
}

void QJsonRpcClient::onNewMessageReceived(const QJsonObject& messageObject)
{
    const QString jsonrpc = messageObject.value(QStringLiteral("jsonrpc")).toString();          //mandatory
    const QString id = messageObject.value(QStringLiteral("id")).toString();                    //in case of a valid result or error
    const QString methodName = messageObject.value(QStringLiteral("method")).toString();        //in case of a notification
    const QJsonValue paramsObject = messageObject.value(QStringLiteral("params"));              //in case of a notification
    const QJsonValue resultObject = messageObject.value(QStringLiteral("result"));              //in case of a valid result
    const QJsonObject errorObject = messageObject.value(QStringLiteral("error")).toObject();    //in case of an error

    //invalid message
    if(jsonrpc != QStringLiteral("2.0")) {
        qCWarning(MODULES_QJSONRPC_CLIENT) << "Invalid rpc protocol:" << messageObject;
        return;
    }

    //no id means notification
    if(id.isEmpty()) {
        emit notificationReceived(methodName, paramsObject);
        return;
    }

    //check if a pending call is waiting on that message
    if(!d_data->pendingResults.contains(id)) {
        qCWarning(MODULES_QJSONRPC_CLIENT) << "Unknown/timed out reply ( ID:" << id << ") received.";
        return;
    }

    //take the corresponding pending call
    QJsonObject pendingResult = d_data->pendingResults.take(id);
    pendingResult.insert(QStringLiteral("received"), QDateTime::currentDateTime().toString("yyyyMMdd-hh:mm:ss.zzz"));
    pendingResult.insert("error", errorObject);
    pendingResult.insert("result", resultObject);

    //handle possible sync calls
    if(d_data->syncEventLoops.contains(id)) {
        QEventLoop* syncWaitLoop = d_data->syncEventLoops.value(id);
        syncWaitLoop->setProperty("result", QVariant(resultObject));
        syncWaitLoop->exit(errorObject.isEmpty() ?  0 : errorObject.value(QStringLiteral("code")).toInt());
    }

    //check if an error was returned
    if(!errorObject.isEmpty()) {
        qCWarning(MODULES_QJSONRPC_CLIENT) << "Method" << pendingResult.value(QStringLiteral("method")).toString() << "returned with an error:" << errorObject;
        emit errorReceived(methodName, errorObject, id);
        return;
    }

    //emit received data
    emit resultReceived(methodName, resultObject, id);
}

QJsonValue QJsonRpcClient::callMethod(const QString &methodName, QJsonValue params, int timeout)
{
    if(!isConnected()) {
        qCWarning(MODULES_QJSONRPC_CLIENT) << "Unable to call remote method (" << methodName << "). Not connected.";
        return QJsonValue();
    }

    QString id = QUuid::createUuid().toString();
    QJsonObject messageObject;
    messageObject.insert(QStringLiteral("jsonrpc"), QStringLiteral("2.0"));
    messageObject.insert(QStringLiteral("method"), methodName);
    messageObject.insert(QStringLiteral("params"), params);
    messageObject.insert(QStringLiteral("id"), id);

    QJsonObject internalMessageObject(messageObject);
    internalMessageObject.insert(QStringLiteral("sent"), QDateTime::currentDateTime().toString("yyyyMMdd-hh:mm:ss.zzz"));
    internalMessageObject.insert(QStringLiteral("timeout"), timeout);
    internalMessageObject.insert(QStringLiteral("sync"), !d_data->async);
    d_data->pendingResults.insert(id, internalMessageObject);

    sendMessage(messageObject);

    //return immediately if this is an async call
    if(d_data->async) return id;

    //start event loop and wait for result or timeout on a sync call
    QScopedPointer<QEventLoop> syncEventLoop(new QEventLoop());
    d_data->syncEventLoops.insert(id, syncEventLoop.data());

    //blocking wait
    int syncRetValue = syncEventLoop->exec();

    QJsonValue syncResult = QJsonValue::fromVariant(syncEventLoop->property("result"));
    d_data->syncEventLoops.remove(id);

    return syncRetValue != 0 ? QJsonValue() : syncResult;
}

void QJsonRpcClient::open(QString serverName)
{
#ifdef QDISCOVERYSERVICE_USED
    if(!serverName.contains("ws://") && !serverName.contains("wss://")) {
        d_data->remoteService.setServiceName(serverName);
        d_data->remoteService.startDiscovery();
        return;
    }
#endif

    qDebug() << "Connecting...";




    d_data->socket.open(serverName);
}

void QJsonRpcClient::test() {

}

void QJsonRpcClient::close()
{
#ifdef QDISCOVERYSERVICE_USED
    d_data->remoteService.stopDiscovery();
#endif

    d_data->socket.close();
}

