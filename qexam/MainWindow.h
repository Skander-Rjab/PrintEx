#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include "Exam.h"
#include "qcombobox.h"
#include <QtCharts>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QCalendarWidget>
#include <QMap>
#include <QTime>
#include <QDate>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

    // pdf and stats
    void generatePdfReport();
    void setupStatsCharts();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *examModel;
    int currentExamId;
    QString selectedPdfPathCreate;
    QString selectedPdfPathUpdate;
    bool isCreatingNewExam;

    // Initialization helpers
    void initializeFormComponents();
    void loadInstitutions();
    void loadGovernorates();
    void refreshExamModel();

    // Validation
    bool validateForm(QDateTimeEdit *dateEdit, QComboBox *institutionCombo,
                      QComboBox *destinationCombo, QLabel *pdfLabel);

    // Database helpers
    QString getEmployeeName(int employeeId);
    QString getInstitutionName(int institutionId);

    //calendar help
    QMap<QDate, QList<QTime>> examTimesByDate;

    void loadExamDates();

    QGraphicsScene   *mapScene    = nullptr;
    QSvgRenderer     *mapRenderer = nullptr;

    // id ↔ DB‑name lookup
    QMap<QString, QString> idToNameMap;
    QMap<QString, QString> nameToIdMap;

    // prebuilt HTML tooltips, keyed by SVG element‑ID
    QMap<QString, QString> tooltipHtmlMap;

    // setup helpers
    void setupMapMapping();
    void loadMapData();
    void setupMapView();

protected:
    // for catching hover/tooltips on the calendar
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // MAINWINDOW_H
