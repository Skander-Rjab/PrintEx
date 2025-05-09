#include "qgraphicssvgitem.h"

#include "ExamWindow.h"
#include "ui_ExamWindow.h"

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
#include <QCalendarWidget>
#include <QTableView>
#include <QFile>
#include <QDomDocument>
#include "arduino.h"




ExamWindow::ExamWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExamWindow)
    , examModel(new QSqlQueryModel(this))
    , currentExamId(0)
{
    ui->setupUi(this);


    initializeFormComponents();

    //table view
    ui->tableView->setModel(examModel);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableView->setAlternatingRowColors(true);

    //map

    setupMapMapping();


    mapRenderer = new QSvgRenderer(QStringLiteral(":/maps/maps/tunisia.svg"), this);
    mapScene    = new QGraphicsScene(this);
    ui->graphicsViewMap->setScene(mapScene);


    // Connect signals
    connect(ui->tableView->horizontalHeader(), &QHeaderView::sectionClicked,this, &ExamWindow::sortTable);
    connect(ui->btnCreate, &QPushButton::clicked, this, &ExamWindow::showCreatePage);
    connect(ui->btnUpdate, &QPushButton::clicked, this, &ExamWindow::showUpdatePage);
    connect(ui->btnDelete, &QPushButton::clicked, this, &ExamWindow::deleteExam);
    connect(ui->btnPDF, &QPushButton::clicked, this, &ExamWindow::generatePdfReport);
    connect(ui->btnStats, &QPushButton::clicked, this, &ExamWindow::showStatsPage);
    connect(ui->btnSelectPdf, &QPushButton::clicked, this, &ExamWindow::selectPdfFileCreate);
    connect(ui->tableView, &QTableView::clicked, this, &ExamWindow::examTableClicked);
    connect(ui->btnSubmitForm, &QPushButton::clicked, this, &ExamWindow::handleFormSubmit);
    connect(ui->btnCancelForm, &QPushButton::clicked, this, &ExamWindow::showListPage);
    connect(ui->btnBackStats, &QPushButton::clicked, this, &ExamWindow::showListPage);
    connect(ui->txtSearch, &QLineEdit::textChanged,this, &ExamWindow::searchExams);
    connect(ui->btnCalendar, &QPushButton::clicked,this, &ExamWindow::showCalendarPage);
    connect(ui->btnBackCalendar, &QPushButton::clicked,this, &ExamWindow::showListPage);
    connect(ui->btnMap,     &QPushButton::clicked, this, &ExamWindow::showMapPage);
    connect(ui->btnBackMap, &QPushButton::clicked, this, &ExamWindow::showListPage);



    connect(ui->btnBack, &QPushButton::clicked,this, &ExamWindow::backToMainRequested);



    arduino = new ArduinoInterface(this);
    connect(arduino, &ArduinoInterface::error,
            this, [](const QString &msg){
                QMessageBox::warning(nullptr, "Arduino Error", msg);
            });
    if (!arduino->connectPort(9600)) {
        // error() will already have shown a warning
    }




    connect(ui->btnFireDetection, &QPushButton::clicked,this, &ExamWindow::showFirePage);
    connect(ui->btnBackFire,&QPushButton::clicked, this,&ExamWindow::backFromFire);
    connect(ui->btnMuteAlarm, &QPushButton::clicked,this, &ExamWindow::toggleMuteAlarm);


    //calendar
    if (auto *calView = ui->calendarWidget->findChild<QTableView*>()) {
        calView->setMouseTracking(true);
        calView->viewport()->installEventFilter(this);
    }


    connect(ui->stackedWidget, &QStackedWidget::currentChanged,
            [this](int idx){
                if (ui->stackedWidget->widget(idx) == ui->calendarPage)
                    loadExamDates();
            });



    refreshExamModel();
}

ExamWindow::~ExamWindow()
{
    delete ui;
}


void ExamWindow::initializeFormComponents()
{

    loadInstitutions();
    loadGovernorates();

    // Set date formats
    ui->dtScheduled->setDateTime(QDateTime::currentDateTime().addDays(1));
    ui->dtScheduled->setCalendarPopup(true);

    ui->cmbStatus->addItems({"Scheduled", "In Progress", "Completed", "Canceled"});
}

void ExamWindow::loadInstitutions()
{
    ui->cmbInstitution->clear();

    QSqlQuery query("SELECT INSTITUTION_ID, NAME FROM QT_INSTITUTIONS");
    while(query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        ui->cmbInstitution->addItem(name, id);
    }
}

void ExamWindow::loadGovernorates()
{
    ui->cmbDestination->addItems(Exam::tunisianGovernorates());
}

void ExamWindow::refreshExamModel()
{
    loadInstitutions();
    QString queryStr =
        "SELECT e.EXAM_ID, i.NAME AS INSTITUTION, emp.FIRST_NAME || ' ' || emp.LAST_NAME AS EMPLOYEE, "
        "TO_CHAR(e.SUBMISSION_DATE, 'YYYY-MM-DD HH24:MI') AS SUBMISSION, "
        "TO_CHAR(e.SCHEDULED_DELIVERY_DATE, 'YYYY-MM-DD HH24:MI') AS SCHEDULED, "
        "e.STATUS, e.DESTINATION_ADDRESS "
        "FROM QT_EXAMS e "
        "JOIN QT_INSTITUTIONS i ON e.INSTITUTION_ID = i.INSTITUTION_ID "
        "JOIN QT_EMPLOYEES emp ON e.EMPLOYEE_ID = emp.EMPLOYEE_ID";

    examModel->setQuery(queryStr);

    // Set headers
    examModel->setHeaderData(0, Qt::Horizontal, "Exam ID");
    examModel->setHeaderData(1, Qt::Horizontal, "Institution");
    examModel->setHeaderData(2, Qt::Horizontal, "Employee");
    examModel->setHeaderData(3, Qt::Horizontal, "Submission Date");
    examModel->setHeaderData(4, Qt::Horizontal, "Scheduled Date");
    examModel->setHeaderData(5, Qt::Horizontal, "Status");
    examModel->setHeaderData(6, Qt::Horizontal, "Destination");

    ui->tableView->resizeColumnsToContents();
}




void ExamWindow::showCreatePage()
{
    isCreatingNewExam = true;
    ui->stackedWidget->setCurrentWidget(ui->formPage);
    ui->cmbInstitution->setCurrentIndex(0);
    ui->dtScheduled->setDateTime(QDateTime::currentDateTime().addDays(1));
    ui->cmbDestination->setCurrentIndex(0);
    ui->lblPdfPath->setText("No file selected");
    selectedPdfPathCreate.clear();
}

void ExamWindow::showUpdatePage()
{
    isCreatingNewExam = false;
    if(currentExamId == 0) return;

    QSqlQuery query;
    query.prepare("SELECT INSTITUTION_ID, SCHEDULED_DELIVERY_DATE, "
                  "STATUS, DESTINATION_ADDRESS FROM QT_EXAMS WHERE EXAM_ID = ?");
    query.addBindValue(currentExamId);

    if(query.exec() && query.next()) {
        ui->cmbInstitution->setCurrentIndex(ui->cmbInstitution->findData(query.value(0)));
        ui->dtScheduled->setDateTime(query.value(1).toDateTime());
        ui->cmbStatus->setCurrentText(query.value(2).toString());
        ui->cmbDestination->setCurrentText(query.value(3).toString());
    }

    ui->stackedWidget->setCurrentWidget(ui->formPage);
}

void ExamWindow::handleFormSubmit()
{
    if(isCreatingNewExam) {
        createExam();
    } else {
        updateExam();
    }
}

void ExamWindow::createExam()
{
    if(!validateForm(ui->dtScheduled, ui->cmbInstitution, ui->cmbDestination, ui->lblPdfPath)) {
        return;
    }

    QFile file(selectedPdfPathCreate);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Could not open PDF file");
        return;
    }

    Exam exam;
    exam.setExamId(Exam::generateNewExamId());
    exam.setInstitutionId(ui->cmbInstitution->currentData().toInt());
    exam.setEmployeeId(2); // when integration replace with function to get emp id
    exam.setExamContent(file.readAll());
    exam.setSubmissionDate(QDateTime::currentDateTime());
    exam.setScheduledDeliveryDate(ui->dtScheduled->dateTime());
    exam.setStatus(ui->cmbStatus->currentText());
    exam.setDestinationAddress(ui->cmbDestination->currentText());

    if(exam.create()) {
        QMessageBox::information(this, "Success", "Exam created successfully");
        showListPage();
    } else {
        QMessageBox::critical(this, "Error", "Failed to create exam");
    }
}

void ExamWindow::updateExam()
{
    if(currentExamId == 0) return;
    QByteArray pdfData;
    if(!selectedPdfPathUpdate.isEmpty()) {
        QFile file(selectedPdfPathUpdate);
        if(file.open(QIODevice::ReadOnly)) {
            pdfData = file.readAll();
            file.close();
        }
    } else {
        QSqlQuery query;
        query.prepare("SELECT EXAM_CONTENT FROM QT_EXAMS WHERE EXAM_ID = ?");
        query.addBindValue(currentExamId);
        if(query.exec() && query.next()) {
            pdfData = query.value(0).toByteArray();
        }
    }


    Exam exam;
    exam.setExamId(currentExamId);
    exam.setInstitutionId(ui->cmbInstitution->currentData().toInt());
    exam.setEmployeeId(2); // when integration replace with function to get emp id
    exam.setScheduledDeliveryDate(ui->dtScheduled->dateTime());
    exam.setExamContent(pdfData);
    exam.setStatus(ui->cmbStatus->currentText());
    exam.setDestinationAddress(ui->cmbDestination->currentText());

    if(!selectedPdfPathUpdate.isEmpty()) {
        QFile file(selectedPdfPathUpdate);
        if(file.open(QIODevice::ReadOnly)) {
            exam.setExamContent(file.readAll());
        }
    }

    if(exam.update()) {
        QMessageBox::information(this, "Success", "Exam updated successfully");
        showListPage();
    } else {
        QMessageBox::critical(this, "Error", "Failed to update exam");
    }
}

void ExamWindow::deleteExam()
{
    if(currentExamId == 0) return;

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirm Delete",
        QString("Delete exam #%1?").arg(currentExamId),
        QMessageBox::Yes | QMessageBox::No
        );

    if(reply == QMessageBox::Yes) {
        Exam exam;
        exam.setExamId(currentExamId);
        if(exam.remove()) {
            refreshExamModel();
            currentExamId = 0;
        }
    }
}

bool ExamWindow::validateForm(QDateTimeEdit *dateEdit, QComboBox *institutionCombo,
                              QComboBox *destinationCombo, QLabel *pdfLabel)
{
    if(institutionCombo->currentIndex() == -1) {
        QMessageBox::warning(this, "Validation", "Please select an institution");
        return false;
    }

    if(dateEdit->dateTime() <= QDateTime::currentDateTime()) {
        QMessageBox::warning(this, "Validation", "Scheduled date must be in the future");
        return false;
    }

    if(destinationCombo->currentText().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Please select a destination");
        return false;
    }

    if(pdfLabel->text() == "No file selected") {
        QMessageBox::warning(this, "Validation", "Please select a PDF file");
        return false;
    }

    return true;
}


void ExamWindow::searchExams(const QString &searchText)
{
    QString baseQuery =
        "SELECT e.EXAM_ID, i.NAME AS INSTITUTION, emp.FIRST_NAME || ' ' || emp.LAST_NAME AS EMPLOYEE, "
        "TO_CHAR(e.SUBMISSION_DATE, 'YYYY-MM-DD HH24:MI') AS SUBMISSION, "
        "TO_CHAR(e.SCHEDULED_DELIVERY_DATE, 'YYYY-MM-DD HH24:MI') AS SCHEDULED, "
        "e.STATUS, e.DESTINATION_ADDRESS "
        "FROM QT_EXAMS e "
        "JOIN QT_INSTITUTIONS i ON e.INSTITUTION_ID = i.INSTITUTION_ID "
        "JOIN QT_EMPLOYEES emp ON e.EMPLOYEE_ID = emp.EMPLOYEE_ID ";

    // If user enter words nzid il where clause
    if(!searchText.isEmpty()) {
        baseQuery += "WHERE UPPER(e.EXAM_ID) LIKE UPPER(:search) "
                     "OR UPPER(i.NAME) LIKE UPPER(:search) "
                     "OR UPPER(emp.FIRST_NAME || ' ' || emp.LAST_NAME) LIKE UPPER(:search) "
                     "OR UPPER(e.DESTINATION_ADDRESS) LIKE UPPER(:search) "
                     "OR UPPER(e.STATUS) LIKE UPPER(:search) "
                     "OR TO_CHAR(e.SUBMISSION_DATE, 'YYYY-MM-DD') LIKE UPPER(:search)"
                     "OR TO_CHAR(e.SCHEDULED_DELIVERY_DATE, 'YYYY-MM-DD') LIKE UPPER(:search)";
    }

    QSqlQuery query;
    query.prepare(baseQuery);

    if(!searchText.isEmpty()) {

        query.bindValue(":search", "%" + searchText + "%");
    }


    if (!query.exec()) {
        QString errorMsg = "Failed to execute search query:\n" + query.lastError().text();
        qDebug() << errorMsg;
        QMessageBox::critical(this, "Search Error", errorMsg);
        return;
    }


    examModel->setQuery(std::move(query));


    if (examModel->lastError().isValid()) {
        QString errorMsg = "Failed to update model:\n" + examModel->lastError().text();
        qDebug() << errorMsg;
        QMessageBox::critical(this, "Model Error", errorMsg);
        return;
    }


    ui->tableView->resizeColumnsToContents();
}



void ExamWindow::sortTable(int column)
{

    static QMap<int, Qt::SortOrder> sortStates;

    //i made it upper case just in case oracle is case sensitive
    QString headerText = examModel->headerData(column, Qt::Horizontal).toString().toUpper();


    QMap<QString, QString> columnMapping = {
        {"EXAM ID", "e.EXAM_ID"},
        {"INSTITUTION", "i.NAME"},
        {"EMPLOYEE", "emp.LAST_NAME"},
        {"SUBMISSION DATE", "e.SUBMISSION_DATE"},
        {"SCHEDULED DATE", "e.SCHEDULED_DELIVERY_DATE"},
        {"STATUS", "e.STATUS"},
        {"DESTINATION", "e.DESTINATION_ADDRESS"}
    };


    QString orderBy = columnMapping.value(headerText, "e.EXAM_ID");


    Qt::SortOrder order = (sortStates[column] == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;
    sortStates[column] = order;


    QString queryStr = examModel->query().executedQuery();

    //clear
    static const QRegularExpression orderRegex("ORDER BY.*$", QRegularExpression::CaseInsensitiveOption);
    queryStr.replace(orderRegex, "");

    // new order by
    queryStr += " ORDER BY " + orderBy + (order == Qt::DescendingOrder ? " DESC" : " ASC");


    examModel->setQuery(std::move(queryStr));
}

void ExamWindow::generatePdfReport()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", QDir::homePath(), "PDF Files (*.pdf)");
    if(fileName.isEmpty())
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


    QColor headerColor(109, 18, 19);
    QColor titleColor(85, 0, 0);
    QFont titleFont("Arial", 18, QFont::Bold);
    QFont headerFont("Arial", 8, QFont::Bold);
    QFont contentFont("Arial", 9);

    const int lineHeight = painter.fontMetrics().height();
    const int rowHeight = lineHeight * 1.8;
    const int availableWidth = printer.width() - 30;


    const double colPercentages[] = {0.10, 0.20, 0.15, 0.15, 0.15, 0.15, 0.10};
    int colWidths[7];
    for (int i = 0; i < 7; i++) {
        colWidths[i] = availableWidth * colPercentages[i];
    }

    int pageNumber = 1;
    int yPos = 50;


    painter.setPen(titleColor);
    painter.setFont(titleFont);
    painter.drawText(QRect(15, yPos, availableWidth, lineHeight*2),
                     Qt::AlignLeft | Qt::AlignVCenter, "Exam Management System Report");

    yPos += lineHeight * 3;

    painter.setPen(Qt::white);
    painter.setBrush(headerColor);
    painter.drawRoundedRect(15, yPos - 5, availableWidth, rowHeight + 10, 5, 5);


    QStringList headers = {"Exam ID", "Institution", "Employee", "Submission", "Scheduled", "Status", "Destination"};
    int xPos = 15;
    painter.setFont(headerFont);
    QFontMetrics fm(headerFont);
    for (int col = 0; col < 7; col++) {

        QString headerText = fm.elidedText(headers[col], Qt::ElideRight, colWidths[col] - 4);
        painter.drawText(QRect(xPos, yPos, colWidths[col], rowHeight),
                         Qt::AlignCenter, headerText);
        xPos += colWidths[col];
    }
    yPos += rowHeight + 10;


    painter.setFont(contentFont);
    for (int row = 0; row < examModel->rowCount(); row++) {
        if (yPos + rowHeight > printer.height() - 30) {

            printer.newPage();
            yPos = 50;
            pageNumber++;

            painter.setPen(Qt::white);
            painter.setBrush(headerColor);
            painter.drawRoundedRect(15, yPos - 5, availableWidth, rowHeight + 10, 5, 5);

            xPos = 15;
            painter.setFont(headerFont);
            for (int col = 0; col < 7; col++) {
                QString headerText = fm.elidedText(headers[col], Qt::ElideRight, colWidths[col] - 4);
                painter.drawText(QRect(xPos, yPos, colWidths[col], rowHeight),
                                 Qt::AlignCenter, headerText);
                xPos += colWidths[col];
            }
            yPos += rowHeight + 10;
        }


        painter.setBrush(row % 2 ? Qt::white : QColor(240, 240, 240));

        xPos = 15;
        for (int col = 0; col < 7; col++) {
            QString data = examModel->index(row, col).data().toString();


            painter.drawRect(xPos, yPos, colWidths[col], rowHeight);


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


QString ExamWindow::getEmployeeName(int employeeId)
{
    QSqlQuery query;
    query.prepare(
        "SELECT FIRST_NAME, LAST_NAME "
        "FROM QT_EMPLOYEES "
        "WHERE EMPLOYEE_ID = ?"
        );
    query.addBindValue(employeeId);
    query.exec();
    return query.next() ? query.value(0).toString() + " " + query.value(1).toString() : "Unknown";
}

QString ExamWindow::getInstitutionName(int institutionId)
{
    QSqlQuery query;
    query.prepare("SELECT NAME FROM QT_INSTITUTIONS WHERE INSTITUTION_ID = ?");
    query.addBindValue(institutionId);
    query.exec();
    return query.next() ? query.value(0).toString() : "Unknown Institution";
}

void ExamWindow::examTableClicked(const QModelIndex &index)
{
    if(index.isValid()) {
        currentExamId = examModel->index(index.row(), 0).data().toInt();
    }
}

void ExamWindow::selectPdfFileCreate()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select PDF", "", "PDF Files (*.pdf)");
    if(!filePath.isEmpty()) {
        selectedPdfPathCreate = filePath;
        ui->lblPdfPath->setText(QFileInfo(filePath).fileName());
    }
}

void ExamWindow::selectPdfFileUpdate()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select PDF", "", "PDF Files (*.pdf)");
    if(!filePath.isEmpty()) {
        selectedPdfPathUpdate = filePath;
        ui->lblPdfPath->setText(QFileInfo(filePath).fileName());
    }
}


//stats

void ExamWindow::setupStatsCharts()
{

    QWidget* backButton = ui->btnBackStats;

    QLayout* oldLayout = ui->statsPage->layout();
    if(oldLayout) {
        QLayoutItem* child;
        while((child = oldLayout->takeAt(0)) != nullptr) {
            // Do not delete the back button widget.
            if(child->widget() && child->widget() == backButton) {

                child->widget()->setParent(nullptr);
            } else if(child->widget()) {
                delete child->widget();
            }
            delete child;
        }
        delete oldLayout;
    }

    QVBoxLayout* layout = new QVBoxLayout(ui->statsPage);
    layout->setContentsMargins(10, 10, 10, 10);


    bool chartsCreated = false;

    // months chart
    QSqlQuery monthlyQuery;
    if(monthlyQuery.exec("SELECT TO_CHAR(SCHEDULED_DELIVERY_DATE, 'YYYY-MM'), COUNT(*) "
                          "FROM QT_EXAMS "
                          "GROUP BY TO_CHAR(SCHEDULED_DELIVERY_DATE, 'YYYY-MM') "
                          "ORDER BY TO_CHAR(SCHEDULED_DELIVERY_DATE, 'YYYY-MM')"))
    {
        QStringList categories;
        QVector<int> counts;
        int maxValue = 0;

        while(monthlyQuery.next()) {
            categories << monthlyQuery.value(0).toString();
            int count = monthlyQuery.value(1).toInt();
            counts << count;
            maxValue = qMax(maxValue, count);
        }

        if(!categories.isEmpty()) {
            QBarSeries *barSeries = new QBarSeries();
            QBarSet *barSet = new QBarSet("Exams");

            for(int i = 0; i < counts.size(); ++i) {
                *barSet << counts[i];
            }
            barSeries->append(barSet);

            QChart *barChart = new QChart();
            barChart->addSeries(barSeries);
            barChart->setTitle("Exams Per Month");
            barChart->setAnimationOptions(QChart::SeriesAnimations);


            QBarCategoryAxis *axisX = new QBarCategoryAxis();
            axisX->append(categories);
            axisX->setTitleText("Months");
            barChart->addAxis(axisX, Qt::AlignBottom);
            barSeries->attachAxis(axisX);


            QValueAxis *axisY = new QValueAxis();
            axisY->setRange(0, maxValue + 1);
            axisY->setTitleText("Number of Exams");
            axisY->setTickCount(maxValue + 2); // for a step of 1
            axisY->setLabelFormat("%d");
            barChart->addAxis(axisY, Qt::AlignLeft);
            barSeries->attachAxis(axisY);


            barSet->setColor(QColor(109, 18, 19));
            barChart->legend()->setVisible(false);

            QChartView *barChartView = new QChartView(barChart);
            barChartView->setRenderHint(QPainter::Antialiasing);
            layout->addWidget(barChartView);
            chartsCreated = true;
        }
    } else {
        qDebug() << "Monthly query error:" << monthlyQuery.lastError();
    }

    // Institution Chart
    QSqlQuery institutionQuery;
    if (institutionQuery.exec(
            "SELECT i.NAME, COUNT(*) "
            "FROM QT_EXAMS e "
            "JOIN QT_INSTITUTIONS i ON e.INSTITUTION_ID = i.INSTITUTION_ID "
            "GROUP BY i.NAME"))
    {
        QVector<QPair<QString,int>> data;
        int totalCount = 0;

        // Collect data
        while (institutionQuery.next()) {
            QString name  = institutionQuery.value(0).toString();
            int     count = institutionQuery.value(1).toInt();
            data.append(qMakePair(name, count));
            totalCount += count;
        }

        if (!data.isEmpty() && totalCount > 0) {
            // --- Inner series: percentages inside ---
            QPieSeries *seriesPerc = new QPieSeries();
            for (int i = 0; i < data.size(); ++i)
                seriesPerc->append(data[i].first, data[i].second);

            seriesPerc->setLabelsVisible(true);
            seriesPerc->setLabelsPosition(QPieSlice::LabelInsideTangential);
            seriesPerc->setPieSize(0.6);
            seriesPerc->setHoleSize(0.0);

            QFont fontPerc;
            fontPerc.setPointSize(8);
            // Non‑range‑based loop to avoid detach issues
            QList<QPieSlice*> percSlices = seriesPerc->slices();
            for (int i = 0; i < percSlices.size(); ++i) {
                QPieSlice *slice = percSlices.at(i);
                qreal pct = slice->percentage() * 100.0;
                slice->setLabel(QString("%1\%").arg(pct, 0, 'f', 1));
                slice->setLabelFont(fontPerc);
                slice->setLabelColor(Qt::white);
                slice->setLabelVisible(true);
            }

            // --- Outer series: names outside ---
            QPieSeries *seriesNames = new QPieSeries();
            for (int i = 0; i < data.size(); ++i)
                seriesNames->append(data[i].first, data[i].second);

            seriesNames->setLabelsVisible(true);
            seriesNames->setLabelsPosition(QPieSlice::LabelOutside);
            seriesNames->setPieSize(0.8);
            seriesNames->setHoleSize(0.6);

            QFont fontName;
            fontName.setPointSize(9);
            // Non‑range‑based loop here as well
            QList<QPieSlice*> nameSlices = seriesNames->slices();
            for (int i = 0; i < nameSlices.size(); ++i) {
                QPieSlice *slice = nameSlices.at(i);
                slice->setLabelFont(fontName);
                slice->setLabelColor(Qt::black);
                slice->setBrush(Qt::transparent);
                slice->setPen(QPen(Qt::transparent));
            }

            // --- Build chart ---
            QChart *pieChart = new QChart();
            pieChart->addSeries(seriesNames);
            pieChart->addSeries(seriesPerc);
            pieChart->setTitle(
                QString("Institution Distribution (%1 exams)").arg(totalCount)
                );
            pieChart->setAnimationOptions(QChart::SeriesAnimations);
            pieChart->legend()->hide();

            QChartView *pieChartView = new QChartView(pieChart);
            pieChartView->setRenderHint(QPainter::Antialiasing);
            layout->addWidget(pieChartView);
            chartsCreated = true;
        }
        // else: no data case
    }
    else {
        qDebug() << "Institution query error:" << institutionQuery.lastError();
    }




    if(!chartsCreated) {
        QLabel *errorLabel = new QLabel("No statistics data available or error loading data.");
        errorLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(errorLabel);
    }

    ui->statsPage->setLayout(layout);



    layout->addStretch();

    // Ensure button is visible
    ui->btnBackStats->setVisible(true);
    layout->addWidget(ui->btnBackStats, 0, Qt::AlignLeft);
}

void ExamWindow::showStatsPage()
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


//calendar

void ExamWindow::showCalendarPage()
{
    ui->stackedWidget->setCurrentWidget(ui->calendarPage);
}

void ExamWindow::loadExamDates()
{
    examTimesByDate.clear();

    ui->calendarWidget->setDateTextFormat(QDate(), QTextCharFormat());

    QSqlQuery q;
    if (!q.exec("SELECT SCHEDULED_DELIVERY_DATE FROM QT_EXAMS")) {
        qWarning() << "Failed to load dates:" << q.lastError();
        return;
    }

    while (q.next()) {
        QDateTime dt = q.value(0).toDateTime();
        examTimesByDate[dt.date()].append(dt.time());//hethy to be used by eventFilter bch najmou nwariw il wa9t
    }


    QTextCharFormat redFmt;
    redFmt.setBackground(Qt::magenta);
    for (auto it = examTimesByDate.constBegin(); it != examTimesByDate.constEnd(); ++it) {
        ui->calendarWidget->setDateTextFormat(it.key(), redFmt);
    }
}


bool ExamWindow::eventFilter(QObject *obj, QEvent *event)
{
    auto *calView = ui->calendarWidget->findChild<QTableView*>();
    if (obj == calView->viewport() && event->type() == QEvent::ToolTip) {
        auto *he = static_cast<QHelpEvent*>(event);
        QModelIndex idx = calView->indexAt(calView->viewport()->mapFromGlobal(he->globalPos()));
        if (idx.isValid()) {
            bool ok;
            int day = idx.data(Qt::DisplayRole).toInt(&ok);
            if (ok) {
                int year  = ui->calendarWidget->yearShown();
                int month = ui->calendarWidget->monthShown();
                QDate d(year, month, day);
                if (examTimesByDate.contains(d)) {
                    auto times = examTimesByDate[d];
                    QString tip = QString("<b>%1 exam(s) on %2:</b><br>")
                                      .arg(times.size())
                                      .arg(d.toString("yyyy-MM-dd"));
                    for (auto &t : times)
                        tip += t.toString("hh:mm:ss") + "<br>";
                    QToolTip::showText(he->globalPos(), tip, calView);
                    return true;
                }
            }
        }
        QToolTip::hideText();
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

//map

void ExamWindow::setupMapMapping()
{

    idToNameMap = {
        { "TN12", "Ariana"   }, { "TN13", "Ben Arous" },
        { "TN23", "Bizerte"  }, { "TN11", "Tunis"     },
        { "TN22", "Zaghouan" }, { "TN14", "Manouba"   },
        { "TN21", "Nabeul"   }, { "TN33", "Kef"       },
        { "TN31", "Béja"     }, { "TN32", "Jendouba"  },
        { "TN34", "Siliana"  }, { "TN52", "Monastir"  },
        { "TN53", "Mahdia"   }, { "TN51", "Sousse"    },
        { "TN61", "Sfax"     }, { "TN42", "Kasserine" },
        { "TN41", "Kairouan" }, { "TN43", "Sidi Bouzid"},
        { "TN72", "Tozeur"   }, { "TN71", "Gafsa"     },
        { "TN73", "Kébili"   }, { "TN81", "Gabès"     },
        { "TN82", "Médenine" }, { "TN83", "Tataouine"}
    };
    // invert it bch nasna3 nameToId
    for (auto it = idToNameMap.constBegin(); it != idToNameMap.constEnd(); ++it)
        nameToIdMap[it.value()] = it.key();
}

void ExamWindow::loadMapData()
{
    tooltipHtmlMap.clear();


    const QString sql = R"__(
        SELECT destination_address,
               COUNT(*) AS cnt,
               LISTAGG(
                 TO_CHAR(scheduled_delivery_date, 'YYYY-MM-DD HH24:MI'),
                 ';'
               ) WITHIN GROUP (ORDER BY scheduled_delivery_date) AS dates
        FROM QT_EXAMS
        GROUP BY destination_address
    )__";

    QSqlQuery q;
    if (!q.exec(sql)) {
        qWarning() << "Failed to load map data:" << q.lastError().text();
        return;
    }

    while (q.next()) {
        QString gov   = q.value("destination_address").toString();
        int     cnt   = q.value("cnt").toInt();
        QString blob  = q.value("dates").toString();
        QStringList dateList = blob.split(';', Qt::SkipEmptyParts);

        QString html = QString("<b>%1</b><br/>Exams: %2<ul>") //juste bich nzayen il tool tip
                           .arg(gov).arg(cnt);
        for (auto &dt : dateList) {
            html += QString("<li>%1</li>").arg(dt);
        }
        html += "</ul>";


        if (nameToIdMap.contains(gov))
            tooltipHtmlMap[nameToIdMap[gov]] = html;
    }
}

void ExamWindow::setupMapView()
{
    mapScene->clear();


    if (!mapRenderer->isValid()) {
        qWarning() << "tunisia.svg failed to load!";
        return;
    }


    auto *bg = new QGraphicsSvgItem;
    bg->setSharedRenderer(mapRenderer);
    bg->setElementId(QString());        // Qstring() instead of "" cause we need NULL string
    bg->setZValue(0); //elevation
    mapScene->addItem(bg);


    QFile f(":/maps/maps/tunisia.svg");
    if (!f.open(QIODevice::ReadOnly)) {
        qWarning() << "Cannot open SVG for parsing:" << f.errorString();
    } else {
        QDomDocument doc;
        doc.setContent(&f);
        f.close();

        const auto circles = doc.elementsByTagName("circle");
        constexpr double DEFAULT_R = 8.0;

        for (int i = 0; i < circles.count(); ++i) {
            auto e = circles.at(i).toElement();
            QString id = e.attribute("id");
            if (!idToNameMap.contains(id))
                continue;

            bool ok;
            double cx = e.attribute("cx").toDouble(&ok);
            if (!ok) continue;
            double cy = e.attribute("cy").toDouble(&ok);
            if (!ok) continue;
            double r  = e.attribute("r").toDouble(&ok) ? e.attribute("r").toDouble() : DEFAULT_R;


            QString tooltip = tooltipHtmlMap.value(
                id,
                QString("<b>%1</b><br/><i>No exams</i>")
                    .arg(idToNameMap[id])
                );


            auto *circleItem = mapScene->addEllipse(
                cx - r, cy - r, 2*r, 2*r,
                QPen(Qt::white, 0.5),
                QBrush(QColor("#6f9c76"))
                );
            circleItem->setAcceptHoverEvents(true);
            circleItem->setToolTip(tooltip);
            circleItem->setZValue(1);
        }
    }

    // fit while keeping aspect ratio
    const QRectF bounds = mapScene->itemsBoundingRect();
    mapScene->setSceneRect(bounds);
    ui->graphicsViewMap->fitInView(bounds, Qt::KeepAspectRatio);


    ui->graphicsViewMap->setBackgroundBrush(Qt::white);


    ui->graphicsViewMap->setRenderHints(
        QPainter::Antialiasing | QPainter::SmoothPixmapTransform
        );
}


void ExamWindow::showMapPage()
{
    loadMapData();
    setupMapView();
    ui->stackedWidget->setCurrentWidget(ui->mapPage);
}

//fire

void ExamWindow::showFirePage()
{
    // stop gentle when entering Fire page
    arduino->sendGentleOff();

    // allow one fresh fire alert
    arduino->resetSmokeNotification();
    connect(arduino, &ArduinoInterface::smokeDetected,
            this, &ExamWindow::handleSmoke);

    // enable smoke‐alarm on Arduino
    arduino->sendSmokeOn();

    refreshFireModel();
    ui->stackedWidget->setCurrentWidget(ui->firePage);
}


void ExamWindow::backFromFire()
{
    // disable fire‐alarm
    disconnect(arduino, &ArduinoInterface::smokeDetected,
               this, &ExamWindow::handleSmoke);
    arduino->sendSmokeOff();

    // reset mute‐state
    alarmMuted = false;
    ui->btnMuteAlarm->setText("🔇 Mute");
    arduino->sendUnmuteCommand();

    // go back to list (this will also handle gentle‐buzz)
    showListPage();
}

void ExamWindow::toggleMuteAlarm()
{
    alarmMuted = !alarmMuted;
    if (alarmMuted) {
        ui->btnMuteAlarm->setText("🔊 Unmute");
        arduino->sendMuteCommand();
    } else {
        ui->btnMuteAlarm->setText("🔇 Mute");
        arduino->sendUnmuteCommand();
    }
}

void ExamWindow::refreshFireModel()
{
    // only id, submission, scheduled, status, destination for non-completed
    QString q = R"(
      SELECT EXAM_ID,
             TO_CHAR(SUBMISSION_DATE,'YYYY-MM-DD HH24:MI') AS SUBMISSION,
             TO_CHAR(SCHEDULED_DELIVERY_DATE,'YYYY-MM-DD HH24:MI') AS SCHEDULED,
             STATUS,
             DESTINATION_ADDRESS
      FROM QT_EXAMS
      WHERE STATUS <> 'Completed'
    )";
    auto *m = new QSqlQueryModel(this);
    m->setQuery(q);
    m->setHeaderData(0, Qt::Horizontal, "Exam ID");
    m->setHeaderData(1, Qt::Horizontal, "Submission");
    m->setHeaderData(2, Qt::Horizontal, "Scheduled");
    m->setHeaderData(3, Qt::Horizontal, "Status");
    m->setHeaderData(4, Qt::Horizontal, "Destination");
    ui->fireTableView->setModel(m);
    ui->fireTableView->resizeColumnsToContents();
}



void ExamWindow::handleSmoke()
{
    if (!alarmMuted) {
        QMessageBox::critical(this, "🔥 Fire Detected",
                              "Smoke detected! Cancelling all pending exams.");
    } else {
        QMessageBox::warning(this, "🔥 Fire (Muted)",
                             "Smoke detected (muted), cancelling exams.");
    }

    QSqlQuery q;
    if (!q.exec("UPDATE QT_EXAMS SET STATUS='Canceled' WHERE STATUS <> 'Completed'")) {
        QMessageBox::critical(this, "DB Error", q.lastError().text());
    }

    refreshExamModel();
    refreshFireModel();
}


bool ExamWindow::checkForCanceledExams()
{
    QSqlQuery q;
    if (!q.exec("SELECT COUNT(*) FROM QT_EXAMS WHERE STATUS='Canceled'")) {
        return false;
    }
    if (q.next())
        return q.value(0).toInt() > 0;
    return false;
}


void ExamWindow::showListPage()
{
    refreshExamModel();
    ui->stackedWidget->setCurrentWidget(ui->listPage);

    // buzz if there are canceled exams
    if (checkForCanceledExams()) {
        arduino->sendGentleOn();
    } else {
        arduino->sendGentleOff();
    }
}

