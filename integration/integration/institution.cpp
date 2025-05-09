#include "institution.h"
#include "Connection.h"
#include "qsqlrecord.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QSqlError>
#include <QDebug>

#ifdef Q_OS_WIN
#include <windows.h>
#else
#include <unistd.h>
#include <pwd.h>
#endif

Institution::Institution(QObject *parent) : QObject(parent),
    m_database(Connection::getInstance()->database())
{
}

bool Institution::addInstitution(const QString &name, const QString &contactInfo, const QString &address)
{

    QSqlQuery maxIdQuery;
    maxIdQuery.prepare("SELECT MAX(INSTITUTION_ID) FROM QT_INSTITUTIONS");

    if (!maxIdQuery.exec()) {
        qDebug() << "Failed to fetch maximum INSTITUTION_ID:" << maxIdQuery.lastError().text();
        return false;
    }

    int maxId = 0;
    if (maxIdQuery.next()) {
        maxId = maxIdQuery.value(0).toInt();
    }

    int newId = maxId + 1;

    QSqlQuery query;
    query.prepare("INSERT INTO QT_INSTITUTIONS (INSTITUTION_ID,NAME, CONTACT_INFO, ADDRESS) "
                  "VALUES (:institutionId, :name, :contact, :address)");
    query.bindValue(":institutionId", newId);
    query.bindValue(":name", name);
    query.bindValue(":contact", contactInfo);
    query.bindValue(":address", address);

    if(!query.exec()) {
        qWarning() << "Add institution failed:" << query.lastError().text();
        return false;
    }

    logAction(getCurrentUser(), "ADD", QString("%1 (Contact: %2)").arg(name).arg(contactInfo));
    return true;
}

bool Institution::deleteInstitution(int institutionId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM QT_INSTITUTIONS WHERE INSTITUTION_ID = :id");
    query.bindValue(":id", institutionId);

    if(!query.exec()) {
        qWarning() << "Delete institution failed:" << query.lastError().text();
        return false;
    }

    logAction(getCurrentUser(), "DELETE", QString("ID %1").arg(institutionId));
    return true;
}

bool Institution::updateInstitution(int institutionId, const QString &name,
                                    const QString &contactInfo, const QString &address)
{
    QSqlQuery query;
    query.prepare("UPDATE QT_INSTITUTIONS SET "
                  "NAME = :name, "
                  "CONTACT_INFO = :contact, "
                  "ADDRESS = :address "
                  "WHERE INSTITUTION_ID = :id");
    query.bindValue(":id", institutionId);
    query.bindValue(":name", name);
    query.bindValue(":contact", contactInfo);
    query.bindValue(":address", address);

    if(!query.exec()) {
        qWarning() << "Update institution failed:" << query.lastError().text();
        return false;
    }

    logAction(getCurrentUser(), "UPDATE", QString("ID %1").arg(institutionId));
    return true;
}

QMap<QString, int> Institution::getStatistics()
{
    QMap<QString, int> stats;

    QSqlQuery countQuery("SELECT COUNT(*) FROM QT_INSTITUTIONS");
    if(countQuery.next()) {
        stats["Total Institutions"] = countQuery.value(0).toInt();
    }

    QSqlQuery domainQuery("SELECT SUBSTR(ADDRESS, INSTR(ADDRESS, '@')+1 AS domain, "
                          "COUNT(*) FROM QT_INSTITUTIONS GROUP BY domain");
    while(domainQuery.next()) {
        stats[domainQuery.value(0).toString()] = domainQuery.value(1).toInt();
    }

    return stats;
}

QSqlRecord Institution::getInstitutionById(int institutionId)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM QT_INSTITUTIONS WHERE INSTITUTION_ID = :id");
    query.bindValue(":id", institutionId);
    query.exec();
    return query.next() ? query.record() : QSqlRecord();
}

QString Institution::getCurrentUser()
{
#ifdef Q_OS_WIN
    wchar_t username[256];
    DWORD size = 256;
    GetUserNameW(username, &size);
    return QString::fromWCharArray(username);
#else
    return qEnvironmentVariable("USER");
#endif
}

void Institution::logAction(const QString &user, const QString &action, const QString &details)
{
    QFile logFile("institution_audit.log");
    if(logFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&logFile);
        out << QDateTime::currentDateTime().toString("[yyyy-MM-dd HH:mm:ss] ")
            << "User: " << user << " | "
            << action << " - " << details << "\n";
        logFile.close();
    }
}
