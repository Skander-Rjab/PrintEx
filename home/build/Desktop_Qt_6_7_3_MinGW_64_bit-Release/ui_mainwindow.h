/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *topBarLayout;
    QLabel *logoLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *logoutButton;
    QGridLayout *gridLayout;
    QToolButton *examsButton;
    QToolButton *materialsButton;
    QToolButton *employeesButton;
    QToolButton *centersButton;
    QToolButton *institutionsButton;
    QToolButton *toolButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        topBarLayout = new QHBoxLayout();
        topBarLayout->setObjectName("topBarLayout");
        logoLabel = new QLabel(centralwidget);
        logoLabel->setObjectName("logoLabel");

        topBarLayout->addWidget(logoLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topBarLayout->addItem(horizontalSpacer);

        logoutButton = new QPushButton(centralwidget);
        logoutButton->setObjectName("logoutButton");

        topBarLayout->addWidget(logoutButton);


        verticalLayout->addLayout(topBarLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        examsButton = new QToolButton(centralwidget);
        examsButton->setObjectName("examsButton");
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../icons/exam.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        examsButton->setIcon(icon);
        examsButton->setIconSize(QSize(64, 64));
        examsButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout->addWidget(examsButton, 0, 0, 1, 1);

        materialsButton = new QToolButton(centralwidget);
        materialsButton->setObjectName("materialsButton");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../icons/printer.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        materialsButton->setIcon(icon1);
        materialsButton->setIconSize(QSize(64, 64));
        materialsButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout->addWidget(materialsButton, 0, 1, 1, 1);

        employeesButton = new QToolButton(centralwidget);
        employeesButton->setObjectName("employeesButton");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../../icons/employee.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        employeesButton->setIcon(icon2);
        employeesButton->setIconSize(QSize(64, 64));
        employeesButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout->addWidget(employeesButton, 0, 2, 1, 1);

        centersButton = new QToolButton(centralwidget);
        centersButton->setObjectName("centersButton");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../../icons/center.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        centersButton->setIcon(icon3);
        centersButton->setIconSize(QSize(64, 64));
        centersButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout->addWidget(centersButton, 1, 0, 1, 1);

        institutionsButton = new QToolButton(centralwidget);
        institutionsButton->setObjectName("institutionsButton");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../../icons/university.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        institutionsButton->setIcon(icon4);
        institutionsButton->setIconSize(QSize(64, 64));
        institutionsButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout->addWidget(institutionsButton, 1, 1, 1, 1);

        toolButton = new QToolButton(centralwidget);
        toolButton->setObjectName("toolButton");
        toolButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout->addWidget(toolButton, 1, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        logoLabel->setText(QCoreApplication::translate("MainWindow", "LOGO", nullptr));
        logoutButton->setText(QCoreApplication::translate("MainWindow", "Logout", nullptr));
        examsButton->setText(QCoreApplication::translate("MainWindow", "Exams", nullptr));
        materialsButton->setText(QCoreApplication::translate("MainWindow", "Materials", nullptr));
        employeesButton->setText(QCoreApplication::translate("MainWindow", "Employees", nullptr));
        centersButton->setText(QCoreApplication::translate("MainWindow", "Centers", nullptr));
        institutionsButton->setText(QCoreApplication::translate("MainWindow", "Institutions", nullptr));
        toolButton->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
