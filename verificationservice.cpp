#include "verificationservice.h"

VerificationService::VerificationService(QObject *parent)
    : QObject(parent),
    twoFAService()  // Explicitly initialize twoFAService
{
}

void VerificationService::sendVerification(const QString &email, const QString &phoneNumber)
{
    QString code = twoFAService.generateCode();  // Generate the 2FA code
    QString message = "Your verification code is: " + code;

    emailService.sendEmail(email, "Verification Code", message);  // Send email
    twoFAService.sendCode(phoneNumber);  // Send SMS or any other way of sending the code
}

bool VerificationService::verifyCode(const QString &phoneNumber, const QString &code)
{
    return twoFAService.verifyCode(phoneNumber, code);  // Verify the code
}
