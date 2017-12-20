#include "qembrobostepper.h"
#include <QtWebSockets>

static int getProcValue(const QString &filename)
{
    QFile procFile(filename);
    if(!procFile.open(QFile::ReadOnly)) {
        qWarning() << "Unable to open proc file" << filename << "for reading.";
        return 0;
    }

    return procFile.readAll().simplified().toInt();
}

static void setProcValue(const QString &filename, int value)
{
    QFile procFile(filename);
    if(!procFile.open(QFile::WriteOnly)) {
        qWarning() << "Unable to open proc file" << filename << "for writing.";
        return;
    }

    procFile.write(QString::number(value).toLocal8Bit());
}

class QEmbRoboStepper::PrivateData
{
public:
    bool procEntryExists;
    QFile procFile;
    QString basePath;
    int stepperNumber;
    bool enable;
    int frequency;
    int targetFrequency;
    int acceleration;
    bool fault;

    QTimer readTimer;
};

QEmbRoboStepper::QEmbRoboStepper(QObject *parent) : QObject(parent)
  ,d_data(new PrivateData)
{
    d_data->procEntryExists = QFileInfo("/proc/sys/embrobo").exists();
    d_data->stepperNumber = -1;
    d_data->enable = false;
    d_data->frequency = 0;
    d_data->targetFrequency = 0;
    d_data->acceleration = 10000;
    d_data->fault = false;

    //convinence merged changed signal
    QObject::connect(this, &QEmbRoboStepper::stepperNumberChanged, this, &QEmbRoboStepper::stepperChanged);
    QObject::connect(this, &QEmbRoboStepper::enableChanged, this, &QEmbRoboStepper::stepperChanged);
    QObject::connect(this, &QEmbRoboStepper::frequencyChanged, this, &QEmbRoboStepper::stepperChanged);
    QObject::connect(this, &QEmbRoboStepper::targetFrequencyChanged, this, &QEmbRoboStepper::stepperChanged);
    QObject::connect(this, &QEmbRoboStepper::accelerationChanged, this, &QEmbRoboStepper::stepperChanged);
    QObject::connect(this, &QEmbRoboStepper::faultChanged, this, &QEmbRoboStepper::stepperChanged);

    //read values from proc filesystem (polling)
    QObject::connect(&d_data->readTimer, &QTimer::timeout, [this]() {
        if(!QFileInfo(d_data->basePath).exists()) return;

        setEnable(getProcValue(d_data->basePath + "/enable"));
        setTargetFrequency(getProcValue(d_data->basePath + "/targetFrequency"));
        setFrequency(getProcValue(d_data->basePath + "/currentFrequency"));
        setAcceleration(getProcValue(d_data->basePath + "/acceleration"));
        setFault(getProcValue(d_data->basePath + "/fault"));
    });
    d_data->readTimer.start(10);
}

QEmbRoboStepper::~QEmbRoboStepper()
{

}

int QEmbRoboStepper::stepperNumber() const
{
    return d_data->stepperNumber;
}

void QEmbRoboStepper::setStepperNumber(int arg)
{
    if (d_data->stepperNumber == arg)
        return;

    d_data->stepperNumber = arg;
    d_data->basePath = QString("/proc/sys/embrobo/stepper%1").arg(arg);
    emit stepperNumberChanged(arg);
}

bool QEmbRoboStepper::isEnable() const
{
    return d_data->enable;
}

void QEmbRoboStepper::setEnable(bool arg)
{
    if (d_data->enable == arg)
        return;

    d_data->enable = arg;
    emit enableChanged(arg);
}

int QEmbRoboStepper::frequency() const
{
    return d_data->frequency;
}

void QEmbRoboStepper::setFrequency(int arg)
{
    if (d_data->frequency == arg)
        return;

    d_data->frequency = arg;
    emit frequencyChanged(arg);
}

int QEmbRoboStepper::targetFrequency() const
{
    return d_data->targetFrequency;
}

void QEmbRoboStepper::setTargetFrequency(int arg)
{
    if (d_data->targetFrequency == arg)
        return;

    d_data->targetFrequency = arg;
    emit targetFrequencyChanged(arg);
}

int QEmbRoboStepper::acceleration() const
{
    return d_data->acceleration;
}

void QEmbRoboStepper::setAcceleration(int arg)
{
    if (d_data->acceleration == arg)
        return;

    d_data->acceleration = arg;
    emit accelerationChanged(arg);
}

bool QEmbRoboStepper::hasFault() const
{
    return d_data->fault;
}

void QEmbRoboStepper::setFault(bool arg)
{
    if (d_data->fault == arg)
        return;

    d_data->fault = arg;
    emit faultChanged(arg);
}

void QEmbRoboStepper::storeEnable(bool arg)
{
    if(d_data->enable == arg) return;

    if(d_data->procEntryExists)
        setProcValue(d_data->basePath + "/enable", arg);

    emit enableStoreRequest(arg);
}

void QEmbRoboStepper::storeTargetFrequency(int arg)
{
    if(d_data->targetFrequency == arg) return;

    if(d_data->procEntryExists)
        setProcValue(d_data->basePath + "/targetFrequency", arg);

    emit targetFrequencyStoreRequest(arg);
}

void QEmbRoboStepper::storeAcceleration(int arg)
{
    if(d_data->acceleration == arg) return;

    if(d_data->procEntryExists)
        setProcValue(d_data->basePath + "/acceleration", arg);

    emit accelerationStoreRequest(arg);
}

void QEmbRoboStepper::resetWatchdog() const
{
    //reset only if already enabled
    setProcValue(d_data->basePath + "/enable", getProcValue(d_data->basePath + "/enable"));
}

void QEmbRoboStepper::setJson(QJsonValue value)
{
    QJsonObject stepperObject = value.toObject();
    if(stepperObject.isEmpty()) return;
    if(stepperObject.value("stepperNumber").toInt(-1) != d_data->stepperNumber) return;

    setEnable(stepperObject.value("enable").toBool(d_data->enable));
    setTargetFrequency(stepperObject.value("targetFrequency").toInt(d_data->targetFrequency));
    setFrequency(stepperObject.value("frequency").toInt(d_data->frequency));
    setAcceleration(stepperObject.value("acceleration").toInt(d_data->acceleration));
    setFault(stepperObject.value("fault").toBool(d_data->fault));
}

QJsonValue QEmbRoboStepper::toJson() const
{
    QJsonObject stepperObject;
    stepperObject.insert("stepperNumber", d_data->stepperNumber);
    stepperObject.insert("enable", d_data->enable);
    stepperObject.insert("frequency", d_data->frequency);
    stepperObject.insert("targetFrequency", d_data->targetFrequency);
    stepperObject.insert("acceleration", d_data->acceleration);
    stepperObject.insert("fault", d_data->fault);
    return stepperObject;
}

