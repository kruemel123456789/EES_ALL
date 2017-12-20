#ifndef QEMBROBOHAL_H
#define QEMBROBOHAL_H

#include <QtCore>

class QEmbRoboHAL : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal channel0 READ channel0 WRITE setChannel0 NOTIFY channel0Changed)
    Q_PROPERTY(qreal channel1 READ channel1 WRITE setChannel1 NOTIFY channel1Changed)
    Q_PROPERTY(qreal channel2 READ channel2 WRITE setChannel2 NOTIFY channel2Changed)

    Q_PROPERTY(qreal output0 READ output0 NOTIFY outputsChanged)
    Q_PROPERTY(qreal output1 READ output1 NOTIFY outputsChanged)
    Q_PROPERTY(qreal output2 READ output2 NOTIFY outputsChanged)
    Q_PROPERTY(qreal output3 READ output3 NOTIFY outputsChanged)

    Q_PROPERTY(qreal maxOutput READ maxOutput WRITE setMaxOutput NOTIFY maxOutputChanged)

    class PrivateData;
    QScopedPointer<PrivateData> d_data;

    qreal outputTransferFunction0(qreal channel0, qreal channel1, qreal channel2);
    qreal outputTransferFunction1(qreal channel0, qreal channel1, qreal channel2);
    qreal outputTransferFunction2(qreal channel0, qreal channel1, qreal channel2);
    qreal outputTransferFunction3(qreal channel0, qreal channel1, qreal channel2);

public:
    explicit QEmbRoboHAL(QObject *parent = 0);
    virtual ~QEmbRoboHAL();

    qreal channel0() const;
    void setChannel0(qreal arg);

    qreal channel1() const;
    void setChannel1(qreal arg);

    qreal channel2() const;
    void setChannel2(qreal arg);

    qreal output0() const;
    qreal output1() const;
    qreal output2() const;
    qreal output3() const;

    qreal maxOutput() const;
    void setMaxOutput(qreal arg);

    void setJson(QJsonValue value);
    QJsonValue toJson() const;

public slots:
    void updateOutputs();

signals:
    void channel0Changed(qreal channel0);
    void channel1Changed(qreal channel1);
    void channel2Changed(qreal channel2);
    void channelsChanged();
    void outputsChanged();

    void maxOutputChanged(qreal maxOutput);
};

#endif // QEMBROBOHAL_H
