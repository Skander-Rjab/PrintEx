#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QRandomGenerator>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:

    void on_tableView_clicked(const QModelIndex &index);

    void on_refresh_clicked();

    void on_pdf_clicked();

    void on_add_clicked();

    void on_delete_2_clicked();

    void on_sortalphabitic_clicked();

    void on_searchlineedit_textChanged(const QString &arg1);

    void on_Edit_clicked();

    void on_tableViewhistory_activated(const QModelIndex &index);

    void on_askAI_clicked();

    void on_Exportexcel_clicked();

    void on_sendemail_clicked();
    
    void on_dropdownmanagers_activated(int index);

    void on_dropdownmanagers_currentIndexChanged(int index);

private:
    void loadManagersDropdown();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
