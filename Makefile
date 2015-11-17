SYS=$(shell g++ -dumpmachine)
CC=g++
CFLAGS=-Wall

SRC=GeneticMain/*.cpp

TESTSRC=GeneticTest/*.cpp

EXECUTABLE=build/geneticWorkshop
TESTEXECUTABLE=build/geneticWorkshopTest

LIBRARY=build/libgenetic.so
MOVE=mv
LDFLAGS=-L build -lgenetic
REMOVE=rm -f build/*

all: $(EXECUTABLE)

$(EXECUTABLE): GeneticExec/main.cpp $(LIBRARY)
	$(CC) $(CFLAGS) GeneticExec/main.cpp -I GeneticMain $(LDFLAGS) -o $(EXECUTABLE)
	$(EXECUTABLE)

$(LIBRARY): $(SRC)
	$(CC) $^ -shared -fPIC -o $(LIBRARY)
	
clean:
	$(REMOVE)

test: $(TESTEXECUTABLE)

$(TESTEXECUTABLE): GeneticTest/testMain.cpp $(LIBRARY)
	$(CC) $(CFLAGS) GeneticTest/testMain.cpp -I GeneticMain $(LDFLAGS) -o $(TESTEXECUTABLE)
	$(TESTEXECUTABLE)
