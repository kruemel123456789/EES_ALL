#include "qdiscoveryservice.h"

#include <QtNetwork>
#include <QtDebug>

Q_LOGGING_CATEGORY(MODULES_QDISCOVERYSERVICE, "modules.qdiscoveryservice", QtWarningMsg)

const quint16 QDiscoveryService::PUBLISHING_PORT = 51051;
const quint16 QDiscoveryService::PUBLISHING_PORT_ALTERNATIVE = 26026;
const QString QDiscoveryService::PUBLISH_TYPE = QStringLiteral("DiscoveryService");

class QDiscoveryService::PrivateData
{
public:
    QString serviceName;
    QJsonObject serviceInfo;
    QUdpSocket publishSocket;
    QUdpSocket discoverySocket;
    QJsonObject serviceMetaInfo;
    bool loopbackEnabled;
};


QDiscoveryService::QDiscoveryService(QString serviceName, QObject *parent) : QObject(parent)
  ,d_data(new PrivateData())
{
    d_data->serviceName = serviceName.isEmpty() ? QUuid::createUuid().toString() : serviceName;
    d_data->loopbackEnabled = true;

    //connect discovery channel
    QObject::connect(&d_data->discoverySocket, &QUdpSocket::readyRead, [this]() {
        QHostAddress senderAddress;
        quint16 senderPort;

        //read the datagram
        QByteArray datagram(d_data->discoverySocket.pendingDatagramSize(), '\0');
        d_data->discoverySocket.readDatagram(datagram.data(), datagram.size(), &senderAddress, &senderPort);

        //try to parse the json message
        QJsonObject service = QJsonDocument::fromJson(datagram).object();
        QString type = service.value(QStringLiteral("type")).toString();
        QString serviceName = service.value(QStringLiteral("serviceName")).toString();

        //check if valid and relevant to this service
        if((type != PUBLISH_TYPE) || (serviceName != this->serviceName())) return;

        d_data->serviceMetaInfo.insert(QStringLiteral("serviceName"), serviceName);
        d_data->serviceMetaInfo.insert(QStringLiteral("remoteAddress"), senderAddress.toString().remove(QRegularExpression(QStringLiteral(":.*:"))));
        d_data->serviceMetaInfo.insert(QStringLiteral("lastDiscovery"), QDateTime::currentDateTime().toString());

        //convert payload
        QByteArray serviceInfoRaw = service.value(QStringLiteral("serviceInfo")).toString().toLocal8Bit();
        QJsonObject serviceInfo = QJsonDocument::fromBinaryData(QByteArray::fromBase64(serviceInfoRaw)).object();
        serviceInfo.insert(QStringLiteral("_metaData"), d_data->serviceMetaInfo);

        setServiceInfo(serviceInfo);
    });

    QObject::connect(&d_data->discoverySocket, &QUdpSocket::stateChanged, [this](QAbstractSocket::SocketState state) {
        emit discoveryActiveChanged(state == QUdpSocket::BoundState);
    });
}

QDiscoveryService::~QDiscoveryService()
{

}

bool QDiscoveryService::waitForServiceInfo(int msecs)
{
    if(!isDiscoveryActive()) return false;

    return d_data->discoverySocket.waitForReadyRead(msecs);
}

void QDiscoveryService::setServiceName(QString arg)
{
    if(d_data->serviceName == arg) return;

    d_data->serviceName = arg;
    emit serviceNameChanged(arg);
}

QString QDiscoveryService::serviceName() const
{
    return d_data->serviceName;
}

void QDiscoveryService::setDiscoveryActive(bool enable)
{
    if(isDiscoveryActive() == enable) return;

    if(isDiscoveryActive()) stopDiscovery();
    else startDiscovery();
}

bool QDiscoveryService::isDiscoveryActive() const
{
    return d_data->discoverySocket.state() == QUdpSocket::BoundState;
}

void QDiscoveryService::setLoopbackEnabled(bool arg)
{
    if(d_data->loopbackEnabled == arg) return;

    d_data->loopbackEnabled = arg;
    emit loopbackEnabledChanged(arg);
}

bool QDiscoveryService::isLoopbackEnabled() const
{
    return d_data->loopbackEnabled;
}

void QDiscoveryService::startDiscovery()
{
    if(!d_data->discoverySocket.bind(PUBLISHING_PORT)) {
        qCWarning(MODULES_QDISCOVERYSERVICE) << "Binding to publishing port" << PUBLISHING_PORT << "failed.";
        if(!d_data->discoverySocket.bind(PUBLISHING_PORT_ALTERNATIVE))
            qCWarning(MODULES_QDISCOVERYSERVICE) << "Binding to alternative publishing port" << PUBLISHING_PORT_ALTERNATIVE << "failed also. NO SERVICE DISCOVERY AVAILABLE!";
    }
}

void QDiscoveryService::stopDiscovery()
{
    d_data->discoverySocket.close();
}

void QDiscoveryService::publishServiceInfo()
{
    QJsonObject discoveryObject;
    discoveryObject.insert(QStringLiteral("type"), PUBLISH_TYPE);
    discoveryObject.insert(QStringLiteral("serviceName"), serviceName());
    discoveryObject.insert(QStringLiteral("serviceInfo"), QString::fromLatin1(QJsonDocument(d_data->serviceInfo).toBinaryData().toBase64()));
    d_data->publishSocket.writeDatagram(QJsonDocument(discoveryObject).toJson(QJsonDocument::Compact), QHostAddress::Broadcast, PUBLISHING_PORT);
    d_data->publishSocket.writeDatagram(QJsonDocument(discoveryObject).toJson(QJsonDocument::Compact), QHostAddress::Broadcast, PUBLISHING_PORT_ALTERNATIVE);

    if(isLoopbackEnabled()) {
        d_data->publishSocket.writeDatagram(QJsonDocument(discoveryObject).toJson(QJsonDocument::Compact), QHostAddress::LocalHost, PUBLISHING_PORT);
        d_data->publishSocket.writeDatagram(QJsonDocument(discoveryObject).toJson(QJsonDocument::Compact), QHostAddress::LocalHost, PUBLISHING_PORT_ALTERNATIVE);
    }

    qCDebug(MODULES_QDISCOVERYSERVICE) << "Publish service info:" << d_data->serviceInfo;
}

void QDiscoveryService::setServiceInfo(const QJsonObject &arg)
{
    if(d_data->serviceInfo == arg) return;

    d_data->serviceInfo = arg;
    emit serviceInfoChanged(arg);
}

QJsonObject QDiscoveryService::serviceInfo() const
{
    return d_data->serviceInfo;
}
