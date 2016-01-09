#-------------------------------------------------
#
# Project created by QtCreator 2016-01-04T11:10:53
#
#-------------------------------------------------

QT       += core gui network websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QT
TEMPLATE = app
CONFIG += c++11 -DQT_NO_SSL

# Input
HEADERS += bimap.h \
           mainwindow.h \
           sluicetcphandler.h \
           ui_mainwindow.h \
    websocketclient.h \
    qwst.h \
    Base64.h
FORMS += mainwindow.ui
SOURCES += main.cpp \
           mainwindow.cpp \
           sluicetcphandler.cpp \
    websocketclient.cpp \
    qwst.cpp \
    Base64.cpp

