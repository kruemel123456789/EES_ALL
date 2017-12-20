#include "server.h"

#include <QtConcurrent/QtConcurrent>




Server::Server(QObject *parent)
    : QObject(parent)
{


}



void Server::init(QString servername, int port) {

    this->server = new QJsonRpcServer(servername);

    this->server->startListening(QHostAddress::Any, port);


    this->registerMethods();


    qDebug() << "Server initialized as " << this->server->serverName();

}



void Server::registerMethods() {

    auto platform_appcontrol_feedback_move = [&](QJsonValue param)->QJsonValue {
        emit received_platform_appcontrol_feedback_move(param.toInt());
        return param;
    };

    auto robot_appcontrol_feedback_move = [&](QJsonValue param)->QJsonValue {
        emit received_robot_appcontrol_feedback_move(param.toInt());
        return param;
    };

    this->server->registerMethod(QStringLiteral("platform_appcontrol_feedback_move"), platform_appcontrol_feedback_move);
    this->server->registerMethod(QStringLiteral("robot_appcontrol_feedback_move"), robot_appcontrol_feedback_move);

}

void Server::unregisterMethods() {
    this->server->unregister(QStringLiteral("platform_appcontrol_feedback_move"));
    this->server->unregister(QStringLiteral("robot_appcontrol_feedback_move"));
}

QString Server::getServername() {
    return this->server->serverName();
}






