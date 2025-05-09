/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
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
    QToolButton *toolButton;
    QToolButton *institutionsButton;
    QToolButton *centersButton;
    QToolButton *employeesButton;
    QToolButton *materialsButton;
    QToolButton *examsButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(995, 622);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        topBarLayout = new QHBoxLayout();
        topBarLayout->setObjectName("topBarLayout");
        logoLabel = new QLabel(centralwidget);
        logoLabel->setObjectName("logoLabel");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(logoLabel->sizePolicy().hasHeightForWidth());
        logoLabel->setSizePolicy(sizePolicy);
        logoLabel->setMinimumSize(QSize(200, 200));
        logoLabel->setFrameShape(QFrame::Shape::NoFrame);
        logoLabel->setPixmap(QPixmap(QString::fromUtf8(":/image/logo.png")));
        logoLabel->setScaledContents(true);
        logoLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        topBarLayout->addWidget(logoLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topBarLayout->addItem(horizontalSpacer);

        logoutButton = new QPushButton(centralwidget);
        logoutButton->setObjectName("logoutButton");
        sizePolicy.setHeightForWidth(logoutButton->sizePolicy().hasHeightForWidth());
        logoutButton->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        logoutButton->setPalette(palette);
        QFont font;
        font.setPointSize(20);
        font.setWeight(QFont::ExtraBold);
        font.setItalic(true);
        font.setUnderline(false);
        font.setStrikeOut(false);
        font.setKerning(true);
        logoutButton->setFont(font);
        logoutButton->setCheckable(false);
        logoutButton->setFlat(true);

        topBarLayout->addWidget(logoutButton);

        topBarLayout->setStretch(0, 1);
        topBarLayout->setStretch(1, 15);
        topBarLayout->setStretch(2, 5);

        verticalLayout->addLayout(topBarLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(20);
        gridLayout->setVerticalSpacing(30);
        toolButton = new QToolButton(centralwidget);
        toolButton->setObjectName("toolButton");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/about.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButton->setIcon(icon);
        toolButton->setIconSize(QSize(128, 128));
        toolButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout->addWidget(toolButton, 1, 2, 1, 1);

        institutionsButton = new QToolButton(centralwidget);
        institutionsButton->setObjectName("institutionsButton");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/university.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        institutionsButton->setIcon(icon1);
        institutionsButton->setIconSize(QSize(128, 128));
        institutionsButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout->addWidget(institutionsButton, 1, 1, 1, 1);

        centersButton = new QToolButton(centralwidget);
        centersButton->setObjectName("centersButton");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/center.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        centersButton->setIcon(icon2);
        centersButton->setIconSize(QSize(128, 128));
        centersButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout->addWidget(centersButton, 1, 0, 1, 1);

        employeesButton = new QToolButton(centralwidget);
        employeesButton->setObjectName("employeesButton");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/employee.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        employeesButton->setIcon(icon3);
        employeesButton->setIconSize(QSize(128, 128));
        employeesButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout->addWidget(employeesButton, 0, 2, 1, 1);

        materialsButton = new QToolButton(centralwidget);
        materialsButton->setObjectName("materialsButton");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/image/printer.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        materialsButton->setIcon(icon4);
        materialsButton->setIconSize(QSize(128, 128));
        materialsButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout->addWidget(materialsButton, 0, 1, 1, 1);

        examsButton = new QToolButton(centralwidget);
        examsButton->setObjectName("examsButton");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/image/exam.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        examsButton->setIcon(icon5);
        examsButton->setIconSize(QSize(128, 128));
        examsButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout->addWidget(examsButton, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 995, 21));
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
        logoLabel->setText(QString());
        logoutButton->setText(QCoreApplication::translate("MainWindow", "Logout", nullptr));
        toolButton->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        institutionsButton->setText(QCoreApplication::translate("MainWindow", "Institutions", nullptr));
        centersButton->setText(QCoreApplication::translate("MainWindow", "Centers", nullptr));
        employeesButton->setText(QCoreApplication::translate("MainWindow", "Employees", nullptr));
        materialsButton->setText(QCoreApplication::translate("MainWindow", "Materials", nullptr));
        examsButton->setText(QCoreApplication::translate("MainWindow", "Exams", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
