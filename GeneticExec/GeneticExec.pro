
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GeneticMain/release/ -lGeneticMain
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GeneticMain/debug/ -lGeneticMain
else:unix: LIBS += -L$$OUT_PWD/../GeneticMain/ -lGeneticMain

INCLUDEPATH += $$PWD/../GeneticMain
DEPENDPATH += $$PWD/../GeneticMain

SOURCES += main.cpp
