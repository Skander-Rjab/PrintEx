/********************************************************************************
** Form generated from reading UI file 'EmployeeWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLOYEEWINDOW_H
#define UI_EMPLOYEEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmployeeWindow
{
public:
    QStackedWidget *stackedWidget;
    QWidget *listPage;
    QTableView *tableView;
    QPushButton *btnCreate;
    QPushButton *btnUpdate;
    QPushButton *btnDelete;
    QPushButton *btnPDF;
    QPushButton *btnStats;
    QLineEdit *txtSearch;
    QPushButton *btnBack;
    QWidget *formPage;
    QGroupBox *grpEmployeeForm;
    QLineEdit *txtUsername;
    QLineEdit *txtPassword;
    QLineEdit *txtFirstName;
    QLineEdit *txtLastName;
    QComboBox *cmbRole;
    QLineEdit *txtPhone;
    QPushButton *btnSubmitForm;
    QPushButton *btnCancelForm;
    QWidget *statsPage;
    QGraphicsView *chartView;
    QPushButton *btnBackStats;

    void setupUi(QWidget *EmployeeWindow)
    {
        if (EmployeeWindow->objectName().isEmpty())
            EmployeeWindow->setObjectName("EmployeeWindow");
        EmployeeWindow->resize(1600, 900);
        EmployeeWindow->setMinimumSize(QSize(1600, 900));
        EmployeeWindow->setStyleSheet(QString::fromUtf8("\n"
"    EmployeeWindow {\n"
"        background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"            stop:0 #f8f9fa, stop:1 #e9ecef);\n"
"    }\n"
"    QGroupBox {\n"
"        border: 2px solid #dee2e6;\n"
"        border-radius: 8px;\n"
"        margin-top: 20px;\n"
"        padding-top: 15px;\n"
"        font: bold 14px 'Segoe UI';\n"
"        color: #2b2d42;\n"
"        background: white;\n"
"    }\n"
"    QPushButton {\n"
"        background-color: #6c757d;\n"
"        color: white;\n"
"        border: none;\n"
"        padding: 10px 20px;\n"
"        border-radius: 5px;\n"
"        font: 13px 'Segoe UI';\n"
"        min-width: 120px;\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: #5a6268;\n"
"    }\n"
"    QPushButton:pressed {\n"
"        background-color: #545b62;\n"
"    }\n"
"    QTableView {\n"
"        background: white;\n"
"        border: 2px solid #dee2e6;\n"
"        selection-background-color: #cce3ff;\n"
"        alternate-background-color:#dadde0;\n"
"        color: "
                        "#2b2d42;\n"
"    }\n"
"    QTableView::item:selected {\n"
"        background-color: #5d6294;\n"
"    }\n"
"    QTableView::item:!selected:alternate {\n"
"        background-color: #dadde0;\n"
"    }\n"
"    QHeaderView::section {\n"
"        background: #6c757d;\n"
"        color: white;\n"
"        padding: 8px;\n"
"        border: none;\n"
"    }\n"
"    QLineEdit, QComboBox {\n"
"        background-color: black;\n"
"        border: 2px solid #ced4da;\n"
"        border-radius: 4px;\n"
"        padding: 6px;\n"
"        font: 13px 'Segoe UI';\n"
"    }\n"
"    QLabel {\n"
"        font: 13px 'Segoe UI';\n"
"        color: #495057;\n"
"    }\n"
"    QChartView {\n"
"        background: white;\n"
"        border: 1px solid #dee2e6;\n"
"        border-radius: 5px;\n"
"        margin: 5px;\n"
"    }\n"
"   "));
        stackedWidget = new QStackedWidget(EmployeeWindow);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 30, 1560, 860));
        listPage = new QWidget();
        listPage->setObjectName("listPage");
        tableView = new QTableView(listPage);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(20, 80, 1100, 500));
        btnCreate = new QPushButton(listPage);
        btnCreate->setObjectName("btnCreate");
        btnCreate->setGeometry(QRect(30, 590, 160, 40));
        btnUpdate = new QPushButton(listPage);
        btnUpdate->setObjectName("btnUpdate");
        btnUpdate->setGeometry(QRect(200, 590, 160, 40));
        btnDelete = new QPushButton(listPage);
        btnDelete->setObjectName("btnDelete");
        btnDelete->setGeometry(QRect(370, 590, 160, 40));
        btnPDF = new QPushButton(listPage);
        btnPDF->setObjectName("btnPDF");
        btnPDF->setGeometry(QRect(1130, 130, 160, 40));
        btnStats = new QPushButton(listPage);
        btnStats->setObjectName("btnStats");
        btnStats->setGeometry(QRect(1130, 210, 160, 40));
        txtSearch = new QLineEdit(listPage);
        txtSearch->setObjectName("txtSearch");
        txtSearch->setGeometry(QRect(20, 30, 300, 35));
        btnBack = new QPushButton(listPage);
        btnBack->setObjectName("btnBack");
        btnBack->setGeometry(QRect(940, 30, 160, 41));
        stackedWidget->addWidget(listPage);
        formPage = new QWidget();
        formPage->setObjectName("formPage");
        grpEmployeeForm = new QGroupBox(formPage);
        grpEmployeeForm->setObjectName("grpEmployeeForm");
        grpEmployeeForm->setGeometry(QRect(200, 100, 1200, 600));
        txtUsername = new QLineEdit(grpEmployeeForm);
        txtUsername->setObjectName("txtUsername");
        txtUsername->setGeometry(QRect(30, 110, 300, 35));
        txtPassword = new QLineEdit(grpEmployeeForm);
        txtPassword->setObjectName("txtPassword");
        txtPassword->setGeometry(QRect(30, 170, 300, 35));
        txtPassword->setEchoMode(QLineEdit::Password);
        txtFirstName = new QLineEdit(grpEmployeeForm);
        txtFirstName->setObjectName("txtFirstName");
        txtFirstName->setGeometry(QRect(30, 230, 300, 35));
        txtLastName = new QLineEdit(grpEmployeeForm);
        txtLastName->setObjectName("txtLastName");
        txtLastName->setGeometry(QRect(30, 290, 300, 35));
        cmbRole = new QComboBox(grpEmployeeForm);
        cmbRole->setObjectName("cmbRole");
        cmbRole->setGeometry(QRect(30, 350, 300, 35));
        txtPhone = new QLineEdit(grpEmployeeForm);
        txtPhone->setObjectName("txtPhone");
        txtPhone->setGeometry(QRect(30, 410, 300, 35));
        btnSubmitForm = new QPushButton(grpEmployeeForm);
        btnSubmitForm->setObjectName("btnSubmitForm");
        btnSubmitForm->setGeometry(QRect(30, 470, 160, 40));
        btnCancelForm = new QPushButton(grpEmployeeForm);
        btnCancelForm->setObjectName("btnCancelForm");
        btnCancelForm->setGeometry(QRect(170, 470, 160, 40));
        stackedWidget->addWidget(formPage);
        statsPage = new QWidget();
        statsPage->setObjectName("statsPage");
        chartView = new QGraphicsView(statsPage);
        chartView->setObjectName("chartView");
        chartView->setGeometry(QRect(100, 100, 800, 500));
        btnBackStats = new QPushButton(statsPage);
        btnBackStats->setObjectName("btnBackStats");
        btnBackStats->setGeometry(QRect(380, 610, 160, 40));
        btnBackStats->setStyleSheet(QString::fromUtf8("\n"
"                      background-color: #6c757d;\n"
"                      color: white;\n"
"                      border-radius: 5px;\n"
"                  "));
        stackedWidget->addWidget(statsPage);

        retranslateUi(EmployeeWindow);

        QMetaObject::connectSlotsByName(EmployeeWindow);
    } // setupUi

    void retranslateUi(QWidget *EmployeeWindow)
    {
        EmployeeWindow->setWindowTitle(QCoreApplication::translate("EmployeeWindow", "Employee Management System", nullptr));
        btnCreate->setText(QCoreApplication::translate("EmployeeWindow", "\342\236\225 New Employee", nullptr));
        btnUpdate->setText(QCoreApplication::translate("EmployeeWindow", "\342\234\217\357\270\217 Edit", nullptr));
        btnDelete->setText(QCoreApplication::translate("EmployeeWindow", "\342\235\214 Delete", nullptr));
        btnPDF->setText(QCoreApplication::translate("EmployeeWindow", "\360\237\223\212 Generate PDF", nullptr));
        btnStats->setText(QCoreApplication::translate("EmployeeWindow", "\360\237\223\210 Statistics", nullptr));
        txtSearch->setPlaceholderText(QCoreApplication::translate("EmployeeWindow", "Search employees...", nullptr));
        btnBack->setText(QCoreApplication::translate("EmployeeWindow", "\360\237\217\240 home", nullptr));
        grpEmployeeForm->setTitle(QCoreApplication::translate("EmployeeWindow", "Employee Details", nullptr));
        txtUsername->setPlaceholderText(QCoreApplication::translate("EmployeeWindow", "Username", nullptr));
        txtPassword->setPlaceholderText(QCoreApplication::translate("EmployeeWindow", "Password", nullptr));
        txtFirstName->setPlaceholderText(QCoreApplication::translate("EmployeeWindow", "First Name", nullptr));
        txtLastName->setPlaceholderText(QCoreApplication::translate("EmployeeWindow", "Last Name", nullptr));
        cmbRole->setPlaceholderText(QCoreApplication::translate("EmployeeWindow", "Select Role", nullptr));
        txtPhone->setPlaceholderText(QCoreApplication::translate("EmployeeWindow", "Phone Number", nullptr));
        btnSubmitForm->setText(QCoreApplication::translate("EmployeeWindow", "\360\237\222\276 Save", nullptr));
        btnCancelForm->setText(QCoreApplication::translate("EmployeeWindow", "\342\235\214 Cancel", nullptr));
        btnBackStats->setText(QCoreApplication::translate("EmployeeWindow", "\342\206\220 Back to List", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmployeeWindow: public Ui_EmployeeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLOYEEWINDOW_H
