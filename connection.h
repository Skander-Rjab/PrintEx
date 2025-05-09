#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>

class Connection {
public:
    static QSqlDatabase createConnection();
    static QSqlDatabase getDatabase();
    static void closeConnection();
};

#endif // CONNECTION_H
