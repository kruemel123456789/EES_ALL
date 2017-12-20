#ifndef COUCHDBMODEL_H
#define COUCHDBMODEL_H

#include <QtCore>
#include <QAbstractListModel>

Q_DECLARE_LOGGING_CATEGORY(MODULES_COUCHDB_MODEL)

#include "couchdbdatabase.h"

class CouchDBModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(CouchDBDatabase* database READ database WRITE setDatabase NOTIFY databaseChanged)
    Q_PROPERTY(QString designDoc READ designDoc WRITE setDesignDoc NOTIFY designDocChanged)
    Q_PROPERTY(QString viewName READ viewName WRITE setViewName NOTIFY viewNameChanged)

    class PrivateData;
    QScopedPointer<PrivateData> d_data;

public:
    explicit CouchDBModel(QObject *parent = 0);
    ~CouchDBModel();

    Q_INVOKABLE void load();
    Q_INVOKABLE void setDoc(QJsonObject json);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;

    CouchDBDatabase* database() const;
    void setDatabase(CouchDBDatabase* database);

    QString designDoc() const;
    void setDesignDoc(QString designDoc);

    QString viewName() const;
    void setViewName(QString viewName);

signals:
    void databaseChanged(CouchDBDatabase* database);

    void designDocChanged(QString designDoc);
    void viewNameChanged(QString viewName);
};

#endif // CouchDBModel_H
