#include "client.h"

#include <QtNetwork>



Client::Client(QString clientname, int port, QObject *parent)
    : QObject(parent)
{
    this->clientname = clientname;
    this->port = port;

    // Reicht das connectedChange-Signal der Klasse QJsonRpcClient weiter
    // Das Signal wird aufgerufen, wenn sich der Verbindungsstatus des Clients aendert (verbunden / nicht verbunden)
    QObject::connect(&this->client, SIGNAL(connectedChanged(bool)), this, SLOT(received_connectedChanged(bool)));

    QObject::connect(&this->client, SIGNAL(notificationReceived(QString, QJsonValue)), this, SLOT(messageReceived(QString, QJsonValue)));

}



// Mit dem Server verbinden
bool Client::connectToServer(QString address)
{
    this->address = address;
    emit newMessage(this->clientname, "Connecting to " + this->address + ":" + QString::number(this->port));
    this->client.open(QString("ws://%1:%2").arg(this->address).arg(this->port));
    return true;
}

// Zeigt alle Funktionen, welche vom Server bereitgestellt werden, im Log an
void Client::getMethods() {
    QJsonArray methods = this->client.callMethod(QStringLiteral("rpc.listMethods"), QJsonValue()).toArray();

    QJsonDocument doc;
    doc.setArray(methods);


    emit newMessage(this->clientname, QString(doc.toJson()));


    qDebug() << "Methods received:" << methods.toVariantList();
}

// Wird aufgerufen, wenn sich der Verbindungsstatus des Clients aktualisiert
void Client::received_connectedChanged(bool connectionState) {
    // Loggen und Signal weiterreichen
    emit newMessage(this->clientname, QString("Client " + (connectionState ? QString("connected to") : QString("disconnected from")) + " Server"));
    emit connectedChanged(connectionState);
}


// Die Clientklasse wird hier fuer mehrere Gruppen verwendet und kann deshalb folgende Funktionsaufrufe durchfuehren

// AppControl --> Platform
void Client::sendPlatformMoveRequest(int userId) {
    auto requestcontent = QJsonObject(
    {
        qMakePair(QString("userId"), QJsonValue(userId)),
    });

    this->client.callMethod(QStringLiteral("appcontrol_platform_move"), requestcontent);

}



// AppControl --> Robot
void Client::sendRobotMoveRequest(int movementId, int glassId) {

    auto requestcontent = QJsonObject(
    {
        qMakePair(QString("movementId"), QJsonValue(movementId)),
     qMakePair(QString("glassId"), QJsonValue(glassId)),
    });


    this->client.callMethod(QStringLiteral("appcontrol_robot_move"), requestcontent);

}

void Client::messageReceived(QString methodname, QJsonValue params) {
    if (methodname == "platform_appcontrol_feedback_move") {
       emit this->newMessage(this->clientname, "Received move feedback from Platform: " + QString::number(params.toObject().value("workstate").toInt()));
    } else if (methodname == "robot_appcontrol_feedback_move") {
        emit this->newMessage(this->clientname, "Received move feedback from Robot: " + QString::number(params.toObject().value("workstate").toInt()));
    }
}
