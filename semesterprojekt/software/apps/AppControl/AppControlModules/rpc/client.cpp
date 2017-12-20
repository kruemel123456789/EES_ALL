#include "client.h"

Client::Client(QString clientname, QObject *parent)
    : QObject(parent)
{
    this->clientname = clientname;


    QObject::connect(&this->client, SIGNAL(connectedChanged(bool)), this, SLOT(received_connectedChanged(bool)));

    QObject::connect(&this->client, SIGNAL(notificationReceived(QString, QJsonValue)), this, SLOT(messageReceived(QString, QJsonValue)));



}


void Client::connect(QString servername) {
    this->client.setAsync(false);
    this->client.open(servername);
}

void Client::send_appcontrol_platform_move(int userId) {
    auto requestcontent = QJsonObject(
    {
        qMakePair(QString("userId"), QJsonValue(userId)),
    });
    this->client.callMethod(QStringLiteral("appcontrol_platform_move"), requestcontent);
}

void Client::send_appcontrol_robot_move(int movementId, int glassId) {
    auto requestcontent = QJsonObject(
    {
        qMakePair(QString("movementId"), QJsonValue(movementId)),
        qMakePair(QString("glassId"), QJsonValue(glassId)),
    });

    this->client.callMethod(QStringLiteral("appcontrol_robot_move"), requestcontent);
}

void Client::received_connectedChanged(bool connectionState) {
    emit connectedChanged(connectionState);
}


void Client::getServerMethods() {
    QJsonArray methods = this->client.callMethod(QStringLiteral("rpc.listMethods"), QJsonValue()).toArray();

    QJsonDocument doc;
    doc.setArray(methods);


    //emit newMessage(this->clientname, QString(doc.toJson()));


    qDebug() << "Methods received:" << methods.toVariantList();
}

void Client::messageReceived(QString methodname, QJsonValue params) {
    if (methodname == "platform_appcontrol_feedback_move") {
        emit received_platform_appcontrol_feedback_move(params.toObject().value("workstate").toInt());
    } else if (methodname == "robot_appcontrol_feedback_move") {
        emit received_robot_appcontrol_feedback_move(params.toObject().value("workstate").toInt());
    }
}

