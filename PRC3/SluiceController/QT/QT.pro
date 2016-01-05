#-------------------------------------------------
#
# Project created by QtCreator 2016-01-04T11:10:53
#
#-------------------------------------------------

QT       += core gui network websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QT
TEMPLATE = app
CONFIG += c++11

# Input
HEADERS += bimap.h \
           mainwindow.h \
           sluicetcphandler.h \
           sychronouswebsocketsresponder.h \
           ui_mainwindow.h \
    justbecauseqtdoesntallowstaticorglobalsignals.h
FORMS += mainwindow.ui
SOURCES += main.cpp \
           mainwindow.cpp \
           sluicetcphandler.cpp \
           sychronouswebsocketsresponder.cpp \
    justbecauseqtdoesntallowstaticorglobalsignals.cpp

