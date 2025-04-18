#include <QApplication>
#include <QMessageBox>
#include "MainWindow.h"
#include <QFile>
#include <QApplication>
#include <QLocale>
#include <QSqlError>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    QFile styles("C:/Users/skand/Desktop/qtc/styles/amoled.qss");
    styles.open(QFile::ReadOnly);

    QString stylesheet = QLatin1String(styles.readAll());
    app.setStyleSheet(stylesheet);

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
    w.show();

    return app.exec();
}
