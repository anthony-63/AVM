#include <iostream>
#include "../headers/avm.hpp"
#include <cstring>
int main(int argc, char** argv) {
    AVM::Processor cpu(16);
    if(argc < 3 || argc > 4) {
        std::cout << "Usage: avm.exe <bin_file> <debug>" << std::endl;
        exit(0);
    }
    std::cout << "dbg: " << argv[2] << ", cmp " << !strcmp(argv[2], "true") << std::endl;
    cpu.loadbin(argv[1], 0, 0x0000);
    cpu.run(0x0000, !strcmp(argv[2], "true"));
    return 0;
}