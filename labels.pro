#-------------------------------------------------
#
# Project created by QtCreator 2011-09-01T13:55:39
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = labels
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pgdialog.cpp \
    lblengine.cpp

HEADERS  += mainwindow.h \
    pgdialog.h \
    lblengine.h

FORMS    += mainwindow.ui \
    pgdialog.ui

RESOURCES += \
    res.qrc

DISTFILES += \
    templates/glabels_szsm.xml \
    runlbl.sh
