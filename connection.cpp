#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("MyDB");
    db.setUserName("omar");//inserer nom de l'utilisateur
    db.setPassword("omar123");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;

    return  test;
}
