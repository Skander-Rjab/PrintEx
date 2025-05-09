#ifndef CENTER_H
#define CENTER_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class center
{
    QString center_name, location, contact_details;
    int id, manager_id;

public:
    //Constructeurs
    center();
    center(int id, QString center_name, QString location, int manager_id, QString contact_details);

    //Getters
    int getCenterId(){return id;}
    QString getCenterName(){return center_name;}
    QString getLocation(){return location;}
    int getManagerId(){return manager_id;}
    QString getContactDetails(){return contact_details;}


    //Setters
    void setCenterId(int id)
    {
        this->id = id;
    }

    void setCenterName(QString name)
    {
        center_name = name;
    }

    void setLocation(QString loc)
    {
        location = loc;
    }

    void setManagerId(int id)
    {
        manager_id = id;
    }

    void setContactDetails(QString details)
    {
        contact_details = details;
    }

    //Basic features related to the center entity
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQuery afficherById(int);
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel* RechercheCenter(QString);
    QSqlQueryModel* afficherCenter(QString);
    
    // Manager-related functionality
    QSqlQueryModel* getAllManagerIds();
    QSqlQueryModel* filterByManagerId(int managerId);





};

#endif // CENTER_H
