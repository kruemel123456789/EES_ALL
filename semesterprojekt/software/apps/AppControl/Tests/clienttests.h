#ifndef CLIENTTESTS_H
#define CLIENTTESTS_H

#include <QtNetwork>

class ClientTests : public QTcpSocket
{
    Q_OBJECT
public:
    ClientTests(QObject *parent = 0);

public slots:
    bool doTests2();
    bool SendTest();
    void readData();
};

#endif // CLIENTTESTS_H
