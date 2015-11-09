SYS=$(shell g++ -dumpmachine)
CC=g++
CFLAGS=-c -Wall

SRC=GeneticMain/*.cpp
OBJS=$(SRC:GeneticMain/%.cpp=build/%.o) 

TESTSRC=GeneticTest/*.cpp
TESTOBJS=$(TESTSRC:GeneticTest/%.cpp=build/%.o) 

EXECUTABLE=build/geneticWorkshop
TESTEXECUTABLE=build/geneticWorkshopTest

ifneq (, $(findstring apple, $(SYS)))
LIBRARY=build/libgenetic.so
MOVE=mv
LDFLAGS=-Lbuild -lgenetic
REMOVE=rm -f build/*.o
else ifneq (, $(findstring mingw, $(SYS)))
LIBRARY=build/libgenetic.dll
MOVE=move
LDFLAGS=-Lbuild -llibgenetic
REMOVE=del /q build
else
exit
endif

all: $(EXECUTABLE)

$(EXECUTABLE): build/main.o $(LIBRARY)
	$(CC) build/main.o $(LDFLAGS) -o $(EXECUTABLE) 
	$(EXECUTABLE)

build/main.o: GeneticExec/main.cpp
	$(CC) $(CFLAGS) GeneticExec/main.cpp -o build/main.o -I GeneticMain

$(LIBRARY): $(OBJS)
	$(CC) $^ -shared -fPIC -o $(LIBRARY)	

$(OBJS): $(SRC)
	$(CC) $(CFLAGS) $(SRC)
	$(MOVE) *.o build

test: $(TESTEXECUTABLE)
	
$(TESTEXECUTABLE): $(TESTOBJS) $(LIBRARY)
	$(CC) $(TESTOBJS) -Lbuild -llibgenetic -o $(TESTEXECUTABLE) 
	$(TESTEXECUTABLE)
	
$(TESTOBJS): $(TESTSRC)
	$(CC) $(CFLAGS) $(TESTSRC)
	$(MOVE) *.o build
	
clean:
	$(REMOVE)
