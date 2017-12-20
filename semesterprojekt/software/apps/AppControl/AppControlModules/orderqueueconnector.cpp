#include "orderqueueconnector.h"

CouchDBDatabase db;

OrderQueueConnector::OrderQueueConnector()
{

}


/*
 * Establishes a connection to the CouchDB-Instance
*/

bool OrderQueueConnector::InitDBConnection(QString hostname, QString database)
{
    db.setHostname(hostname);
    db.setDatabase(database);

    return true;
}

/*
 * Fills the database with some dummy data
*/

bool OrderQueueConnector::InitDB()
{
    CouchDBDocument testDoc;
    testDoc.setDatabase(&db);
    testDoc.setId("a3571c1d164dfd047d4f674b67006528");


    testDoc.setDoc(QJsonObject({{"cocktailId", "2"},
                                   {"cocktailState", 1},
                                   {"iceRequired", false},
                                   {"userId", "1"}
                                 }));

    testDoc.save();

    CouchDBDocument testDoc2;
    testDoc2.setDatabase(&db);
    testDoc2.setId("a3571c1d164dfd047d4f674b67008cf5");


    testDoc2.setDoc(QJsonObject({{"cocktailId", "5"},
                                   {"cocktailState", 0},
                                   {"iceRequired", false},
                                   {"userId", "1"}
                                 }));

    testDoc2.save();

    return 0;
}

/*
 * Retrieves all available orders from the database
*/

QJsonArray OrderQueueConnector::getAllOrders()
{

    CouchDBDocument orders;
    orders.setDatabase(&db);
    orders.setId("_design/orders/_view/allOrders?include_docs=true");

    orders.load();

    QJsonArray rows = orders.getDoc()["rows"].toArray();

    return rows;
}


/*
 * Retrieves only open orders from the database
*/

QJsonArray OrderQueueConnector::getOpenOrders()
{
    CouchDBDocument orders;
    orders.setDatabase(&db);
    orders.setId("_design/orders/_view/openOrders?include_docs=true");

    orders.load();

    QJsonArray rows = orders.getDoc()["rows"].toArray();

    return rows;
}

/*
 * Retrieves a specific order from the database
*/

QJsonObject OrderQueueConnector::getOrder(QString orderId)
{

    CouchDBDocument order;
    order.setDatabase(&db);
    order.setId(orderId);

    order.load();



    return order.getDoc();
}

/*
 * Updates the state of an order
*/

bool OrderQueueConnector::updateOrderState(QString orderId, uint8_t state)
{

    if ((state < 0) || (state > 2)) {
        return false;
    }


    CouchDBDocument order;
    order.setDatabase(&db);
    order.setId(orderId);

    order.load();

    order.doc()->insert("cocktailState", state);

    order.save();

    return true;
}

bool OrderQueueConnector::addOrderDoc(CouchDBDocument *testDoc)
{
    //setting the database for the JSON Object
    testDoc->setDatabase(&db);
    //adding it to the database
    testDoc->save();
    return true;
}

bool OrderQueueConnector::deleteOrderDoc(CouchDBDocument *testDoc)
{
    //setting the database for the JSON Object
    testDoc->setDatabase(&db);
    //removing it from the database
    testDoc->deleteDoc();
    return true;
}


