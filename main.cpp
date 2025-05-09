#include <QApplication>
#include <QMessageBox>
#include <QProcessEnvironment>  // For environment variable debugging
#include <QDir>                  // For current directory checking
#include "mainwindow.h"
#include "connection.h"
#include "envloader.h"  // Make sure this file contains loadEnv()
#include <QSslSocket>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Debugging: print current working directory
    qDebug() << "Current working directory: " << QDir::currentPath();

    QCoreApplication::setOrganizationName("TwoFAService");
    QCoreApplication::setApplicationName("UserManagementApp");

    // Load environment variables
    loadEnv();
    qDebug() << "SSL supported:" << QSslSocket::supportsSsl();
    qDebug() << "SSL version:" << QSslSocket::sslLibraryBuildVersionString();

    // Debugging: print the loaded environment variables to confirm
    QString sendGridApiKey = QProcessEnvironment::systemEnvironment().value("SENDGRID_API_KEY");
    QString sendGridSenderEmail = QProcessEnvironment::systemEnvironment().value("SENDGRID_SENDER_EMAIL");

    if (sendGridApiKey.isEmpty()) {
        qWarning() << "❗ SENDGRID_API_KEY is missing in the environment!";
    }
    if (sendGridSenderEmail.isEmpty()) {
        qWarning() << "❗ SENDGRID_SENDER_EMAIL is missing in the environment!";
    }

    // Try to connect to the database
    QSqlDatabase db = Connection::createConnection();
    if (!db.isOpen()) {
        QMessageBox::critical(nullptr, "Database Connection Failed",
                              "The application could not connect to the database. It will now close.");
        return -1; // Exit the app if the DB isn't open
    }

    // Create the main window and show it
    MainWindow w;
    w.show();

    return a.exec();
}
