#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QString>
#include <QSqlError>
#include <QDebug>

class Connection {
public:
    static Connection* getInstance();
    bool createConnection();
    void closeConnection();
    QSqlDatabase database() const;

private:
    Connection();
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    static Connection* instance;
    QSqlDatabase m_database;
};

#endif // CONNECTION_H
