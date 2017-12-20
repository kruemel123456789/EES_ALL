#ifndef ORDERQUEUETESTS_H
#define ORDERQUEUETESTS_H

#include <QObject>

class OrderQueueTests : public QObject
{
    Q_OBJECT
public:
    OrderQueueTests();

public slots:
    bool doTests();
};

#endif // ORDERQUEUETESTS_H
