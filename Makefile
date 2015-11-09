SYS=$(shell g++ -dumpmachine)
CC=g++
CFLAGS=-c -Wall

ifneq (, $(findstring apple, $(SYS)))
LIBRARY=build/libgenetic.so
all: $(LIBRARY)

$(LIBRARY): build/*.o
	$(CC) $^ -shared -o $(LIBRARY)

build/%.o: GeneticMain/%.cpp 
	$(CC) $(CFLAGS) -fPIC $< -o $@
	
else ifneq (, $(findstring mingw, $(SYS)))
LIBRARY=build/libgenetic.dll
all: $(LIBRARY)

$(LIBRARY): build/*.o
	$(CC) $^ -shared -o $(LIBRARY)

build/%.o: GeneticMain/%.cpp
	$(CC) $(CFLAGS) $< -o $@
	
else ifneq (, $(findstring linux, $(SYS)))
all:
	echo "LINUX"
else
all:
	echo $(SYS)
endif
