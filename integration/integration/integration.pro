QT       += core gui sql network charts printsupport svg widgets serialport xml svgwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Connection.cpp \
    Employee.cpp \
    EmployeeWindow.cpp \
    Exam.cpp \
    ExamWindow.cpp \
    InstitutionWidget.cpp \
    LoginDialog.cpp \
    MainWindow.cpp \
    arduino.cpp \
    institution.cpp \
    main.cpp

HEADERS += \
    Connection.h \
    Employee.h \
    EmployeeWindow.h \
    Exam.h \
    ExamWindow.h \
    InstitutionWidget.h \
    LoginDialog.h \
    MainWindow.h \
    arduino.h \
    institution.h

FORMS += \
    EmployeeWindow.ui \
    ExamWindow.ui \
    InstitutionWidget.ui \
    LoginDialog.ui \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \
    resources.qrc
