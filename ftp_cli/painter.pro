#-------------------------------------------------
#
# Project created by QtCreator 2019-03-29T15:36:11
#
#-------------------------------------------------

QT       += core gui
CONFIG+= console
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = painter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    painter.cpp \
    ip_port.cpp \
    dialog.cpp \
    dialogupload.cpp \
    download.cpp \
    mythread.cpp \
    threaddownload.cpp

HEADERS  += mainwindow.h \
    painter.h \
    ip_port.h \
    dialog.h \
    dialogupload.h \
    download.h \
    mythread.h \
    threaddownload.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui \
    dialogupload.ui \
    download.ui

RESOURCES += \
    tu.qrc \
    222.qrc
