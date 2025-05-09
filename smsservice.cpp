#include "smsservice.h"
#include <QDebug>
#include <QUrlQuery>

SMSService::SMSService(QObject *parent)
    : QObject(parent),
    networkManager(new QNetworkAccessManager(this))
{
    // Load from environment variables (ensure they are set in .env or system environment)
    accountSid = QString::fromUtf8(qgetenv("TWILIO_SID"));
    authToken = QString::fromUtf8(qgetenv("TWILIO_AUTH_TOKEN"));
    twilioNumber = QString::fromUtf8(qgetenv("TWILIO_PHONE"));

    if (accountSid.isEmpty() || authToken.isEmpty() || twilioNumber.isEmpty()) {
        qWarning() << "❗ Missing TWILIO credentials in environment!";
    }
}

void SMSService::sendSMS(const QString &phoneNumber, const QString &message)
{
    QString apiUrl = QString("https://api.twilio.com/2010-04-01/Accounts/%1/Messages.json").arg(accountSid);
    QUrl url(apiUrl);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery params;
    params.addQueryItem("To", phoneNumber);
    params.addQueryItem("From", twilioNumber);
    params.addQueryItem("Body", message);
    QByteArray postData = params.toString(QUrl::FullyEncoded).toUtf8();

    // Set basic auth header
    QString credentials = accountSid + ":" + authToken;
    QByteArray authHeader = "Basic " + credentials.toUtf8().toBase64();
    request.setRawHeader("Authorization", authHeader);

    QNetworkReply *reply = networkManager->post(request, postData);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() { onSmsSent(reply); });
}

void SMSService::onSmsSent(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "✅ SMS sent successfully!";
    } else {
        qDebug() << "❌ Failed to send SMS:" << reply->errorString();
        qDebug() << "↪️ Response:" << reply->readAll();
    }
    reply->deleteLater();
}
