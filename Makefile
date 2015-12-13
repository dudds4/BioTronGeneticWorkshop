SYS=$(shell g++ -dumpmachine)
CC=g++
CFLAGS=-Wall

SRC=GeneticMain/*.cpp

TESTSRC=GeneticTest/*.cpp

EXECUTABLE=build/geneticWorkshop
TESTEXECUTABLE=build/geneticWorkshopTest

MOVE=mv
REMOVE=rm -f build/*

all: $(EXECUTABLE)

$(EXECUTABLE): GeneticExec/main.cpp $(LIBRARY)
	$(CC) $(CFLAGS) GeneticExec/main.cpp GeneticMain/*.cpp -I GeneticMain -o $(EXECUTABLE)
	$(EXECUTABLE)
	
clean:
	$(REMOVE)

test: $(TESTEXECUTABLE)

$(TESTEXECUTABLE): GeneticTest/testMain.cpp $(LIBRARY)
	$(CC) $(CFLAGS) GeneticTest/testMain.cpp -I GeneticMain $(LDFLAGS) -o $(TESTEXECUTABLE)
	$(TESTEXECUTABLE)
