#include "couchdbview.h"

Q_LOGGING_CATEGORY(MODULES_COUCHDB_VIEW, "modules.couchdb.view")

class CouchDBView::PrivateData
{
public:
    CouchDBDatabase* database;
    QString designDoc;
    QString viewName;
    QVariant key;
    QVariant startKey;
    QVariant endKey;

    QJsonArray rows;
};

QUrl CouchDBView::createUrl() const
{
    QMap<QString, QVariant> parameter;
    if(!key().isNull()) {
        parameter.insert(QStringLiteral("key"), key());
    }
    else if(!startKey().isNull() && endKey().isNull()) {
        parameter.insert(QStringLiteral("startkey"), startKey());
    }
    else if(!startKey().isNull() && !endKey().isNull()) {
        parameter.insert(QStringLiteral("startkey"), startKey());
        parameter.insert(QStringLiteral("endkey"), endKey());
    }

    QString url = d_data->database->url() + QStringLiteral("/_design/") + designDoc() + QStringLiteral("/_view/") + view();
    foreach(QString key, parameter.keys()) {
        QVariant value = parameter.value(key);
        url += QStringLiteral("&") + key + QStringLiteral("=") + (value.type() == QMetaType::QString ? (QStringLiteral("\"") + value.toString() + QStringLiteral("\"")) : value.toString());
    }
    url.replace(view() + QStringLiteral("&"), view() + QStringLiteral("?"));
    return QUrl(url);
}

CouchDBView::CouchDBView(QObject *parent) : QObject(parent)
  ,d_data(new PrivateData)
{
    //QObject::connect(this, &CouchDBView::designDocChanged, this, &CouchDBView::load);
    //QObject::connect(this, &CouchDBView::viewNameChanged, this, &CouchDBView::load);
}

CouchDBView::~CouchDBView()
{

}

void CouchDBView::load()
{
    if(d_data->database == nullptr) {
        qCWarning(MODULES_COUCHDB_VIEW) << "No database set!";
        return;
    }
    if(designDoc().isEmpty() || view().isEmpty()) {
        qCWarning(MODULES_COUCHDB_VIEW) << "No design and/or view set!";
        return;
    }

    QUrl url = createUrl();
    qCDebug(MODULES_COUCHDB_VIEW) << "GET from" << url;

    QScopedPointer<QEventLoop> waitLoop(new QEventLoop);
    d_data->database->get(url, [this, &waitLoop](int statusCode, QJsonObject resultObject, QString errorString) {
        if(statusCode >= 200 && statusCode < 300) {
            setDoc(resultObject);
        }
        else {
            CouchDBDatabase::defaultErrorHandler(statusCode, errorString);
        }
        waitLoop->exit();
    });
    waitLoop->exec();
}

void CouchDBView::setDoc(QJsonObject json)
{
    setRows( json.value(QStringLiteral("rows")).toArray() );
}

QString CouchDBView::getId(int i) const
{
    QJsonArray rows = this->rows();
    if(i < 0 || i >= rows.size()) {
        qCWarning(MODULES_COUCHDB_VIEW) << "Index out of bounds!";
        return QString();
    }

    return rows.at(i).toObject().value(QStringLiteral("id")).toString();
}

QJsonValue CouchDBView::getKey(int i) const
{
    QJsonArray rows = this->rows();
    if(i < 0 || i >= rows.size()) {
        qCWarning(MODULES_COUCHDB_VIEW) << "Index out of bounds!";
        return QJsonValue();
    }

    return rows.at(i).toObject().value(QStringLiteral("key"));
}

QJsonValue CouchDBView::getValue(int i) const
{
    QJsonArray rows = this->rows();
    if(i < 0 || i >= rows.size()) {
        qCWarning(MODULES_COUCHDB_VIEW) << "Index out of bounds!";
        return QJsonValue();
    }

    return rows.at(i).toObject().value(QStringLiteral("value"));
}

CouchDBDatabase *CouchDBView::database() const
{
    return d_data->database;
}

void CouchDBView::setDatabase(CouchDBDatabase *database)
{
    if (d_data->database == database)
        return;

    d_data->database = database;
    emit databaseChanged(database);
}

QJsonArray CouchDBView::rows() const
{
    return d_data->rows;
}

void CouchDBView::setRows(QJsonArray rows)
{
    if (d_data->rows == rows)
        return;

    d_data->rows = rows;
    emit rowsChanged(d_data->rows);
}

int CouchDBView::rowCount() const
{
    return d_data->rows.size();
}

QString CouchDBView::designDoc() const
{
    return d_data->designDoc;
}

void CouchDBView::setDesignDoc(QString designDoc)
{
    if (d_data->designDoc == designDoc)
        return;

    d_data->designDoc = designDoc;
    emit designDocChanged(designDoc);
}

QString CouchDBView::view() const
{
    return d_data->viewName;
}

void CouchDBView::setView(QString view)
{
    if (d_data->viewName == view)
        return;

    d_data->viewName = view;
    emit viewChanged(view);
}

QVariant CouchDBView::key() const
{
    return d_data->key;
}

void CouchDBView::setKey(QVariant key)
{
    if (d_data->key == key)
        return;

    d_data->key = key;
    emit keyChanged(d_data->key);
}

QVariant CouchDBView::startKey() const
{
    return d_data->startKey;
}

void CouchDBView::setStartKey(QVariant startKey)
{
    if (d_data->startKey == startKey)
        return;

    d_data->startKey = startKey;
    emit startKeyChanged(d_data->startKey);
}

QVariant CouchDBView::endKey() const
{
    return d_data->endKey;
}

void CouchDBView::setEndKey(QVariant endKey)
{
    if (d_data->endKey == endKey)
        return;

    d_data->endKey = endKey;
    emit endKeyChanged(d_data->endKey);
}
