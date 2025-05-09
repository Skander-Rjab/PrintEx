QT       += core gui sql widgets charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += network

# Oracle configuration
QT += sql

# Add these paths according to your Oracle installation
ORACLE_HOME = C:/Oracle/instantclient_19_19  # Update this path
INCLUDEPATH += $$ORACLE_HOME/sdk/include
LIBS += $$ORACLE_HOME/oci.dll \
        $$ORACLE_HOME/oraociei19.dll


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    center.cpp \
    connection.cpp \
    history.cpp \
    main.cpp \
    mainwindow.cpp \
    smtp.cpp

HEADERS += \
    center.h \
    connection.h \
    history.h \
    mainwindow.h \
    smtp.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    ../../../../Downloads/Gestion Centers/background.jpg

RESOURCES += \
    background.qrc


