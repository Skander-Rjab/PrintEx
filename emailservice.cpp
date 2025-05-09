#include "emailservice.h"
#include <QDebug>
#include <QProcessEnvironment>

EmailService::EmailService(QObject *parent) : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &EmailService::onEmailSent);

    // Load from environment variables
    sendGridApiKey = QString::fromUtf8(qgetenv("SENDGRID_API_KEY"));
    fromEmail = QString::fromUtf8(qgetenv("SENDGRID_SENDER_EMAIL"));

    // ✅ Add debug prints
    qDebug() << "📥 SENDGRID_API_KEY loaded:" << sendGridApiKey.left(10) << "...";
    qDebug() << "📥 SENDGRID_SENDER_EMAIL loaded:" << fromEmail;

    if (sendGridApiKey.isEmpty() || fromEmail.isEmpty()) {
        qWarning() << "❗ Missing SENDGRID_API_KEY or SENDGRID_SENDER_EMAIL in environment.";
    }
}

void EmailService::sendEmail(const QString &to, const QString &subject, const QString &body)
{
    QUrl url("https://api.sendgrid.com/v3/mail/send");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + sendGridApiKey).toUtf8());

    QJsonObject email;
    QJsonObject personalizations;
    QJsonArray toArray;
    QJsonObject toObj;
    toObj["email"] = to;
    toArray.append(toObj);
    personalizations["to"] = toArray;
    email["personalizations"] = QJsonArray{ personalizations };

    QJsonObject from;
    from["email"] = fromEmail;
    email["from"] = from;
    email["subject"] = subject;

    QJsonObject contentObj;
    contentObj["type"] = "text/plain";
    contentObj["value"] = body;
    email["content"] = QJsonArray{ contentObj };

    QJsonDocument doc(email);
    QByteArray jsonData = doc.toJson();

    networkManager->post(request, jsonData);
}

void EmailService::onEmailSent(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "✅ Email sent successfully!";
    } else {
        qDebug() << "❌ Failed to send email:" << reply->errorString();
        qDebug() << "↪️ Response:" << reply->readAll();
    }
    reply->deleteLater();
}
