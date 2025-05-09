#include "MainWindow.h"
#include <QFile>
#include <QApplication>
#include <QLocale>
#include <QMessageBox>
#include <QSqlError>
#include "LoginDialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog loginDialog;
    if (loginDialog.exec() != QDialog::Accepted) {
        return 0; // Exit if login failed or was canceled
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("QT_PROJECT");
    db.setUserName("skan");
    db.setPassword("123");

    if(!db.open()){
        QMessageBox::critical(nullptr, "Database Connection Error",
                              "Failed to connect to database: " + db.lastError().text());
        return -1;
    }

    MainWindow w;

    QFile styles("C:/Users/skand/Desktop/qtc/styles/amoled.qss");
    styles.open(QFile::ReadOnly);

    QString stylesheet = QLatin1String(styles.readAll());
    a.setStyleSheet(stylesheet);




    w.show();
    return a.exec();
}
