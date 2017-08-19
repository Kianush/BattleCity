#-------------------------------------------------
#
# Project created by QtCreator 2017-08-10T08:48:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += debug_and_release c++11

TARGET = Alex_Kolosov_10_08_2017
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Labyrinth.cpp \
    LabyrinthCell.cpp \
    AlienPanzers.cpp \
    PanzersPathes.cpp \
    Bullet.cpp \
    DynamicGameThings.cpp \
    StaticGameThings.cpp \
    ExternalWall.cpp \
    InternalWall.cpp \
    FreeSpace.cpp \
    ImplicitInternalWall.cpp \
    IronInternalWall.cpp \
    GameThings.cpp \
    PrizesThings.cpp \
    KillThemAllPrize.cpp \
    PrizesPathes.cpp \
    OurPanzer.cpp \
    FlagPrize.cpp \
    GameStatistic.cpp \
    SpeedAlienPanzer.cpp

HEADERS  += mainwindow.h \
    Labyrinth.h \
    LabyrinthCell.h \
    GameThings.h \
    AlienPanzers.h \
    PanzersPathes.h \
    Bullet.h \
    DynamicGameThings.h \
    StaticGameThings.h \
    ExternalWall.h \
    InternalWall.h \
    FreeSpace.h \
    ImplicitInternalWall.h \
    IronInternalWall.h \
    PrizesThings.h \
    KillThemAllPrize.h \
    PrizesPathes.h \
    OurPanzer.h \
    GameStatistic.h \
    SpeedAlienPanzer.h \
    FlagPrize.h

FORMS    += mainwindow.ui
