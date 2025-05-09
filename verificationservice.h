#ifndef VERIFICATIONSERVICE_H
#define VERIFICATIONSERVICE_H

#include <QObject>
#include "emailservice.h"
#include "twofaservice.h"

class VerificationService : public QObject
{
    Q_OBJECT

public:
    explicit VerificationService(QObject *parent = nullptr);
    void sendVerification(const QString &email, const QString &phoneNumber);
    bool verifyCode(const QString &phoneNumber, const QString &code);

private:
    TwoFAService twoFAService;  // Explicitly initialized in constructor
    EmailService emailService;
};

#endif // VERIFICATIONSERVICE_H
