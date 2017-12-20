#include "server.h"

#include <QtConcurrent/QtConcurrent>




Server::Server(QString servername, int port, QObject *parent)
    : QObject(parent)
{

    // Name wird verwendet um die verschiedenen Server in diesem Programm im Log auseinanderzuhalten
    this->servername = servername;
    this->port = port;

    this->server = new QJsonRpcServer(this->servername);

}


// Startet bzw. stoppt den Server
void Server::toggle() {
    if (!this->serverRunning) {
        this->start();
    } else {
        this->stop();
    }
}


// Startet den Server
void Server::start() {
    this->server->startListening(QHostAddress::Any, this->port);


    this->registerMethods();

    emit this->newMessage(this->servername, "Server started on port " + QString::number(this->port));

    this->serverRunning = true;

    emit statusChanged(true);

}

// Stoppt den Server
void Server::stop() {
    this->server->stopListening();

    this->unregisterMethods();

    emit this->newMessage(this->servername, "Server stopped on port " + QString::number(this->port));

    this->serverRunning = false;

    emit statusChanged(false);

}


// Registriert abhängig von der Gruppe, zu welcher der Server gehoert, die Funktionen auf die er reagiert
void Server::registerMethods() {


    if (this->servername == "Platform") {

        auto appcontrol_platform_move = [&](QJsonValue param)->QJsonValue {
                // Wenn die Funktion durch einen Client aufgerufen wird, wird ein Signal ausgesandt
                // Dies bewirkt durch die entsprechende Beruecksichtigung in der QML-Datei, eine Ausgabe im Log
                emit this->newMessage(this->servername, "Received request to move to user " + QString::number(param.toObject().value("userId").toInt()));
            return param;
        };

        this->server->registerMethod(QStringLiteral("appcontrol_platform_move"), appcontrol_platform_move);
    } else if (this->servername == "Robot") {
        auto appcontrol_robot_move = [&](QJsonValue param)->QJsonValue {
                emit this->newMessage(this->servername, "Received request to execute movement " + QString::number(param.toObject().value("movementId").toInt()) + " for glass " + QString::number(param.toObject().value("glassId").toInt()));
            return param;
        };

        this->server->registerMethod(QStringLiteral("appcontrol_robot_move"), appcontrol_robot_move);
    }

}

void Server::unregisterMethods() {

    if (this->servername == "Platform") {
        this->server->unregister(QStringLiteral("platform_appcontrol_feedback_move"));
    } else if (this->servername == "Robot") {
        this->server->unregister(QStringLiteral("robot_appcontrol_feedback_move"));
    } else if (this->servername == "AppControl") {
        this->server->unregister(QStringLiteral("platform_appcontrol_feedback_move"));
         this->server->unregister(QStringLiteral("robot_appcontrol_feedback_move"));
    }
}

QString Server::getServername() {
    return server->serverName();
}

// Platform --> AppControl
void Server::sendPlatformFeedbackMove(int workstate) {
    auto requestcontent = QJsonObject(
    {
        qMakePair(QString("workstate"), QJsonValue(workstate)),
    });

    this->server->sendNotification(QStringLiteral("platform_appcontrol_feedback_move"), requestcontent);

}

// Robot --> AppControl
void Server::sendRobotFeedbackMove(int workstate) {
    auto requestcontent = QJsonObject(
    {
        qMakePair(QString("workstate"), QJsonValue(workstate)),
    });
    this->server->sendNotification(QStringLiteral("robot_appcontrol_feedback_move"), requestcontent);

}






