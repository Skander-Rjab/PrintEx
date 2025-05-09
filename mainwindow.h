#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QTableWidgetItem>
#include <QDateTime>
#include <QResizeEvent>
#include "institutionwindow.h"
#include "user.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(const User& user, QWidget *parent = nullptr); // 👈 ajout du constructeur
    ~MainWindow();
 void setCurrentUserId(const QString &id);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_button_userManagement_clicked();
    void on_button_save_clicked();
    void on_button_update_clicked();
    void on_button_delete_clicked();
    void on_tableWidget_users_cellClicked(int row, int column);
    void on_pushButton_exit_clicked();
    void on_pushButton_exitUserTable_clicked();
    void on_pushButton_searchByPhone_clicked();
    void onHomePageButtonClicked();
    void on_pushButton_exportPdf_clicked();
    void on_pushButton_savechanges_clicked();
    void on_button_institutionManagement_clicked();

private:
    void loadUsers();
    void clearUserForm();
    void setupConnections();
    void setupUI();
    void sortUsers(int index);
    bool checkIfEmailExists(const QString& email, const QString& userId);
    void showChartImage();
    Ui::MainWindow *ui;
    User currentUser;
    InstitutionWindow *institutionWin = nullptr;


};

#endif // MAINWINDOW_H
