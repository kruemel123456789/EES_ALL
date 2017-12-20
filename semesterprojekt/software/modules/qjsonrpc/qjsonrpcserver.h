#ifndef QJSONRPCSERVER_H
#define QJSONRPCSERVER_H

#include <QtCore>
#include <QtNetwork>
#include <functional>

Q_DECLARE_LOGGING_CATEGORY(MODULES_QJSONRPC_SERVER)

class QJsonRpcServer : public QObject
{
    Q_OBJECT

public:
    typedef std::function<QJsonValue(QJsonValue)> RemoteProcedureType;

private:
    class PrivateData;
    QScopedPointer<PrivateData> d_data;

public:
    explicit QJsonRpcServer(QString serverName = QString(), QObject *parent = 0);
    virtual ~QJsonRpcServer();

    QString serverName() const;

    void registerMethod(const QString& methodName, RemoteProcedureType method, QString signature = QString());
    void unregister(const QString& methodName);

    void sendNotification(const QString& methodName, QJsonValue params = QJsonValue());

protected:
    QJsonValue listMethods(QJsonValue params) const;
    QJsonValue getSignature(QJsonValue params) const;

protected slots:
    QJsonObject onNewMessageReceived(QJsonObject messageObject);
    void onNewConnection();

public slots:
    bool startListening(QHostAddress address = QHostAddress::AnyIPv4, quint16 port = 0);
    void stopListening();

signals:

};

#endif // QJSONRPCSERVER_H
