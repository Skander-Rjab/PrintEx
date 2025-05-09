#ifndef EXAMWINDOW_H
#define EXAMWINDOW_H

#include <QWidget>  // Changed from QMainWindow
#include <QSqlQueryModel>
#include <QSqlRecord>
#include "Exam.h"
#include <QComboBox>
#include <QtCharts>
#include <QCalendarWidget>
#include <QMap>
#include <QGraphicsScene>
#include <QSvgRenderer>
#include "arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ExamWindow;  // Changed from MainWindow
}
QT_END_NAMESPACE

class ExamWindow : public QWidget  // Changed base class
{
    Q_OBJECT

public:
    explicit ExamWindow(QWidget *parent = nullptr);
    ~ExamWindow();

    // Added for integration with main app
    void showWindow() { this->show(); }
    void hideWindow() { this->hide(); }

signals:
    void backToMainRequested();

private slots:
    // Page navigation
    void showListPage();
    void showCreatePage();
    void showUpdatePage();
    void showStatsPage();
    void handleFormSubmit();
    void showCalendarPage();
    void showMapPage();

    // CRUD operations
    void createExam();
    void updateExam();
    void deleteExam();

    // UI interactions
    void examTableClicked(const QModelIndex &index);
    void selectPdfFileCreate();
    void selectPdfFileUpdate();
    void searchExams(const QString &searchText);
    void sortTable(int column);

    // PDF and stats
    void generatePdfReport();
    void setupStatsCharts();

    // Fire alarm
    void showFirePage();
    void toggleMuteAlarm();
    void handleSmoke();
    void backFromFire();

private:
    Ui::ExamWindow *ui;  // Changed type
    QSqlQueryModel *examModel;
    int currentExamId;
    QString selectedPdfPathCreate;
    QString selectedPdfPathUpdate;
    bool isCreatingNewExam;

    ArduinoInterface *arduino;
    bool alarmMuted = false;

    // Helper methods
    void refreshFireModel();
    bool checkForCanceledExams();
    void initializeFormComponents();
    void loadInstitutions();
    void loadGovernorates();
    void refreshExamModel();
    bool validateForm(QDateTimeEdit *dateEdit,
                      QComboBox *institutionCombo,
                      QComboBox *destinationCombo,
                      QLabel *pdfLabel);
    QString getEmployeeName(int employeeId);
    QString getInstitutionName(int institutionId);

    // Calendar
    QMap<QDate, QList<QTime>> examTimesByDate;
    void loadExamDates();

    // Map visualization
    QGraphicsScene *mapScene = nullptr;
    QSvgRenderer *mapRenderer = nullptr;
    QMap<QString, QString> idToNameMap;
    QMap<QString, QString> nameToIdMap;
    QMap<QString, QString> tooltipHtmlMap;
    void setupMapMapping();
    void loadMapData();
    void setupMapView();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // EXAMWINDOW_H
