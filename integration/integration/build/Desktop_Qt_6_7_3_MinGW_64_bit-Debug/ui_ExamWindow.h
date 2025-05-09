/********************************************************************************
** Form generated from reading UI file 'ExamWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXAMWINDOW_H
#define UI_EXAMWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExamWindow
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
    QPushButton *btnCalendar;
    QPushButton *btnMap;
    QPushButton *btnFireDetection;
    QLabel *label;
    QPushButton *btnBack;
    QWidget *formPage;
    QGroupBox *grpExamForm;
    QComboBox *cmbInstitution;
    QDateTimeEdit *dtScheduled;
    QComboBox *cmbDestination;
    QComboBox *cmbStatus;
    QLabel *lblPdfPath;
    QPushButton *btnSelectPdf;
    QPushButton *btnSubmitForm;
    QPushButton *btnCancelForm;
    QWidget *statsPage;
    QGraphicsView *chartView;
    QPushButton *btnBackStats;
    QWidget *calendarPage;
    QCalendarWidget *calendarWidget;
    QPushButton *btnBackCalendar;
    QWidget *mapPage;
    QGraphicsView *graphicsViewMap;
    QPushButton *btnBackMap;
    QWidget *firePage;
    QTableView *fireTableView;
    QPushButton *btnMuteAlarm;
    QPushButton *btnBackFire;

    void setupUi(QWidget *ExamWindow)
    {
        if (ExamWindow->objectName().isEmpty())
            ExamWindow->setObjectName("ExamWindow");
        ExamWindow->resize(1600, 900);
        ExamWindow->setMinimumSize(QSize(1600, 900));
        ExamWindow->setStyleSheet(QString::fromUtf8("\n"
"    ExamWindow {\n"
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
"        color: #2b2"
                        "d42;\n"
"    }\n"
"\n"
"    QTableView::item:selected {\n"
"        background-color: #5d6294;\n"
"    }\n"
"\n"
"    QTableView::item:!selected:alternate {\n"
"        background-color: #dadde0;\n"
"    }\n"
"\n"
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
"\n"
"    QCalendarWidget QWidget {\n"
"        background: white;\n"
"        color: #2b2d42;\n"
"    }\n"
"\n"
"    QCalendarWidget QToolButton {\n"
"        background: #6c757d;\n"
"        color: white;\n"
"    }\n"
"    QLabel {\n"
"        font: 13px 'Segoe UI';\n"
"        color: #495057;\n"
"    }\n"
"    QChartView {\n"
"        background: white;\n"
"        border: 1px solid #dee2e6;\n"
"        border-radius: 5px;\n"
""
                        "        margin: 5px;\n"
"    }\n"
"   "));
        stackedWidget = new QStackedWidget(ExamWindow);
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
        btnCalendar = new QPushButton(listPage);
        btnCalendar->setObjectName("btnCalendar");
        btnCalendar->setGeometry(QRect(1130, 290, 160, 40));
        btnMap = new QPushButton(listPage);
        btnMap->setObjectName("btnMap");
        btnMap->setGeometry(QRect(1130, 370, 160, 40));
        btnFireDetection = new QPushButton(listPage);
        btnFireDetection->setObjectName("btnFireDetection");
        btnFireDetection->setGeometry(QRect(920, 590, 200, 40));
        label = new QLabel(listPage);
        label->setObjectName("label");
        label->setGeometry(QRect(330, 34, 24, 24));
        label->setPixmap(QPixmap(QString::fromUtf8(":/maps/maps/search.png")));
        label->setScaledContents(true);
        btnBack = new QPushButton(listPage);
        btnBack->setObjectName("btnBack");
        btnBack->setGeometry(QRect(940, 30, 160, 41));
        stackedWidget->addWidget(listPage);
        formPage = new QWidget();
        formPage->setObjectName("formPage");
        grpExamForm = new QGroupBox(formPage);
        grpExamForm->setObjectName("grpExamForm");
        grpExamForm->setGeometry(QRect(200, 100, 1200, 600));
        cmbInstitution = new QComboBox(grpExamForm);
        cmbInstitution->setObjectName("cmbInstitution");
        cmbInstitution->setGeometry(QRect(30, 110, 300, 35));
        dtScheduled = new QDateTimeEdit(grpExamForm);
        dtScheduled->setObjectName("dtScheduled");
        dtScheduled->setGeometry(QRect(30, 170, 300, 35));
        dtScheduled->setCalendarPopup(true);
        cmbDestination = new QComboBox(grpExamForm);
        cmbDestination->setObjectName("cmbDestination");
        cmbDestination->setGeometry(QRect(30, 230, 300, 35));
        cmbStatus = new QComboBox(grpExamForm);
        cmbStatus->setObjectName("cmbStatus");
        cmbStatus->setGeometry(QRect(30, 290, 300, 35));
        lblPdfPath = new QLabel(grpExamForm);
        lblPdfPath->setObjectName("lblPdfPath");
        lblPdfPath->setGeometry(QRect(30, 350, 300, 35));
        btnSelectPdf = new QPushButton(grpExamForm);
        btnSelectPdf->setObjectName("btnSelectPdf");
        btnSelectPdf->setGeometry(QRect(340, 350, 160, 35));
        btnSubmitForm = new QPushButton(grpExamForm);
        btnSubmitForm->setObjectName("btnSubmitForm");
        btnSubmitForm->setGeometry(QRect(30, 400, 160, 40));
        btnCancelForm = new QPushButton(grpExamForm);
        btnCancelForm->setObjectName("btnCancelForm");
        btnCancelForm->setGeometry(QRect(170, 400, 160, 40));
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
        calendarPage = new QWidget();
        calendarPage->setObjectName("calendarPage");
        calendarPage->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        calendarWidget = new QCalendarWidget(calendarPage);
        calendarWidget->setObjectName("calendarWidget");
        calendarWidget->setGeometry(QRect(20, 20, 1100, 600));
        calendarWidget->setGridVisible(true);
        btnBackCalendar = new QPushButton(calendarPage);
        btnBackCalendar->setObjectName("btnBackCalendar");
        btnBackCalendar->setGeometry(QRect(20, 640, 160, 40));
        stackedWidget->addWidget(calendarPage);
        mapPage = new QWidget();
        mapPage->setObjectName("mapPage");
        graphicsViewMap = new QGraphicsView(mapPage);
        graphicsViewMap->setObjectName("graphicsViewMap");
        graphicsViewMap->setGeometry(QRect(20, 20, 1100, 700));
        btnBackMap = new QPushButton(mapPage);
        btnBackMap->setObjectName("btnBackMap");
        btnBackMap->setGeometry(QRect(20, 740, 160, 40));
        stackedWidget->addWidget(mapPage);
        firePage = new QWidget();
        firePage->setObjectName("firePage");
        fireTableView = new QTableView(firePage);
        fireTableView->setObjectName("fireTableView");
        fireTableView->setGeometry(QRect(20, 80, 1100, 500));
        btnMuteAlarm = new QPushButton(firePage);
        btnMuteAlarm->setObjectName("btnMuteAlarm");
        btnMuteAlarm->setGeometry(QRect(1130, 130, 160, 40));
        btnBackFire = new QPushButton(firePage);
        btnBackFire->setObjectName("btnBackFire");
        btnBackFire->setGeometry(QRect(1130, 210, 160, 40));
        stackedWidget->addWidget(firePage);

        retranslateUi(ExamWindow);

        QMetaObject::connectSlotsByName(ExamWindow);
    } // setupUi

    void retranslateUi(QWidget *ExamWindow)
    {
        ExamWindow->setWindowTitle(QCoreApplication::translate("ExamWindow", "Exam Management System", nullptr));
        btnCreate->setText(QCoreApplication::translate("ExamWindow", "\342\236\225 New Exam", nullptr));
        btnUpdate->setText(QCoreApplication::translate("ExamWindow", "\342\234\217\357\270\217 Edit", nullptr));
        btnDelete->setText(QCoreApplication::translate("ExamWindow", "\342\235\214 Delete", nullptr));
        btnPDF->setText(QCoreApplication::translate("ExamWindow", "\360\237\223\212 Generate PDF", nullptr));
        btnStats->setText(QCoreApplication::translate("ExamWindow", "\360\237\223\210 Statistics", nullptr));
        txtSearch->setPlaceholderText(QCoreApplication::translate("ExamWindow", "Search exams...", nullptr));
        btnCalendar->setText(QCoreApplication::translate("ExamWindow", "\360\237\227\223\357\270\217 Calendar", nullptr));
        btnMap->setText(QCoreApplication::translate("ExamWindow", "\360\237\227\272\357\270\217 Map View", nullptr));
        btnFireDetection->setText(QCoreApplication::translate("ExamWindow", "\360\237\247\257 Fire Detection", nullptr));
        label->setText(QString());
        btnBack->setText(QCoreApplication::translate("ExamWindow", "\360\237\217\240 home", nullptr));
        grpExamForm->setTitle(QCoreApplication::translate("ExamWindow", "Exam Details", nullptr));
        lblPdfPath->setText(QCoreApplication::translate("ExamWindow", "No file selected", nullptr));
        btnSelectPdf->setText(QCoreApplication::translate("ExamWindow", "Select PDF", nullptr));
        btnSubmitForm->setText(QCoreApplication::translate("ExamWindow", "\360\237\222\276 Save", nullptr));
        btnCancelForm->setText(QCoreApplication::translate("ExamWindow", "\342\235\214 Cancel", nullptr));
        btnBackStats->setText(QCoreApplication::translate("ExamWindow", "\342\206\220 Back to List", nullptr));
        btnBackCalendar->setText(QCoreApplication::translate("ExamWindow", "\342\206\220 Back to List", nullptr));
        btnBackMap->setText(QCoreApplication::translate("ExamWindow", "\342\206\220 Back to List", nullptr));
        btnMuteAlarm->setText(QCoreApplication::translate("ExamWindow", "\360\237\224\207 Mute", nullptr));
        btnBackFire->setText(QCoreApplication::translate("ExamWindow", "\342\206\220 Back to List", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExamWindow: public Ui_ExamWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXAMWINDOW_H
