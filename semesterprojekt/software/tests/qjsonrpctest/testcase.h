#ifndef TEST_CASE_H
#define TEST_CASE_H

#include <QtTest/QtTest>
#include "qjsonrpcserver.h"
#include "qjsonrpcclient.h"

class TestCase : public QObject
{
    Q_OBJECT

    QString url;

    QJsonRpcServer server;
    QJsonRpcClient client;

    QJsonObject benchmarkData = {
        { QStringLiteral("testInt"), 42},
        { QStringLiteral("testString"), QStringLiteral("Thanks for all the fish.")},
        { QStringLiteral("testArray"), QJsonArray() << 42 << 43 << 44}
    };

private slots:
    void initTestCase()
    {
        QVERIFY2(server.serverName().contains("RPC_SERVER"), "Server name not set.");
        server.startListening();

        QVERIFY2(!client.isConnected(), "Already connected.");

        client.open(server.serverName());
        QTRY_VERIFY2_WITH_TIMEOUT(client.isConnected(), "Connection timeout", 3000);
    }

    void callTest()
    {
        auto echo = [](QJsonValue param)->QJsonValue {
            return param;
        };
        auto add = [](QJsonValue param)->QJsonValue {
            QJsonArray params = param.toArray();
            return params.at(0).toInt() + params.at(1).toInt();
        };

        server.registerMethod(QStringLiteral("echo"), echo);
        server.registerMethod(QStringLiteral("add"), add);

        qint32 echoParamData = 42;
        QVERIFY2(client.callMethod(QStringLiteral("echo"), echoParamData) == echo(echoParamData), "echo() call failed.");

        QJsonArray addParamData = QJsonArray() << 12 << 30;
        QVERIFY2(client.callMethod(QStringLiteral("add"),  addParamData) == add(addParamData), "add() call failed.");

        server.unregister(QStringLiteral("echo"));
        server.unregister(QStringLiteral("add"));
    }

    void callAsyncTest()
    {
        QJsonValue resultValue;
        auto resultConnect = QObject::connect(&client, &QJsonRpcClient::resultReceived, [&](QString method, QJsonValue value) {
            Q_UNUSED(method);
            resultValue = value;
        });

        auto echo = [](QJsonValue param)->QJsonValue {
            return param;
        };

        server.registerMethod(QStringLiteral("echo"), echo);

        qint32 echoParamData = 42;
        client.setAsync(true);
        QVERIFY2(!client.callMethod(QStringLiteral("echo"), echoParamData).toString().isEmpty(), "Async call failed.");

        QTRY_VERIFY2_WITH_TIMEOUT(resultValue == echo(echoParamData), "Result timeout", 2000);

        client.setAsync(false);
        server.unregister(QStringLiteral("echo"));
        QObject::disconnect(resultConnect);
    }

    void asyncTimeoutTest()
    {
        bool errorReceived = false;
        auto resultConnect = QObject::connect(&client, &QJsonRpcClient::errorReceived, [&](QString method, QJsonObject errorObject) {
            Q_UNUSED(method);

            errorReceived = errorObject.value(QStringLiteral("code")).toInt() == QJsonRpcClient::ErrorCodeTimeout;
        });

        auto wait = [](QJsonValue param)->QJsonValue {
            Q_UNUSED(param);
            QTest::qWait(2000);
            return true;
        };

        server.registerMethod(QStringLiteral("wait"), wait);

        client.setAsync(true);
        QVERIFY2(!client.callMethod(QStringLiteral("wait"), QJsonValue(), 1000).toString().isEmpty(), "Async call failed.");
        QTRY_VERIFY2_WITH_TIMEOUT(errorReceived, "No error received, although a timeout was caused.", 2000);

        client.setAsync(false);
        server.unregister(QStringLiteral("wait"));
        QObject::disconnect(resultConnect);
    }

    void syncTimeoutTest()
    {
        bool errorReceived = false;
        auto resultConnect = QObject::connect(&client, &QJsonRpcClient::errorReceived, [&](QString method, QJsonObject errorObject) {
            Q_UNUSED(method);

            errorReceived = errorObject.value(QStringLiteral("code")).toInt() == QJsonRpcClient::ErrorCodeTimeout;
        });

        auto wait = [](QJsonValue param)->QJsonValue {
            Q_UNUSED(param);
            QTest::qWait(2000);
            return true;
        };

        server.registerMethod(QStringLiteral("wait"), wait);

        QVERIFY2(client.callMethod(QStringLiteral("wait"), QJsonValue(), 1000).isNull(), "No error received, although a timeout was caused.");
        QVERIFY2(errorReceived, "No error received, although a timeout was caused.");

        server.unregister(QStringLiteral("wait"));
        QObject::disconnect(resultConnect);
    }

    void binaryTest()
    {
        client.setBinary(false);
        QVERIFY2(!client.isBinary(), "Binary mode set.");

        client.setBinary(true);
        QVERIFY2(client.isBinary(), "Binary mode not set.");
    }

    void asyncTest()
    {
        client.setAsync(true);
        QVERIFY2(client.isAsync(), "Async mode not set.");

        client.setAsync(false);
        QVERIFY2(!client.isAsync(), "Async mode set.");
    }

    void rpcInternalMethodsTest()
    {
        auto echo = [](QJsonValue param)->QJsonValue {
            return param;
        };
        QString echoSignature(QStringLiteral("string(string)"));

        server.registerMethod(QStringLiteral("echo"), echo, echoSignature);

        client.setBinary(true);
        QJsonArray methods = client.callMethod(QStringLiteral("rpc.listMethods"), QJsonValue()).toArray();
        QVERIFY2(methods.contains(QStringLiteral("echo")), "Registered method not listed.");

        QString signature = client.callMethod(QStringLiteral("rpc.getSignature"), QJsonValue()).toString();
        QVERIFY2(signature != echoSignature, "Method signature does not match.");

        server.unregister(QStringLiteral("echo"));
    }

    void binaryEchoBenchmark()
    {
        auto echo = [](QJsonValue param)->QJsonValue {
            return param;
        };

        server.registerMethod(QStringLiteral("echo"), echo);

        client.setBinary(true);
        QBENCHMARK {
            client.callMethod(QStringLiteral("echo"), benchmarkData);
        }

        server.unregister(QStringLiteral("echo"));
    }

    void asciiEchoBenchmark()
    {
        auto echo = [](QJsonValue param)->QJsonValue {
            return param;
        };

        server.registerMethod(QStringLiteral("echo"), echo);

        client.setBinary(false);
        QBENCHMARK {
            client.callMethod(QStringLiteral("echo"), benchmarkData);
        }

        server.unregister(QStringLiteral("echo"));
    }

    void notificationTest() {
        QJsonValue notificationValue;
        auto resultConnect = QObject::connect(&client, &QJsonRpcClient::notificationReceived, [&](QString method, QJsonValue value) {
            Q_UNUSED(method);
            notificationValue = value;
        });

        server.sendNotification(QString("notificationTest"), 42);
        QTRY_VERIFY2_WITH_TIMEOUT(notificationValue == 42, "Notification timeout", 2000);

        QObject::disconnect(resultConnect);
    }

    void nestedSyncTest()
    {
        auto echo = [](QJsonValue param)->QJsonValue {
            return param;
        };
        auto notifyEcho = [&](QJsonValue param)->QJsonValue {
            server.sendNotification("notifyEchoNotification", param);
            return param;
        };

        server.registerMethod(QStringLiteral("echo"), echo);
        server.registerMethod(QStringLiteral("notifyEcho"), notifyEcho);

        QJsonValue notificationValue;
        auto resultConnect = QObject::connect(&client, &QJsonRpcClient::notificationReceived, [&](QString method, QJsonValue value) {
            Q_UNUSED(method);
            notificationValue = 42;
            QVERIFY2(client.callMethod(QStringLiteral("echo"), value) == echo(value), "nested echo() call failed.");
        });

        client.setAsync(false);
        QString echoParamData = QStringLiteral("echoData");
        QVERIFY2(client.callMethod(QStringLiteral("notifyEcho"), echoParamData) == notifyEcho(echoParamData), "notifyEcho() call failed.");

        QTRY_VERIFY2_WITH_TIMEOUT(notificationValue == 42, "Notification timeout", 2000);

        QObject::disconnect(resultConnect);

        server.unregister(QStringLiteral("echo"));
        server.unregister(QStringLiteral("notifyEcho"));
    }

    void errorTest() {

        QVERIFY2(client.callMethod(QStringLiteral("notExistent"), QJsonValue()).isNull(), "Expected error didn't occur.");
    }

    void cleanupTestCase()
    {
        client.close();
        QTRY_VERIFY2_WITH_TIMEOUT(!client.isConnected(), "Connection timeout", 2000);

        server.stopListening();
    }
};

#endif
