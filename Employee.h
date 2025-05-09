#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QByteArray>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class Employee {
public:
    // Constructor
    Employee();
    Employee(int employeeId, const QString &username, const QString &hashedPassword,
             const QString &firstName, const QString &lastName,
             const QString &role, const QString &phoneNumber);

    // Getters & Setters
    int employeeId() const;
    void setEmployeeId(int employeeId);

    QString username() const;
    void setUsername(const QString &username);

    QString hashedPassword() const;
    void setHashedPassword(const QString &hashedPassword);

    QString firstName() const;
    void setFirstName(const QString &firstName);

    QString lastName() const;
    void setLastName(const QString &lastName);

    QString role() const;
    void setRole(const QString &role);

    QString phoneNumber() const;
    void setPhoneNumber(const QString &phoneNumber);

    // CRUD Operations
    bool create();
    static QSqlQueryModel* read();
    bool update();
    bool remove();

    // ID Generation
    static int generateNewEmployeeId();

    // Role options
    static const QStringList roleOptions();

private:
    // Validation
    bool validate() const;

    // Member Variables
    int m_employeeId;
    QString m_username;
    QString m_hashedPassword;
    QString m_firstName;
    QString m_lastName;
    QString m_role;
    QString m_phoneNumber;
};

#endif // EMPLOYEE_H
