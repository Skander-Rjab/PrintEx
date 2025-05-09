#ifndef TWOFASERVICE_H
#define TWOFASERVICE_H

#include <QObject>
#include <QPair>
#include <QDateTime>
#include <QMap>
#include <QRandomGenerator>
#include <QDebug>
#include "smsservice.h"

class TwoFAService : public QObject
{
    Q_OBJECT

public:
    explicit TwoFAService(QObject *parent = nullptr);

    QString generateCode();  // Method to generate the verification code
    void sendCode(const QString &phoneNumber);  // Send the code
    bool verifyCode(const QString &phoneNumber, const QString &code);  // Verify the code

private:
    QMap<QString, QPair<QString, QDateTime>> codeStorage;  // Stores codes with timestamps
    SMSService smsService;  // Use SMS service to send code
};

#endif // TWOFASERVICE_H
