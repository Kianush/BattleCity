#-------------------------------------------------
#
# Project created by QtCreator 2017-08-10T08:48:58
#
#-------------------------------------------------

QT       += core gui declarative multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += debug_and_release c++11

TARGET = BattleCity
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Labyrinth.cpp \
    LabyrinthCell.cpp \
    AlienPanzers.cpp \
    Bullet.cpp \
    DynamicGameThings.cpp \
    ExternalWall.cpp \
    InternalWall.cpp \
    FreeSpace.cpp \
    ImplicitInternalWall.cpp \
    IronInternalWall.cpp \
    GameThings.cpp \
    PrizesThings.cpp \
    KillThemAllPrize.cpp \
    OurPanzer.cpp \
    FlagPrize.cpp \
    GameStatistic.cpp \
    SpeedAlienPanzer.cpp \
    MainDeclarativeView.cpp \
    FrozePrize.cpp \
    AudioThread.cpp \
    AudioDelegate.cpp \
    BulletExplosion.cpp \
    BigExplosion.cpp

HEADERS  += mainwindow.h \
    Labyrinth.h \
    LabyrinthCell.h \
    GameThings.h \
    AlienPanzers.h \
    Bullet.h \
    DynamicGameThings.h \
    ExternalWall.h \
    InternalWall.h \
    FreeSpace.h \
    ImplicitInternalWall.h \
    IronInternalWall.h \
    PrizesThings.h \
    KillThemAllPrize.h \
    OurPanzer.h \
    GameStatistic.h \
    SpeedAlienPanzer.h \
    FlagPrize.h \
    MainDeclarativeView.h \
    FrozePrize.h \
    AudioThread.h \
    AudioEvents.h \
    AudioDelegate.h \
    BulletExplosion.h \
    BigExplosion.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    qml/main.qml \
    qml/GameCell.qml \
    qml/GameOver.qml \
    qml/Alien.qml

RESOURCES += \
    res.qrc
