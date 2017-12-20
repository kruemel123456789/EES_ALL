#ifndef QJSONRPCCLIENT_H
#define QJSONRPCCLIENT_H

#include <QtCore>

Q_DECLARE_LOGGING_CATEGORY(MODULES_QJSONRPC_CLIENT)

/// \brief JsonRPC client
///
/// \author Timo Zimmermann
class QJsonRpcClient : public QObject
{
    Q_OBJECT

public:
    enum ErrorCode {
        ErrorCodeInvalidRequest = -32600,
        ErrorCodeUnkownProdcedure = -32601,
        ErrorCodeTimeout = -32602
    };

private:
    class PrivateData;
    QScopedPointer<PrivateData> d_data;

    void setConnected(bool arg);

public:
    explicit QJsonRpcClient(QObject *parent = 0);
    virtual ~QJsonRpcClient();

    bool isConnected() const;

    bool isBinary() const;
    void setBinary(bool arg);

    bool isAsync() const;
    void setAsync(bool arg);

    void test();

protected slots:
    void sendMessage(const QJsonObject& messageObject);
    void onNewMessageReceived(const QJsonObject& messageObject);

public slots:
    QJsonValue callMethod(const QString& methodName, QJsonValue params, int timeout = 1000);

    void open(QString serverName = QString());
    void close();

signals:
    void notificationReceived(QString methodName, QJsonValue params);
    void resultReceived(QString methodName, QJsonValue result, QString id);
    void errorReceived(QString methodName, QJsonObject errorObject, QString id);

    void connectedChanged(bool);
    void binaryChanged(bool);
    void asyncChanged(bool);
};

#endif // QJSONRPCCLIENT_H
