#include "center.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSet>
#include <QSqlRecord>

center::center()
{
    id = 0;
    center_name = "";
    location = "";
    manager_id = 0;
    contact_details = "";
}

center::center(int id, QString center_name, QString location, int manager_id, QString contact_details)
{
    this->id = id;
    this->center_name = center_name;
    this->location = location;
    this->manager_id = manager_id;
    this->contact_details = contact_details;
}

bool center::ajouter()
{
    QSqlQuery query;
    // Since ID is auto-increment, we don't include it in the INSERT
    query.prepare("INSERT INTO SYSTEM.CENTER (CENTER_NAME, LOCATION, MANAGER_ID, CONTACT_DETAILS) "
                 "VALUES (:center_name, :location, :manager_id, :contact_details)");
    
    query.bindValue(":center_name", center_name);
    query.bindValue(":location", location);
    query.bindValue(":manager_id", manager_id);
    query.bindValue(":contact_details", contact_details);

    return query.exec();
}

QSqlQueryModel* center::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM SYSTEM.CENTER ORDER BY CENTER_NAME");
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Location"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Contact Details"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Manager ID"));
    
    return model;
}

QSqlQuery center::afficherById(int searchId)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM SYSTEM.CENTER WHERE ID = :id");
    query.bindValue(":id", searchId);
    query.exec();
    return query;
}

bool center::supprimer(int searchId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM SYSTEM.CENTER WHERE ID = :id");
    query.bindValue(":id", searchId);
    return query.exec();
}

bool center::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE SYSTEM.CENTER SET CENTER_NAME=:center_name, LOCATION=:location, "
                 "MANAGER_ID=:manager_id, CONTACT_DETAILS=:contact_details WHERE ID=:id");
    
    query.bindValue(":id", id);
    query.bindValue(":center_name", center_name);
    query.bindValue(":location", location);
    query.bindValue(":manager_id", manager_id);
    query.bindValue(":contact_details", contact_details);

    return query.exec();
}

QSqlQueryModel* center::RechercheCenter(QString search)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM SYSTEM.CENTER WHERE "
                   "LOWER(CENTER_NAME) LIKE '%" + search.toLower() + "%' OR "
                   "LOWER(LOCATION) LIKE '%" + search.toLower() + "%' OR "
                   "LOWER(CONTACT_DETAILS) LIKE '%" + search.toLower() + "%'");
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Location"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Contact Details"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Manager ID"));
    
    return model;
}

QSqlQueryModel* center::afficherCenter(QString sort)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query = "SELECT * FROM SYSTEM.CENTER";
    
    if (sort == "A-Z")
        query += " ORDER BY NLSSORT(CENTER_NAME, 'NLS_SORT=BINARY') ASC";
    else if (sort == "Z-A")
        query += " ORDER BY NLSSORT(CENTER_NAME, 'NLS_SORT=BINARY') DESC";
        
    model->setQuery(query);
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Location"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Contact Details"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Manager ID"));
    
    return model;
}

QSqlQueryModel* center::getAllManagerIds()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    // Query to get distinct manager IDs, ordered numerically
    QString queryStr = "SELECT DISTINCT MANAGER_ID FROM SYSTEM.CENTER ORDER BY MANAGER_ID ASC";
    model->setQuery(queryStr);
    
    // Debug information
    qDebug() << "Manager ID query: " << queryStr;
    qDebug() << "Query error: " << model->lastError().text();
    qDebug() << "Results: " << model->rowCount() << " rows";
    
    // Log the actual results
    for (int i = 0; i < model->rowCount(); ++i) {
        qDebug() << "Manager ID at row " << i << ": " << model->data(model->index(i, 0)).toString();
    }
    
    return model;
}

QSqlQueryModel* center::filterByManagerId(int managerId)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    // Query to filter centers by manager ID
    QString query = QString("SELECT * FROM SYSTEM.CENTER WHERE MANAGER_ID = %1").arg(managerId);
    model->setQuery(query);
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Location"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Contact Details"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Manager ID"));
    
    return model;
}
