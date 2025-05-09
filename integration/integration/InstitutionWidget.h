#ifndef INSTITUTIONWIDGET_H
#define INSTITUTIONWIDGET_H

#include "qlabel.h"
#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class InstitutionWidget;
}

class InstitutionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InstitutionWidget(QWidget *parent = nullptr);
    ~InstitutionWidget();
    void refreshTable();

signals:
    void backToMainRequested();

private slots:
    void onAddClicked();
    void onDeleteClicked();
    void onUpdateClicked();
    void onSearch(const QString &text);
    void onExportPDF();
    void onShowStats();
    void onFormSubmit();
    void onFormCancel();
    void sortTable(int column);

private:
    Ui::InstitutionWidget *ui;
    QSqlQueryModel *model;
    int currentInstitutionId = 0;


    void showForm();
    void hideForm();
    bool validateForm();
    void clearForm();
    void highlightConflicts();

    // Database operations
    bool addInstitution(const QString &name, const QString &contact, const QString &address);
    bool updateInstitution(int id, const QString &name, const QString &contact, const QString &address);
    bool deleteInstitution(int id);

    QLabel* createHighlightLabel(const QString &text, const QColor &color, bool frameOnly = false);
};

#endif // INSTITUTIONWIDGET_H
