#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <qjsonrpcserver.h>
#include <qjsonrpcclient.h>

class Server : public QObject
{
    Q_OBJECT

QJsonRpcServer *server;

public:
    Server(QObject *parent = 0);

signals:
    void received_platform_appcontrol_feedback_move(int workstate);
    void received_robot_appcontrol_feedback_move(int workstate);

public slots:
    void init(QString servername, int port);
    void registerMethods();
    void unregisterMethods();
    QString getServername();


};

#endif // SERVER_H
