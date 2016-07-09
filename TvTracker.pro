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
        core/tvtrackermanager.cpp \
        db/dbhandler.cpp \
        http/sourcegrabber.cpp \
        http/filedownloader.cpp \
        core/customlistitem.cpp

HEADERS += core/mainwindow.h \
           db/dbhandler.h \
           core/tvtrackermanager.h \
           http/sourcegrabber.h \
           http/filedownloader.h \
           core/customlistitem.h

FORMS    += core/mainwindow.ui

RESOURCES += \
    Resources/images.qrc

