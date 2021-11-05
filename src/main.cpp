#include <iostream>
#include "../headers/avm.hpp"
int main() {
    AVM::Processor cpu = AVM::Processor(16); // set up a cpu with a bank count of 16
    int prog[] = {
        movir, 0x30, ar,
        movir, 0x01, br,
        addrr, ar, br,
        hlt
    };
    int psize = std::end(prog) - std::begin(prog);
    cpu.load(prog, psize, 0, 0x0000);
    cpu.run(0x0000, true);
    return 0;
}