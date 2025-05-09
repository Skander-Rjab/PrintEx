/****************************************************************************
** Meta object code from reading C++ file 'ExamWindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ExamWindow.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qabstractbarseries.h>
#include <QtCharts/qvbarmodelmapper.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCharts/qcandlestickseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qxyseries.h>
#include <QtCharts/qxyseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qxyseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ExamWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSExamWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSExamWindowENDCLASS = QtMocHelpers::stringData(
    "ExamWindow",
    "backToMainRequested",
    "",
    "showListPage",
    "showCreatePage",
    "showUpdatePage",
    "showStatsPage",
    "handleFormSubmit",
    "showCalendarPage",
    "showMapPage",
    "createExam",
    "updateExam",
    "deleteExam",
    "examTableClicked",
    "QModelIndex",
    "index",
    "selectPdfFileCreate",
    "selectPdfFileUpdate",
    "searchExams",
    "searchText",
    "sortTable",
    "column",
    "generatePdfReport",
    "setupStatsCharts",
    "showFirePage",
    "toggleMuteAlarm",
    "handleSmoke",
    "backFromFire"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSExamWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  146,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,  147,    2, 0x08,    2 /* Private */,
       4,    0,  148,    2, 0x08,    3 /* Private */,
       5,    0,  149,    2, 0x08,    4 /* Private */,
       6,    0,  150,    2, 0x08,    5 /* Private */,
       7,    0,  151,    2, 0x08,    6 /* Private */,
       8,    0,  152,    2, 0x08,    7 /* Private */,
       9,    0,  153,    2, 0x08,    8 /* Private */,
      10,    0,  154,    2, 0x08,    9 /* Private */,
      11,    0,  155,    2, 0x08,   10 /* Private */,
      12,    0,  156,    2, 0x08,   11 /* Private */,
      13,    1,  157,    2, 0x08,   12 /* Private */,
      16,    0,  160,    2, 0x08,   14 /* Private */,
      17,    0,  161,    2, 0x08,   15 /* Private */,
      18,    1,  162,    2, 0x08,   16 /* Private */,
      20,    1,  165,    2, 0x08,   18 /* Private */,
      22,    0,  168,    2, 0x08,   20 /* Private */,
      23,    0,  169,    2, 0x08,   21 /* Private */,
      24,    0,  170,    2, 0x08,   22 /* Private */,
      25,    0,  171,    2, 0x08,   23 /* Private */,
      26,    0,  172,    2, 0x08,   24 /* Private */,
      27,    0,  173,    2, 0x08,   25 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ExamWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSExamWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSExamWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSExamWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ExamWindow, std::true_type>,
        // method 'backToMainRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showListPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showCreatePage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showUpdatePage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showStatsPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleFormSubmit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showCalendarPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showMapPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'createExam'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateExam'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteExam'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'examTableClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'selectPdfFileCreate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'selectPdfFileUpdate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'searchExams'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'sortTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'generatePdfReport'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setupStatsCharts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showFirePage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'toggleMuteAlarm'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleSmoke'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'backFromFire'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ExamWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ExamWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->backToMainRequested(); break;
        case 1: _t->showListPage(); break;
        case 2: _t->showCreatePage(); break;
        case 3: _t->showUpdatePage(); break;
        case 4: _t->showStatsPage(); break;
        case 5: _t->handleFormSubmit(); break;
        case 6: _t->showCalendarPage(); break;
        case 7: _t->showMapPage(); break;
        case 8: _t->createExam(); break;
        case 9: _t->updateExam(); break;
        case 10: _t->deleteExam(); break;
        case 11: _t->examTableClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 12: _t->selectPdfFileCreate(); break;
        case 13: _t->selectPdfFileUpdate(); break;
        case 14: _t->searchExams((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 15: _t->sortTable((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 16: _t->generatePdfReport(); break;
        case 17: _t->setupStatsCharts(); break;
        case 18: _t->showFirePage(); break;
        case 19: _t->toggleMuteAlarm(); break;
        case 20: _t->handleSmoke(); break;
        case 21: _t->backFromFire(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ExamWindow::*)();
            if (_t _q_method = &ExamWindow::backToMainRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *ExamWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExamWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSExamWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ExamWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void ExamWindow::backToMainRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
