#ifndef QEMBROBOPROXIMITY_H
#define QEMBROBOPROXIMITY_H

#include <QtCore>

class QEmbRoboProximity : public QObject
{
    Q_OBJECT

public:
    enum ProximityPosition {
        ProximityFront= 0x01,
        ProximityBack = 0x02,
        ProximityLeft = 0x04,
        ProximityRight = 0x08
    };

private:
    Q_ENUMS(ProximityPosition)
    Q_PROPERTY(int triggeredSensor READ triggeredSensor NOTIFY triggeredSensorChanged)
    Q_PROPERTY(bool front READ front NOTIFY triggeredSensorChanged)
    Q_PROPERTY(bool back READ back NOTIFY triggeredSensorChanged)
    Q_PROPERTY(bool left READ left NOTIFY triggeredSensorChanged)
    Q_PROPERTY(bool right READ right NOTIFY triggeredSensorChanged)

    class PrivateData;
    QScopedPointer<PrivateData> d_data;

public:
    explicit QEmbRoboProximity(QObject *parent = 0);
    virtual ~QEmbRoboProximity();

    int triggeredSensor() const;
    void setTriggeredSensor(int arg);

    bool front() const;
    bool back() const;
    bool left() const;
    bool right() const;

    void setJson(QJsonValue value);
    QJsonValue toJson() const;

public slots:


signals:
    void triggeredSensorChanged(int triggered);
};

#endif // QEMBROBOPROXIMITY_H
