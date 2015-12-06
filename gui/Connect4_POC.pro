TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    BoardController.cpp

RESOURCES += qml.qrc

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    BoardController.h

