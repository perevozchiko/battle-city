#-------------------------------------------------
#
# Project created by QtCreator 2019-03-05T12:15:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = battlecity
TEMPLATE = app


SOURCES += main.cpp

HEADERS  +=

LIBS += -L/home/andrey/Projects/sfml25/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsafml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += /home/andrey/Projects/sfml25/include
DEPENDPATH += /home/andrey/Projects/sfml25/include
