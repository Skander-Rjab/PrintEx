#include "qdialog.h"
#include "twofaservice.h"
#include "ui_twofadialog.h"

class TwoFADialog : public QDialog
{
    Q_OBJECT

public:
    explicit TwoFADialog(TwoFAService* service, const QString& phoneNumber, QWidget *parent = nullptr);
    ~TwoFADialog();

private slots:
    void onSubmitCode();

private:
    Ui::TwoFADialog *ui;
    TwoFAService* twoFAService;
    QString phoneNumber;
};
