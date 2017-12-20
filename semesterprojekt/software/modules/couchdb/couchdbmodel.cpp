#include "couchdbmodel.h"

Q_LOGGING_CATEGORY(MODULES_COUCHDB_MODEL, "modules.couchdb.view")

class CouchDBModel::PrivateData
{
public:
    CouchDBDatabase* database;
    QString designDoc;
    QString viewName;
    QJsonArray rows;

    QHash<int, QByteArray> roleNames;
};

CouchDBModel::CouchDBModel(QObject *parent) : QAbstractListModel(parent)
  ,d_data(new PrivateData)
{
    //QObject::connect(this, &CouchDBModel::designDocChanged, this, &CouchDBModel::load);
    //QObject::connect(this, &CouchDBModel::viewNameChanged, this, &CouchDBModel::load);
}

CouchDBModel::~CouchDBModel()
{

}

void CouchDBModel::load()
{
    if(d_data->database == nullptr) {
        qCWarning(MODULES_COUCHDB_MODEL) << "No database set!";
        return;
    }
    if(designDoc().isEmpty() || viewName().isEmpty()) {
        qCWarning(MODULES_COUCHDB_MODEL) << "No design and/or view set!";
        return;
    }

    d_data->database->get(d_data->database->url() + "/_design/" + designDoc() + "/_view/" + viewName(), [this](int statusCode, QJsonObject resultObject, QString errorString) {
        if(statusCode >= 200 && statusCode < 300) {
            setDoc(resultObject);
        }
        else {
            CouchDBDatabase::defaultErrorHandler(statusCode, errorString);
        }
    });
}

void CouchDBModel::setDoc(QJsonObject json)
{
    QAbstractListModel::beginResetModel();
    d_data->rows = json.value(QStringLiteral("rows")).toArray();
    QAbstractListModel::endResetModel();
}

QVariant CouchDBModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    if (row < 0 || row >= rowCount())
        return QVariant();

    if(role < Qt::UserRole) {
        return QVariant();
    }
    else {
        return d_data->rows.at(row);
    }
}

int CouchDBModel::rowCount(const QModelIndex &parent) const
{
    return d_data->rows.count();
}

QHash<int, QByteArray> CouchDBModel::roleNames() const
{
    //return d_data->roleNames;
    return { {Qt::UserRole + 1, "modelData"} };
}

CouchDBDatabase *CouchDBModel::database() const
{
    return d_data->database;
}

void CouchDBModel::setDatabase(CouchDBDatabase *database)
{
    if (d_data->database == database)
        return;

    d_data->database = database;
    emit databaseChanged(database);
}

QString CouchDBModel::designDoc() const
{
    return d_data->designDoc;
}

void CouchDBModel::setDesignDoc(QString designDoc)
{
    if (d_data->designDoc == designDoc)
        return;

    d_data->designDoc = designDoc;
    emit designDocChanged(designDoc);
}

QString CouchDBModel::viewName() const
{
    return d_data->viewName;
}

void CouchDBModel::setViewName(QString viewName)
{
    if (d_data->viewName == viewName)
        return;

    d_data->viewName = viewName;
    emit viewNameChanged(viewName);
}
