SYS=$(shell g++ -dumpmachine)

ifneq (, $(findstring apple, $(SYS)))
all:
	echo "APPLE"
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
