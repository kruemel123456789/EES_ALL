#include "couchdbdatabase.h"

#include <QtNetwork>

Q_LOGGING_CATEGORY(MODULES_COUCHDB_DATABASE, "modules.couchdb.database")

CouchDBDatabase::ErrorHandlerType CouchDBDatabase::defaultErrorHandler = [](int code, QString error){ qCWarning(MODULES_COUCHDB_DATABASE) << "Default error handler:" << error << code; };

class CouchDBDatabase::PrivateData
{
public:
    bool available;
    QNetworkAccessManager manager;
    QJsonObject databaseInfos;
    QString hostname;
    QString database;
    QString url;
    QQmlPropertyMap parameter;
};

void CouchDBDatabase::get(const QUrl& url, FinishedHandlerType onFinished)
{
    QNetworkReply* reply = d_data->manager.get(QNetworkRequest(url));
    QObject::connect(reply, &QNetworkReply::finished, [reply, onFinished]() {
        onFinished(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(), QJsonDocument::fromJson(reply->readAll()).object(), reply->errorString() );
        reply->deleteLater();
    });
}

void CouchDBDatabase::put(const QUrl &url, QJsonObject requestObject, CouchDBDatabase::FinishedHandlerType onFinished)
{
    put(url, QJsonDocument(requestObject).toJson(), "application/json", onFinished);
}

void CouchDBDatabase::put(const QUrl &url, QByteArray content, QString contentType, CouchDBDatabase::FinishedHandlerType onFinished)
{
    QNetworkRequest request(url);
    request.setRawHeader( "Content-Type", contentType.toLocal8Bit() );

    QNetworkReply* reply = d_data->manager.put(request, content);
    QObject::connect(reply, &QNetworkReply::finished, [reply, onFinished]() {
        onFinished(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(), QJsonDocument::fromJson(reply->readAll()).object(), reply->errorString());
        reply->deleteLater();
    });
}

void CouchDBDatabase::post(const QUrl &url, QJsonObject requestObject, CouchDBDatabase::FinishedHandlerType onFinished)
{
    QNetworkRequest request(url);
    request.setRawHeader( "Content-Type", "application/json" );

    QNetworkReply* reply = d_data->manager.post(request, QJsonDocument(requestObject).toJson());
    QObject::connect(reply, &QNetworkReply::finished, [reply, onFinished]() {
        onFinished(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(), QJsonDocument::fromJson(reply->readAll()).object(), reply->errorString());
        reply->deleteLater();
    });
}

void CouchDBDatabase::del(const QUrl &url, CouchDBDatabase::FinishedHandlerType onFinished)
{
    QNetworkReply* reply = d_data->manager.deleteResource(QNetworkRequest(url));
    QObject::connect(reply, &QNetworkReply::finished, [reply, onFinished]() {
        onFinished(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(), QJsonDocument::fromJson(reply->readAll()).object(), reply->errorString());
        reply->deleteLater();
    });
}

void CouchDBDatabase::updateDatabaseInfos()
{
    get(url(), [this](int statusCode, QJsonObject resultObject, QString errorString) {
        if(statusCode >= 200 && statusCode < 300) {
            foreach(QString key, d_data->parameter.keys()) {
                d_data->parameter.insert(key, QVariant());
            }

            foreach(QString key, resultObject.keys()) {
                d_data->parameter.insert(key, resultObject.value(key));
            }

            setAvailable(!resultObject.isEmpty());
        }
        else {
            defaultErrorHandler(statusCode, errorString);
        }
    });
}

void CouchDBDatabase::updateUrl()
{
    setUrl(QStringLiteral("http://") + hostname() + QStringLiteral("/") + database() + QStringLiteral("/"));
}

CouchDBDatabase::CouchDBDatabase(QObject *parent) : QObject(parent)
  ,d_data(new PrivateData)
{
    d_data->available = false;

    QObject::connect(this, &CouchDBDatabase::hostnameChanged, this, &CouchDBDatabase::updateUrl);
    QObject::connect(this, &CouchDBDatabase::databaseChanged, this, &CouchDBDatabase::updateUrl);

    //immediatly connect for faster queries
    QObject::connect(this, &CouchDBDatabase::hostnameChanged, [this](QString hostname) {
        updateDatabaseInfos();
    });

    QObject::connect(&d_data->manager, &QNetworkAccessManager::sslErrors, [](QNetworkReply *reply, const QList<QSslError> &errors){
        reply->ignoreSslErrors(errors);
    });
}

CouchDBDatabase::~CouchDBDatabase()
{

}

void CouchDBDatabase::compact()
{
    post(url() + QStringLiteral("_compact"), QJsonObject(), [](int statusCode, QJsonObject resultObject, QString errorString){

    });
}

QString CouchDBDatabase::hostname() const
{
    return d_data->hostname;
}

void CouchDBDatabase::setHostname(QString hostname)
{
    if (d_data->hostname == hostname)
        return;

    d_data->hostname = hostname;
    emit hostnameChanged(hostname);
}

QString CouchDBDatabase::database() const
{
    return d_data->database;
}

void CouchDBDatabase::setDatabase(QString database)
{
    if (d_data->database == database)
        return;

    d_data->database = database;
    emit databaseChanged(database);
}

QString CouchDBDatabase::url() const
{
    return d_data->url;
}

void CouchDBDatabase::setUrl(QString url)
{
    if (d_data->url == url)
        return;

    d_data->url = url;
    emit urlChanged(url);
}

QQmlPropertyMap *CouchDBDatabase::parameter() const
{
    return &d_data->parameter;
}

bool CouchDBDatabase::available() const
{
    return d_data->available;
}

void CouchDBDatabase::setAvailable(bool available)
{
    if (d_data->available == available)
        return;

    d_data->available = available;
    emit availableChanged(available);
}

