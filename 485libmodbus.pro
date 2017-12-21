#-------------------------------------------------
#
# Project created by QtCreator 2017-12-20T17:16:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 485libmodbus
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    libmodbus/src/modbus-tcp.c \
    libmodbus/src/modbus-rtu.c \
    libmodbus/src/modbus-data.c \
    libmodbus/src/modbus.c

HEADERS  += mainwindow.h \
    libmodbus/src/modbus-version.h.in \
    libmodbus/src/modbus-version.h \
    libmodbus/src/modbus-tcp-private.h \
    libmodbus/src/modbus-tcp.h \
    libmodbus/src/modbus-rtu-private.h \
    libmodbus/src/modbus-rtu.h \
    libmodbus/src/modbus-private.h \
    libmodbus/src/modbus.h \
    libmodbus/config.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    libmodbus/src/Makefile.am
