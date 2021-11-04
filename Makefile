CPP = g++
SRC = ./src/*.cpp
OUT = avm.exe
all:
	$(CPP) $(SRC) -o ./bin/$(OUT) -Wall
	.\bin\$(OUT)
