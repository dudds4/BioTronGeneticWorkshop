#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T20:52:31
#
#-------------------------------------------------

QT       -=  gui

TARGET = GeneticMain
TEMPLATE = lib

DEFINES += GENETICMAIN_LIBRARY

SOURCES += GameSimulator.cpp\
		AbstractPlayer.cpp\
		Player.cpp \
    DefaultPlayer.cpp \
    globals.cpp \
    Match.cpp

HEADERS += GameSimulator.h\
		AbstractPlayer.h\
		Player.h\
        geneticmain_global.h \
    DefaultPlayer.h \
    Match.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
