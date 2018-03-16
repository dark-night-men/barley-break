CONFIG += debug
CONFIG += c++14

TARGET = guibreak

TEMPLATE = app

QT += widgets

SOURCES += main.cpp

INCLUDEPATH += ../libbreaks
HEADERS += ../libbreaks/cell.h

LIBS += -lbreaks -L../build/libbreaks
