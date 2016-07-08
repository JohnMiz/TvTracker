#-------------------------------------------------
#
# Project created by QtCreator 2016-06-18T19:42:52
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TvTracker
TEMPLATE = app


SOURCES += main.cpp\
        core/mainwindow.cpp \
        core/dbhandler.cpp \
    core/sourcegrabber.cpp \
    core/tvtrackermanager.cpp \
    core/filedownloader.cpp

HEADERS  += core/mainwindow.h \
            core/dbhandler.h \
    core/sourcegrabber.h \
    core/tvtrackermanager.h \
    core/filedownloader.h

FORMS    += core/mainwindow.ui

RESOURCES += \
    images.qrc

