#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <qjsonrpcserver.h>
#include <qjsonrpcclient.h>

class Server : public QObject
{
    Q_OBJECT

QJsonRpcServer *server;
QString servername;
int port;

bool serverRunning = false;

public:
    Server(QString servername, int port, QObject *parent = 0);
    void start();
    void stop();


signals:
    void statusChanged(bool serverRunning);
    void newMessage(QString servername, QString message);

public slots:
    void toggle();
    void registerMethods();
    void unregisterMethods();
    QString getServername();
    void sendPlatformFeedbackMove(int workstate);
    void sendRobotFeedbackMove(int workstate);


};

#endif // SERVER_H
