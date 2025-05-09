#include "twofadialog.h"
#include "ui_twofadialog.h"
#include <QMessageBox>

TwoFADialog::TwoFADialog(TwoFAService* service, const QString& phone, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::TwoFADialog),
    twoFAService(service),
    phoneNumber(phone)
{
    ui->setupUi(this);
    setWindowTitle("Enter 2FA Code");
    setModal(true);

    ui->lineEditCode->setMaxLength(6);
    ui->lineEditCode->setFocus();

    connect(ui->btnSubmit, &QPushButton::clicked, this, &TwoFADialog::onSubmitCode);
}

TwoFADialog::~TwoFADialog()
{
    delete ui;
}

void TwoFADialog::onSubmitCode()
{
    QString code = ui->lineEditCode->text().trimmed();

    if (code.length() != 6 || !code.toUInt()) {
        ui->labelStatus1->setText("❌ Enter a valid 6-digit code.");
        return;
    }

    if (twoFAService->verifyCode(phoneNumber, code)) {
        QMessageBox::information(this, "Success", " Verification successful!");
        accept(); // Close dialog with success
    } else {
        ui->labelStatus2->setText("❌ Invalid or expired code.");
    }
}
