#include "Employee.h"

Employee::Employee()
    : m_employeeId(0),
    m_username(""),
    m_hashedPassword(""),
    m_firstName(""),
    m_lastName(""),
    m_role(""),
    m_phoneNumber("") {}

Employee::Employee(int employeeId, const QString &username, const QString &hashedPassword,
                   const QString &firstName, const QString &lastName,
                   const QString &role, const QString &phoneNumber)
    : m_employeeId(employeeId),
    m_username(username),
    m_hashedPassword(hashedPassword),
    m_firstName(firstName),
    m_lastName(lastName),
    m_role(role),
    m_phoneNumber(phoneNumber) {}

// Getters
int Employee::employeeId() const { return m_employeeId; }
QString Employee::username() const { return m_username; }
QString Employee::hashedPassword() const { return m_hashedPassword; }
QString Employee::firstName() const { return m_firstName; }
QString Employee::lastName() const { return m_lastName; }
QString Employee::role() const { return m_role; }
QString Employee::phoneNumber() const { return m_phoneNumber; }

// Setters
void Employee::setEmployeeId(int employeeId) { m_employeeId = employeeId; }
void Employee::setUsername(const QString &username) { m_username = username; }
void Employee::setHashedPassword(const QString &hashedPassword) { m_hashedPassword = hashedPassword; }
void Employee::setFirstName(const QString &firstName) { m_firstName = firstName; }
void Employee::setLastName(const QString &lastName) { m_lastName = lastName; }
void Employee::setRole(const QString &role) { m_role = role; }
void Employee::setPhoneNumber(const QString &phoneNumber) { m_phoneNumber = phoneNumber; }

const QStringList Employee::roleOptions() {
    return {"Admin", "Manager", "Employee", "Driver"};
}

bool Employee::validate() const {
    if (m_username.isEmpty()) {
        qDebug() << "Error: Username cannot be empty";
        return false;
    }

    if (m_hashedPassword.isEmpty()) {
        qDebug() << "Error: Password cannot be empty";
        return false;
    }

    if (m_firstName.isEmpty()) {
        qDebug() << "Error: First name cannot be empty";
        return false;
    }

    if (m_lastName.isEmpty()) {
        qDebug() << "Error: Last name cannot be empty";
        return false;
    }

    if (!roleOptions().contains(m_role)) {
        qDebug() << "Error: Invalid role:" << m_role;
        return false;
    }

    return true;
}

int Employee::generateNewEmployeeId() {
    QSqlQuery query;
    if(query.exec("SELECT NVL(MAX(EMPLOYEE_ID), 0) FROM QT_EMPLOYEES")) {
        if(query.next())
            return query.value(0).toInt() + 1;
    } else {
        qDebug() << "ID Generation Error:" << query.lastError().text();
    }
    return 1;
}

bool Employee::create() {
    if(!validate()) return false;

    QSqlQuery query;
    query.prepare(
        "INSERT INTO QT_EMPLOYEES ("
        "EMPLOYEE_ID, USERNAME, HASHED_PASSWORD, "
        "FIRST_NAME, LAST_NAME, ROLE, PHONE_NUMBER"
        ") VALUES ("
        ":employee_id, :username, :hashed_password, "
        ":first_name, :last_name, :role, :phone_number)"
        );

    query.bindValue(":employee_id", generateNewEmployeeId());
    query.bindValue(":username", m_username);
    query.bindValue(":hashed_password", m_hashedPassword);
    query.bindValue(":first_name", m_firstName);
    query.bindValue(":last_name", m_lastName);
    query.bindValue(":role", m_role);
    query.bindValue(":phone_number", m_phoneNumber);

    if(!query.exec()) {
        qDebug() << "Create Error:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* Employee::read() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(
        "SELECT EMPLOYEE_ID, USERNAME, FIRST_NAME, LAST_NAME, "
        "ROLE, PHONE_NUMBER "
        "FROM QT_EMPLOYEES"
        );
    return model;
}

bool Employee::update() {
    if(!validate()) return false;

    QSqlQuery query;
    query.prepare(
        "UPDATE QT_EMPLOYEES SET "
        "USERNAME = :username, "
        "HASHED_PASSWORD = :hashed_password, "
        "FIRST_NAME = :first_name, "
        "LAST_NAME = :last_name, "
        "ROLE = :role, "
        "PHONE_NUMBER = :phone_number "
        "WHERE EMPLOYEE_ID = :employee_id"
        );

    query.bindValue(":employee_id", m_employeeId);
    query.bindValue(":username", m_username);
    query.bindValue(":hashed_password", m_hashedPassword);
    query.bindValue(":first_name", m_firstName);
    query.bindValue(":last_name", m_lastName);
    query.bindValue(":role", m_role);
    query.bindValue(":phone_number", m_phoneNumber);

    if(!query.exec()) {
        qDebug() << "Update Error:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Employee::remove() {
    QSqlQuery query;
    query.prepare("DELETE FROM QT_EMPLOYEES WHERE EMPLOYEE_ID = :employee_id");
    query.bindValue(":employee_id", m_employeeId);

    if(!query.exec()) {
        qDebug() << "Delete Error:" << query.lastError().text();
        return false;
    }
    return true;
}
