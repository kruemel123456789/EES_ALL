#include <QString>
#include <QtTest>
#include "../AppControl/AppControlModules/utils.h"
#include "../AppControl/AppControlModules/orderqueueconnector.h"
#include <QtDebug>


#define COUCHDB_HOST "78.47.115.243"
//#define COUCHDB_HOST "127.0.0.1:5984"
#define COUCHDB_DBNAME "ees"
#define SERVER_PORT 20001

class AppControlTest : public QObject
{
    Q_OBJECT

public:
    AppControlTest();

private Q_SLOTS:
//    void testCase1();

    //Testing
    //  Class Utils
    void utilsPrintOrderStateOpen();
    void utilsPrintOrderStateProcessing();
    void utilsPrintOrderStateDone();

    //  Class OrderQueue Connector
    void orderQueueConnectorInitDBConnection();
//    void orderQueueConnectorInitDB();
    void orderQueueConnectorGetAllOrders();
    void orderQueueConnectorGetOpenOrders();
    void orderQueueConnectorGetOrder();
//    void updateOrderState();

};

AppControlTest::AppControlTest()
{
}

//void AppControlTest::testCase1()
//{
//    QVERIFY2(true, "Failure");
//}


//class: Utils

void AppControlTest::utilsPrintOrderStateOpen(){
    //creating object for test
    Utils utilsObj;
    QString returnValue = utilsObj.printOrderState(0);
    QVERIFY(returnValue.compare("open") == 0);
}

void AppControlTest::utilsPrintOrderStateProcessing(){
    //creating object for test
    Utils utilsObj;
    QString returnValue = utilsObj.printOrderState(1);
    QVERIFY(returnValue.compare("processing") == 0);
}

void AppControlTest::utilsPrintOrderStateDone(){
    //creating object for test
    Utils utilsObj;
    QString returnValue = utilsObj.printOrderState(2);

    QVERIFY(returnValue.compare("done") == 0);
}

//class: OrderQueueConnector

void AppControlTest::orderQueueConnectorInitDBConnection(){
    //creating object for test
    OrderQueueConnector connectorObj;

    bool returnValue = connectorObj.InitDBConnection(COUCHDB_HOST, COUCHDB_DBNAME);
    QVERIFY(returnValue);
}

//void AppControlTest::orderQueueConnectorInitDB(){
//    //Creating the DB for test
//    OrderQueueConnector connectorObj;
//    bool connectionOK = connectorObj.InitDBConnection(COUCHDB_HOST, COUCHDB_DBNAME);

//    //if the DB was not correctly created, abort test
//    if(!connectionOK) {
//        qDebug() << "connectionOK is false!";
//        QVERIFY(false);
//    }

//    //trying to input values to the DB
//    //int returnValue = connectorObj.InitDB();

//    QVERIFY(connectionOK);
//}

void AppControlTest::orderQueueConnectorGetAllOrders(){
    //creating object for test
    OrderQueueConnector connectorObj;
    //CouchDB items should be saved in this JSON array
    QJsonArray orders;

    bool returnValue = connectorObj.InitDBConnection(COUCHDB_HOST, COUCHDB_DBNAME);

    if(!returnValue) {
        qDebug() << "Connections is not done!";
        QVERIFY(false);
    }

    //creating a sample object to be added to the database
    CouchDBDocument dbDoc;
    dbDoc.setId("99999999999999999999999999999999");


    dbDoc.setDoc(QJsonObject({{"cocktailId", "99"},
                                   {"cocktailState", 0},
                                   {"iceRequired", false},
                                   {"userId", "99"}
                                 }));
    qDebug() << "Adding object to the Database";
    //qDebug() << dbDoc;

    returnValue = connectorObj.addOrderDoc(&dbDoc);

    orders = connectorObj.getAllOrders();

    qDebug() << orders.size() <<" orders retrieved";



//    //if no item is in the server, problem in the test
//    if(orders.size() == 0) { QVERIFY(false); }

//    qDebug() << orders.at(0);

//    //JSON object
//    QJsonObject order2obj = orders.at(0).toObject();
//    //sub-obj ect
//    QJsonObject orderObjTest = order2obj.value("doc").toObject();
//    qDebug() << "orderObjTest.value(\"timestamp\"): " << orderObjTest.value("timestamp").toDouble();

    if(orders.size() == 0){
        qDebug() << "Item was not correctly added";
        QVERIFY(false);
    }else{
        qDebug() << "Correctly added, now removing item...";

        returnValue = connectorObj.deleteOrderDoc(&dbDoc);

        orders = connectorObj.getAllOrders();

        qDebug() << orders.size() <<" orders retrieved";

        QVERIFY(true);
    }

}

void AppControlTest::orderQueueConnectorGetOpenOrders(){
    //creating object for test
    OrderQueueConnector connectorObj;
    //CouchDB items should be saved in this JSON array
    QJsonArray orders;

    bool returnValue = connectorObj.InitDBConnection(COUCHDB_HOST, COUCHDB_DBNAME);

    if(!returnValue) {
        qDebug() << "Connections is not done!";
        QVERIFY(false);
    }

    //creating a sample object to be added to the database
    CouchDBDocument dbDoc;
    dbDoc.setId("99999999999999999999999999999999");


    dbDoc.setDoc(QJsonObject({{"cocktailId", "99"},
                                   {"cocktailState", 0},
                                   {"iceRequired", false},
                                   {"userId", "99"}
                                 }));
    qDebug() << "Adding object to the Database";
    //qDebug() << dbDoc;

    returnValue = connectorObj.addOrderDoc(&dbDoc);

    orders = connectorObj.getOpenOrders();

    qDebug() << orders.size() <<" open orders retrieved";

    if(orders.size() == 0){
        qDebug() << "Item was not correctly added";
        QVERIFY(false);
    }else{
        qDebug() << "Correctly added, now removing item...";

        returnValue = connectorObj.deleteOrderDoc(&dbDoc);

        orders = connectorObj.getOpenOrders();

        qDebug() << orders.size() <<" open orders retrieved";

        QVERIFY(true);
    }

    //QVERIFY(orders.size() > 0);
}

void AppControlTest::orderQueueConnectorGetOrder(){
    //creating object for test
    OrderQueueConnector connectorObj;
    //CouchDB items should be saved in this JSON array
    QJsonArray orders;

    bool returnValue = connectorObj.InitDBConnection(COUCHDB_HOST, COUCHDB_DBNAME);

    if(!returnValue) {
        qDebug() << "Connections is not done!";
        QVERIFY(false);
    }

    //creating a sample object to be added to the database
    CouchDBDocument dbDoc;
    QString id2test = "99999999999999999999999999999999";
    dbDoc.setId(id2test);

    QJsonObject jsondbDoc = QJsonObject({{"cocktailId", "99"},
                                         {"cocktailState", 0},
                                         {"iceRequired", false},
                                         {"userId", "99"}
                                       });
    dbDoc.setDoc(jsondbDoc);
    qDebug() << "Adding object to the Database";
    //qDebug() << dbDoc;

    returnValue = connectorObj.addOrderDoc(&dbDoc);

    orders = connectorObj.getAllOrders();

    qDebug() << orders.size() <<" total orders retrieved";

    //if no item is in the server, problem in the test
    if(orders.size() == 0) { QVERIFY(false); }




    //JSON object
    //QJsonObject order2obj = jsondbDoc;
    //sub-obj ect
    //QJsonObject orderObjTest = order2obj.value("doc").toObject();

    qDebug() << "running getOrder() with id from first item: " << id2test;

    QJsonObject specificOrder;
    specificOrder = connectorObj.getOrder(id2test);

    qDebug() << "retrieved item";
    qDebug() << specificOrder;

    QString originalID = id2test;
    QString retrievedID = specificOrder.value("_id").toString();

    //ID from retrieved item should be the same from the one given as parameter
    QVERIFY(originalID.compare(retrievedID) == 0);







    if(orders.size() == 0){
        qDebug() << "Item was not correctly added";
        QVERIFY(false);
    }else{
        qDebug() << "Correctly added, now removing item...";

        returnValue = connectorObj.deleteOrderDoc(&dbDoc);

        orders = connectorObj.getAllOrders();

        qDebug() << orders.size() <<" total orders retrieved";

        QVERIFY(true);
    }

}



//QTEST_APPLESS_MAIN(AppControlTest)
QTEST_MAIN(AppControlTest)

#include "tst_appcontroltest.moc"
