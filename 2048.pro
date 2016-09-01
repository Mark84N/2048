#-------------------------------------------------
#
# Project created by QtCreator 2016-08-22T21:41:12
#
#-------------------------------------------------

QT       += core gui

CONFIG   += static

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2048
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    tile.cpp \
    filerecordmanager.cpp \
    fieldsizemenu.cpp \
    gamefield.cpp \
    canvas.cpp \
    classictilegenerator.cpp

HEADERS  += mainwindow.h \
    tile.h \
    interfaces\irecordmanager.h \
    filerecordmanager.h \
    fieldsizemenu.h \
    gamefield.h \
    canvas.h \
    interfaces\itilegenerator.h \
    classictilegenerator.h

FORMS    +=

RESOURCES += \
    res.qrc
