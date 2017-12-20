#include "logic.h"
#include <QObject>
#include <QDebug>
#include <QStateMachine>


#define COUCHDB_HOST "78.47.115.243"
//#define COUCHDB_HOST "127.0.0.1:5984"


QJsonArray orders;


Logic::Logic(QObject *parent)
    : QObject(parent)
{
        connected_db = orderQueueConnector.InitDBConnection(COUCHDB_HOST, "ees");


        if (connected_db) {
            qDebug() << "[OrderQueue] Connection setup done";
        } else {
            qDebug() << "[OrderQueue] Could not connect to the database, please see the log for further details.";
            return;
        }

        machine = new QStateMachine();
                QState *sWait_for_all_components = new QState();
                QState *sGet_orders = new QState();
                QState *sHandle_order = new QState();
                QState *sNo_glasses = new QState();
                QState *sFeedback_from_platform_ice = new QState();
                QState *sFeedback_from_robot_ice = new QState();
                QState *sFeedback_from_platform_bar = new QState();
                QState *sFeedback_from_robot_bar = new QState();
                QState *sFeedback_from_platform_user = new QState();
                QState *sFeedback_from_robot_user = new QState();


                sWait_for_all_components->addTransition(this, SIGNAL(all_connected()), sGet_orders);
                sGet_orders->addTransition(this, SIGNAL(use_infos_from_order()), sHandle_order);
                sHandle_order->addTransition(this, SIGNAL(error_no_glases()), sNo_glasses);
                sHandle_order->addTransition(this, SIGNAL(platform_ice_required()), sFeedback_from_platform_ice);
                sHandle_order->addTransition(this, SIGNAL(platform_no_ice_required()), sFeedback_from_platform_bar);
                sFeedback_from_platform_ice->addTransition(this, SIGNAL(received_feedback_platform()), sFeedback_from_robot_ice);
                sFeedback_from_robot_ice->addTransition(this, SIGNAL(received_feedback_robot()), sFeedback_from_platform_bar);
                sFeedback_from_platform_bar->addTransition(this, SIGNAL(received_feedback_platform()), sFeedback_from_robot_bar);
                sFeedback_from_robot_bar->addTransition(this, SIGNAL(received_feedback_robot()), sFeedback_from_platform_user);
                sFeedback_from_platform_user->addTransition(this, SIGNAL(received_feedback_platform()), sFeedback_from_robot_user);
                sFeedback_from_robot_user->addTransition(this, SIGNAL(received_feedback_robot()), sGet_orders);



                QObject::connect(sWait_for_all_components, SIGNAL(entered()), this, SLOT(waitForComponents()));
                QObject::connect(sGet_orders, SIGNAL(entered()), this, SLOT(startFetchUpdates()));
                QObject::connect(sHandle_order, SIGNAL(entered()), this, SLOT(handle_order()));
                QObject::connect(sFeedback_from_platform_ice, SIGNAL(entered()), this, SLOT(doFeedback_from_platform_ice()));
                QObject::connect(sFeedback_from_robot_ice, SIGNAL(entered()), this, SLOT(doFeedback_from_robot_ice()));
                QObject::connect(sFeedback_from_platform_bar, SIGNAL(entered()), this, SLOT(doFeedback_from_platform_bar()));
                QObject::connect(sFeedback_from_robot_bar, SIGNAL(entered()), this, SLOT(doFeedback_from_robot_bar()));
                QObject::connect(sFeedback_from_platform_user, SIGNAL(entered()), this, SLOT(doFeedback_from_platform_user()));
                QObject::connect(sFeedback_from_robot_user, SIGNAL(entered()), this, SLOT(doFeedback_from_robot_user()));


                QObject::connect(sFeedback_from_robot_user, SIGNAL(exited()), this, SLOT(doFeedback_from_robot_user_done()));








                machine->addState(sWait_for_all_components);
                machine->addState(sGet_orders);
                machine->addState(sHandle_order);
                machine->addState(sNo_glasses);
                machine->addState(sFeedback_from_platform_ice);
                machine->addState(sFeedback_from_robot_ice);
                machine->addState(sFeedback_from_platform_bar);
                machine->addState(sFeedback_from_robot_bar);
                machine->addState(sFeedback_from_platform_user);
                machine->addState(sFeedback_from_robot_user);
                machine->setInitialState(sWait_for_all_components);
                machine->start();




}



void Logic::waitForComponents() {
    qDebug() << "[Logic] Waiting for components";
}

void Logic::printStates() {
            //qDebug() << "[Logic] Active State:" << machine.activeStateNames(true).at(0);
}

void Logic::handle_order() {
    QJsonObject item_order = orders[0].toObject();
    QJsonObject item_order_doc = item_order.value("doc").toObject();

    currentcocktail.id = item_order_doc.value("_id").toString();
    currentcocktail.cocktailId = item_order_doc.value("cocktailId").toInt();
    currentcocktail.iceRequired = item_order_doc.value("iceRequired").toBool();
    currentcocktail.userId = item_order_doc.value("userId").toInt();

   qDebug().nospace() << "[Logic] Handling order " << currentcocktail.id << " (Cocktail " << currentcocktail.cocktailId << ") to glass " << glasId;
    if (glasId==4) {
        emit error_no_glases();
    }else{
        qDebug() << "[Logic] Cocktail needs" << (!currentcocktail.iceRequired ? "no" : "") << "ice";
        if (currentcocktail.iceRequired){
            emit platform_ice_required();
        }
        else {
            emit platform_no_ice_required();
        }

        orderQueueConnector.updateOrderState(currentcocktail.id, 1);
    }
}

void Logic::connection_to_platform_changed(bool connectionState) {
    if (connectionState) {
        qDebug() << "[PlatformClient] Connected to Platform";
        this->connected_platform = true;
        componentConnected();
    } else {
        this->connected_platform = false;
        qDebug() << "[PlatformClient] Disconnected from Platform";
    }

}

void Logic::connection_to_robot_changed(bool connectionState) {
    if (connectionState) {
        qDebug() << "[RobotClient] Connected to Robot";
        this->connected_robot = true;
        componentConnected();
    } else {
        this->connected_robot = false;
        qDebug() << "[RobotClient] Disconnected from Robot";
    }

}

// Checks if all components are connected
void Logic::componentConnected() {
    qDebug() << "[Logic] Connected components:" << (this->connected_platform ? "Platform" : "") << (this->connected_robot ? "Robot" : "");
    if (this->connected_platform && this->connected_robot) {
        emit all_connected();
    }
}


void Logic::received_platform_appcontrol_feedback_move(int workstate) {

    qDebug() << "[PlatformClient] Received feedback from platform:" << workstate;

    if (workstate == 0) {
       emit received_feedback_platform();
    }
}

void Logic::received_robot_appcontrol_feedback_move(int workstate) {
    qDebug() << "[RobotClient] Feedback from robot:" << workstate;



    if (workstate == 0) {
            emit received_feedback_robot();
    }
}


void Logic::startFetchUpdates() {
    qDebug() << "[Logic] Fetching open cocktail orders...";


    int openOrders = 0;

    while (openOrders == 0) {
        orders =  orderQueueConnector.getOpenOrders();
        openOrders = orders.size();


        // Init database with dummy data, if no items have been found
        if (orders.size() > 0) {
            qDebug() << "[Logic] Found" << openOrders << "open orders";
            emit use_infos_from_order();
            break;
        } else {
            qDebug() << "[Logic] No open cocktail orders";
        }
        QThread::sleep(1);
    }
}

void Logic::doFeedback_from_platform_ice() {
    printStates();
    qDebug() << "[Logic] Requesting platform to move to the ice dispenser";
    emit appcontrol_platform_move(65531);
    qDebug() << "[Logic] Waiting for feedback from platform";
}

void Logic::doFeedback_from_robot_ice() {
    printStates();
    qDebug() << "[Logic] Requesting robot to collect ice for glass" << glasId;
    emit appcontrol_robot_move(251, glasId);
    qDebug() << "[Logic] Waiting for feedback from robot";
}

void Logic::doFeedback_from_platform_bar() {
    printStates();
    qDebug() << "[Logic] Requesting platform to move to the bar";
    emit appcontrol_platform_move(65532);
    qDebug() << "[Logic] Waiting for feedback from platform";
}

void Logic::doFeedback_from_robot_bar() {
    printStates();
    qDebug() << "[Logic] Requesting robot to mix cocktail" << currentcocktail.cocktailId << "in glass" << glasId;
    emit appcontrol_robot_move(currentcocktail.cocktailId, glasId);
    qDebug() << "[Logic] Waiting for feedback from robot";
}


void Logic::doFeedback_from_platform_user() {
    printStates();
    qDebug() << "[Logic] Requesting platform to move to user" << currentcocktail.userId;
    emit appcontrol_platform_move(currentcocktail.userId);
    qDebug() << "[Logic] Waiting for feedback from platform";
}

void Logic::doFeedback_from_robot_user() {
    printStates();
    qDebug() << "[Logic] Requesting robot to serve the cocktail in glas" << glasId;
    emit appcontrol_robot_move(253, glasId);
    qDebug() << "[Logic] Waiting for feedback from robot";


}

void Logic::doFeedback_from_robot_user_done() {
    printStates();
    orderQueueConnector.updateOrderState(currentcocktail.id, 2);
    glasId=glasId+1;



}

