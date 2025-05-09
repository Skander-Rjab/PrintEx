#ifndef INSTITUTION_H
#define INSTITUTION_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMap>
#include <QString>

class Institution : public QObject
{
    Q_OBJECT

public:
    explicit Institution(QObject *parent = nullptr);

    // Core CRUD Operations
    bool addInstitution(const QString &name, const QString &contactInfo, const QString &address);
    bool deleteInstitution(int institutionId);
    bool updateInstitution(int institutionId, const QString &name, const QString &contactInfo, const QString &address);

    // Data Analysis
    QMap<QString, int> getStatistics();
    QSqlRecord getInstitutionById(int institutionId);

private:
    QSqlDatabase m_database;

    // Audit logging
    void logAction(const QString &user, const QString &action, const QString &details);
    QString getCurrentUser();
};

#endif // INSTITUTION_H
