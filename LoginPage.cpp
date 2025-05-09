#include "LoginPage.h"
#include "ui_LoginPage.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDateTime>
#include <QMessageBox>
#include "user.h"
#include "twofadialog.h"
#include "emailservice.h"
#include "smsservice.h"
#include "verificationservice.h"
#include "institutionwindow.h"


LoginPage::LoginPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginPage),
    currentUser("", "", "", "", "", "", QDateTime::currentDateTime())  // Initialize currentUser with default values
{
    ui->setupUi(this);
    twoFAService = new TwoFAService(this);

    ui->signUpGroupBox->hide();
    QPixmap pixmap("C:\\Users\\benrh\\OneDrive\\Pictures\\Frame2.png");
    if (!pixmap.isNull()) {
        ui->frame2->setPixmap(pixmap.scaled(ui->frame2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    connect(ui->loginButton, &QPushButton::clicked, this, &LoginPage::onSubmitLoginButtonClicked);
    connect(ui->signUpButton, &QPushButton::clicked, this, &LoginPage::onSignUpClicked);
    connect(ui->cancelSignUpButton, &QPushButton::clicked, this, &LoginPage::onCancelSignUpButtonClicked);
    connect(ui->submitSignUpButton, &QPushButton::clicked, this, &LoginPage::onSubmitSignUpButtonClicked);
}

LoginPage::~LoginPage() {
    delete ui;
}

bool LoginPage::isAuthenticated() const {
    return authenticated;
}

void LoginPage::onSubmitLoginButtonClicked() {
    QString firstName = ui->firstNameLineEdit->text();
    QString lastName = ui->lastNameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (firstName.isEmpty() || lastName.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return;
    }

    if (currentUser.login(firstName, lastName, password)) {
        QMessageBox::information(this, "Login Success", "Login successful!");

        if (currentUser.login(firstName, lastName, password)) {
            QMessageBox::information(this, "Login Success", "Login successful!");

            institutionWindow = new InstitutionWindow();
            institutionWindow->show();

            this->close();
        }


        this->close();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid credentials.");
    }
}


void LoginPage::onSignUpClicked() {
    ui->signUpGroupBox->show();
    ui->loginGroupBox->hide();
}

void LoginPage::onSubmitSignUpButtonClicked() {
    QString firstName = ui->signUpFirstNameLineEdit->text().trimmed();
    QString lastName = ui->signUpLastNameLineEdit->text().trimmed();
    QString phone = ui->phoneLineEdit->text().trimmed();
    QString email = ui->emailLineEdit->text().trimmed();
    QString password = ui->signUpPasswordLineEdit->text();
    QString confirmPassword = ui->confirmPasswordLineEdit->text();

    if (firstName.isEmpty() || lastName.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all required fields.");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Password Mismatch", "Passwords do not match.");
        return;
    }

    User newUser;
    newUser.setFirstname(firstName);
    newUser.setLastname(lastName);
    newUser.setPhone(phone);
    newUser.setemail(email);
    newUser.setPassword(password);
    newUser.setRole("employee");
    newUser.setDateTime(QDateTime::currentDateTime());

    if (newUser.saveToDatabase()) {
        QMessageBox::information(this, "Sign Up Success", "Account created successfully!");

        // Generate the verification code using TwoFAService
        QString code = twoFAService->generateCode();

        // Send email with a verification code
        EmailService *emailService = new EmailService(this);
        QString emailBody = "Your verification code is: " + code;
        emailService->sendEmail(email, "Verify Your Account", emailBody);

        // Send SMS with a 2FA code (optional)
        SMSService *smsService = new SMSService(this);
        QString smsBody = "Your 2FA code is: " + code;
        smsService->sendSMS(phone, smsBody);

        // Clear sign-up fields
        ui->firstNameLineEdit->setText("");
        ui->lastNameLineEdit->setText("");
        ui->passwordLineEdit->setText("");
        ui->confirmPasswordLineEdit->setText("");
        ui->phoneLineEdit->setText("");
        ui->emailLineEdit->setText("");

        // Show login page
        ui->signUpGroupBox->hide();
        ui->loginGroupBox->show();
    } else {
        QMessageBox::warning(this, "Error", "Error creating account. Please try again.");
    }
}


void LoginPage::onCancelSignUpButtonClicked() {
    ui->signUpGroupBox->hide();
    ui->loginGroupBox->show();
}
