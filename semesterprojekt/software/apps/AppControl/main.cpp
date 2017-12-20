
#include <AppControlModules/logic.h>
#include "AppControlModules/rpc/client.h"
#include "AppControlModules/rpc/server.h"

#include <QtTest>
#include <QCoreApplication>

#include <QtConcurrent/QtConcurrent>

#include "libs/leds.h"



#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);



    Client *client_platform = new Client("Platform");
    client_platform->connect("ws://localhost:30002");

    Client *client_robot = new Client("Robot");
    client_robot->connect("ws://localhost:30003");


     LEDs *led = new LEDs();
     Logic *logic = new Logic();

     led->init(argc, argv);
     led->lightGlas(1,255,255,255);




    QObject::connect(client_platform,SIGNAL(received_platform_appcontrol_feedback_move(int)), logic, SLOT(received_platform_appcontrol_feedback_move(int)));
    QObject::connect(client_robot,SIGNAL(received_robot_appcontrol_feedback_move(int)), logic, SLOT(received_robot_appcontrol_feedback_move(int)));


    QObject::connect(client_platform,SIGNAL(connectedChanged(bool)), logic, SLOT(connection_to_platform_changed(bool)));
    QObject::connect(client_robot,SIGNAL(connectedChanged(bool)), logic, SLOT(connection_to_robot_changed(bool)));
    QObject::connect(logic, SIGNAL(appcontrol_platform_move(int)), client_platform, SLOT(send_appcontrol_platform_move(int)));
    QObject::connect(logic, SIGNAL(appcontrol_robot_move(int, int)), client_robot, SLOT(send_appcontrol_robot_move(int, int)));




    return a.exec();
}


