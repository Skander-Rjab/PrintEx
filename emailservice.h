#ifndef EMAILSERVICE_H
#define EMAILSERVICE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class EmailService : public QObject
{
    Q_OBJECT

public:
    explicit EmailService(QObject *parent = nullptr);
    void sendEmail(const QString &to, const QString &subject, const QString &body);

private slots:
    void onEmailSent(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;
    QString sendGridApiKey;
    QString fromEmail;
};

#endif // EMAILSERVICE_H
