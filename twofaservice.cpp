#include "twofaservice.h"

TwoFAService::TwoFAService(QObject *parent)
    : QObject(parent)
{
}

QString TwoFAService::generateCode()
{
    int code = QRandomGenerator::global()->bounded(100000, 999999);  // Generate a 6-digit code
    return QString::number(code);
}

void TwoFAService::sendCode(const QString &phoneNumber)
{
    QString code = generateCode();  // Generate the verification code

    // Rate limit logic (prevent sending too frequently)
    if (codeStorage.contains(phoneNumber)) {
        QDateTime lastSent = codeStorage[phoneNumber].second.addSecs(-300);
        if (lastSent.secsTo(QDateTime::currentDateTime()) < 60) {
            qDebug() << "Rate limit: Code request too soon for" << phoneNumber;
            return;
        }
    }

    codeStorage[phoneNumber] = qMakePair(code, QDateTime::currentDateTime().addSecs(300));  // Store code and timestamp
    QString message = "Your verification code is: " + code;
    smsService.sendSMS(phoneNumber, message);  // Send the code via SMS
}

bool TwoFAService::verifyCode(const QString &phoneNumber, const QString &code)
{
    if (!codeStorage.contains(phoneNumber))
        return false;

    QPair<QString, QDateTime> stored = codeStorage.value(phoneNumber);
    if (stored.second < QDateTime::currentDateTime())  // Check if the code has expired
        return false;

    return stored.first == code;  // Verify the code
}
