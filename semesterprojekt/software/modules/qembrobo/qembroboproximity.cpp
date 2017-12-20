#include "qembroboproximity.h"

static int getProcValue(const QString &filename)
{
    if(!QFileInfo(filename).exists()) return 0;

    QFile procFile(filename);
    if(!procFile.open(QFile::ReadOnly)) {
        qWarning() << "Unable to open proc file" << filename << "for reading.";
        return 0;
    }

    return procFile.readAll().simplified().toInt();
}

class QEmbRoboProximity::PrivateData
{
public:
    QString basePath;
    int triggeredSensors;

    QTimer readTimer;
};

QEmbRoboProximity::QEmbRoboProximity(QObject *parent) : QObject(parent)
  ,d_data(new PrivateData())
{
    d_data->triggeredSensors = 0x00;
    d_data->basePath = "/proc/sys/embrobo/proximity";

    //read values from proc filesystem (polling)
    QObject::connect(&d_data->readTimer, &QTimer::timeout, [this]() {
        if(!QFileInfo(d_data->basePath).exists()) return;

        setTriggeredSensor(getProcValue(d_data->basePath));
    });
    d_data->readTimer.start(10);
}

QEmbRoboProximity::~QEmbRoboProximity()
{

}

int QEmbRoboProximity::triggeredSensor() const
{
    return d_data->triggeredSensors;
}

void QEmbRoboProximity::setTriggeredSensor(int arg)
{
    if(d_data->triggeredSensors == arg) return;

    d_data->triggeredSensors = arg;
    emit triggeredSensorChanged(arg);
}

bool QEmbRoboProximity::front() const
{
    return d_data->triggeredSensors & QEmbRoboProximity::ProximityFront;
}

bool QEmbRoboProximity::back() const
{
    return d_data->triggeredSensors & QEmbRoboProximity::ProximityBack;
}

bool QEmbRoboProximity::left() const
{
    return d_data->triggeredSensors & QEmbRoboProximity::ProximityLeft;
}

bool QEmbRoboProximity::right() const
{
    return d_data->triggeredSensors & QEmbRoboProximity::ProximityRight;
}

void QEmbRoboProximity::setJson(QJsonValue value)
{
    QJsonObject proximityObject = value.toObject();
    if(proximityObject.isEmpty()) return;

    setTriggeredSensor(proximityObject.value("triggeredSensors").toInt(d_data->triggeredSensors));
}

QJsonValue QEmbRoboProximity::toJson() const
{
    QJsonObject proximityObject;
    proximityObject.insert("triggeredSensors", d_data->triggeredSensors);
    return proximityObject;
}

