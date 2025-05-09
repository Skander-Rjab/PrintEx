#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include "MainWindow.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowTitle("Login");

    // Connect login button
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginButtonClicked);

    // Set password field to show asterisks
    ui->passwordField->setEchoMode(QLineEdit::Password);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::onLoginButtonClicked()
{
    QString username = ui->usernameField->text();
    QString password = ui->passwordField->text();

    // Check credentials (fake login)
    if (username == "nada" && password == "nada123") {
        accept(); // This will close the dialog with QDialog::Accepted
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password");
    }
}
