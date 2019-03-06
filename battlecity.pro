#-------------------------------------------------
#
# Project created by QtCreator 2019-03-05T12:15:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = battlecity
TEMPLATE = app


SOURCES += main.cpp \
    src/tank.cpp \
    src/game.cpp \
    src/map.cpp

HEADERS  += \
    include/tank.h \
    include/game.h \
    include/map.h

ROOT = $${PWD}/..
LIBS        += -L"$${ROOT}/SFML/lib/debug/"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += "$${ROOT}/SFML/include"
INCLUDEPATH += "$${ROOT}/battlecity/include"
DEPENDPATH += "$${ROOT}/SFML/include"





#LIBS += -L$$(HOME)/Projects/sfml25/lib

#CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
#CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

#INCLUDEPATH += $$(HOME)/Projects/sfml25/include
#INCLUDEPATH += $$(HOME)/Projects/battlecity/include
#DEPENDPATH += $$(HOME)/Projects/sfml25/include
