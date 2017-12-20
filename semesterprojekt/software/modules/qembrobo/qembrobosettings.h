#ifndef QEmbRoboSettings_H
#define QEmbRoboSettings_H

#include <QtCore>

class QEmbRoboSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int maxAcceleration READ maxAcceleration WRITE setMaxAcceleration NOTIFY maxAccelerationChanged)
    Q_PROPERTY(int minAcceleration READ minAcceleration WRITE setMinAcceleration NOTIFY minAccelerationChanged)
    Q_PROPERTY(int maxVelocity READ maxVelocity WRITE setMaxVelocity NOTIFY maxVelocityChanged)
    Q_PROPERTY(int startAcceleration READ startAcceleration WRITE setStartAcceleration NOTIFY startAccelerationChanged)
    Q_PROPERTY(int stopAcceleration READ stopAcceleration WRITE setStopAcceleration NOTIFY stopAccelerationChanged)

    class PrivateData;
    QScopedPointer<PrivateData> d_data;

public:
    explicit QEmbRoboSettings(QObject *parent = 0);
    virtual ~QEmbRoboSettings();

    int maxAcceleration() const;
    void setMaxAcceleration(int arg);

    int minAcceleration() const;
    void setMinAcceleration(int arg);

    int maxVelocity() const;
    void setMaxVelocity(int arg);

    int startAcceleration() const;
    void setStartAcceleration(int arg);

    int stopAcceleration() const;
    void setStopAcceleration(int arg);

    void setJson(QJsonValue value);
    QJsonValue toJson() const;

signals:
    void maxAccelerationChanged(int);
    void minAccelerationChanged(int);
    void maxVelocityChanged(int);
    void startAccelerationChanged(int);
    void stopAccelerationChanged(int);

};

#endif // QEmbRoboSettings_H
