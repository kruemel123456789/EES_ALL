#ifndef COUCHDBVIEW_H
#define COUCHDBVIEW_H

#include <QtCore>

Q_DECLARE_LOGGING_CATEGORY(MODULES_COUCHDB_VIEW)

#include "couchdbdatabase.h"

class CouchDBView : public QObject
{
    Q_OBJECT
    Q_PROPERTY(CouchDBDatabase* database READ database WRITE setDatabase NOTIFY databaseChanged)
    Q_PROPERTY(QJsonArray rows READ rows NOTIFY rowsChanged)
    Q_PROPERTY(int rowCount READ rowCount NOTIFY rowsChanged)
    Q_PROPERTY(QString designDoc READ designDoc WRITE setDesignDoc NOTIFY designDocChanged)
    Q_PROPERTY(QString view READ view WRITE setView NOTIFY viewChanged)
    Q_PROPERTY(QVariant key READ key WRITE setKey NOTIFY keyChanged)
    Q_PROPERTY(QVariant startKey READ startKey WRITE setStartKey NOTIFY startKeyChanged)
    Q_PROPERTY(QVariant endKey READ endKey WRITE setEndKey NOTIFY endKeyChanged)

    class PrivateData;
    QScopedPointer<PrivateData> d_data;

    QUrl createUrl() const;

public:
    explicit CouchDBView(QObject *parent = 0);
    ~CouchDBView();

    Q_INVOKABLE void load();
    Q_INVOKABLE void setDoc(QJsonObject json);

    Q_INVOKABLE QString getId(int i) const;
    Q_INVOKABLE QJsonValue getKey(int i) const;
    Q_INVOKABLE QJsonValue getValue(int i) const;

    CouchDBDatabase* database() const;
    void setDatabase(CouchDBDatabase* database);

    QJsonArray rows() const;
    void setRows(QJsonArray rows);

    int rowCount() const;

    QString designDoc() const;
    void setDesignDoc(QString designDoc);

    QString view() const;
    void setView(QString view);

    QVariant key() const;
    void setKey(QVariant key);

    QVariant startKey() const;
    void setStartKey(QVariant startKey);

    QVariant endKey() const;
    void setEndKey(QVariant endKey);

signals:
    void databaseChanged(CouchDBDatabase* database);
    void designDocChanged(QString designDoc);
    void viewChanged(QString view);
    void keyChanged(QVariant key);
    void startKeyChanged(QVariant startKey);
    void endKeyChanged(QVariant endKey);
    void rowsChanged(QJsonArray rows);
};

#endif // COUCHDBVIEW_H
