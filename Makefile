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
else ifneq (, $(findstring linux, $(SYS)))
all:
	echo "LINUX"
else
all:
	echo $(SYS)
endif
