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
    src/game.cpp \
    src/player.cpp \
    src/enemy.cpp \
    src/tilemap.cpp \
    src/entity.cpp \
    src/tank.cpp \
    src/utils.cpp \
    src/enemy.cpp \

HEADERS  += \
    include/game.h \
    include/player.h \
    include/enemy.h \
    include/tilemap.h \
    include/entity.h \
    include/tank.h \
    include/randomgen.h \
    include/utils.h \
    include/set.h \


ROOT = $${PWD}/..
LIBS        += -L"$${ROOT}/SFML/lib/debug/"
LIBS        += -L"$${ROOT}/SFML/lib/release/"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += "$${ROOT}/SFML/include"
INCLUDEPATH += "$${ROOT}/battlecity/include"
DEPENDPATH += "$${ROOT}/SFML/include"

DISTFILES += \
    resources/Templates/Шаблон для заполнения карты.ods \
    resources/fonts/vapor_trails_remixed.otf \
    resources/fonts/FiraMono-Regular.ttf \
    resources/fonts/tahoma.ttf \
    resources/images/sprite.bmp \

