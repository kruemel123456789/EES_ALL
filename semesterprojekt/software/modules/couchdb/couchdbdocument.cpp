#include "couchdbdocument.h"

Q_LOGGING_CATEGORY(MODULES_COUCHDB_DOCUMENT, "modules.couchdb.document")

class CouchDBDocument::PrivateData
{
public:
    CouchDBDatabase* database;
    QQmlPropertyMap doc;
    QString id;
    QString rev;
    QJsonObject docAttachments;
    QEventLoop eventLoop;
};


void CouchDBDocument::updateRev()
{
    if(d_data->database == nullptr) {
        qCWarning(MODULES_COUCHDB_DOCUMENT) << "No database set!";
        return;
    }

    if(d_data->eventLoop.isRunning()) {
        qCWarning(MODULES_COUCHDB_DOCUMENT) << "Another sync call is not yet finished. Async calls are not supported.";
        return;
    }

    d_data->database->get(d_data->database->url() + id(), [this](int statusCode, QJsonObject resultObject, QString errorString) {
        if(statusCode >= 200 && statusCode < 300) {
            setRev(resultObject.value(QStringLiteral("_rev")).toString());
        }
        else {
            CouchDBDatabase::defaultErrorHandler(statusCode, errorString);
        }
        d_data->eventLoop.exit();
    });
    d_data->eventLoop.exec();
}

void CouchDBDocument::load()
{
    if(d_data->database == nullptr) {
        qCWarning(MODULES_COUCHDB_DOCUMENT) << "No database set!";
        return;
    }

    if(d_data->eventLoop.isRunning()) {
        qCWarning(MODULES_COUCHDB_DOCUMENT) << "Another sync call is not yet finished. Async calls are not supported.";
        return;
    }

    d_data->database->get(d_data->database->url() + id(), [this](int statusCode, QJsonObject resultObject, QString errorString) {
        if(statusCode >= 200 && statusCode < 300) {
            setDoc(resultObject);
        }
        else {
            CouchDBDatabase::defaultErrorHandler(statusCode, errorString);
        }
        d_data->eventLoop.exit();
    });
    d_data->eventLoop.exec();
}

void CouchDBDocument::save()
{
    if(d_data->database == nullptr) {
        qCWarning(MODULES_COUCHDB_DOCUMENT) << "No database set!";
        return;
    }

    if(d_data->eventLoop.isRunning()) {
        qCWarning(MODULES_COUCHDB_DOCUMENT) << "Another sync call is not yet finished. Async calls are not supported.";
        return;
    }

    d_data->database->put(d_data->database->url() + id(), getDoc(), [this](int statusCode, QJsonObject resultObject, QString errorString) {
        if(statusCode >= 200 && statusCode < 300) {
            setRev(resultObject.value("rev").toString());
        }
        else if(statusCode == 409) {
            qCWarning(MODULES_COUCHDB_DOCUMENT) << errorString << "- Trying to overwrite conflicting version...";
            updateRev();
            save();
        }
        else {
            CouchDBDatabase::defaultErrorHandler(statusCode, errorString);
        }
        d_data->eventLoop.exit();
    });
    d_data->eventLoop.exec();
}

void CouchDBDocument::deleteDoc()
{
    if(d_data->database == nullptr) {
        qCWarning(MODULES_COUCHDB_DOCUMENT) << "No database set!";
        return;
    }

    if(d_data->eventLoop.isRunning()) {
        qCWarning(MODULES_COUCHDB_DOCUMENT) << "Another sync call is not yet finished. Async calls are not supported.";
        return;
    }

    d_data->database->del(d_data->database->url() + id() + QStringLiteral("?rev=") + rev(), [this](int statusCode, QJsonObject resultObject, QString errorString) {
        Q_UNUSED(resultObject)
        if(statusCode >= 200 && statusCode < 300) {
            setId("");
            setRev("");
            setAttachments(QJsonObject());
            setDoc(QJsonObject());
        }
        else {
            CouchDBDatabase::defaultErrorHandler(statusCode, errorString);
        }
        d_data->eventLoop.exit();
    });
    d_data->eventLoop.exec();
}

void CouchDBDocument::addAttachment(QString attachmentName, QByteArray content, QString contentType)
{
    if(d_data->eventLoop.isRunning()) {
        qCWarning(MODULES_COUCHDB_DOCUMENT) << "Another sync call is not yet finished. Async calls are not supported.";
        return;
    }

    d_data->database->put(d_data->database->url() + id() + "/" + attachmentName + "?rev=" + rev(), content, contentType, [attachmentName, content, contentType, this](int statusCode, QJsonObject resultObject, QString errorString) {
        if(statusCode >= 200 && statusCode < 300) {
            setRev(resultObject.value("rev").toString());
        }
        else if(statusCode == 409) {
            updateRev();
            addAttachment(attachmentName, content, contentType);
        }
        else {
            CouchDBDatabase::defaultErrorHandler(statusCode, errorString);
        }
        d_data->eventLoop.exit();
    });
    d_data->eventLoop.exec();
}

CouchDBDocument::CouchDBDocument(QObject *parent) : QObject(parent)
  ,d_data(new PrivateData)
{
    d_data->database = nullptr;
}

CouchDBDocument::~CouchDBDocument()
{
    if(d_data->eventLoop.isRunning()) {
        qCWarning(MODULES_COUCHDB_DOCUMENT) << "Try to delete document object, but event loop is still running! This may result in unexpected behavior.";

        QElapsedTimer timeout;
        timeout.start();
        while(d_data->eventLoop.isRunning() && !timeout.hasExpired(3000))
            QCoreApplication::processEvents();

        if(timeout.hasExpired(3000)) {
            qCWarning(MODULES_COUCHDB_DOCUMENT) << "Event loop is still running after waiting to finish! This most definetly results in unexpected behavior.";
        }
    }
}

void CouchDBDocument::setDoc(QJsonObject json)
{
    foreach(QString key, d_data->doc.keys()) {
        d_data->doc.insert(key, QVariant());
    }
    foreach(QString key, json.keys()) {
        if(key.startsWith('_')) continue;
        d_data->doc.insert(key, json.value(key));
    }
    if(json.contains(QStringLiteral("_id"))) setId(json.value(QStringLiteral("_id")).toString(QString()));
    if(json.contains(QStringLiteral("_rev"))) setRev(json.value(QStringLiteral("_rev")).toString(QString()));
    if(json.contains(QStringLiteral("_attachments"))) setAttachments(json.value(QStringLiteral("_attachments")).toObject());
}

QJsonObject CouchDBDocument::getDoc()
{
    QJsonObject returnObject;
    foreach(QString key, d_data->doc.keys()) {
        if(d_data->doc.value(key).isValid())
            returnObject.insert(key, QJsonValue::fromVariant(d_data->doc.value(key)));
    }
    if(!id().isEmpty()) returnObject.insert(QStringLiteral("_id"), id());
    if(!rev().isEmpty()) returnObject.insert(QStringLiteral("_rev"), rev());
    if(!attachments().isEmpty()) returnObject.insert(QStringLiteral("_attachments"), attachments());
    return returnObject;
}

CouchDBDatabase *CouchDBDocument::database() const
{
    return d_data->database;
}

void CouchDBDocument::setDatabase(CouchDBDatabase *database)
{
    if (d_data->database == database)
        return;

    d_data->database = database;
    emit databaseChanged(database);
}

QQmlPropertyMap *CouchDBDocument::doc() const
{
    return &d_data->doc;
}

QString CouchDBDocument::id() const
{
    return d_data->id;
}

void CouchDBDocument::setId(QString id)
{
    if (d_data->id == id)
        return;

    d_data->id = id;
    emit idChanged(id);
}

QString CouchDBDocument::rev() const
{
    return d_data->rev;
}

void CouchDBDocument::setRev(QString rev)
{
    if (d_data->rev == rev)
        return;

    d_data->rev = rev;
    emit revChanged(rev);
}

QJsonObject CouchDBDocument::attachments() const
{
    return d_data->docAttachments;
}

void CouchDBDocument::setAttachments(QJsonObject attachments)
{
    if (d_data->docAttachments == attachments)
        return;

    d_data->docAttachments = attachments;
    emit attachmentsChanged(attachments);
}
