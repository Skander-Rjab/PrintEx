#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ExamWindow.h"
#include "InstitutionWidget.h"
#include "EmployeeWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showExamWindow();  // Renamed for clarity
    void showInstitutionWidget();
    void returnToMainWindow();
    void showEmployeeWindow();


private:
    Ui::MainWindow *ui;
    ExamWindow *examWindow;
    InstitutionWidget *institutionWidget;
    EmployeeWindow *employeeWindow;

};
#endif // MAINWINDOW_H
