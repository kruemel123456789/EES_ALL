#ifndef COUCHDBDATABASE_H
#define COUCHDBDATABASE_H

#include <QtCore>
#include <QtQml>
#include <functional>

Q_DECLARE_LOGGING_CATEGORY(MODULES_COUCHDB_DATABASE)

class CouchDBDatabase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool available READ available NOTIFY availableChanged)
    Q_PROPERTY(QString hostname READ hostname WRITE setHostname NOTIFY hostnameChanged)
    Q_PROPERTY(QString database READ database WRITE setDatabase NOTIFY databaseChanged)
    Q_PROPERTY(QString url READ url NOTIFY urlChanged)
    Q_PROPERTY(QQmlPropertyMap* parameter READ parameter CONSTANT)

    class PrivateData;
    QScopedPointer<PrivateData> d_data;

    friend class CouchDBDocument;
    friend class CouchDBModel;
    friend class CouchDBView;

    typedef std::function<void(int, QJsonObject, QString)> FinishedHandlerType;
    typedef std::function<void(int, QString)> ErrorHandlerType;

    static ErrorHandlerType defaultErrorHandler;

protected:
    void get(const QUrl& url, FinishedHandlerType onFinished);
    void put(const QUrl& url, QJsonObject requestObject, FinishedHandlerType onFinished);
    void put(const QUrl& url, QByteArray content, QString contentType, FinishedHandlerType onFinished);
    void post(const QUrl& url, QJsonObject requestObject, FinishedHandlerType onFinished);
    void del(const QUrl& url, FinishedHandlerType onFinished);

    void updateDatabaseInfos();
    void updateUrl();

public:
    explicit CouchDBDatabase(QObject *parent = 0);
    ~CouchDBDatabase();

    Q_INVOKABLE void compact();

    QString hostname() const;
    void setHostname(QString hostname);

    QString database() const;
    void setDatabase(QString database);

    QString url() const;
    void setUrl(QString url);

    QQmlPropertyMap* parameter() const;

    bool available() const;
    void setAvailable(bool available);

signals:
    void hostnameChanged(QString hostname);
    void databaseChanged(QString database);
    void urlChanged(QString url);
    void availableChanged(bool available);
};

#endif // COUCHDBDATABASE_H
