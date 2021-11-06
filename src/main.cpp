#include <iostream>
#include "../headers/avm.hpp"
int main() {
    AVM::Processor cpu = AVM::Processor(16); // set up a cpu with a bank count of 16
    int prog[] = {
        movir, 0x4, ar,
        decr, ar,
        cmpir, 0x00, ar,
        jne, 0x3,
        hlt,
    };
    int psize = std::end(prog) - std::begin(prog);
    cpu.load(prog, psize, 0, 0x0000);
    cpu.run(0x0000, true);
    delete &cpu;
    return 0;

}