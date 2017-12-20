#include "qembrobohal.h"

class QEmbRoboHAL::PrivateData
{
public:
    qreal channel0;
    qreal channel1;
    qreal channel2;
    qreal output0;
    qreal output1;
    qreal output2;
    qreal output3;
    qreal maxOutput;
};

qreal QEmbRoboHAL::outputTransferFunction0(qreal channel0, qreal channel1, qreal channel2)
{
    return (channel0 + channel1 - channel2);
}

qreal QEmbRoboHAL::outputTransferFunction1(qreal channel0, qreal channel1, qreal channel2)
{
    return (channel0 - channel1 - channel2);
}

qreal QEmbRoboHAL::outputTransferFunction2(qreal channel0, qreal channel1, qreal channel2)
{
    return (channel0 + channel1 + channel2);
}

qreal QEmbRoboHAL::outputTransferFunction3(qreal channel0, qreal channel1, qreal channel2)
{
    return (channel0 - channel1 + channel2);
}

QEmbRoboHAL::QEmbRoboHAL(QObject *parent) : QObject(parent)
  ,d_data(new PrivateData())
{
    d_data->channel0 = 0;
    d_data->channel1 = 0;
    d_data->channel2 = 0;
    d_data->output0 = 0;
    d_data->output1 = 0;
    d_data->output2 = 0;
    d_data->output3 = 0;
    d_data->maxOutput = 15000;

    QObject::connect(this, &QEmbRoboHAL::maxOutputChanged, this, &QEmbRoboHAL::updateOutputs);
    QObject::connect(this, &QEmbRoboHAL::channel0Changed, this, &QEmbRoboHAL::updateOutputs);
    QObject::connect(this, &QEmbRoboHAL::channel1Changed, this, &QEmbRoboHAL::updateOutputs);
    QObject::connect(this, &QEmbRoboHAL::channel2Changed, this, &QEmbRoboHAL::updateOutputs);

    QObject::connect(this, &QEmbRoboHAL::channel0Changed, this, &QEmbRoboHAL::channelsChanged);
    QObject::connect(this, &QEmbRoboHAL::channel1Changed, this, &QEmbRoboHAL::channelsChanged);
    QObject::connect(this, &QEmbRoboHAL::channel2Changed, this, &QEmbRoboHAL::channelsChanged);
}

QEmbRoboHAL::~QEmbRoboHAL()
{

}

qreal QEmbRoboHAL::channel0() const
{
    return d_data->channel0;
}

void QEmbRoboHAL::setChannel0(qreal arg)
{
    if (qFuzzyCompare(d_data->channel0, arg))
        return;

    d_data->channel0 = arg;
    emit channel0Changed(arg);
}

qreal QEmbRoboHAL::channel1() const
{
    return d_data->channel1;
}

void QEmbRoboHAL::setChannel1(qreal arg)
{
    if (qFuzzyCompare(d_data->channel1, arg))
        return;

    d_data->channel1 = arg;
    emit channel1Changed(arg);
}

qreal QEmbRoboHAL::channel2() const
{
    return d_data->channel2;
}

void QEmbRoboHAL::setChannel2(qreal arg)
{
    if (qFuzzyCompare(d_data->channel2, arg))
        return;

    d_data->channel2 = arg;
    emit channel2Changed(arg);
}

qreal QEmbRoboHAL::output0() const
{
    return d_data->output0;
}

qreal QEmbRoboHAL::output1() const
{
    return d_data->output1;
}

qreal QEmbRoboHAL::output2() const
{
    return d_data->output2;
}

qreal QEmbRoboHAL::output3() const
{
    return d_data->output3;
}

qreal QEmbRoboHAL::maxOutput() const
{
    return d_data->maxOutput;
}

void QEmbRoboHAL::setMaxOutput(qreal arg)
{
    if (qFuzzyCompare(d_data->maxOutput, arg))
        return;

    d_data->maxOutput = arg;
    emit maxOutputChanged(arg);
}

void QEmbRoboHAL::setJson(QJsonValue value)
{
    QJsonObject halObject = value.toObject();
    if(halObject.isEmpty()) return;

    setChannel0(halObject.value("channel0").toDouble(d_data->channel0));
    setChannel1(halObject.value("channel1").toDouble(d_data->channel1));
    setChannel2(halObject.value("channel2").toDouble(d_data->channel2));
    setMaxOutput(halObject.value("maxOutput").toDouble(d_data->maxOutput));
}

QJsonValue QEmbRoboHAL::toJson() const
{
    QJsonObject halObject;
    halObject.insert("channel0", d_data->channel0);
    halObject.insert("channel1", d_data->channel1);
    halObject.insert("channel2", d_data->channel2);
    halObject.insert("maxOutput", d_data->maxOutput);
    return halObject;
}

void QEmbRoboHAL::updateOutputs()
{
    const qreal unscaledOutput0 = outputTransferFunction0(d_data->channel0, d_data->channel1, d_data->channel2);
    const qreal unscaledOutput1 = outputTransferFunction1(d_data->channel0, d_data->channel1, d_data->channel2);
    const qreal unscaledOutput2 = outputTransferFunction2(d_data->channel0, d_data->channel1, d_data->channel2);
    const qreal unscaledOutput3 = outputTransferFunction3(d_data->channel0, d_data->channel1, d_data->channel2);

    const qreal normalizingFactor = ( 1.0 / std::max(unscaledOutput0, std::max(unscaledOutput1, std::max(unscaledOutput2, std::max(unscaledOutput3, 1.0)))) );

    d_data->output0 = (unscaledOutput0*normalizingFactor)*d_data->maxOutput;
    d_data->output1 = (unscaledOutput1*normalizingFactor)*d_data->maxOutput;
    d_data->output2 = (unscaledOutput2*normalizingFactor)*d_data->maxOutput;
    d_data->output3 = (unscaledOutput3*normalizingFactor)*d_data->maxOutput;

    emit outputsChanged();
}
