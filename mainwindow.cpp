#include "mainwindow.h"
#include "ui_institution.h"
#include "connection.h"
#include "ui_mainwindow.h"
#include "user.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QPixmap>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QDebug>
#include <QRegularExpression>
#include "LoginPage.h"
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QTextCursor>
#include <QFileDialog>
#include <QVBoxLayout>

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include "institutionwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QSqlDatabase db = Connection::createConnection();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Could not connect to the database.");
        return;
    }

    setupUI();
    setupConnections();
    loadUsers();

    qDebug() << "Logged-in user:" << currentUser.getFirstname() << currentUser.getLastname();
}

MainWindow::~MainWindow() {
    Connection::closeConnection();
    delete ui;
}

void MainWindow::setupUI() {
    ui->groupBox_bgForm->hide();
    ui->groupBox_userForm->hide();
    ui->tableWidget_users->setVisible(false);
    ui->groupBox_bg_user->setVisible(false);

    ui->comboBox_sort->addItem("First Name (A-Z)");
    ui->comboBox_sort->addItem("First Name (Z-A)");
    ui->comboBox_sort->addItem("Last Name (A-Z)");
    ui->comboBox_sort->addItem("Last Name (Z-A)");

    QPixmap pixmap("C:\\Users\\benrh\\OneDrive\\Pictures\\Screenshots\\im1.png");
    if (!pixmap.isNull()) {
        ui->im1->setPixmap(pixmap.scaled(ui->im1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}


void MainWindow::setupConnections() {
    connect(ui->pushButton_userManagement, &QPushButton::clicked, this, &MainWindow::on_button_userManagement_clicked);
    connect(ui->pushButton_save, &QPushButton::clicked, this, &MainWindow::on_button_save_clicked);
    connect(ui->pushButton_update, &QPushButton::clicked, this, &MainWindow::on_button_update_clicked);
    connect(ui->pushButton_savechanges, &QPushButton::clicked, this, &MainWindow::on_pushButton_savechanges_clicked);
    connect(ui->pushButton_delete, &QPushButton::clicked, this, &MainWindow::on_button_delete_clicked);
    connect(ui->pushButton_exit, &QPushButton::clicked, this, &MainWindow::on_pushButton_exit_clicked);
    connect(ui->pushButton_exit2, &QPushButton::clicked, this, &MainWindow::on_pushButton_exitUserTable_clicked);
    connect(ui->pushButton_search, &QPushButton::clicked, this, &MainWindow::on_pushButton_searchByPhone_clicked);
    connect(ui->tableWidget_users, &QTableWidget::cellClicked,this, &MainWindow::on_tableWidget_users_cellClicked);
    connect(ui->homePageButton, &QPushButton::clicked, this, &MainWindow::onHomePageButtonClicked);
    connect(ui->comboBox_sort, SIGNAL(currentIndexChanged(int)), this, SLOT(sortUsers(int)));
    connect(ui->pushButton_exportPdf, &QPushButton::clicked, this, &MainWindow::on_pushButton_exportPdf_clicked);
    connect(ui->pushButtonShowChart, &QPushButton::clicked, this, &MainWindow::showChartImage);
    connect(ui->pushbutton_institutionManagement, &QPushButton::clicked,
            this, &MainWindow::on_button_institutionManagement_clicked);

}

void MainWindow::on_pushButton_exit_clicked() {
    ui->groupBox_userForm->hide();
    ui->groupBox_bgForm->hide();
    qDebug() << "Exit button pressed: Group boxes hidden.";
}

void MainWindow::on_pushButton_exitUserTable_clicked() {
    ui->tableWidget_users->setVisible(false);
    ui->groupBox_bg_user->setVisible(false);
    qDebug() << "User table and background hidden.";
}

void MainWindow::loadUsers() {
    ui->tableWidget_users->setRowCount(0);

    QSqlDatabase db = Connection::createConnection();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection lost");
        return;
    }

    QSqlQuery query(db);
    if (query.exec("SELECT USER_ID, FIRSTNAME, lASTNAME, PHONE, ROLE, DATETIME, EMAIL FROM users")) {
        while (query.next()) {
            int row = ui->tableWidget_users->rowCount();
            ui->tableWidget_users->insertRow(row);

            ui->tableWidget_users->setItem(row, 0, new QTableWidgetItem(query.value("user_id").toString()));
            ui->tableWidget_users->setItem(row, 1, new QTableWidgetItem(query.value("firstname").toString()));
            ui->tableWidget_users->setItem(row, 2, new QTableWidgetItem(query.value("lastname").toString()));
            ui->tableWidget_users->setItem(row, 3, new QTableWidgetItem("\u2022\u2022\u2022\u2022\u2022\u2022"));
            ui->tableWidget_users->setItem(row, 4, new QTableWidgetItem(query.value("phone").toString()));
            ui->tableWidget_users->setItem(row, 5, new QTableWidgetItem(query.value("role").toString()));
            ui->tableWidget_users->setItem(row,6, new QTableWidgetItem(query.value("email").toString()));
            ui->tableWidget_users->setItem(row, 9, new QTableWidgetItem(query.value("datetime").toString()));
        }
        ui->tableWidget_users->setVisible(true);
        ui->tableWidget_users->setSortingEnabled(true);
    } else {
        QMessageBox::critical(this, "Query Error", query.lastError().text());
    }
}

void MainWindow::clearUserForm() {
    ui->lineEdit_user_id->clear();
    ui->lineEdit_firstname->clear();
    ui->lineEdit_lastname->clear();
    ui->lineEdit_password->clear();
    ui->lineEdit_phone->clear();
    ui->lineEdit_email->clear();
    ui->dateTimeEdit->clear();
    ui->comboBox_role->setCurrentIndex(0);
}

void MainWindow::on_button_userManagement_clicked() {
    bool isVisible = ui->groupBox_userForm->isVisible();
    ui->groupBox_bgForm->setVisible(!isVisible);
    ui->groupBox_userForm->setVisible(!isVisible);
    ui->tableWidget_users->setVisible(true);
    ui->groupBox_bg_user->setVisible(true);
    loadUsers();
}
void MainWindow::on_button_institutionManagement_clicked() {
    InstitutionWindow *institutionWin = new InstitutionWindow(this);  // 'this' sets parent to auto-clean memory
    institutionWin->show();  // Use show() for non-modal window, or exec() for modal if it's a QDialog
}

void MainWindow::on_button_save_clicked() {
    // Retrieve the data from the form
    QString firstNameText = ui->lineEdit_firstname->text().trimmed();
    QString lastNameText = ui->lineEdit_lastname->text().trimmed();
    QString passwordText = ui->lineEdit_password->text();
    QString phoneText = ui->lineEdit_phone->text().trimmed();
    QString roleText = ui->comboBox_role->currentText();
    QString emailText = ui->lineEdit_email->text().trimmed();
    QDateTime dateTimeVal = ui->dateTimeEdit->dateTime();

    // Validation checks for empty fields
    if (firstNameText.isEmpty() || lastNameText.isEmpty() || passwordText.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all required fields.");
        return;
    }

    // Check if names start with a capital letter
    if (!firstNameText[0].isUpper() || !lastNameText[0].isUpper()) {
        QMessageBox::warning(this, "Input Error", "Names must start with a capital letter.");
        return;
    }

    // Validate password length
    if (passwordText.length() < 6) {
        QMessageBox::warning(this, "Input Error", "Password must be at least 6 characters.");
        return;
    }

    // Validate phone number (check if it's a valid number and has at least 8 digits)
    bool phoneConversionOk = false;
    phoneText.toLongLong(&phoneConversionOk);
    if (phoneText.length() < 8 || !phoneConversionOk) {
        QMessageBox::warning(this, "Input Error", "Phone must be a valid number with at least 8 digits.");
        return;
    }

    // Validate email using regular expression
    QRegularExpression emailRegex(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = emailRegex.match(emailText);
    if (!match.hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid email address.");
        return;
    }

    // Create new user (center/equipment removed)
    User newuser(firstNameText, lastNameText, passwordText, phoneText, roleText, emailText, dateTimeVal);

    // Save to database
    if (newuser.saveToDatabase()) {
        QMessageBox::information(this, "Success", "User added successfully.");
        loadUsers();
    } else {
        QMessageBox::critical(this, "Error", "Could not add user.");
    }

    clearUserForm();
}



void MainWindow::on_pushButton_savechanges_clicked() {
    // Get the input values from the UI
    QString userId = ui->lineEdit_user_id->text();
    QString firstname = ui->lineEdit_firstname->text();
    QString lastname = ui->lineEdit_lastname->text();
    QString password = ui->lineEdit_password->text();
    QString phone = ui->lineEdit_phone->text();
    QString email = ui->lineEdit_email->text();
    QString role = ui->comboBox_role->currentText();
    QDateTime dateTime = ui->dateTimeEdit->dateTime();

    // Validation for empty fields
    if (userId.isEmpty() || firstname.isEmpty() || lastname.isEmpty() || password.isEmpty() ||
        phone.isEmpty() || email.isEmpty() || role.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
        return;
    }

    // Check if email is already used by another user
    if (checkIfEmailExists(email, userId)) {
        QMessageBox::warning(this, "Input Error", "This email is already used by another user.");
        return;
    }

    // Update the user info in the database
    User user;
    user.setUserId(userId);
    user.setFirstname(firstname);
    user.setLastname(lastname);
    user.setPassword(password); // Ideally hash this before saving
    user.setPhone(phone);
    user.setemail(email);
    user.setRole(role);
    user.setDateTime(dateTime);

    if (user.updateToDatabase()) {
        QMessageBox::information(this, "Success", "User info updated successfully.");
        ui->groupBox_userForm->setVisible(false);
        ui->groupBox_bgForm->setVisible(false);
        loadUsers(); // Refresh the user table
    } else {
        QMessageBox::critical(this, "Error", "Failed to update user.");
    }
}

bool MainWindow::checkIfEmailExists(const QString &email, const QString &userId) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE email = :email AND user_id != :user_id");
    query.bindValue(":email", email);
    query.bindValue(":user_id", userId);  // Ensuring that the current user's ID is excluded

    if (query.exec()) {
        query.next();
        int count = query.value(0).toInt();  // Get the number of rows returned
        qDebug() << "Email check: count=" << count;
        return count > 0;  // Return true if the email exists, otherwise false
    } else {
        qDebug() << "Error checking email: " << query.lastError().text();
        return false;  // If query fails, return false
    }
}

void MainWindow::on_button_delete_clicked() {
    QString userId = ui->lineEdit_user_id2->text().trimmed();

    if (userId.isEmpty()) {
        // Ask whether to delete all or just one user
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Delete Options");
        msgBox.setText("Who do you want to delete?");
        msgBox.setIcon(QMessageBox::Question);

        QPushButton *allUsersButton = msgBox.addButton("All Users", QMessageBox::AcceptRole);
        QPushButton *oneUserButton = msgBox.addButton("Just One User", QMessageBox::ActionRole);

        msgBox.exec();

        if (msgBox.clickedButton() == allUsersButton) {
            QSqlDatabase db = Connection::getDatabase();
            if (!db.isOpen()) {
                QMessageBox::critical(this, "Error", "Database connection lost");
                return;
            }

            QSqlQuery query(db);
            if (query.exec("DELETE FROM users")) {
                QMessageBox::information(this, "Success", "All users were successfully deleted.");
                loadUsers();
            } else {
                QMessageBox::critical(this, "Error", "Failed to delete users.");
            }

        } else if (msgBox.clickedButton() == oneUserButton) {
            QMessageBox::information(this, "Info", "Please enter the User ID to delete and press delete again.");
            ui->lineEdit_user_id2->setFocus();
        }

    } else {
        // Confirmation before deleting the specific user
        QMessageBox confirmBox;
        confirmBox.setWindowTitle("Confirm Deletion");
        confirmBox.setText("Are you sure you want to delete the user with ID: " + userId + "?");
        confirmBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        confirmBox.setIcon(QMessageBox::Warning);

        if (confirmBox.exec() == QMessageBox::Yes) {
            User user;
            user.setUserId(userId);

            if (user.deleteFromDatabase()) {
                QMessageBox::information(this, "Success", "User deleted successfully.");
                ui->lineEdit_user_id2->clear(); // Clear field
                loadUsers();
            } else {
                QMessageBox::critical(this, "Error", "Failed to delete user. ID might not exist.");
            }
        }
    }
}

void MainWindow::on_button_update_clicked() {
    QString userId = ui->lineEdit_user_id->text();

    // Check if the user ID field is empty
    if (userId.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter the user ID to update.");
        return;
    }

    // Create a user object to search for the user
    User user;

    // Search for the user by the ID
    if (user.searchUserById(userId)) {
        // Populate the form fields with their data
        ui->lineEdit_firstname->setText(user.getFirstname());
        ui->lineEdit_lastname->setText(user.getLastname());
        ui->lineEdit_password->setText(user.getPassword()); // Should be hashed ideally
        ui->lineEdit_phone->setText(user.getPhone());
        ui->lineEdit_email->setText(user.getemail());
        ui->comboBox_role->setCurrentText(user.getRole());
        ui->dateTimeEdit->setDateTime(user.getDateTime());

        // Show the groupBox_userForm and background form
        ui->groupBox_userForm->setVisible(true);
        ui->groupBox_bgForm->setVisible(true);

        // Change the button text to "Save Changes"
        ui->pushButton_savechanges->setVisible(true);  // Make the Save Changes button visible
    } else {
        // If user is not found, show a message box
        QMessageBox::information(this, "Not Found", "User not found.");
    }
}

void MainWindow::on_tableWidget_users_cellClicked(int row, int /*column*/) {
    // Assuming the user ID is in column 0 of the table
    QTableWidgetItem *item = ui->tableWidget_users->item(row, 0);
    if (item) {
        QString userId = item->text();
        ui->lineEdit_user_id->setText(userId);
        ui->lineEdit_user_id2->setText(userId);
        qDebug() << "User ID" << userId << "loaded into ID field.";
    }
}
void MainWindow::on_pushButton_searchByPhone_clicked() {
    // Get the phone number from the input field and trim any extra spaces
    QString phoneNumber = ui->lineEdit_phoneSearch->text().trimmed();

    // Check if the phone number field is empty
    if (phoneNumber.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a phone number to search.");
        return;
    }

    // Create a User object and search by the phone number
    User user;
    bool found = false;  // Variable to track if the user was found

    // Assuming the search method looks something like this
    if (user.searchUserByPhone(phoneNumber, found)) {
        if (found) {
            ui->lineEdit_user_id->setText(user.getUserId());
            ui->lineEdit_firstname->setText(user.getFirstname());
            ui->lineEdit_lastname->setText(user.getLastname());
            ui->lineEdit_phone->setText(user.getPhone());
            ui->comboBox_role->setCurrentText(user.getRole());
            ui->lineEdit_email->setText(user.getemail());
            ui->dateTimeEdit->setDateTime(user.getDateTime());
            QMessageBox::information(this, "User Found", "User found and displayed.");
        } else {
            QMessageBox::information(this, "Not Found", "No user found with that phone number.");
        }
    } else {
        QMessageBox::critical(this, "Error", "An error occurred while searching for the user.");
    }
}

void MainWindow::onHomePageButtonClicked()
{
    // Create a new LoginPage instance
    LoginPage *loginPage = new LoginPage();
    loginPage->show();  // Show LoginPage

    this->close();  // Optionally close MainWindow
}
void MainWindow::sortUsers(int index) {
    switch (index) {
    case 0: // First Name (A-Z)
        ui->tableWidget_users->sortByColumn(1, Qt::AscendingOrder);  // Assuming first name is in column 1
        break;
    case 1: // First Name (Z-A)
        ui->tableWidget_users->sortByColumn(1, Qt::DescendingOrder);
        break;
    case 2: // Last Name (A-Z)
        ui->tableWidget_users->sortByColumn(2, Qt::AscendingOrder);  // Assuming last name is in column 2
        break;
    case 3: // Last Name (Z-A)
        ui->tableWidget_users->sortByColumn(2, Qt::DescendingOrder);
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButton_exportPdf_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", "", "*.pdf");
    if (fileName.isEmpty())
        return;

    if (!fileName.endsWith(".pdf"))
        fileName += ".pdf";

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    QTextDocument doc;
    QTextCursor cursor(&doc);
    cursor.insertHtml("<h2>User List</h2>");
    cursor.insertHtml("<table border='1' cellspacing='0' cellpadding='2'>");

    // Headers
    cursor.insertHtml("<tr>");
    for (int col = 0; col < ui->tableWidget_users->columnCount(); ++col) {
        cursor.insertHtml("<th>" + ui->tableWidget_users->horizontalHeaderItem(col)->text() + "</th>");
    }
    cursor.insertHtml("</tr>");

    // Rows
    for (int row = 0; row < ui->tableWidget_users->rowCount(); ++row) {
        cursor.insertHtml("<tr>");
        for (int col = 0; col < ui->tableWidget_users->columnCount(); ++col) {
            QTableWidgetItem *item = ui->tableWidget_users->item(row, col);
            cursor.insertHtml("<td>" + (item ? item->text() : "") + "</td>");
        }
        cursor.insertHtml("</tr>");
    }

    cursor.insertHtml("</table>");

    doc.print(&printer);
    QMessageBox::information(this, "PDF Export", "PDF exported successfully 🎉");
}
void MainWindow::showChartImage() {
    // Load the image from file
    QPixmap chartImage("C:\\Users\\benrh\\OneDrive\\Pictures\\Screenshots\\piechart.png");

    // Check if the image was loaded successfully
    if (chartImage.isNull()) {
        qWarning() << "Failed to load the image.";
        return;
    }

    // Create a QLabel to display the image
    QLabel *chartLabel = new QLabel(this);
    chartLabel->setPixmap(chartImage);
    chartLabel->setAlignment(Qt::AlignCenter);

    // Create a layout to display the image
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartLabel);

    // Create a widget to hold the layout
    QWidget *imageWidget = new QWidget();
    imageWidget->setLayout(layout);

    // Show the image widget
    imageWidget->show();
}

void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);
    QPixmap pixmap("C:\\Users\\benrh\\OneDrive\\Pictures\\Screenshots\\im1.png");
    if (!pixmap.isNull()) {
        ui->im1->setPixmap(pixmap.scaled(ui->im1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}
