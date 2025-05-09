#ifndef SMSSERVICE_H
#define SMSSERVICE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>

class SMSService : public QObject
{
    Q_OBJECT

public:
    explicit SMSService(QObject *parent = nullptr);
    void sendSMS(const QString &phoneNumber, const QString &message);

private slots:
    void onSmsSent(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;
    QString accountSid;
    QString authToken;
    QString twilioNumber;
};

#endif // SMSSERVICE_H
