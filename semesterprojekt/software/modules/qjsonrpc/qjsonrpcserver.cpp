#include "qjsonrpcserver.h"
#include "qjsonrpcclient.h"

#include <QtWebSockets>
#include <functional>

Q_LOGGING_CATEGORY(MODULES_QJSONRPC_SERVER, "modules.qjsonrpc.server", QtWarningMsg)

#ifdef QDISCOVERYSERVICE_USED
    #include "qdiscoveryservice.h"
#endif

class QJsonRpcServer::PrivateData
{
public:
    QString serverName;
    QScopedPointer<QWebSocketServer> listenServer;
    QHash<QString, QJsonRpcServer::RemoteProcedureType> prodcedureMap;
    QHash<QString, QString> signatureMap;
    QSet<QWebSocket*> connectedClients;

#ifdef QDISCOVERYSERVICE_USED
    QDiscoveryService publishService;
    QTimer publishTimer;
#endif
};

QJsonRpcServer::QJsonRpcServer(QString serverName, QObject *parent) : QObject(parent)
  ,d_data(new PrivateData)
{
    d_data->serverName = serverName.isEmpty() ? (QUuid::createUuid().toString() + "_RPC_SERVER") : serverName;
    d_data->listenServer.reset(new QWebSocketServer(d_data->serverName, QWebSocketServer::NonSecureMode));

    QObject::connect(d_data->listenServer.data(), &QWebSocketServer::newConnection, this, &QJsonRpcServer::onNewConnection);

#ifdef QDISCOVERYSERVICE_USED
    QObject::connect(&d_data->publishTimer, &QTimer::timeout, &d_data->publishService, &QDiscoveryService::publishServiceInfo);
#endif

    //register internal methods to list all registered methods and their signature
    registerMethod(QStringLiteral("rpc.listMethods"), std::bind(&QJsonRpcServer::listMethods, this, std::placeholders::_1), QStringLiteral("array(null)"));
    registerMethod(QStringLiteral("rpc.getSignature"), std::bind(&QJsonRpcServer::getSignature, this, std::placeholders::_1), QStringLiteral("string(string)"));
}

QJsonRpcServer::~QJsonRpcServer()
{

}

QString QJsonRpcServer::serverName() const
{
    return d_data->serverName;
}

void QJsonRpcServer::registerMethod(const QString &methodName, QJsonRpcServer::RemoteProcedureType method, QString signature)
{
    d_data->prodcedureMap.insert(methodName, method);
    d_data->signatureMap.insert(methodName, signature);
}

void QJsonRpcServer::unregister(const QString &methodName)
{
    d_data->prodcedureMap.remove(methodName);
    d_data->signatureMap.remove(methodName);
}

void QJsonRpcServer::sendNotification(const QString &methodName, QJsonValue params)
{
    foreach(QWebSocket* client, d_data->connectedClients) {
        QJsonObject notificationObject;
        notificationObject.insert(QStringLiteral("jsonrpc"), QStringLiteral("2.0"));
        notificationObject.insert(QStringLiteral("method"), methodName);
        notificationObject.insert(QStringLiteral("params"), params);

        //client->sendTextMessage(QString::fromUtf8(QJsonDocument(notificationObject).toJson()));
        client->sendBinaryMessage(QJsonDocument(notificationObject).toBinaryData());
    }
}

QJsonValue QJsonRpcServer::listMethods(QJsonValue params) const
{
    Q_UNUSED(params)
    QJsonArray methods;
    foreach(QString method, d_data->prodcedureMap.keys()) {
        methods << method;
    }
    return methods;
}

QJsonValue QJsonRpcServer::getSignature(QJsonValue params) const
{
    return d_data->signatureMap.value(params.toString(), QString());
}

QJsonObject QJsonRpcServer::onNewMessageReceived(QJsonObject messageObject)
{
    const QString jsonrpc = messageObject.value(QStringLiteral("jsonrpc")).toString();
    const QString method = messageObject.value(QStringLiteral("method")).toString();
    const QJsonValue params = messageObject.value(QStringLiteral("params"));
    const QString id = messageObject.value(QStringLiteral("id")).toString();

    QJsonObject resultObject;
    resultObject.insert(QStringLiteral("jsonrpc"), QStringLiteral("2.0"));
    resultObject.insert(QStringLiteral("id"), id);

    if(jsonrpc != QStringLiteral("2.0")) {
        qCWarning(MODULES_QJSONRPC_SERVER) << "Invalid json rpc message.";

        QJsonObject errorObject;
        errorObject.insert(QStringLiteral("code"), QJsonRpcClient::ErrorCodeInvalidRequest);
        errorObject.insert(QStringLiteral("message"), QStringLiteral("Invalid Request"));
        resultObject.insert(QStringLiteral("error"), errorObject);
        return resultObject;
    }

    if(!d_data->prodcedureMap.contains(method)) {
        qCWarning(MODULES_QJSONRPC_SERVER) << "Unknown method name" << method;

        QJsonObject errorObject;
        errorObject.insert(QStringLiteral("code"), QJsonRpcClient::ErrorCodeUnkownProdcedure);
        errorObject.insert(QStringLiteral("message"), QStringLiteral("Procedure not found."));
        resultObject.insert(QStringLiteral("error"), errorObject);
        return resultObject;
    }

    RemoteProcedureType methodCallback = d_data->prodcedureMap.value(method);
    QJsonValue result = methodCallback(params);
    resultObject.insert(QStringLiteral("result"), result);

    return resultObject;
}

void QJsonRpcServer::onNewConnection()
{
    QWebSocket *client = d_data->listenServer->nextPendingConnection();
    d_data->connectedClients.insert(client);

    qCDebug(MODULES_QJSONRPC_SERVER) << "Client connected" << client->peerAddress().toString() << "on port" << client->peerPort();

    QObject::connect(client, &QWebSocket::textMessageReceived, [this, client](const QString& message) {
        QJsonObject returnObject = onNewMessageReceived(QJsonDocument::fromJson(message.toUtf8()).object());
        client->sendTextMessage(QString::fromUtf8(QJsonDocument(returnObject).toJson()));
    });

    QObject::connect(client, &QWebSocket::binaryMessageReceived, [this, client](const QByteArray& message) {
        QJsonObject returnObject = onNewMessageReceived(QJsonDocument::fromBinaryData(message).object());
        client->sendBinaryMessage(QJsonDocument(returnObject).toBinaryData());
    });

    QObject::connect(client, &QWebSocket::disconnected, [this, client]() {
        qCDebug(MODULES_QJSONRPC_SERVER) << "Client disconnected" << client->peerAddress().toString() << "on port" << client->peerPort();

        d_data->connectedClients.remove(client);
        client->deleteLater();
    });
}

bool QJsonRpcServer::startListening(QHostAddress address, quint16 port)
{
    if(!d_data->listenServer->listen(address, port))
        return false;

#ifdef QDISCOVERYSERVICE_USED
    d_data->publishService.setServiceName(d_data->serverName);
    d_data->publishService.setServiceInfo({
                                              {QStringLiteral("address"), d_data->listenServer->serverAddress().toString()},
                                              {QStringLiteral("port"), d_data->listenServer->serverPort()},
                                              {QStringLiteral("url"), d_data->listenServer->serverUrl().toString()},
                                              {QStringLiteral("availableMethods"), listMethods(QJsonValue())}
                                          });
    d_data->publishTimer.start(2000);
#endif

    return true;
}

void QJsonRpcServer::stopListening()
{
#ifdef QDISCOVERYSERVICE_USED
    d_data->publishTimer.stop();
#endif

    d_data->listenServer->close();
    foreach(QWebSocket* client, d_data->connectedClients) {
        client->close();
    }
}

