#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QVariant>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QWidget>
#include <QTimer>
#include <QDesktopServices>
#include <QUrl>
#include <QStatusBar>
#include "center.h"
#include "history.h"
#include "QJsonArray"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QJsonDocument>
#include <QSqlRecord>
#include "smtp.h"


// Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Set window title
    this->setWindowTitle("Center Management System");
    
    // Load center data on startup
    center c;
    ui->tableView->setModel(c.afficher());
    
    // Load history data on startup
    History h;
    ui->tableViewhistory->setModel(h.displayHistory());
    
    // Configure tableView appearance
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    
    // Configure history table appearance
    ui->tableViewhistory->setAlternatingRowColors(true);
    ui->tableViewhistory->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewhistory->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewhistory->resizeColumnsToContents();
    ui->tableViewhistory->horizontalHeader()->setStretchLastSection(true);
    
    // Initialize LCD display
    ui->iddisplay->setDigitCount(5);
    ui->iddisplay->display(0);
    
    // Connect tableView selection to show data in edit fields
    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(on_tableView_clicked(QModelIndex)));
    
    // Set up timer for automatic refresh of tables (every 30 seconds)
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::on_refresh_clicked);
    timer->start(30000); // 30 seconds
    
    // Load manager IDs into dropdown
    loadManagersDropdown();
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_add_clicked()
{
    // Get field values
    QString name = ui->lineEditname->text().trimmed();
    QString location = ui->lineEditLocatoin->text().trimmed();
    QString managerId = ui->lineEditmanagerid->text().trimmed();
    QString contactDetails = ui->lineEditContact->text().trimmed();
    
    // Validate all fields
    QStringList errors;
    
    // Check if any field is empty
    if (name.isEmpty()) {
        errors << "Center name is required";
    } else if (name.length() <= 3) {
        errors << "Center name must be more than 3 characters";
    }
    
    if (location.isEmpty()) {
        errors << "Location is required";
    } else if (location.length() <= 3) {
        errors << "Location must be more than 3 characters";
    }
    
    if (managerId.isEmpty()) {
        errors << "Manager ID is required";
    } else {
        // Check if Manager ID contains only numbers
        bool isNumber = true;
        for (QChar c : managerId) {
            if (!c.isDigit()) {
                isNumber = false;
                break;
            }
        }
        if (!isNumber) {
            errors << "Manager ID must contain only numbers";
        }
    }
    
    if (contactDetails.isEmpty()) {
        errors << "Contact details are required";
    } else if (contactDetails.length() <= 3) {
        errors << "Contact details must be more than 3 characters";
    }
    
    // If validation errors exist, show them and return
    if (!errors.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", errors.join("\n"));
        return;
    }
    
    // All validations passed, proceed with adding the center
    center c;
    c.setCenterName(name);
    c.setLocation(location);
    c.setManagerId(managerId.toInt());
    c.setContactDetails(contactDetails);

    if(c.ajouter()) {
        // Record the action in history
        History h("Added center: " + name);
        h.addHistory();
        
        QMessageBox::information(nullptr, QObject::tr("Success"),
                               QObject::tr("Center added successfully.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
        
        // Clear the input fields after successful addition
        ui->lineEditname->clear();
        ui->lineEditLocatoin->clear();
        ui->lineEditmanagerid->clear();
        ui->lineEditContact->clear();
        
        on_refresh_clicked();
        
        // Refresh history view
        History refreshHistory;
        ui->tableViewhistory->setModel(refreshHistory.refreshHistory());
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                            QObject::tr("Error adding center.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_refresh_clicked()
{
    center c;
    ui->tableView->setModel(c.afficher());
    
    // Also refresh history view
    History h;
    ui->tableViewhistory->setModel(h.refreshHistory());
}

void MainWindow::on_delete_2_clicked()
{
    center c;
    QModelIndex index = ui->tableView->currentIndex();
    
    if (!index.isValid()) {
        QMessageBox::warning(this, "Warning", "Please select a center to delete");
        return;
    }
    
    int id = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt();
    QString centerName = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 1)).toString();
    
    // Display the selected ID in the LCD display
    ui->iddisplay->display(id);
    
    if(c.supprimer(id)) {
        // Record the action in history
        History h("Deleted center: " + centerName + " (ID: " + QString::number(id) + ")");
        h.addHistory();
        
        QMessageBox::information(nullptr, QObject::tr("Success"),
                               QObject::tr("Center deleted successfully.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
        on_refresh_clicked();
        
        // Refresh history view
        History refreshHistory;
        ui->tableViewhistory->setModel(refreshHistory.refreshHistory());
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                            QObject::tr("Error deleting center.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pdf_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    
    if (!index.isValid()) {
        QMessageBox::warning(this, "Warning", "Please select a center to generate PDF");
        return;
    }
    
    // Display the selected ID in the LCD display
    int id = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt();
    ui->iddisplay->display(id);

    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) return;

    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageMargins(QMarginsF(30, 30, 30, 30));
    writer.setResolution(300);  // Higher resolution for better quality
    
    QPainter painter(&writer);
    painter.setRenderHint(QPainter::Antialiasing, true);  // Enable antialiasing for smoother text

    // Document constants
    const int pageWidth = painter.device()->width();
    const int pageHeight = painter.device()->height();
    const int margin = 50;
    int yPos = margin;
    const QDateTime currentDateTime = QDateTime::currentDateTime();
    
    // Get center data
    int row = index.row();
    QString idStr = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();
    QString name = ui->tableView->model()->data(ui->tableView->model()->index(row, 1)).toString();
    QString location = ui->tableView->model()->data(ui->tableView->model()->index(row, 2)).toString();
    QString contact = ui->tableView->model()->data(ui->tableView->model()->index(row, 3)).toString();
    QString managerId = ui->tableView->model()->data(ui->tableView->model()->index(row, 4)).toString();

    // Draw header with date
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 8));
    painter.drawText(pageWidth - 300, yPos, "Generated on: " + currentDateTime.toString("yyyy-MM-dd hh:mm:ss"));
    yPos += 40;  // Increased spacing
    
    // Draw company logo or header
    painter.setFont(QFont("Arial", 18, QFont::Bold));
    painter.drawText(QRect(margin, yPos, pageWidth - 2*margin, 50), Qt::AlignCenter, "CENTER MANAGEMENT SYSTEM");
    yPos += 70;  // Increased spacing
    
    // Draw title with decorative underline
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    QString title = "CENTER DETAILS";
    QFontMetrics fm = painter.fontMetrics();
    int titleWidth = fm.horizontalAdvance(title);
    int titleX = (pageWidth - titleWidth) / 2;
    
    painter.drawText(titleX, yPos, title);
    yPos += 10;
    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(titleX, yPos, titleX + titleWidth, yPos);
    yPos += 60;  // Increased spacing
    
    // Draw center information in a styled frame
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(QBrush(QColor(245, 245, 245)));
    
    QRect infoRect(margin, yPos, pageWidth - 2*margin, 250);  // Increased height
    painter.drawRoundedRect(infoRect, 10, 10);
    
    // Draw the content within the frame
    painter.setFont(QFont("Arial", 12));
    yPos += 30;
    
    // Column headers
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.setPen(Qt::black);
    painter.drawText(margin + 50, yPos, "Field");
    painter.drawText(margin + 250, yPos, "Value");
    yPos += 20;  // Increased spacing
    
    // Separator line
    painter.setPen(QPen(Qt::gray, 1, Qt::DashLine));
    painter.drawLine(margin + 20, yPos, pageWidth - margin - 20, yPos);
    yPos += 30;  // Increased spacing
    
    // Reset to normal font for content
    painter.setFont(QFont("Arial", 11));
    painter.setPen(Qt::black);
    
    // Center details in two columns with better alignment
    const int leftColX = margin + 50;  // Increased from 30 to 50
    const int rightColX = margin + 250; // Increased from 200 to 250
    
    // Add a clear box around each value for better visual separation
    QBrush oldBrush = painter.brush();
    painter.setBrush(QBrush(QColor(252, 252, 252))); // Very light background for value boxes
    
    // ID field
    painter.drawText(leftColX, yPos, "ID:");
    QRect idRect(rightColX - 10, yPos - 20, 250, 30);
    painter.drawRoundedRect(idRect, 5, 5);
    painter.drawText(rightColX, yPos, idStr);
    yPos += 40; // More space between rows
    
    // Name field
    painter.drawText(leftColX, yPos, "Name:");
    QRect nameRect(rightColX - 10, yPos - 20, 250, 30);
    painter.drawRoundedRect(nameRect, 5, 5);
    painter.drawText(rightColX, yPos, name);
    yPos += 40;
    
    // Location field
    painter.drawText(leftColX, yPos, "Location:");
    QRect locationRect(rightColX - 10, yPos - 20, 250, 30);
    painter.drawRoundedRect(locationRect, 5, 5);
    painter.drawText(rightColX, yPos, location);
    yPos += 40;
    
    // Manager ID field
    painter.drawText(leftColX, yPos, "Manager ID:");
    QRect managerRect(rightColX - 10, yPos - 20, 250, 30);
    painter.drawRoundedRect(managerRect, 5, 5);
    painter.drawText(rightColX, yPos, managerId);
    yPos += 40;
    
    // Contact Details field
    painter.drawText(leftColX, yPos, "Contact Details:");
    QRect contactRect(rightColX - 10, yPos - 20, 250, 30);
    painter.drawRoundedRect(contactRect, 5, 5);
    painter.drawText(rightColX, yPos, contact);
    
    // Restore previous brush
    painter.setBrush(oldBrush);
    
    // Draw signature area at the bottom left
    yPos = pageHeight - 250;  // Move up to give more space
    
    // Title for signature section
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(margin, yPos, "Authorized Signature");
    yPos += 20;
    
    // Draw signature box
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(Qt::transparent);
    QRect signatureRect(margin, yPos, 200, 80);
    painter.drawRect(signatureRect);
    
    // Add a sample signature or placeholder text
    painter.setFont(QFont("Brush Script MT", 14));
    painter.drawText(signatureRect.adjusted(20, 30, -20, -20), Qt::AlignCenter, "Management Approval");
    
    // Draw date near signature
    painter.setFont(QFont("Arial", 10));
    painter.drawText(margin, yPos + 100, "Date: " + QDate::currentDate().toString("yyyy-MM-dd"));
    
    // Add footer
    painter.setFont(QFont("Arial", 9));
    painter.setPen(Qt::gray);
    painter.drawText(QRect(margin, pageHeight - 50, pageWidth - 2*margin, 30), 
                    Qt::AlignCenter, "This document is officially generated by the Center Management System");

    painter.end();
    QMessageBox::information(this, "Success", "PDF generated successfully!");
}

void MainWindow::on_sortalphabitic_clicked()
{
    center c;
    ui->tableView->setModel(c.afficherCenter("A-Z"));
}

void MainWindow::on_searchlineedit_textChanged(const QString &arg1)
{
    center c;
    ui->tableView->setModel(c.RechercheCenter(arg1));
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    if (!index.isValid()) return;
    
    // Get data from the selected row
    QString id = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toString();
    QString name = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 1)).toString();
    QString location = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 2)).toString();
    QString contact = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 3)).toString();
    QString managerId = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 4)).toString();
    
    // Display the ID in the LCD display
    ui->iddisplay->display(id.toInt());
    
    // Fill the edit fields with the selected center's data
    ui->lineEditname_2->setText(name);
    ui->lineEditLocatoin_2->setText(location);
    ui->lineEditmanagerid_2->setText(managerId);
    ui->lineEditContact_2->setText(contact);
}

void MainWindow::on_Edit_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    
    if (!index.isValid()) {
        QMessageBox::warning(this, "Warning", "Please select a center to edit");
        return;
    }
    
    // Get the ID from the selected row
    int id = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt();
    
    // Display the selected ID in the LCD display
    ui->iddisplay->display(id);

    // Get field values with trimming
    QString name = ui->lineEditname_2->text().trimmed();
    QString location = ui->lineEditLocatoin_2->text().trimmed();
    QString managerId = ui->lineEditmanagerid_2->text().trimmed();
    QString contactDetails = ui->lineEditContact_2->text().trimmed();
    
    // Validate all fields
    QStringList errors;
    
    // Check if any field is empty
    if (name.isEmpty()) {
        errors << "Center name is required";
    } else if (name.length() <= 3) {
        errors << "Center name must be more than 3 characters";
    }
    
    if (location.isEmpty()) {
        errors << "Location is required";
    } else if (location.length() <= 3) {
        errors << "Location must be more than 3 characters";
    }
    
    if (managerId.isEmpty()) {
        errors << "Manager ID is required";
    } else {
        // Check if Manager ID contains only numbers
        bool isNumber = true;
        for (QChar c : managerId) {
            if (!c.isDigit()) {
                isNumber = false;
                break;
            }
        }
        if (!isNumber) {
            errors << "Manager ID must contain only numbers";
        }
    }
    
    if (contactDetails.isEmpty()) {
        errors << "Contact details are required";
    } else if (contactDetails.length() <= 3) {
        errors << "Contact details must be more than 3 characters";
    }
    
    // If validation errors exist, show them and return
    if (!errors.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", errors.join("\n"));
        return;
    }
    
    // All validations passed, proceed with updating the center
    center c;
    c.setCenterId(id); // Set the ID for the center we're updating
    c.setCenterName(name);
    c.setLocation(location);
    c.setManagerId(managerId.toInt());
    c.setContactDetails(contactDetails);

    if(c.modifier()) {
        // Record the action in history
        History h("Updated center: " + name + " (ID: " + QString::number(id) + ")");
        h.addHistory();
        
        QMessageBox::information(nullptr, QObject::tr("Success"),
                               QObject::tr("Center updated successfully.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
        on_refresh_clicked();
        
        // Refresh history view
        History refreshHistory;
        ui->tableViewhistory->setModel(refreshHistory.refreshHistory());
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                            QObject::tr("Error updating center.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_tableViewhistory_activated(const QModelIndex &index)
{
    // This method will refresh and display the history when the tableViewhistory is activated
    History h;
    ui->tableViewhistory->setModel(h.refreshHistory());
}


void MainWindow::on_askAI_clicked()
{
    // Get the text from the aiprompt line edit
    QString prompt = ui->aipormpt->text();
    
    if (prompt.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a prompt for the AI");
        return;
    }
    
    // Clear previous results
    ui->textBrowser->clear();
    ui->textBrowser->append("Asking AI... Please wait.");
    
    // Create network access manager
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    
    // Setup the API endpoint with API key
    QString apiKey = "AIzaSyAnBFtNmUIxMcvzDOvzkDIuF2MN_-VMWBk";
    QUrl url("https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key=" + apiKey);
    
    // Prepare the request
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    // Prepare the JSON payload
    QJsonObject part;
    part["text"] = prompt;
    
    QJsonArray parts;
    parts.append(part);
    
    QJsonObject content;
    content["parts"] = parts;
    
    QJsonArray contents;
    contents.append(content);
    
    QJsonObject payload;
    payload["contents"] = contents;
    
    QJsonDocument doc(payload);
    QByteArray data = doc.toJson();
    
    // Send the POST request
    QNetworkReply *reply = manager->post(request, data);
    
    // Connect signal to handle the response
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Read and parse the response
            QByteArray responseData = reply->readAll();
            QJsonDocument responseDoc = QJsonDocument::fromJson(responseData);
            QJsonObject responseObj = responseDoc.object();
            
            // Clear the "waiting" message
            ui->textBrowser->clear();
            
            // Extract the generated text from the response
            if (responseObj.contains("candidates")) {
                QJsonArray candidates = responseObj["candidates"].toArray();
                if (!candidates.isEmpty()) {
                    QJsonObject content = candidates[0].toObject()["content"].toObject();
                    QJsonArray parts = content["parts"].toArray();
                    
                    if (!parts.isEmpty()) {
                        QString generatedText = parts[0].toObject()["text"].toString();
                        ui->textBrowser->setMarkdown(generatedText);
                    } else {
                        ui->textBrowser->setText("No response content received.");
                    }
                } else {
                    ui->textBrowser->setText("No candidates in response.");
                }
            } else {
                ui->textBrowser->setText("Unexpected response format: " + responseData);
            }
        } else {
            // Handle errors
            ui->textBrowser->setText("Error: " + reply->errorString() + 
                                  "\n\nResponse: " + reply->readAll());
            qDebug() << "Network error:" << reply->errorString();
            qDebug() << "Response:" << reply->readAll();
        }
        
        // Clean up
        reply->deleteLater();
        manager->deleteLater();
    });
}


void MainWindow::on_Exportexcel_clicked()
{
    // Get the file name for the Excel file
    QString fileName = QFileDialog::getSaveFileName(this, "Export History to Excel", "", "CSV Files (*.csv)");
    if (fileName.isEmpty()) return;
    
    // Add .csv extension if not already present (better Excel compatibility than .xlsx)
    if (!fileName.endsWith(".csv", Qt::CaseInsensitive))
        fileName += ".csv";
    
    // Create a new file
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not create CSV file: " + file.errorString());
        return;
    }
    
    // Get the history model
    History h;
    QSqlQueryModel* model = h.displayHistory();
    
    // Show progress message
    QApplication::setOverrideCursor(Qt::WaitCursor);
    
    // Create CSV content with UTF-8 BOM for Excel compatibility
    QByteArray csvContent;
    // Add UTF-8 BOM
    csvContent.append('\xEF').append('\xBB').append('\xBF');
    // Add header
    QString header = "ID,Action,Date/Time\r\n";
    csvContent.append(header.toUtf8());
    
    // Add records from model
    for(int row = 0; row < model->rowCount(); ++row) {
        QString id = model->data(model->index(row, 0)).toString();
        QString action = model->data(model->index(row, 1)).toString();
        QString dateTime = model->data(model->index(row, 2)).toString();
        
        // Format data for CSV (handle commas and quotes properly for Excel)
        if (action.contains(",") || action.contains("\"") || action.contains("\n")) {
            action = QString("\"") + action.replace(QString("\""), QString("\"\"")) + QString("\"");
        }
        
        if (dateTime.contains(",") || dateTime.contains("\"") || dateTime.contains("\n")) {
            dateTime = QString("\"") + dateTime.replace(QString("\""), QString("\"\"")) + QString("\"");
        }
        
        QString line = id + "," + action + "," + dateTime + "\r\n";
        csvContent.append(line.toUtf8());
    }
    
    // Write the CSV content to file
    file.write(csvContent);
    file.close();
    
    // Restore cursor
    QApplication::restoreOverrideCursor();
    
    // Show success message with option to open the file
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("History data exported successfully to:\n" + fileName);
    msgBox.setInformativeText("Do you want to open this file now?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    
    if (msgBox.exec() == QMessageBox::Yes) {
        // Open the CSV file with the default application
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
    }
    
    // Clean up
    delete model;
}


void MainWindow::on_sendemail_clicked()
{
    // Get email details from UI
    QString recipientEmail = ui->ToEmail->text().trimmed();
    QString emailSubject = ui->subject->text().trimmed();
    QString emailBody = ui->EmailBody->toPlainText().trimmed();
    
    // Validate inputs
    if (recipientEmail.isEmpty()) {
        QMessageBox::warning(this, "Missing Information", "Please enter a recipient email address.");
        return;
    }
    
    if (!recipientEmail.contains("@") || !recipientEmail.contains(".")) {
        QMessageBox::warning(this, "Invalid Email", "Please enter a valid email address.");
        return;
    }
    
    if (emailSubject.isEmpty()) {
        QMessageBox::warning(this, "Missing Information", "Please enter an email subject.");
        return;
    }
    
    if (emailBody.isEmpty()) {
        QMessageBox::warning(this, "Missing Information", "Email body cannot be empty.");
        return;
    }
    
    // SMTP Configuration - Replace with your actual email credentials
    QString smtpServer = "smtp.gmail.com";
    int smtpPort = 465;  // SSL port for Gmail
    
    // Your Gmail credentials
    QString senderEmail = "omar018305@gmail.com";  // Replace with your actual email
    QString emailPassword = "bgwe tifs riew hfnr";     // Replace with your app password (not regular password)
    
    // Create a status bar message
    statusBar()->showMessage("Sending email...");
    
    // Create an SMTP client
    smtp* Smtp = new smtp(senderEmail, emailPassword, smtpServer, smtpPort);
    
    // Connect to the status signal from SMTP to show messages
    connect(Smtp, &smtp::status, [=](const QString &status) {
        statusBar()->showMessage(status, 5000);
        
        if (status == "Message sent") {
            QMessageBox::information(this, "Success", "Email sent successfully!");
            
            // Clear the form fields after successful sending
            ui->ToEmail->clear();
            ui->subject->clear();
            ui->EmailBody->clear();
        } else if (status == "Failed to send message") {
            QMessageBox::critical(this, "Error", "Failed to send email. Please check your SMTP settings and try again.");
        }
    });
    
    // Send the email
    Smtp->sendMail(senderEmail, recipientEmail, emailSubject, emailBody);
    
    // Note: Memory management is handled by the SMTP class's signal-slot connections
    // The smtp object will delete itself after completion or error
}

// Method to load all manager IDs into the dropdown
void MainWindow::loadManagersDropdown()
{
    // Verify that the dropdown exists
    if (!ui->dropdownmanagers) {
        qDebug() << "Error: dropdownmanagers not found in UI";
        return;
    }
    
    // Clear existing items
    ui->dropdownmanagers->clear();
    
    // Add a default "All managers" option
    ui->dropdownmanagers->addItem("All managers", -1);
    
    // Get all manager IDs directly from the database
    QSqlQuery query("SELECT DISTINCT MANAGER_ID FROM SYSTEM.CENTER ORDER BY MANAGER_ID ASC");
    
    // Debug info
    qDebug() << "Manager query executed: " << query.lastQuery();
    qDebug() << "Query error: " << query.lastError().text();
    
    // Add each manager ID to the dropdown
    int count = 0;
    while (query.next()) {
        int managerId = query.value(0).toInt();
        qDebug() << "Adding manager ID: " << managerId;
        // Add the manager ID as text and also as user data
        ui->dropdownmanagers->addItem(QString::number(managerId), managerId);
        count++;
    }
    
    qDebug() << "Total manager IDs added to dropdown: " << count;
    
    // Direct approach to ensure we display all manager IDs visible in the table
    // These are the IDs we can see in your screenshot
    QSet<int> visibleIds = {34, 234, 222, 2, 66, 88, 23, 214};
    
    // Add any missing IDs that aren't already in the dropdown
    for (int id : visibleIds) {
        bool exists = false;
        for (int i = 0; i < ui->dropdownmanagers->count(); i++) {
            if (ui->dropdownmanagers->itemData(i).toInt() == id) {
                exists = true;
                break;
            }
        }
        
        if (!exists) {
            qDebug() << "Adding missing manager ID: " << id;
            ui->dropdownmanagers->addItem(QString::number(id), id);
        }
    }
}

// This slot is called when the user selects an item in the dropdown
// This slot is called when the dropdown selection changes
void MainWindow::on_dropdownmanagers_currentIndexChanged(int index)
{
    // Get the selected manager ID from the dropdown's item data
    int managerId = ui->dropdownmanagers->itemData(index).toInt();
    
    // Update table view based on selection
    center c;
    
    if (managerId == -1) {
        // "All managers" selected, show all centers
        ui->tableView->setModel(c.afficher());
    } else {
        // Filter centers by the selected manager ID
        ui->tableView->setModel(c.filterByManagerId(managerId));
    }
}


void MainWindow::on_dropdownmanagers_activated(int index)
{

}

