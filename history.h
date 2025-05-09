#ifndef HISTORY_H
#define HISTORY_H

#include <QString>
#include <QSqlQueryModel>
#include <QDateTime>

class History
{
private:
    int id;
    QString action;
    QString dateAction;

public:
    // Constructors
    History();
    History(QString action);

    // Getters and setters
    int getId() const { return id; }
    QString getAction() const { return action; }
    QString getDateAction() const { return dateAction; }
   /// setters
    void setId(int id) { this->id = id; }
    void setAction(QString action) { this->action = action; }
    void setDateAction(QString dateAction) { this->dateAction = dateAction; }

    // CRUD operations
    bool addHistory();
    QSqlQueryModel* displayHistory();
    QSqlQueryModel* refreshHistory();
};

#endif // HISTORY_H
