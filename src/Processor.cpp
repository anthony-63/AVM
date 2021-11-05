#include "../headers/Processor.hpp"
#include "../headers/Instructions.hpp"
#include "../headers/Registers.hpp"

#include <iostream>
#include <cstdarg>
#include <string>
namespace AVM {

    void Processor::step() {
        regs.setRegister(ip, regs.getRegister(ip) + 1);
    }
    int Processor::getFromIP() {
        int t = m.fetch(regs.getRegister(mb), regs.getRegister(ip));
        step();
        return t;
    }


    int Processor::__movir() {
        int imm = getFromIP();
        int reg = getFromIP();
        regs.setRegister(reg, imm);
        return 0x00;
    }
    int Processor::__addrr() {
        int regf1 = regs.getRegister(getFromIP());
        int regf2 = regs.getRegister(getFromIP());
        regs.setRegister(zr, regf1 + regf2);
        return 0x00;
    }


    int Processor::execute(int __instruction) {
        switch(__instruction) {
            case hlt:   return 0x60;
            case movir: return __movir();
            case addrr: return __addrr();
            default: return 0xe5;
        }
    }
    void Processor::run(int __location, bool __dbg) {
        if(__dbg) dbg();
        regs.setRegister(ip, __location);
        while(true) {
            herror(execute(getFromIP()));
            if(__dbg) dbg();
        }
    }
    void Processor::load(int *__prog, int __psize, int __bank, int __location) {
        for(auto i = 0; i < __psize; i++){
            m.send(__bank, __prog[i], i + __location);
            std::cout << std::hex << i + __location << " <- " << std::hex << __prog[i] << '\n';
        }
    }
    void errormsg(int __code, const char* fmt, ...) {
        std::cout << std::hex << __code << ": ";
        va_list va;
        va_start(va, fmt);
        vprintf(fmt, va);
        va_end(va);
        std::cout << "\n";
        exit(-1);
    }
    void Processor::herror(int __code) {
        switch(__code) {
            case 0x60: exit(0);
            case 0x00: return;
            case 0xe5: errormsg(__code, "Instruction %02X not found", regs.getRegister(ip));
            default: errormsg(__code, "Error code not found, exiting...");
        }
    }
    void Processor::dbg() {
        std::cout << "\n";
        std::cout << "ip: " << regs.getRegister(ip) << "\n";
        std::cout << "sp: " << regs.getRegister(sp) << "\n";
        std::cout << "mb: " << regs.getRegister(mb) << "\n";
        std::cout << "ar: " << regs.getRegister(ar) << "\n";
        std::cout << "br: " << regs.getRegister(br) << "\n";
        std::cout << "cr: " << regs.getRegister(cr) << "\n";
        std::cout << "dr: " << regs.getRegister(dr) << "\n";
        std::cout << "er: " << regs.getRegister(er) << "\n";
        std::cout << "fr: " << regs.getRegister(fr) << "\n";
        std::cout << "gr: " << regs.getRegister(gr) << "\n";
        std::cout << "hr: " << regs.getRegister(hr) << "\n";
        std::cout << "zr: " << regs.getRegister(zr) << "\n";
    }
}
    