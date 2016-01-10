TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    BoardController.cpp \
    ../GeneticMain/AbstractPlayer.cpp \
    ../GeneticMain/Match.cpp \
    Player1.cpp \
    Player2.cpp


RESOURCES += qml.qrc

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    BoardController.h \
    ../GeneticMain/AbstractPlayer.h \
    ../GeneticMain/Match.h \
    Player1.h \
    Player2.h

