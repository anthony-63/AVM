#include <iostream>
#include <vector>
#include "../headers/Assembler.hpp"
#include "../headers/avm.hpp"
int main() {
    AVM::Processor cpu(16);
    AVM::Assembler asmblr;
    // int prog[] = {
    //     pushi, 0x100,
    //     popr, ar,
    //     hlt,
    // };
    // int psize = std::end(prog) - std::begin(prog);
    // cpu.load(prog, psize, 0, 0x0000);
    // cpu.run(0x0000, true);
    asmblr.assemble("./programs/test.avm", "./programs/out.bin");
    cpu.loadbin("./programs/out.bin", 1, 0x0000);
    return 0;
}