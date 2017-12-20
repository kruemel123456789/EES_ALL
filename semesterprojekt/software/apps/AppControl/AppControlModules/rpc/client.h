#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <qjsonrpcclient.h>

class Client : public QObject
{
    Q_OBJECT

    QString clientname;
    QJsonRpcClient client;

public:
    Client(QString clientname, QObject *parent = 0);
    void connect(QString servername);
    void getServerMethods();


public slots:
    void received_connectedChanged(bool connectionState);
    void send_appcontrol_platform_move(int userId);
    void send_appcontrol_robot_move(int movementId, int glassId);
    void messageReceived(QString, QJsonValue);

signals:
    void connectedChanged(bool connectionState);
    void received_platform_appcontrol_feedback_move(int workstate);
    void received_robot_appcontrol_feedback_move(int workstate);
};

#endif // CLIENT_H
