#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , examWindow(new ExamWindow())  // Don't parent it to avoid hiding issues
    ,institutionWidget(new InstitutionWidget(this))
    , employeeWindow(new EmployeeWindow())
{
    ui->setupUi(this);

    // Connect signals
    connect(ui->examsButton, &QToolButton::clicked,
            this, &MainWindow::showExamWindow);

    connect(examWindow, &ExamWindow::backToMainRequested,
            this, [this]() {
                examWindow->hide();
                this->show();
            });



    connect(ui->institutionsButton, &QToolButton::clicked,
            this, &MainWindow::showInstitutionWidget);

    connect(institutionWidget, &InstitutionWidget::backToMainRequested,
            this, &MainWindow::returnToMainWindow);



    connect(ui->employeesButton, &QToolButton::clicked,
                       this, &MainWindow::showEmployeeWindow);

            // when EmployeeWindow emits backToMainRequested, hide it and show main:
            connect(employeeWindow, &EmployeeWindow::backToMainRequested,
                             this, [this]() {
                                     employeeWindow->hide();
                                     this->show();
                                });
}



void MainWindow::showEmployeeWindow()
    {
        this->hide();
        employeeWindow->show();
        employeeWindow->raise();
        employeeWindow->activateWindow();
    }



void MainWindow::showExamWindow()
{
    this->hide();
    examWindow->show();
    examWindow->raise();
    examWindow->activateWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete examWindow;
    delete employeeWindow;
}


void MainWindow::showInstitutionWidget()
{
    institutionWidget->show();
    institutionWidget->refreshTable();  // Refresh data when shown

    this->hide();  // Hide main window after showing institution widget
}

void MainWindow::returnToMainWindow()
{
    this->show();
    institutionWidget->hide();

}
