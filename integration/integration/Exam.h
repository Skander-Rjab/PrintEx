#ifndef EXAM_H
#define EXAM_H

#include <QString>
#include <QDateTime>
#include <QByteArray>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class Exam {
public:
    // Constructor
    Exam();
    Exam(int examId, int institutionId, int employeeId, const QByteArray &examContent,
         const QDateTime &submissionDate, const QDateTime &scheduledDeliveryDate,
         const QString &status, const QString &destinationAddress);

    // Getters & Setters
    int examId() const;
    void setExamId(int examId);

    int institutionId() const;
    void setInstitutionId(int institutionId);

    int employeeId() const;
    void setEmployeeId(int employeeId);

    QByteArray examContent() const;
    void setExamContent(const QByteArray &examContent);

    QDateTime submissionDate() const;
    void setSubmissionDate(const QDateTime &submissionDate);

    QDateTime scheduledDeliveryDate() const;
    void setScheduledDeliveryDate(const QDateTime &scheduledDeliveryDate);

    QString status() const;
    void setStatus(const QString &status);

    QString destinationAddress() const;
    void setDestinationAddress(const QString &destinationAddress);

    // CRUD Operations
    bool create();
    static QSqlQueryModel* read();
    bool update();
    bool remove();

    // ID Generation
    static int generateNewExamId();


    // Tunisian Governorates
    static const QStringList tunisianGovernorates();

private:
    // Validation
    bool validate() const;


    // Member Variables
    int m_examId;
    int m_institutionId;
    int m_employeeId;
    QByteArray m_examContent;
    QDateTime m_submissionDate;
    QDateTime m_scheduledDeliveryDate;
    QString m_status;
    QString m_destinationAddress;
};

#endif // EXAM_H
