#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <qjsonrpcclient.h>

class Client : public QObject
{
    Q_OBJECT

    QString clientname;
    QString address;
    int port;
    QJsonRpcClient client;

public:
    Client(QString clientname, int port, QObject *parent = 0);

public slots:
    bool connectToServer(QString);
    void received_connectedChanged(bool connectionState);
    void getMethods();
    void sendPlatformMoveRequest(int userId);
    void sendRobotMoveRequest(int movementId, int glassId);
    void messageReceived(QString, QJsonValue);

signals:
    void connectedChanged(bool connectionState);
    void newMessage(QString clientname, QString message);
};

#endif // CLIENT_H
