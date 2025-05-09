QT       += core gui
QT       += sql
QT += core gui widgets printsupport
QT += charts
QT += serialport
QT += network
QT += svg
QT += xml


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Arduino.cpp \
    LoginPage.cpp \
    connection.cpp \
    emailservice.cpp \
    envloader.cpp \
    exam.cpp \
    examwindow.cpp \
    institution.cpp \
    institutionwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    smsservice.cpp \
    twofadialog.cpp \
    twofaservice.cpp \
    user.cpp \
    verificationservice.cpp

HEADERS += \
    Arduino.h \
    LoginPage.h \
    connection.h \
    emailservice.h \
    envloader.h \
    exam.h \
    examwindow.h \
    institution.h \
    institutionwindow.h \
    mainwindow.h \
    smsservice.h \
    twofadialog.h \
    twofaservice.h \
    user.h \
    verificationservice.h

FORMS += \
    Arduino.ui \
    LoginPage.ui \
    examwindow.ui \
    institution.ui \
    institutionwindow.ui \
    mainwindow.ui \
    twofadialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../qexama/maps/search.png \
    ../qexama/maps/tunisia.svg \
    .env

