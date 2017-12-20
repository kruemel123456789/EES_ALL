#ifndef QDISCOVERYSERVICE_H
#define QDISCOVERYSERVICE_H

#include <QtCore>

///\brief Simple class to publish custom service infos via UDP broadcast messages.
/// To publish: Create an object, set the service name, the service info and call publishServiceInfo() (maybe periodically with a timer event).
/// To discover: Create an object, set the service name, connect to the serviceInfoChanged() signal and call startDiscovery()
class QDiscoveryService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString serviceName READ serviceName WRITE setServiceName NOTIFY serviceNameChanged)
    Q_PROPERTY(QJsonObject serviceInfo READ serviceInfo WRITE setServiceInfo NOTIFY serviceInfoChanged)
    Q_PROPERTY(bool discoveryActive READ isDiscoveryActive WRITE setDiscoveryActive NOTIFY discoveryActiveChanged)
    Q_PROPERTY(bool loopbackEnabled READ isLoopbackEnabled WRITE setLoopbackEnabled NOTIFY loopbackEnabledChanged)

    class PrivateData;
    QScopedPointer<PrivateData> d_data;

public:
    static const quint16 PUBLISHING_PORT;
    static const quint16 PUBLISHING_PORT_ALTERNATIVE;
    static const QString PUBLISH_TYPE;

public:
    explicit QDiscoveryService(QString serviceName = QString(), QObject *parent = 0);
    virtual ~QDiscoveryService();

    bool waitForServiceInfo(int msecs = 30000);

    void setServiceName(QString arg);
    QString serviceName() const;

    void setServiceInfo(const QJsonObject& arg);
    QJsonObject serviceInfo() const;

    void setDiscoveryActive(bool enable);
    bool isDiscoveryActive() const;

    void setLoopbackEnabled(bool arg);
    bool isLoopbackEnabled() const;

public slots:
    void startDiscovery();
    void stopDiscovery();
    void publishServiceInfo();

signals:
    void serviceNameChanged(QString serviceName);
    void serviceInfoChanged(QJsonObject serviceInfo);
    void discoveryActiveChanged(bool);
    void loopbackEnabledChanged(bool);
};

#endif // QDISCOVERYSERVICE_H
