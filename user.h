#ifndef USER_H
#define USER_H

#include <QString>
#include <QDateTime>

class User {
private:
    QString UserId;
    QString firstname;
    QString lastname;
    QString password;
    QString phone;
    QString role;
    QString email;
    QDateTime dateTime;

public:
    User();  // Default constructor (for dynamic creation, etc.)
    User(const QString &firstname, const QString &lastname, const QString &password,
         const QString &phone, const QString &role, const QString &email, const QDateTime &dateTime);


    // Getters and setters
    QString getUserId() const;
    void setUserId(const QString &id);

    QString getFirstname() const;
    void setFirstname(const QString &firstname);

    QString getLastname() const;
    void setLastname(const QString &lastname);

    QString getPassword() const;
    void setPassword(const QString &password);

    QString getPhone() const;
    void setPhone(const QString &phone);

    QString getRole() const;
    void setRole(const QString &role);

    QString getemail() const;  // Getter for email
    void setemail(const QString &email);


    QDateTime getDateTime() const;
    void setDateTime(const QDateTime &dateTime);

    bool saveToDatabase();
    bool updateToDatabase();
    bool deleteFromDatabase();
    bool searchUserById(const QString &userId);
    bool existsInDatabase();
    bool searchUserByPhone(const QString &phoneNumber, bool &found);
    bool signUp(); // New user registration
    bool login(const QString &firstName, const QString &lastName, const QString &inputPassword);
    bool trackActivity(const QString &activityType); // Log tracking
    bool checkIfEmailExists(const QString &email, const QString &userId);
    bool saveChanges();
};

#endif // USER_H
