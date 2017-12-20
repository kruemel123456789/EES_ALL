#include "clienttests.h"

#include <QtNetwork>

QTcpSocket *tcpSocket2;
QDataStream in;

ClientTests::ClientTests(QObject *parent)
    : QTcpSocket(parent)
{
    tcpSocket2 = new QTcpSocket;
}

bool ClientTests::doTests2()
{

    qDebug() << "[Client] Connecting...";

    in.setDevice(tcpSocket2);
        in.setVersion(QDataStream::Qt_4_0);

    connect(tcpSocket2, SIGNAL(readyRead()), this, SLOT(readData()));



    tcpSocket2->abort();
        tcpSocket2->connectToHost("127.0.0.1", 20001);

qDebug() << "[Client] connected";


    return true;
}


void ClientTests::readData()
{


    qDebug() << "[Client] Received:" << tcpSocket2->readAll();
    tcpSocket2->write("TestData");
    tcpSocket2->flush();

        return;



}

bool ClientTests::SendTest() {
    qDebug() << "Sending";
    tcpSocket2->write("TestData");
    tcpSocket2->flush();
    return true;
}
