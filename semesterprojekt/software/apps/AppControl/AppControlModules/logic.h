#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <QStateMachine>
#include <AppControlModules/orderqueueconnector.h>


class Logic : public QObject
{
    Q_OBJECT

    bool connected_db = false;
    bool connected_platform = false;
    bool connected_robot = false;

    QStateMachine *machine;

    struct Cocktail {
        QString id = "";
        int userId = 0;
        int cocktailId = 0;
        bool iceRequired = false;
        int cocktail_state = 2;
    };

    OrderQueueConnector orderQueueConnector;

    Cocktail currentcocktail;

    int glasId = 0;



public:
    Logic(QObject *parent = 0);
    void componentConnected();
    void printStates();



public slots:
    void waitForComponents();
    void connection_to_platform_changed(bool connectionState);
    void connection_to_robot_changed(bool connectionState);
    void startFetchUpdates();
    void handle_order();
    void received_platform_appcontrol_feedback_move(int workstate);
    void received_robot_appcontrol_feedback_move(int workstate);

    void doFeedback_from_platform_ice();
    void doFeedback_from_robot_ice();
    void doFeedback_from_platform_bar();
    void doFeedback_from_robot_bar();
    void doFeedback_from_platform_user();
    void doFeedback_from_robot_user();
    void doFeedback_from_robot_user_done();

signals:
    void ordersReceived();
    void appcontrol_platform_move(int userId);
    void appcontrol_robot_move(int movementId, int glassId);


    void all_connected();
    void use_infos_from_order();
    void error_no_glases();
    void platform_ice_required();
    void received_feedback_platform();
    void platform_no_ice_required();
    void received_feedback_robot();


};

#endif // LOGIC_H
