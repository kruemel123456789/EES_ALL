#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QtCore>
#include <QtWebSockets>

class ChatServer : public QObject
{
    Q_OBJECT

    QWebSocketServer m_server;                      //server object
    QSet<QWebSocket*> m_connectedClients;           //set of connected clients
    QHash<QWebSocket*, QJsonObject> m_clientInfos;  //infos of the connected clients

public:
    explicit ChatServer(QObject *parent = 0);
    virtual ~ChatServer();

protected slots:
    void onNewConnection();
    void onNewMessage(QWebSocket *client, const QByteArray &message);

    QJsonObject createErrorMessage(const QString& errorString);

public slots:
    void sendMessage(QWebSocket *client, const QJsonObject &messageObject);
    void broadcastMessage(const QJsonObject &messageObject);

signals:

};

#endif // CHATSERVER_H
