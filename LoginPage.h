#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QDialog>
#include <QMessageBox>
#include "institutionwindow.h"
#include "user.h"
#include "Arduino.h"
#include "twofaservice.h"


namespace Ui {
class LoginPage;
}

class LoginPage : public QDialog
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();
    bool isAuthenticated() const;

private slots:
    void onSubmitLoginButtonClicked();
    void onSignUpClicked();
    void onCancelSignUpButtonClicked();
    void onSubmitSignUpButtonClicked();

private:
    Ui::LoginPage *ui;
    User currentUser;  // This will need to be initialized explicitly
    bool authenticated = false;
    Arduino *arduinoWindow;
    TwoFAService* twoFAService;
    InstitutionWindow *institutionWindow;

};

#endif // LOGINPAGE_H
