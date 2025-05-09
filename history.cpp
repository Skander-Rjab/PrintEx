#include "history.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDateTime>
#include <QSqlError>
#include <QDebug>

// Default constructor
History::History()
{
    id = 0;
    action = "";
    dateAction = "";
}

// Constructor with parameters
History::History(QString action)
{
    this->action = action;
    // Set the current date and time as the action date
    this->dateAction = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
}

// Add a new history record to the database
bool History::addHistory()
{
    QSqlQuery query;
    
    // Prepare SQL query to insert history record
    query.prepare("INSERT INTO SYSTEM.HISTORY (ACTION, DATEACTION) "
                  "VALUES (:action, :dateaction)");
    
    // Bind values
    query.bindValue(":action", action);
    query.bindValue(":dateaction", dateAction);
    
    // Execute the query and return success/failure
    if(!query.exec()) {
        qDebug() << "Error adding history: " << query.lastError().text();
        return false;
    }
    
    return true;
}

// Get a model of all history records for display
QSqlQueryModel* History::displayHistory()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    // Set query to select all history records, ordered by ID (most recent first)
    model->setQuery("SELECT ID, ACTION, DATEACTION FROM SYSTEM.HISTORY ORDER BY ID DESC");
    
    // Set headers
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Action"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date/Time"));
    
    return model;
}

// Refresh the history display (same as displayHistory for now, but could be extended)
QSqlQueryModel* History::refreshHistory()
{
    return displayHistory();
}
