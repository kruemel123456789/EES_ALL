#include "qembrobosettings.h"

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

class QEmbRoboSettings::PrivateData
{
public:
    QString basePath;
    int maxAcceleration;
    int minAcceleration;
    int maxVelocity;
    int startAcceleration;
    int stopAcceleration;

    QTimer readTimer;
};

QEmbRoboSettings::QEmbRoboSettings(QObject *parent) : QObject(parent)
  ,d_data(new PrivateData())
{
    d_data->basePath = "/proc/sys/embrobo/";
    d_data->maxAcceleration = 10000;
    d_data->minAcceleration =  1000;
    d_data->maxVelocity = 50000;
    d_data->startAcceleration = 8000;
    d_data->stopAcceleration = 60000;
}

QEmbRoboSettings::~QEmbRoboSettings()
{

}

int QEmbRoboSettings::maxAcceleration() const
{
    return d_data->maxAcceleration;
}

void QEmbRoboSettings::setMaxAcceleration(int arg)
{
    if (d_data->maxAcceleration == arg)
        return;

    d_data->maxAcceleration = arg;
    emit maxAccelerationChanged(arg);
}

int QEmbRoboSettings::minAcceleration() const
{
    return d_data->minAcceleration;
}

void QEmbRoboSettings::setMinAcceleration(int arg)
{
    if (d_data->minAcceleration == arg)
        return;

    d_data->minAcceleration = arg;
    emit minAccelerationChanged(arg);
}

int QEmbRoboSettings::maxVelocity() const
{
    return d_data->maxVelocity;
}

void QEmbRoboSettings::setMaxVelocity(int arg)
{
    if (d_data->maxVelocity == arg)
        return;

    d_data->maxVelocity = arg;
    emit maxVelocityChanged(arg);
}

int QEmbRoboSettings::startAcceleration() const
{
    return d_data->startAcceleration;
}

void QEmbRoboSettings::setStartAcceleration(int arg)
{
    if (d_data->startAcceleration == arg)
        return;

    d_data->startAcceleration = arg;
    emit startAccelerationChanged(arg);
}

int QEmbRoboSettings::stopAcceleration() const
{
    return d_data->stopAcceleration;
}

void QEmbRoboSettings::setStopAcceleration(int arg)
{
    if (d_data->stopAcceleration == arg)
        return;

    d_data->stopAcceleration = arg;
    emit stopAccelerationChanged(arg);
}

void QEmbRoboSettings::setJson(QJsonValue value)
{
    QJsonObject object = value.toObject();
    if(object.isEmpty()) return;

    setMaxAcceleration(object.value("maxAcceleration").toDouble(d_data->maxAcceleration));
    setMinAcceleration(object.value("minAcceleration").toDouble(d_data->minAcceleration));
    setMaxVelocity(object.value("maxVelocity").toDouble(d_data->maxVelocity));
    setStartAcceleration(object.value("startAcceleration").toDouble(d_data->startAcceleration));
    setStopAcceleration(object.value("stopAcceleration").toDouble(d_data->stopAcceleration));
}

QJsonValue QEmbRoboSettings::toJson() const
{
    QJsonObject object;
    object.insert("maxAcceleration", d_data->maxAcceleration);
    object.insert("minAcceleration", d_data->minAcceleration);
    object.insert("maxVelocity", d_data->maxVelocity);
    object.insert("startAcceleration", d_data->startAcceleration);
    object.insert("stopAcceleration", d_data->stopAcceleration);
    return object;
}
