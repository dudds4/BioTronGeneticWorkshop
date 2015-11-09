SYS=$(shell g++ -dumpmachine)

ifneq (, $(findstring apple, $(SYS)))
all:
	echo "APPLE"
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
