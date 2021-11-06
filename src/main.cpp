#include <iostream>
#include "../headers/avm.hpp"
int main() {
    AVM::Processor cpu = AVM::Processor(16); // set up a cpu with a bank count of 16
    int prog[] = {
        pushi, 0x100,
        popr, ar,
        hlt,
    };
    int psize = std::end(prog) - std::begin(prog);
    cpu.load(prog, psize, 0, 0x0000);
    cpu.run(0x0000, true);
    delete &cpu;
    return 0;

}