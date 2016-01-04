#QT       += core gui

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = Sluice
#TEMPLATE = app


#SOURCES += main.cpp\
#        mainwindow.cpp \

#HEADERS  += mainwindow.h \

#FORMS    += mainwindow.ui



QT       += core websockets
QT       -= gui

TARGET = echoclient
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    echoclient.cpp

HEADERS += \
    echoclient.h
