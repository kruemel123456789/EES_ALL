#ifndef COUCHDBDOCUMENT_H
#define COUCHDBDOCUMENT_H

#include <QtCore>
#include <QtQml>

Q_DECLARE_LOGGING_CATEGORY(MODULES_COUCHDB_DOCUMENT)

#include "couchdbdatabase.h"

class CouchDBDocument : public QObject
{
    Q_OBJECT
    Q_PROPERTY(CouchDBDatabase* database READ database WRITE setDatabase NOTIFY databaseChanged)
    Q_PROPERTY(QQmlPropertyMap* doc READ doc CONSTANT)
    Q_PROPERTY(QString docId READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString docRev READ rev WRITE setRev NOTIFY revChanged)
    Q_PROPERTY(QJsonObject docAttachments READ attachments NOTIFY attachmentsChanged)

    class PrivateData;
    QScopedPointer<PrivateData> d_data;

public:
    explicit CouchDBDocument(QObject *parent = 0);
    ~CouchDBDocument();

    Q_INVOKABLE void updateRev();
    Q_INVOKABLE void load();
    Q_INVOKABLE void save();
    Q_INVOKABLE void deleteDoc();

    Q_INVOKABLE void addAttachment(QString attachmentName, QByteArray content, QString contentType);

    Q_INVOKABLE void setDoc(QJsonObject json);
    Q_INVOKABLE QJsonObject getDoc();

    CouchDBDatabase* database() const;
    void setDatabase(CouchDBDatabase* database);

    QQmlPropertyMap *doc() const;

    QString id() const;
    void setId(QString id);

    QString rev() const;
    void setRev(QString rev);

    QJsonObject attachments() const;
    void setAttachments(QJsonObject attachments);

signals:
    void databaseChanged(CouchDBDatabase* database);
    void idChanged(QString id);
    void revChanged(QString rev);
    void attachmentsChanged(QJsonObject docAttachments);
};

#endif // COUCHDBDOCUMENT_H
