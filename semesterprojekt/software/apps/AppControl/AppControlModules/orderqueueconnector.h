#ifndef ORDERQUEUECONNECTOR_H
#define ORDERQUEUECONNECTOR_H

#include "couchdbdatabase.h"
#include "couchdbdocument.h"

class OrderQueueConnector
{
public:
    OrderQueueConnector();
    bool InitDBConnection(QString hostname, QString database);
    bool InitDB();
    QJsonArray getAllOrders();
    QJsonArray getOpenOrders();
    QJsonObject getOrder(QString orderId);
    bool updateOrderState(QString orderId, uint8_t state);
    bool addOrderDoc(CouchDBDocument *testDoc);
    bool deleteOrderDoc(CouchDBDocument *testDoc);
};

#endif // ORDERQUEUECONNECTOR_H
