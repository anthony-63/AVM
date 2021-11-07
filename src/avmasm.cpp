#include <iostream>
#include <vector>
#include "../headers/Assembler.hpp"
int main(int argc, char** argv) {
    AVM::Assembler asmblr;
    if(argc < 3 || argc > 4) {
        std::cout << "Usage: avmasm.exe <assembly> <output>" << std::endl;
        exit(0);
    }
    asmblr.assemble(argv[1], argv[2]);
    return 0;
}