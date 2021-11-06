CPP = g++
SRC = ./src/*.cpp
OUT = avm.exe
all:
	$(CPP) $(SRC) -o ./bin/$(OUT) -Wall
	.\bin\$(OUT)
debug:
	$(CPP) -g $(SRC) -o ./bin/dbg$(OUT) -Wall
	gdb .\bin\dbg$(OUT)