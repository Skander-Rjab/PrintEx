#include "EmployeeWindow.h"
#include "ui_EmployeeWindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QPrinter>
#include <QPainter>
#include <QHelpEvent>
#include <QToolTip>
#include <QTextCharFormat>
#include <QTableView>
#include <QtCharts>
#include <QRegularExpressionValidator>
#include "Employee.h"


EmployeeWindow::EmployeeWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EmployeeWindow)
    , employeeModel(new QSqlQueryModel(this))
    , currentEmployeeId(0)
{
    ui->setupUi(this);

    initializeFormComponents();

    // Table view setup
    ui->tableView->setModel(employeeModel);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setAlternatingRowColors(true);

    // Connect signals
    connect(ui->tableView->horizontalHeader(), &QHeaderView::sectionClicked,
            this, &EmployeeWindow::sortTable);
    connect(ui->btnCreate, &QPushButton::clicked, this, &EmployeeWindow::showCreatePage);
    connect(ui->btnUpdate, &QPushButton::clicked, this, &EmployeeWindow::showUpdatePage);
    connect(ui->btnDelete, &QPushButton::clicked, this, &EmployeeWindow::deleteEmployee);
    connect(ui->btnPDF, &QPushButton::clicked, this, &EmployeeWindow::generatePdfReport);
    connect(ui->btnStats, &QPushButton::clicked, this, &EmployeeWindow::showStatsPage);
    connect(ui->tableView, &QTableView::clicked, this, &EmployeeWindow::employeeTableClicked);
    connect(ui->btnSubmitForm, &QPushButton::clicked, this, &EmployeeWindow::handleFormSubmit);
    connect(ui->btnCancelForm, &QPushButton::clicked, this, &EmployeeWindow::showListPage);
    connect(ui->btnBackStats, &QPushButton::clicked, this, &EmployeeWindow::showListPage);
    connect(ui->txtSearch, &QLineEdit::textChanged, this, &EmployeeWindow::searchEmployees);
    connect(ui->btnBack, &QPushButton::clicked, this, &EmployeeWindow::backToMainRequested);

    refreshEmployeeModel();
}

EmployeeWindow::~EmployeeWindow()
{
    delete ui;
}


void EmployeeWindow::initializeFormComponents()
{
    loadRoles();

    // Set up form validators if needed
    ui->txtPhone->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{8,15}"), this));
}

void EmployeeWindow::loadRoles()
{
    ui->cmbRole->clear();
    ui->cmbRole->addItems(Employee::roleOptions());
}

void EmployeeWindow::refreshEmployeeModel()
{
    QString queryStr =
        "SELECT EMPLOYEE_ID, USERNAME, FIRST_NAME || ' ' || LAST_NAME AS FULL_NAME, "
        "ROLE, PHONE_NUMBER "
        "FROM QT_EMPLOYEES";

    employeeModel->setQuery(queryStr);

    // Set headers
    employeeModel->setHeaderData(0, Qt::Horizontal, "Employee ID");
    employeeModel->setHeaderData(1, Qt::Horizontal, "Username");
    employeeModel->setHeaderData(2, Qt::Horizontal, "Full Name");
    employeeModel->setHeaderData(3, Qt::Horizontal, "Role");
    employeeModel->setHeaderData(4, Qt::Horizontal, "Phone Number");

    ui->tableView->resizeColumnsToContents();
}

bool EmployeeWindow::validateForm()
{
    if (ui->txtUsername->text().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Username cannot be empty");
        return false;
    }

    if (ui->txtPassword->text().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Password cannot be empty");
        return false;
    }

    if (ui->txtFirstName->text().isEmpty()) {
        QMessageBox::warning(this, "Validation", "First name cannot be empty");
        return false;
    }

    if (ui->txtLastName->text().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Last name cannot be empty");
        return false;
    }

    if (ui->cmbRole->currentIndex() == -1) {
        QMessageBox::warning(this, "Validation", "Please select a role");
        return false;
    }

    if (ui->txtPhone->text().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Phone number cannot be empty");
        return false;
    }

    return true;
}



void EmployeeWindow::showListPage()
{
    refreshEmployeeModel();
    ui->stackedWidget->setCurrentWidget(ui->listPage);
}

void EmployeeWindow::showCreatePage()
{
    isCreatingNewEmployee = true;
    ui->stackedWidget->setCurrentWidget(ui->formPage);

    // Clear form
    ui->txtUsername->clear();
    ui->txtPassword->clear();
    ui->txtFirstName->clear();
    ui->txtLastName->clear();
    ui->cmbRole->setCurrentIndex(0);
    ui->txtPhone->clear();
}

void EmployeeWindow::showUpdatePage()
{
    isCreatingNewEmployee = false;
    if (currentEmployeeId == 0) return;

    QSqlQuery query;
    query.prepare("SELECT USERNAME, HASHED_PASSWORD, FIRST_NAME, LAST_NAME, ROLE, PHONE_NUMBER "
                  "FROM QT_EMPLOYEES WHERE EMPLOYEE_ID = ?");
    query.addBindValue(currentEmployeeId);

    if (query.exec() && query.next()) {
        ui->txtUsername->setText(query.value(0).toString());
        ui->txtPassword->setText(query.value(1).toString());
        ui->txtFirstName->setText(query.value(2).toString());
        ui->txtLastName->setText(query.value(3).toString());
        ui->cmbRole->setCurrentText(query.value(4).toString());
        ui->txtPhone->setText(query.value(5).toString());
    }

    ui->stackedWidget->setCurrentWidget(ui->formPage);
}

void EmployeeWindow::handleFormSubmit()
{
    if (isCreatingNewEmployee) {
        createEmployee();
    } else {
        updateEmployee();
    }
}

void EmployeeWindow::createEmployee()
{
    if (!validateForm()) return;

    Employee employee;
    employee.setEmployeeId(Employee::generateNewEmployeeId());
    employee.setUsername(ui->txtUsername->text());
    employee.setHashedPassword(ui->txtPassword->text()); // In real app, hash this
    employee.setFirstName(ui->txtFirstName->text());
    employee.setLastName(ui->txtLastName->text());
    employee.setRole(ui->cmbRole->currentText());
    employee.setPhoneNumber(ui->txtPhone->text());

    if (employee.create()) {
        QMessageBox::information(this, "Success", "Employee created successfully");
        showListPage();
    } else {
        QMessageBox::critical(this, "Error", "Failed to create employee");
    }
}

void EmployeeWindow::updateEmployee()
{
    if (currentEmployeeId == 0) return;
    if (!validateForm()) return;

    Employee employee;
    employee.setEmployeeId(currentEmployeeId);
    employee.setUsername(ui->txtUsername->text());
    employee.setHashedPassword(ui->txtPassword->text()); // In real app, hash this
    employee.setFirstName(ui->txtFirstName->text());
    employee.setLastName(ui->txtLastName->text());
    employee.setRole(ui->cmbRole->currentText());
    employee.setPhoneNumber(ui->txtPhone->text());

    if (employee.update()) {
        QMessageBox::information(this, "Success", "Employee updated successfully");
        showListPage();
    } else {
        QMessageBox::critical(this, "Error", "Failed to update employee");
    }
}

void EmployeeWindow::deleteEmployee()
{
    if (currentEmployeeId == 0) return;

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirm Delete",
        QString("Delete employee #%1?").arg(currentEmployeeId),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        Employee employee;
        employee.setEmployeeId(currentEmployeeId);
        if (employee.remove()) {
            refreshEmployeeModel();
            currentEmployeeId = 0;
        }
    }
}



void EmployeeWindow::employeeTableClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        currentEmployeeId = employeeModel->index(index.row(), 0).data().toInt();
    }
}

void EmployeeWindow::searchEmployees(const QString &searchText)
{
    QString baseQuery =
        "SELECT EMPLOYEE_ID, USERNAME, FIRST_NAME || ' ' || LAST_NAME AS FULL_NAME, "
        "ROLE, PHONE_NUMBER "
        "FROM QT_EMPLOYEES ";

    if (!searchText.isEmpty()) {
        baseQuery += "WHERE UPPER(EMPLOYEE_ID) LIKE UPPER(:search) "
                     "OR UPPER(USERNAME) LIKE UPPER(:search) "
                     "OR UPPER(FIRST_NAME || ' ' || LAST_NAME) LIKE UPPER(:search) "
                     "OR UPPER(ROLE) LIKE UPPER(:search) "
                     "OR PHONE_NUMBER LIKE :search";
    }

    QSqlQuery query;
    query.prepare(baseQuery);

    if (!searchText.isEmpty()) {
        query.bindValue(":search", "%" + searchText + "%");
    }

    if (!query.exec()) {
        QString errorMsg = "Failed to execute search query:\n" + query.lastError().text();
        qDebug() << errorMsg;
        QMessageBox::critical(this, "Search Error", errorMsg);
        return;
    }

    employeeModel->setQuery(std::move(query));

    if (employeeModel->lastError().isValid()) {
        QString errorMsg = "Failed to update model:\n" + employeeModel->lastError().text();
        qDebug() << errorMsg;
        QMessageBox::critical(this, "Model Error", errorMsg);
        return;
    }

    ui->tableView->resizeColumnsToContents();
}

void EmployeeWindow::sortTable(int column)
{
    static QMap<int, Qt::SortOrder> sortStates;

    QString headerText = employeeModel->headerData(column, Qt::Horizontal).toString().toUpper();

    QMap<QString, QString> columnMapping = {
        {"EMPLOYEE ID", "EMPLOYEE_ID"},
        {"USERNAME", "USERNAME"},
        {"FULL NAME", "LAST_NAME"}, // Sort by last name for full name
        {"ROLE", "ROLE"},
        {"PHONE NUMBER", "PHONE_NUMBER"}
    };

    QString orderBy = columnMapping.value(headerText, "EMPLOYEE_ID");
    Qt::SortOrder order = (sortStates[column] == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;
    sortStates[column] = order;

    QString queryStr = employeeModel->query().executedQuery();
    static const QRegularExpression orderRegex("ORDER BY.*$", QRegularExpression::CaseInsensitiveOption);
    queryStr.replace(orderRegex, "");

    queryStr += " ORDER BY " + orderBy + (order == Qt::DescendingOrder ? " DESC" : " ASC");
    employeeModel->setQuery(std::move(queryStr));
}



void EmployeeWindow::generatePdfReport()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", QDir::homePath(), "PDF Files (*.pdf)");
    if (fileName.isEmpty())
        return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

    QPainter painter;
    if (!painter.begin(&printer)) {
        QMessageBox::critical(this, "Error", "Failed to create PDF");
        return;
    }

    // Setup colors and fonts
    QColor headerColor(109, 18, 19);
    QColor titleColor(85, 0, 0);
    QFont titleFont("Arial", 18, QFont::Bold);
    QFont headerFont("Arial", 8, QFont::Bold);
    QFont contentFont("Arial", 9);

    const int lineHeight = painter.fontMetrics().height();
    const int rowHeight = lineHeight * 1.8;
    const int availableWidth = printer.width() - 30;

    // Column widths (adjust percentages as needed)
    const double colPercentages[] = {0.10, 0.20, 0.25, 0.25, 0.20};
    int colWidths[5];
    for (int i = 0; i < 5; i++) {
        colWidths[i] = availableWidth * colPercentages[i];
    }

    int pageNumber = 1;
    int yPos = 50;

    // Draw title
    painter.setPen(titleColor);
    painter.setFont(titleFont);
    painter.drawText(QRect(15, yPos, availableWidth, lineHeight*2),
                     Qt::AlignLeft | Qt::AlignVCenter, "Employee Management System Report");

    yPos += lineHeight * 3;

    // Draw header row
    painter.setPen(Qt::white);
    painter.setBrush(headerColor);
    painter.drawRoundedRect(15, yPos - 5, availableWidth, rowHeight + 10, 5, 5);

    QStringList headers = {"Employee ID", "Username", "Full Name", "Role", "Phone Number"};
    int xPos = 15;
    painter.setFont(headerFont);
    QFontMetrics fm(headerFont);
    for (int col = 0; col < 5; col++) {
        QString headerText = fm.elidedText(headers[col], Qt::ElideRight, colWidths[col] - 4);
        painter.drawText(QRect(xPos, yPos, colWidths[col], rowHeight),
                         Qt::AlignCenter, headerText);
        xPos += colWidths[col];
    }
    yPos += rowHeight + 10;

    // Draw data rows
    painter.setFont(contentFont);
    for (int row = 0; row < employeeModel->rowCount(); row++) {
        if (yPos + rowHeight > printer.height() - 30) {
            // New page
            printer.newPage();
            yPos = 50;
            pageNumber++;

            // Redraw header on new page
            painter.setPen(Qt::white);
            painter.setBrush(headerColor);
            painter.drawRoundedRect(15, yPos - 5, availableWidth, rowHeight + 10, 5, 5);

            xPos = 15;
            painter.setFont(headerFont);
            for (int col = 0; col < 5; col++) {
                QString headerText = fm.elidedText(headers[col], Qt::ElideRight, colWidths[col] - 4);
                painter.drawText(QRect(xPos, yPos, colWidths[col], rowHeight),
                                 Qt::AlignCenter, headerText);
                xPos += colWidths[col];
            }
            yPos += rowHeight + 10;
        }

        // Alternate row colors
        painter.setBrush(row % 2 ? Qt::white : QColor(240, 240, 240));

        xPos = 15;
        for (int col = 0; col < 5; col++) {
            QString data = employeeModel->index(row, col).data().toString();

            // Draw cell border
            painter.drawRect(xPos, yPos, colWidths[col], rowHeight);

            // Draw cell content
            QTextOption option;
            option.setAlignment(Qt::AlignCenter);
            option.setWrapMode(QTextOption::WordWrap);

            painter.setPen(Qt::black);
            painter.drawText(QRectF(xPos + 2, yPos + 2, colWidths[col] - 4, rowHeight - 4),
                             data, option);

            xPos += colWidths[col];
        }
        yPos += rowHeight;
    }

    painter.end();
    QMessageBox::information(this, "Success", "PDF report generated successfully");
}


void EmployeeWindow::showStatsPage()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    try {
        setupStatsCharts();
        ui->stackedWidget->setCurrentWidget(ui->statsPage);
        ui->btnBackStats->raise();
    } catch(const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to load statistics: %1").arg(e.what()));
    }
    QApplication::restoreOverrideCursor();
}

void EmployeeWindow::setupStatsCharts()
{
    // Clear existing widgets (except back button)
    QWidget* backButton = ui->btnBackStats;
    QLayout* oldLayout = ui->statsPage->layout();
    if (oldLayout) {
        QLayoutItem* child;
        while ((child = oldLayout->takeAt(0)) != nullptr) {
            if (child->widget() && child->widget() == backButton) {
                child->widget()->setParent(nullptr);
            } else if (child->widget()) {
                delete child->widget();
            }
            delete child;
        }
        delete oldLayout;
    }

    QVBoxLayout* layout = new QVBoxLayout(ui->statsPage);
    layout->setContentsMargins(10, 10, 10, 10);

    bool chartsCreated = false;

    // Role Distribution Pie Chart
    QSqlQuery roleQuery;
    if (roleQuery.exec("SELECT ROLE, COUNT(*) FROM QT_EMPLOYEES GROUP BY ROLE")) {
        QPieSeries *series = new QPieSeries();
        int totalEmployees = 0;

        while (roleQuery.next()) {
            QString role = roleQuery.value(0).toString();
            int count = roleQuery.value(1).toInt();
            series->append(role, count);
            totalEmployees += count;
        }

        if (totalEmployees > 0) {
            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle(QString("Role Distribution (%1 employees)").arg(totalEmployees));
            chart->setAnimationOptions(QChart::SeriesAnimations);
            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignBottom);

            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            layout->addWidget(chartView);
            chartsCreated = true;
        }
    }

    // Employee Count by Year (if you have hire dates)
    QSqlQuery yearQuery;
    if (yearQuery.exec("SELECT EXTRACT(YEAR FROM SYSDATE) - EXTRACT(YEAR FROM HIRE_DATE), COUNT(*) "
                       "FROM QT_EMPLOYEES GROUP BY EXTRACT(YEAR FROM SYSDATE) - EXTRACT(YEAR FROM HIRE_DATE) "
                       "ORDER BY EXTRACT(YEAR FROM SYSDATE) - EXTRACT(YEAR FROM HIRE_DATE)")) {
        QBarSeries *series = new QBarSeries();
        QBarSet *barSet = new QBarSet("Employees");
        QStringList categories;
        int maxValue = 0;

        while (yearQuery.next()) {
            int years = yearQuery.value(0).toInt();
            int count = yearQuery.value(1).toInt();
            *barSet << count;
            categories << QString("%1 year(s)").arg(years);
            maxValue = qMax(maxValue, count);
        }

        if (!categories.isEmpty()) {
            series->append(barSet);
            barSet->setColor(QColor(109, 18, 19));

            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Employee Tenure Distribution");
            chart->setAnimationOptions(QChart::SeriesAnimations);

            QBarCategoryAxis *axisX = new QBarCategoryAxis();
            axisX->append(categories);
            chart->addAxis(axisX, Qt::AlignBottom);
            series->attachAxis(axisX);

            QValueAxis *axisY = new QValueAxis();
            axisY->setRange(0, maxValue + 1);
            axisY->setTitleText("Number of Employees");
            chart->addAxis(axisY, Qt::AlignLeft);
            series->attachAxis(axisY);

            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            layout->addWidget(chartView);
            chartsCreated = true;
        }
    }

    if (!chartsCreated) {
        QLabel *errorLabel = new QLabel("No statistics data available or error loading data.");
        errorLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(errorLabel);
    }

    layout->addStretch();
    layout->addWidget(ui->btnBackStats, 0, Qt::AlignLeft);
    ui->statsPage->setLayout(layout);
    ui->btnBackStats->setVisible(true);
}
