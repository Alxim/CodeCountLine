#-------------------------------------------------
#
# Project created by QtCreator 2014-09-12T10:55:12
#
#-------------------------------------------------

QT       += core gui

VERSION = 0.0.0.3

DEFINES += VERSION=\\\"$$VERSION\\\"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodeCountLine
TEMPLATE = app


SOURCES += main.cpp\
        CodeCountLine.cpp \
        CodeCountLineFile.cpp \
        tools/time_string.cpp

HEADERS  += CodeCountLine.h \
    tools/time_string.h

FORMS    += CodeCountLine.ui

