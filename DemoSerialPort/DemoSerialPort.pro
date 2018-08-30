#-------------------------------------------------
#
# Project created by QtCreator 2016-01-28T10:10:05
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DemoSerialPort
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    SerialPort/qextserialbase.cpp \
    SerialPort/qextserialport.cpp

HEADERS  += mainwindow.h \
    SerialPort/qextserialbase.h \
    SerialPort/qextserialport.h


FORMS    += mainwindow.ui

unix:HEADERS           += SerialPort/posix_qextserialport.h
unix:SOURCES           += SerialPort/posix_qextserialport.cpp
unix:DEFINES           += _TTY_POSIX_


win32:HEADERS          += SerialPort/win_qextserialport.h
win32:SOURCES          += SerialPort/win_qextserialport.cpp
win32:DEFINES          += _TTY_WIN_

win32:LIBS             += -lsetupapi


RESOURCES += \
    res/res.qrc


