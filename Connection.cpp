#include "Connection.h"

Connection* Connection::instance = nullptr;

Connection::Connection() {

}

Connection* Connection::getInstance() {
    if (!instance)
        instance = new Connection();
    return instance;
}

bool Connection::createConnection() {
    m_database = QSqlDatabase::addDatabase("QODBC");

    //QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");


    m_database.setDatabaseName("QT_PROJECT");

    m_database.setUserName("skan");
    m_database.setPassword("123");

    if (!m_database.open()) {
        qDebug() << "Database Connection Error:" << m_database.lastError().text();
    } else {
        qDebug() << "Connected to Oracle 11 XE!";
    }



    return true;
}

void Connection::closeConnection() {
    if(m_database.isOpen())
        m_database.close();
}

QSqlDatabase Connection::database() const {
    return m_database;
}


