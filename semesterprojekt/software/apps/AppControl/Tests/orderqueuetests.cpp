#include "orderqueuetests.h"
#define COUCHDB_HOST "78.47.115.243"
//#define COUCHDB_HOST "127.0.0.1:5984"

#define SERVER_PORT 20001


#include "AppControlModules/utils.h"
#include "AppControlModules/orderqueueconnector.h"

OrderQueueTests::OrderQueueTests() {

}


bool OrderQueueTests::doTests()
{
    Utils utils;

    qDebug() << "********* INIT ********";





    // ########## DATABASE CONECTION SETUP #########

    // Create database connector for managing order queue
    OrderQueueConnector orderQueueConnector;

    // Connect to the server
    bool connectionOK = orderQueueConnector.InitDBConnection(COUCHDB_HOST, "ees");

    if (connectionOK) {
        qDebug() << "[OrderQueue] Connection setup done";
    } else {
        qDebug() << "[OrderQueue] Could not connect to the database, please see the log for further details.";
        return false;
    }

    qDebug() << "********* INIT DONE ********";


    // ####### TEST OPERATIONS ON THE SERVER #####

    // Retrieve all orders in queue, will also show already finished items
    QJsonArray orders =  orderQueueConnector.getAllOrders();

    // Retrieve only open orders
    //QJsonArray orders =  orderQueueConnector.getOpenOrders();

    // Init database with dummy data, if no items have been found
    if (orders.size() == 0) {
        qDebug() << "[OrderQueue] Database seems empty, inserting some dummy data...";
        orderQueueConnector.InitDB();
        qDebug() << "[OrderQueue] Inserted dummy items, continuing...";
        orders =  orderQueueConnector.getAllOrders();
    }

    qDebug() << "********* TEST: OUTPUT COCKTAIL ORDER QUEUE ********";
    qDebug() << "[OrderQueue] Got the following orders:";

    foreach (const QJsonValue & v, orders) {
           // Get main JSON object
           QJsonObject doc = v.toObject();
           // Get sub-object
           QJsonObject docValues = doc.value("doc").toObject();

           qDebug() << "[OrderQueue] Cocktail" << docValues.value("cocktailId").toString() << "for user" << docValues.value("userId").toString() << "-" << utils.printOrderState(docValues.value("cocktailState").toInt());
    }



    // Retrieve further details about one specific order
    qDebug() << "********* TEST: GET STATUS OF ONE SPECIFIC ORDER ********";
    QJsonObject testOrder = orderQueueConnector.getOrder("a3571c1d164dfd047d4f674b67006528");
    qDebug() << "[OrderQueue] Status of order" << testOrder.value("_id").toString() << ":" << utils.printOrderState(testOrder.value("cocktailState").toInt());



    // Change the state of an order to "processing" (cocktailState = 1)
    qDebug() << "********* TEST: UPDATE STATUS OF AN ORDER ********";
    bool updateOrderOK = orderQueueConnector.updateOrderState("a3571c1d164dfd047d4f674b67006528", 1);
    if (updateOrderOK) {
        qDebug() << "[OrderQueue] Status updated";
    } else {
        qDebug() << "[OrderQueue] Status updated";
    }



    return true;

}
