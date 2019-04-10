#-------------------------------------------------
#
# Project created by QtCreator 2019-03-05T12:15:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++14 -Wall -Wextra -pedantic

TARGET = battlecity
TEMPLATE = app


SOURCES += main.cpp \
    src/game.cpp \
    src/player.cpp \
    src/enemy.cpp \
    src/entity.cpp \
    src/utils.cpp \
    src/tile.cpp \
    src/bullet.cpp \
    src/counterenemy.cpp \
    src/staff.cpp \

HEADERS  += \
    include/game.h \
    include/player.h \
    include/enemy.h \
    include/entity.h \
    include/randomgen.h \
    include/utils.h \
    include/tile.h \
    include/bullet.h \
    include/settings.h \
    include/counterenemy.h \
    include/staff.h \

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
    resources/Templates/Шаблон для заполнения карты.ods \
    resources/fonts/vapor_trails_remixed.otf \
    resources/fonts/FiraMono-Regular.ttf \
    resources/fonts/tahoma.ttf \
    resources/images/sprite.bmp \
    resources/maps/1 \
    resources/Templates/mapstemplate.ods \
    resources/maps/1.csv \
    resources/maps/3.csv \
    resources/maps/1 \
    resources/maps/1 кирпичик \
    resources/maps/2 \
    resources/maps/4.txt \
    resources/maps/5 \
    resources/maps/6 \
    resources/Templates/mapstemplate2.ods \
    resources/Templates/battle_city_2.jpg \
    resources/Templates/original_first_round.png \

