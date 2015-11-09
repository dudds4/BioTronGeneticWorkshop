SYS=$(shell g++ -dumpmachine)
CC=g++
CFLAGS=-c -Wall

ifneq (, $(findstring apple, $(SYS)))
EXECUTABLE=build/libgenetic.so
all: $(EXECUTABLE)

$(EXECUTABLE): build/*.o
	$(CC) $^ -shared -o $(EXECUTABLE)

build/%.o: GeneticMain/%.cpp 
	$(CC) $(CFLAGS) -fPIC $< -o $@
else ifneq (, $(findstring mingw, $(SYS)))
all:
	echo "MINGW"
	$(CC) -o build/main.o -c GeneticExec/main.cpp -I GeneticMain
	$(CC) -c GeneticMain/*.cpp
	move *.o build
	cd build
	
	
else ifneq (, $(findstring linux, $(SYS)))
all:
	echo "LINUX"
else
all:
	echo $(SYS)
endif
