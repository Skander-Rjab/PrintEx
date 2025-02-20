#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "home_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QFile styles("C:/Users/skand/Desktop/qtc/styles/Incrypt.qss");
    styles.open(QFile::ReadOnly);

    QString stylesheet = QLatin1String(styles.readAll());
    a.setStyleSheet(stylesheet);

    MainWindow w;
    w.show();
    return a.exec();
}
