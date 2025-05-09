#include "InstitutionWidget.h"
#include "ui_InstitutionWidget.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QRegularExpression>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QSqlError>
#include "institution.h"

InstitutionWidget::InstitutionWidget(QWidget *parent) :
    QWidget(parent, Qt::Window),
    ui(new Ui::InstitutionWidget),
    model(new QSqlQueryModel(this))
{
    ui->setupUi(this);
    setWindowTitle("Institution Management");
    setWindowModality(Qt::ApplicationModal);

    // Initialize table view
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setAlternatingRowColors(true);

    // Setup validators
    QRegularExpression contactRegex("^\\d{8}$");
    ui->txtContact->setValidator(new QRegularExpressionValidator(contactRegex, this));

    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    ui->txtAddress->setValidator(new QRegularExpressionValidator(emailRegex, this));

    // Connect signals
    connect(ui->btnAdd, &QPushButton::clicked, this, &InstitutionWidget::onAddClicked);
    connect(ui->btnDelete, &QPushButton::clicked, this, &InstitutionWidget::onDeleteClicked);
    connect(ui->btnUpdate, &QPushButton::clicked, this, &InstitutionWidget::onUpdateClicked);
    connect(ui->txtSearch, &QLineEdit::textChanged, this, &InstitutionWidget::onSearch);
    connect(ui->btnExport, &QPushButton::clicked, this, &InstitutionWidget::onExportPDF);
    connect(ui->btnStats, &QPushButton::clicked, this, &InstitutionWidget::onShowStats);
    connect(ui->btnSubmit, &QPushButton::clicked, this, &InstitutionWidget::onFormSubmit);
    connect(ui->btnCancel, &QPushButton::clicked, this, &InstitutionWidget::onFormCancel);
    connect(ui->btnHome, &QPushButton::clicked, this, &InstitutionWidget::backToMainRequested);

    connect(ui->btnHome, &QPushButton::clicked,this, &InstitutionWidget::backToMainRequested);

    connect(ui->tableView->horizontalHeader(), &QHeaderView::sectionClicked,this, &InstitutionWidget::sortTable);

    ui->grpInstitutionForm->hide();

    refreshTable();
}

InstitutionWidget::~InstitutionWidget()
{
    delete ui;
}

void InstitutionWidget::refreshTable()
{
    model->setQuery("SELECT INSTITUTION_ID, NAME, CONTACT_INFO, ADDRESS FROM QT_INSTITUTIONS");
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, tr("Contact"));
    model->setHeaderData(3, Qt::Horizontal, tr("Address"));
    ui->tableView->resizeColumnsToContents();
    highlightConflicts();
}

void InstitutionWidget::onAddClicked()
{
    clearForm();
    currentInstitutionId = 0;
    ui->grpInstitutionForm->show();
}

void InstitutionWidget::onDeleteClicked()
{
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
    if(selection.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select an institution to delete");
        return;
    }

    int id = selection.first().data().toInt();
    if(QMessageBox::question(this, "Confirm", "Delete institution #" + QString::number(id) + "?") == QMessageBox::Yes) {
        deleteInstitution(id);
        refreshTable();
    }
}

void InstitutionWidget::onUpdateClicked()
{
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
    if(selection.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select an institution to update");
        return;
    }

    currentInstitutionId = selection.first().data().toInt();
    QSqlQuery q;
    q.prepare("SELECT NAME, CONTACT_INFO, ADDRESS FROM QT_INSTITUTIONS WHERE INSTITUTION_ID = ?");
    q.addBindValue(currentInstitutionId);

    if(q.exec() && q.next()) {
        ui->txtName->setText(q.value(0).toString());
        ui->txtContact->setText(q.value(1).toString());
        ui->txtAddress->setText(q.value(2).toString());
        ui->grpInstitutionForm->show();
    }
}

bool InstitutionWidget::validateForm()
{
    if(ui->txtName->text().isEmpty() ||
        ui->txtContact->text().isEmpty() ||
        ui->txtAddress->text().isEmpty())
    {
        QMessageBox::warning(this, "Error", "All fields are required");
        return false;
    }

    if(ui->txtContact->text().length() != 8) {
        QMessageBox::warning(this, "Error", "Contact must be 8 digits");
        return false;
    }

    if(!ui->txtAddress->text().contains('@') || !ui->txtAddress->text().contains('.')) {
        QMessageBox::warning(this, "Error", "Invalid email format");
        return false;
    }

    return true;
}

void InstitutionWidget::onFormSubmit()
{
    if(!validateForm()) return;

    QString name = ui->txtName->text().trimmed();
    QString contact = ui->txtContact->text().trimmed();
    QString address = ui->txtAddress->text().trimmed();

    Institution institution;
    bool success = false;

    if(currentInstitutionId == 0) {
        success = institution.addInstitution(name, contact, address);
    } else {
        success = institution.updateInstitution(currentInstitutionId, name, contact, address);
    }

    if(success) {
        ui->grpInstitutionForm->hide();
        refreshTable();
    } else {
        QMessageBox::critical(this, "Error", "Operation failed. Please try again.");
    }
}

void InstitutionWidget::onFormCancel()
{
    ui->grpInstitutionForm->hide();
}

// Database operations
bool InstitutionWidget::addInstitution(const QString &name, const QString &contact, const QString &address)
{
    Institution institution;
    return institution.addInstitution(name, contact, address);
}

bool InstitutionWidget::updateInstitution(int id, const QString &name, const QString &contact, const QString &address)
{
    Institution institution;
    return institution.updateInstitution(id,name, contact, address);
}

bool InstitutionWidget::deleteInstitution(int id)
{
    Institution institution;
    return institution.deleteInstitution(id);
}

void InstitutionWidget::onSearch(const QString &text)
{
    QSqlQuery q;
    q.prepare("SELECT INSTITUTION_ID, NAME, CONTACT_INFO, ADDRESS FROM QT_INSTITUTIONS "
              "WHERE NAME LIKE :search OR CONTACT_INFO LIKE :search OR ADDRESS LIKE :search");
    q.bindValue(":search", "%" + text + "%");

    if(q.exec()) {
        model->setQuery(std::move(q));
        ui->tableView->resizeColumnsToContents();
    }
}



void InstitutionWidget::onShowStats()
{
    QSqlQuery q("SELECT COUNT(*) FROM QT_INSTITUTIONS");
    if(q.next()) {
        QMessageBox::information(this, "Statistics",
                                 QString("Total Institutions: %1").arg(q.value(0).toString()));
    }
}

void InstitutionWidget::clearForm()
{
    ui->txtName->clear();
    ui->txtContact->clear();
    ui->txtAddress->clear();
}

void InstitutionWidget::onExportPDF()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Export PDF", "", "PDF Files (*.pdf)");
    if(filePath.isEmpty()) return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

    QPainter painter;
    if(!painter.begin(&printer)) {
        QMessageBox::critical(this, "Error", "Failed to create PDF");
        return;
    }

    // PDF styling parameters
    QFont titleFont("Arial", 16, QFont::Bold);
    QFont headerFont("Arial", 10, QFont::Bold);
    QFont contentFont("Arial", 8);
    const int rowHeight = 30;
    int yPos = 100;
    const int xPos = 50;
    const QVector<int> columnWidths {100, 300, 150, 350}; // ID, Name, Contact, Address

    // Draw title
    painter.setFont(titleFont);
    painter.drawText(xPos, yPos, "Institutions Report");
    yPos += 40;

    // Draw headers
    painter.setFont(headerFont);
    int xOffset = xPos;
    QStringList headers = {"ID", "Name", "Contact", "Address"};
    for(int col = 0; col < headers.size(); col++) {
        painter.drawText(xOffset, yPos, headers[col]);
        xOffset += columnWidths[col];
    }
    yPos += rowHeight;

    // Draw data
    painter.setFont(contentFont);
    for(int row = 0; row < model->rowCount(); row++) {
        xOffset = xPos;
        for(int col = 0; col < model->columnCount(); col++) {
            QString text = model->data(model->index(row, col)).toString();
            painter.drawText(xOffset, yPos, columnWidths[col], rowHeight,
                             Qt::TextWordWrap, text);
            xOffset += columnWidths[col];
        }

        yPos += rowHeight;
        if(yPos > printer.height() - 50) {
            printer.newPage();
            yPos = 50;
        }
    }

    painter.end();
    QMessageBox::information(this, "Success", "PDF exported successfully");
}

QLabel* InstitutionWidget::createHighlightLabel(const QString &text, const QColor &color, bool frameOnly)
{
    QLabel *label = new QLabel(text);
    QString style = QString("QLabel {"
                            "  padding: 2px;"
                            "  border-radius: 3px;"
                            "  %1"
                            "  %2"
                            "}").arg(frameOnly ?
                                 QString("border: 2px solid %1; background: transparent;").arg(color.name()) :
                                 QString("background-color: %1; border-left: 3px solid %2;")
                                     .arg(color.lighter(160).name()).arg(color.name()))
                        .arg(frameOnly ? "color: black;" : "color: white;");
    label->setStyleSheet(style);
    label->setAlignment(Qt::AlignCenter);
    return label;
}

void InstitutionWidget::highlightConflicts()
{
    // 1) Clear existing widgets in ID (0) and Address (3) columns
    const int colsToClear[] = { 0, 3 };
    const int rowCount = model->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        for (int colIdx = 0; colIdx < 2; ++colIdx) {
            ui->tableView->setIndexWidget(
                model->index(row, colsToClear[colIdx]),
                nullptr
                );
        }
    }

    // 2) Build maps of contact→rows and address→rows
    QMap<QString, QVector<int>> contactRows;
    QMap<QString, QVector<int>> addressRows;
    for (int row = 0; row < rowCount; ++row) {
        const QString contact = model->data(model->index(row, 2)).toString();
        const QString address = model->data(model->index(row, 3)).toString();
        contactRows[contact].append(row);
        addressRows[address].append(row);
    }

    // 3) Highlight duplicate contacts
    for (auto it = contactRows.constBegin(); it != contactRows.constEnd(); ++it) {
        const QVector<int> &rows = it.value();                // bind by reference
        if (rows.size() > 1) {
            for (int row : rows) {
                ui->tableView->setIndexWidget(
                    model->index(row, 0),
                    createHighlightLabel(u"🚨 Dupe"_qs, Qt::red)
                    );
            }
        }
    }

    // 4) Highlight duplicate addresses (skip empty)
    for (auto it = addressRows.constBegin(); it != addressRows.constEnd(); ++it) {
        const QString &addr = it.key();
        if (addr.isEmpty())
            continue;

        const QVector<int> &rows = it.value();                // bind by reference
        if (rows.size() > 1) {
            for (int row : rows) {
                ui->tableView->setIndexWidget(
                    model->index(row, 3),
                    createHighlightLabel(u"📍"_qs, QColor(255, 165, 0), /*bold=*/true)
                    );
            }
        }
    }
}



void InstitutionWidget::sortTable(int column)
{
    static QMap<int, Qt::SortOrder> sortStates;

    // Get the header text (uppercase for consistency)
    QString headerText = model->headerData(column, Qt::Horizontal).toString().toUpper();

    // Map column headers to database fields
    QMap<QString, QString> columnMapping = {
        {"ID", "INSTITUTION_ID"},
        {"NAME", "NAME"},
        {"CONTACT", "CONTACT_INFO"},
        {"ADDRESS", "ADDRESS"}
    };

    QString orderBy = columnMapping.value(headerText, "INSTITUTION_ID");

    // Toggle sort order
    Qt::SortOrder order = (sortStates[column] == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;
    sortStates[column] = order;

    // Get current query and remove any existing ORDER BY clause
    QString queryStr = model->query().executedQuery();
    static const QRegularExpression orderRegex("ORDER BY.*$", QRegularExpression::CaseInsensitiveOption);
    queryStr.replace(orderRegex, "");

    // Add new ORDER BY clause
    queryStr += " ORDER BY " + orderBy + (order == Qt::DescendingOrder ? " DESC" : " ASC");

    // Execute the sorted query
    model->setQuery(std::move(queryStr));
}
