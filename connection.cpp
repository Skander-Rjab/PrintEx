#include "connection.h"
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

static QSqlDatabase db;

QSqlDatabase Connection::createConnection() {
    if (db.isValid() && db.isOpen()) {
        return db;  // Return the already open connection
    }

    db = QSqlDatabase::addDatabase("QODBC"); // Or other database types (SQLite, etc.)
    db.setDatabaseName("qt");  // replace with your DSN
    db.setUserName("nada123");
    db.setPassword("nada123");

    if (!db.open()) {
        qDebug() << "Failed to connect to database:" << db.lastError().text();
        QMessageBox::critical(nullptr, "Database Error", "Could not connect to the database.\n" + db.lastError().text());
        return QSqlDatabase();  // Return an invalid QSqlDatabase if connection failed
    }

    return db;
}

QSqlDatabase Connection::getDatabase() {
    if (!db.isOpen()) {
        createConnection();  // Ensure the connection is open
    }
    return db;
}

void Connection::closeConnection() {
    if (db.isOpen()) {
        db.close();
    }
}
