#include "Exam.h"

Exam::Exam()
    : m_examId(0),
    m_institutionId(0),
    m_employeeId(0),
    m_submissionDate(QDateTime::currentDateTime()),
    m_scheduledDeliveryDate(QDateTime::currentDateTime().addDays(1)),
    m_status("Scheduled"),
    m_destinationAddress("") {}

Exam::Exam(int examId, int institutionId, int employeeId, const QByteArray &examContent,
           const QDateTime &submissionDate, const QDateTime &scheduledDeliveryDate,
           const QString &status, const QString &destinationAddress)
    : m_examId(examId),
    m_institutionId(institutionId),
    m_employeeId(employeeId),
    m_examContent(examContent),
    m_submissionDate(submissionDate),
    m_scheduledDeliveryDate(scheduledDeliveryDate),
    m_status(status),
    m_destinationAddress(destinationAddress) {}

// Getters
int Exam::examId() const { return m_examId; }
int Exam::institutionId() const { return m_institutionId; }
int Exam::employeeId() const { return m_employeeId; }
QByteArray Exam::examContent() const { return m_examContent; }
QDateTime Exam::submissionDate() const { return m_submissionDate; }
QDateTime Exam::scheduledDeliveryDate() const { return m_scheduledDeliveryDate; }
QString Exam::status() const { return m_status; }
QString Exam::destinationAddress() const { return m_destinationAddress; }

// Setters
void Exam::setExamId(int examId) { m_examId = examId; }
void Exam::setInstitutionId(int institutionId) { m_institutionId = institutionId; }
void Exam::setEmployeeId(int employeeId) { m_employeeId = employeeId; }
void Exam::setExamContent(const QByteArray &examContent) { m_examContent = examContent; }
void Exam::setSubmissionDate(const QDateTime &submissionDate) { m_submissionDate = submissionDate; }
void Exam::setScheduledDeliveryDate(const QDateTime &scheduledDeliveryDate) {
    m_scheduledDeliveryDate = scheduledDeliveryDate;
}
void Exam::setStatus(const QString &status) { m_status = status; }
void Exam::setDestinationAddress(const QString &destinationAddress) {
    m_destinationAddress = destinationAddress;
}

const QStringList Exam::tunisianGovernorates() {
    return {
        "Ariana", "Béja", "Ben Arous", "Bizerte",
        "Gabès", "Gafsa", "Jendouba", "Kairouan",
        "Kasserine", "Kébili", "Kef", "Mahdia",
        "Manouba", "Médenine", "Monastir", "Nabeul",
        "Sfax", "Sidi Bouzid", "Siliana", "Sousse",
        "Tataouine", "Tozeur", "Tunis", "Zaghouan"
    };
}

bool Exam::validate() const {
    // Date validation
    if(m_scheduledDeliveryDate <= m_submissionDate) {
        qDebug() << "Error: Scheduled date must be after submission date";
        return false;
    }

    // Content validation
    if(m_examContent.isEmpty()) {
        qDebug() << "Error: Exam content cannot be empty";
        return false;
    }

    // Destination validation
    if(!tunisianGovernorates().contains(m_destinationAddress, Qt::CaseInsensitive)) {
        qDebug() << "Error: Invalid Tunisian governorate:" << m_destinationAddress;
        return false;
    }

    // Status validation
    const QStringList validStatuses = {"Scheduled", "In Progress", "Completed", "Canceled"};
    if(!validStatuses.contains(m_status, Qt::CaseInsensitive)) {
        qDebug() << "Error: Invalid status:" << m_status;
        return false;
    }

    return true;
}

int Exam::generateNewExamId() {
    QSqlQuery query;
    if(query.exec("SELECT NVL(MAX(EXAM_ID), 0) FROM QT_EXAMS")) {
        if(query.next())
            return query.value(0).toInt() + 1;
    } else {
        qDebug() << "ID Generation Error:" << query.lastError().text();
    }
    return 1;
}

bool Exam::create() {
    if(!validate()) return false;

    QSqlQuery query;
    query.prepare(
        "INSERT INTO QT_EXAMS ("
        "EXAM_ID, INSTITUTION_ID, EMPLOYEE_ID, EXAM_CONTENT, "
        "SUBMISSION_DATE, SCHEDULED_DELIVERY_DATE, STATUS, DESTINATION_ADDRESS"
        ") VALUES ("
        ":exam_id, :institution_id, :employee_id, :exam_content, "
        "TO_DATE(:submission_date, 'YYYY-MM-DD HH24:MI'), "
        "TO_DATE(:scheduled_date, 'YYYY-MM-DD HH24:MI'), "
        ":status, :destination)"
        );

    query.bindValue(":exam_id", generateNewExamId());
    query.bindValue(":institution_id", m_institutionId);
    query.bindValue(":employee_id", m_employeeId);
    query.bindValue(":exam_content", m_examContent);
    query.bindValue(":submission_date", m_submissionDate.toString("yyyy-MM-dd HH:mm"));
    query.bindValue(":scheduled_date", m_scheduledDeliveryDate.toString("yyyy-MM-dd HH:mm"));
    query.bindValue(":status", m_status);
    query.bindValue(":destination", m_destinationAddress);

    if(!query.exec()) {
        qDebug() << "Create Error:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* Exam::read() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(
        "SELECT EXAM_ID, INSTITUTION_ID, EMPLOYEE_ID, "
        "TO_CHAR(SUBMISSION_DATE, 'YYYY-MM-DD HH24:MI') AS SUBMISSION, "
        "TO_CHAR(SCHEDULED_DELIVERY_DATE, 'YYYY-MM-DD HH24:MI') AS SCHEDULED, "
        "STATUS, DESTINATION_ADDRESS "
        "FROM QT_EXAMS"
        );
    return model;
}

bool Exam::update() {
    if(!validate()) return false;

    QSqlQuery query;
    query.prepare(
        "UPDATE QT_EXAMS SET "
        "INSTITUTION_ID = :institution_id, "
        "EMPLOYEE_ID = :employee_id, "
        "EXAM_CONTENT = :exam_content, "
        "SUBMISSION_DATE = TO_DATE(:submission_date, 'YYYY-MM-DD HH24:MI'), "
        "SCHEDULED_DELIVERY_DATE = TO_DATE(:scheduled_date, 'YYYY-MM-DD HH24:MI'), "
        "STATUS = :status, "
        "DESTINATION_ADDRESS = :destination "
        "WHERE EXAM_ID = :exam_id"
        );

    query.bindValue(":exam_id", m_examId);
    query.bindValue(":institution_id", m_institutionId);
    query.bindValue(":employee_id", m_employeeId);
    query.bindValue(":exam_content", m_examContent);
    query.bindValue(":submission_date", m_submissionDate.toString("yyyy-MM-dd HH:mm"));
    query.bindValue(":scheduled_date", m_scheduledDeliveryDate.toString("yyyy-MM-dd HH:mm"));
    query.bindValue(":status", m_status);
    query.bindValue(":destination", m_destinationAddress);

    if(!query.exec()) {
        qDebug() << "Update Error:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Exam::remove() {
    QSqlQuery query;
    query.prepare("DELETE FROM QT_EXAMS WHERE EXAM_ID = :exam_id");
    query.bindValue(":exam_id", m_examId);

    if(!query.exec()) {
        qDebug() << "Delete Error:" << query.lastError().text();
        return false;
    }
    return true;
}
