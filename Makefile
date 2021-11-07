CPP = g++
SRC = ./src/
BASE_FILES = $(SRC)*Bus.cpp $(SRC)Processor.cpp $(SRC)Assembler.cpp 
OUT = avm.exe
all:
	$(CPP) $(SRC)main.cpp $(BASE_FILES) -o ./bin/test.exe -Wall
	.\bin\test.exe
avm:
	$(CPP) $(SRC)avm.cpp $(BASE_FILES) -o ./bin/avm.exe -Wall
avmasm:
	$(CPP) $(SRC)avmasm.cpp $(BASE_FILES) -o ./bin/avmasm.exe -Wall
debug:
	$(CPP) -g $(SRC)main.cpp $(BASE_FILES) -o ./bin/dbg$(OUT) -Wall
	gdb .\bin\dbg$(OUT)