#ifndef EMPLOYEEWINDOW_H
#define EMPLOYEEWINDOW_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QComboBox>
#include <QtCharts>
#include <QPrinter>

QT_BEGIN_NAMESPACE
namespace Ui {
class EmployeeWindow;
}
QT_END_NAMESPACE

class EmployeeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeeWindow(QWidget *parent = nullptr);
    ~EmployeeWindow();

    void showWindow() { this->show(); }
    void hideWindow() { this->hide(); }

signals:
    void backToMainRequested();

private slots:
    // Page navigation
    void showListPage();
    void showCreatePage();
    void showUpdatePage();
    void showStatsPage();

    // CRUD operations
    void createEmployee();
    void updateEmployee();
    void deleteEmployee();
    void handleFormSubmit();

    // UI interactions
    void employeeTableClicked(const QModelIndex &index);
    void searchEmployees(const QString &searchText);
    void sortTable(int column);

    // PDF and stats
    void generatePdfReport();
    void setupStatsCharts();

private:
    Ui::EmployeeWindow *ui;
    QSqlQueryModel *employeeModel;
    int currentEmployeeId;
    bool isCreatingNewEmployee;

    // Helper methods
    void initializeFormComponents();
    void loadRoles();
    void refreshEmployeeModel();
    bool validateForm();
    QString getRoleName(const QString &role);

    // Statistics data
    void setupRoleDistributionChart();
    void setupEmployeeCountChart();
};

#endif // EMPLOYEEWINDOW_H
