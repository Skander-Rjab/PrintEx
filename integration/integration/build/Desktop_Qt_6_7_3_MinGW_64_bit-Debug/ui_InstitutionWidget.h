/********************************************************************************
** Form generated from reading UI file 'InstitutionWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTITUTIONWIDGET_H
#define UI_INSTITUTIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InstitutionWidget
{
public:
    QTableView *tableView;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QPushButton *btnUpdate;
    QLineEdit *txtSearch;
    QPushButton *btnHome;
    QPushButton *btnExport;
    QPushButton *btnStats;
    QGroupBox *grpInstitutionForm;
    QLineEdit *txtName;
    QLineEdit *txtContact;
    QLineEdit *txtAddress;
    QPushButton *btnSubmit;
    QPushButton *btnCancel;

    void setupUi(QWidget *InstitutionWidget)
    {
        if (InstitutionWidget->objectName().isEmpty())
            InstitutionWidget->setObjectName("InstitutionWidget");
        InstitutionWidget->resize(1600, 900);
        InstitutionWidget->setMinimumSize(QSize(1600, 900));
        InstitutionWidget->setStyleSheet(QString::fromUtf8("\n"
"    InstitutionWidget {\n"
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
"        colo"
                        "r: #2b2d42;\n"
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
"    QLineEdit, QComboBox, QDateTimeEdit {\n"
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
"   "));
        tableView = new QTableView(InstitutionWidget);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(20, 80, 1100, 500));
        btnAdd = new QPushButton(InstitutionWidget);
        btnAdd->setObjectName("btnAdd");
        btnAdd->setGeometry(QRect(30, 590, 160, 40));
        btnDelete = new QPushButton(InstitutionWidget);
        btnDelete->setObjectName("btnDelete");
        btnDelete->setGeometry(QRect(200, 590, 160, 40));
        btnUpdate = new QPushButton(InstitutionWidget);
        btnUpdate->setObjectName("btnUpdate");
        btnUpdate->setGeometry(QRect(370, 590, 160, 40));
        txtSearch = new QLineEdit(InstitutionWidget);
        txtSearch->setObjectName("txtSearch");
        txtSearch->setGeometry(QRect(20, 30, 300, 35));
        btnHome = new QPushButton(InstitutionWidget);
        btnHome->setObjectName("btnHome");
        btnHome->setGeometry(QRect(940, 30, 160, 41));
        btnExport = new QPushButton(InstitutionWidget);
        btnExport->setObjectName("btnExport");
        btnExport->setGeometry(QRect(1130, 130, 160, 40));
        btnStats = new QPushButton(InstitutionWidget);
        btnStats->setObjectName("btnStats");
        btnStats->setGeometry(QRect(1130, 210, 160, 40));
        grpInstitutionForm = new QGroupBox(InstitutionWidget);
        grpInstitutionForm->setObjectName("grpInstitutionForm");
        grpInstitutionForm->setGeometry(QRect(710, 390, 1200, 600));
        txtName = new QLineEdit(grpInstitutionForm);
        txtName->setObjectName("txtName");
        txtName->setGeometry(QRect(30, 50, 300, 35));
        txtContact = new QLineEdit(grpInstitutionForm);
        txtContact->setObjectName("txtContact");
        txtContact->setGeometry(QRect(30, 100, 300, 35));
        txtAddress = new QLineEdit(grpInstitutionForm);
        txtAddress->setObjectName("txtAddress");
        txtAddress->setGeometry(QRect(30, 150, 300, 35));
        btnSubmit = new QPushButton(grpInstitutionForm);
        btnSubmit->setObjectName("btnSubmit");
        btnSubmit->setGeometry(QRect(30, 200, 160, 40));
        btnCancel = new QPushButton(grpInstitutionForm);
        btnCancel->setObjectName("btnCancel");
        btnCancel->setGeometry(QRect(200, 200, 160, 40));

        retranslateUi(InstitutionWidget);

        QMetaObject::connectSlotsByName(InstitutionWidget);
    } // setupUi

    void retranslateUi(QWidget *InstitutionWidget)
    {
        InstitutionWidget->setWindowTitle(QCoreApplication::translate("InstitutionWidget", "Institution Management", nullptr));
        btnAdd->setText(QCoreApplication::translate("InstitutionWidget", "\342\236\225 Add Institution", nullptr));
        btnDelete->setText(QCoreApplication::translate("InstitutionWidget", "\342\235\214 Delete", nullptr));
        btnUpdate->setText(QCoreApplication::translate("InstitutionWidget", "\342\234\217\357\270\217 Update", nullptr));
        txtSearch->setPlaceholderText(QCoreApplication::translate("InstitutionWidget", "Search institutions...", nullptr));
        btnHome->setText(QCoreApplication::translate("InstitutionWidget", "\360\237\217\240 Home", nullptr));
        btnExport->setText(QCoreApplication::translate("InstitutionWidget", "\360\237\223\204 Export PDF", nullptr));
        btnStats->setText(QCoreApplication::translate("InstitutionWidget", "\360\237\223\210 Statistics", nullptr));
        grpInstitutionForm->setTitle(QCoreApplication::translate("InstitutionWidget", "Institution Details", nullptr));
        txtName->setPlaceholderText(QCoreApplication::translate("InstitutionWidget", "Institution Name", nullptr));
        txtContact->setPlaceholderText(QCoreApplication::translate("InstitutionWidget", "Contact Info", nullptr));
        txtAddress->setPlaceholderText(QCoreApplication::translate("InstitutionWidget", "Email Address", nullptr));
        btnSubmit->setText(QCoreApplication::translate("InstitutionWidget", "\360\237\222\276 Save", nullptr));
        btnCancel->setText(QCoreApplication::translate("InstitutionWidget", "\342\235\214 Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InstitutionWidget: public Ui_InstitutionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTITUTIONWIDGET_H
