#ifndef QEMBROBO_H
#define QEMBROBO_H

#include <QtCore>

class QEmbRoboStepper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int stepperNumber READ stepperNumber WRITE setStepperNumber NOTIFY stepperNumberChanged)
    Q_PROPERTY(bool enable READ isEnable WRITE storeEnable NOTIFY enableChanged)
    Q_PROPERTY(int frequency READ frequency NOTIFY frequencyChanged)
    Q_PROPERTY(int targetFrequency READ targetFrequency WRITE storeTargetFrequency NOTIFY targetFrequencyChanged)
    Q_PROPERTY(int acceleration READ acceleration WRITE storeAcceleration NOTIFY accelerationChanged)
    Q_PROPERTY(bool fault READ hasFault NOTIFY faultChanged)

    class PrivateData;
    QScopedPointer<PrivateData> d_data;

public:
    explicit QEmbRoboStepper(QObject *parent = 0);
    virtual ~QEmbRoboStepper();

    int stepperNumber() const;
    void setStepperNumber(int arg);

    bool isEnable() const;
    void setEnable(bool arg);

    int frequency() const;
    void setFrequency(int arg);

    int targetFrequency() const;
    void setTargetFrequency(int arg);

    int acceleration() const;
    void setAcceleration(int arg);

    bool hasFault() const;
    void setFault(bool arg);

    //the store functions sending only a store request, they do not set the values
    void storeEnable(bool arg);
    void storeTargetFrequency(int arg);
    void storeAcceleration(int arg);

    Q_INVOKABLE void resetWatchdog() const;

    void setJson(QJsonValue value);
    QJsonValue toJson() const;

signals:
    void stepperChanged();

    void stepperNumberChanged(int);
    void enableChanged(bool);
    void frequencyChanged(int);
    void targetFrequencyChanged(int);
    void accelerationChanged(int);
    void faultChanged(bool);

    void enableStoreRequest(bool);
    void targetFrequencyStoreRequest(int);
    void accelerationStoreRequest(int);
};

#endif // QEMBROBO_H
