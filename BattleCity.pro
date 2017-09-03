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


SOURCES += cpp_files/main.cpp\
        cpp_files/mainwindow.cpp \
    cpp_files/Labyrinth.cpp \
    cpp_files/LabyrinthCell.cpp \
    cpp_files/AlienPanzers.cpp \
    cpp_files/Bullet.cpp \
    cpp_files/DynamicGameThings.cpp \
    cpp_files/ExternalWall.cpp \
    cpp_files/InternalWall.cpp \
    cpp_files/FreeSpace.cpp \
    cpp_files/ImplicitInternalWall.cpp \
    cpp_files/IronInternalWall.cpp \
    cpp_files/GameThings.cpp \
    cpp_files/PrizesThings.cpp \
    cpp_files/KillThemAllPrize.cpp \
    cpp_files/OurPanzer.cpp \
    cpp_files/FlagPrize.cpp \
    cpp_files/GameStatistic.cpp \
    cpp_files/SpeedAlienPanzer.cpp \
    cpp_files/MainDeclarativeView.cpp \
    cpp_files/FrozePrize.cpp \
    cpp_files/AudioThread.cpp \
    cpp_files/AudioDelegate.cpp \
    cpp_files/BulletExplosion.cpp \
    cpp_files/BigExplosion.cpp \
    cpp_files/StaticGameThings.cpp

HEADERS  += cpp_files/mainwindow.h \
    cpp_files/Labyrinth.h \
    cpp_files/LabyrinthCell.h \
    cpp_files/GameThings.h \
    cpp_files/AlienPanzers.h \
    cpp_files/Bullet.h \
    cpp_files/DynamicGameThings.h \
    cpp_files/ExternalWall.h \
    cpp_files/InternalWall.h \
    cpp_files/FreeSpace.h \
    cpp_files/ImplicitInternalWall.h \
    cpp_files/IronInternalWall.h \
    cpp_files/PrizesThings.h \
    cpp_files/KillThemAllPrize.h \
    cpp_files/OurPanzer.h \
    cpp_files/GameStatistic.h \
    cpp_files/SpeedAlienPanzer.h \
    cpp_files/FlagPrize.h \
    cpp_files/MainDeclarativeView.h \
    cpp_files/FrozePrize.h \
    cpp_files/AudioThread.h \
    cpp_files/AudioEvents.h \
    cpp_files/AudioDelegate.h \
    cpp_files/BulletExplosion.h \
    cpp_files/BigExplosion.h \
    cpp_files/StaticGameThings.h


OTHER_FILES += \
    qml/main.qml \
    qml/GameCell.qml \
    qml/GameOver.qml \
    qml/Alien.qml

RESOURCES += \
    res.qrc
