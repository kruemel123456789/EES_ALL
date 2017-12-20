#include <QGuiApplication>
#include <QtQuick>
#include <qjsonrpcclient.h>

#include <rpc/client.h>
#include <rpc/server.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    // Server/Clients fuer die Tests der AppControl-Gruppe
    Server *server_platform = new Server("Platform", 30002);
    Server *server_robot = new Server("Robot", 30003);



    // Clients, welche sich mit den Servern der Gruppen Plattform und Roboter verbinden
    Client *client_appcontrol_platform = new Client("AppControlPlatformClient", 30002);
    Client *client_appcontrol_robot = new Client("AppControlRobotClient", 30003);



    // Objekte fuer grafische Oberflaeche, vgl. EES-Vorlesung / QT Dokumentation
    QScopedPointer<QQmlApplicationEngine> engine(new QQmlApplicationEngine);
    engine->addImportPath(":/");
    engine->rootContext()->setContextProperty("server_platform", server_platform);

    engine->rootContext()->setContextProperty("server_robot", server_robot);

    engine->rootContext()->setContextProperty("client_appcontrol_platform", client_appcontrol_platform);
    engine->rootContext()->setContextProperty("client_appcontrol_robot", client_appcontrol_robot);

    engine->load(QUrl("qrc:/main.qml"));

    QObject *topLevel = engine->rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);



    // Verbinde Signale

    //   Fuer AppControl-Gruppe
    QObject::connect(window, SIGNAL(doPlatformServerToggle()),
                         server_platform, SLOT(toggle()));

    QObject::connect(window, SIGNAL(doPlatformFeedbackMove(int)),
                         server_platform, SLOT(sendPlatformFeedbackMove(int)));


    QObject::connect(window, SIGNAL(doRobotServerToggle()),
                         server_robot, SLOT(toggle()));

    QObject::connect(window, SIGNAL(doRobotFeedbackMove(int)),
                         server_robot, SLOT(sendRobotFeedbackMove(int)));




    //   Fuer Tests der Plattform-Gruppe
    QObject::connect(window, SIGNAL(doPlatformAppControlTestConnect(QString)),
                         client_appcontrol_platform, SLOT(connectToServer(QString)));

    QObject::connect(window, SIGNAL(doPlatformAppControlMoveRequest(int)),
                         client_appcontrol_platform, SLOT(sendPlatformMoveRequest(int)));

    //   Fuer Tests der Roboter-Gruppe
    QObject::connect(window, SIGNAL(doRobotAppControlTestConnect(QString)),
                         client_appcontrol_robot, SLOT(connectToServer(QString)));

    QObject::connect(window, SIGNAL(doRobotAppControlMoveRequest(int, int)),
                         client_appcontrol_robot, SLOT(sendRobotMoveRequest(int, int)));







    return app.exec();
}
