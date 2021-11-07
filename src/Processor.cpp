#include "../headers/Processor.hpp"
#include "../headers/Instructions.hpp"
#include "../headers/Registers.hpp"

#include <iostream>
#include <cstdarg>
#include <string>
#include <fstream>
#define __gr(X) regs.getRegister(X)
#define __sr(X, Y) regs.setRegister(X, Y)
namespace AVM {
    void Processor::step() {
        __sr(ip, __gr(ip) + 1);
    }
    int Processor::getFromIP() {
        int t = m.fetch(__gr(mb), __gr(ip));
        step();
        return t;
    }

    int Processor::__movir() {
        int imm = getFromIP();
        int reg = getFromIP();
        __sr(reg, imm);
        return 0x00;
    }
    int Processor::__movrr(){
        int reg = getFromIP();
        int regt = getFromIP();
        __sr(regt, __gr(reg));
        return 0x00;
    }
    int Processor::__movrm(){
        int data = __gr(getFromIP());
        int addr = getFromIP();
        m.send(__gr(mb), data, addr);
        return 0x00;
    }
    int Processor::__movim(){
        int imm = getFromIP();
        int addr = getFromIP();
        m.send(__gr(mb), imm, addr);
        return 0x00;
    }
    int Processor::__movmr(){
        int addr = getFromIP();
        int reg = getFromIP();
        __sr(reg, m.fetch(__gr(mb), addr));
        return 0x00;
    }
    int Processor::__addir(){
        int imm = getFromIP();
        int regd = __gr(getFromIP());
        __sr(zr, imm + regd);
        return 0x00;
    }
    int Processor::__addrr() {
        int regf1 = __gr(getFromIP());
        int regf2 = __gr(getFromIP());
        __sr(zr, regf1 + regf2);
        return 0x00;
    }
    int Processor::__subir(){
        int imm = getFromIP();
        int regd = __gr(getFromIP());
        __sr(zr, regd - imm);
        return 0x00;
    }
    int Processor::__subrr(){
        int regf1 = __gr(getFromIP());
        int regf2 = __gr(getFromIP());
        __sr(zr, regf1 - regf2);
        return 0x00;
    }
    int Processor::__mulir(){
        int imm = getFromIP();
        int regd = __gr(getFromIP());
        __sr(zr, imm * regd);
        return 0x00;
    }
    int Processor::__mulrr(){
        int regf1 = __gr(getFromIP());
        int regf2 = __gr(getFromIP());
        __sr(zr, regf1 * regf2);
        return 0x00;
    }
    int Processor::__inc(){
        int reg = getFromIP();
        __sr(reg, __gr(reg) + 1);
        return 0x00;
    }
    int Processor::__dec(){
        int reg = getFromIP();
        __sr(reg, __gr(reg) - 1);
        return 0x00;
    }
    int Processor::__cmprr(){
        int valtcf = __gr(getFromIP());
        int valtcs = __gr(getFromIP());
        __sr(jr, 0);
        // 0x[0][0][0][0][0][0]
        //   EQ NE  G  L GE LE
        if(valtcf == valtcs) __sr(jr, __gr(jr) | 0x100000);
        if(valtcf != valtcs) __sr(jr, __gr(jr) | 0x010000);
        if(valtcf >  valtcs) __sr(jr, __gr(jr) | 0x001000);
        if(valtcf <  valtcs) __sr(jr, __gr(jr) | 0x000100);
        if(valtcf >= valtcs) __sr(jr, __gr(jr) | 0x000010);
        if(valtcf <= valtcs) __sr(jr, __gr(jr) | 0x000001);
        return 0x00;
    }
    int Processor::__cmpir(){
        int valtcf = getFromIP();
        int valtcs = __gr(getFromIP());
        __sr(jr, 0);
        // 0x[0][0][0][0][0][0]
        //   EQ NE  G  L GE LE
        if(valtcf == valtcs) __sr(jr, __gr(jr) | 0x100000);
        if(valtcf != valtcs) __sr(jr, __gr(jr) | 0x010000);
        if(valtcf >  valtcs) __sr(jr, __gr(jr) | 0x001000);
        if(valtcf <  valtcs) __sr(jr, __gr(jr) | 0x000100);
        if(valtcf >= valtcs) __sr(jr, __gr(jr) | 0x000010);
        if(valtcf <= valtcs) __sr(jr, __gr(jr) | 0x000001);
        return 0x00;
    }
    int Processor::__je (){
        int addr = getFromIP();
        if((__gr(jr) & 0xF00000) == 0x100000) __sr(ip, addr);
        return 0x00;
    }
    int Processor::__jne(){
        int addr = getFromIP();
        if((__gr(jr) & 0x0F0000) == 0x010000) __sr(ip, addr);
        return 0x00;
    }
    int Processor::__jg (){
        int addr = getFromIP();
        if((__gr(jr) & 0x00F000) == 0x001000) __sr(ip, addr);
        return 0x00;
    }
    int Processor::__jl (){
        int addr = getFromIP();
        if((__gr(jr) & 0x000F00) == 0x000100) __sr(ip, addr);
        return 0x00;
    }
    int Processor::__jge(){
        int addr = getFromIP();
        if((__gr(jr) & 0x0000F0) == 0x000010) __sr(ip, addr);
        return 0x00;
    }
    int Processor::__jle(){
        int addr = getFromIP();
        if((__gr(jr) & 0x00000F) == 0x000001) __sr(ip, addr);
        return 0x00;
    }
    int Processor::__pushr() {
        int rval = __gr(getFromIP());
        stack.push_back(rval);
        return 0x00;
    }
    int Processor::__pushi() {
        int imm = getFromIP();
        stack.push_back(imm);
        return 0x00;
    }
    int Processor::__popd() {
        stack.pop_back();
        return 0x00;
    }
    int Processor::__popr() {
        int reg = getFromIP();
        int val = stack.back();
        stack.pop_back();
        __sr(reg, val);
        return 0x00;
    }
    int Processor::__mbir() {
        int val = getFromIP();
        __sr(mb, val);
        __sr(ip, 0x00);
        return 0x00;
    }
    int Processor::__nop() {
        return 0x00;
    }

    int Processor::execute(int __instruction) {
        switch(__instruction) {
            case hlt:   return 0x60;
            case movir: return __movir();
            case movrr: return __movrr();
            case movrm: return __movrm();
            case movim: return __movim();
            case movmr: return __movmr();
            case addir: return __addir();
            case addrr: return __addrr();
            case subir: return __subir();
            case subrr: return __subrr();
            case mulir: return __mulir();
            case mulrr: return __mulrr();
            case incr: return __inc();
            case decr: return __dec();
            case cmprr: return __cmprr();
            case cmpir: return __cmpir();
            case je : return __je ();
            case jne: return __jne();
            case jg : return __jg ();
            case jl : return __jl ();
            case jge: return __jge();
            case jle: return __jle();
            case pushr: return __pushr();
            case pushi: return __pushi();
            case popd : return __popd();
            case popr : return __popr();
            case mbir: return __mbir();
            case nop: return __nop();
            default: return 0xe5;
        }
    }
    void Processor::run(int __location, bool __dbg) {
        regs.resetFlags();
        if(__dbg) dbg();
        __sr(ip, __location);
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
    void Processor::loadbin(const char* __fname, int __bank, int __location) {
        std::ifstream ifile(__fname, std::ios::binary);
        std::vector<int> p;
        while(ifile.good()) {
            int cinstr;
            ifile.read(reinterpret_cast<char*>(&cinstr), sizeof(cinstr));
            p.push_back(cinstr);
        }
        int parr[p.size()];
        std::copy(p.begin(), p.end(), parr);
        for(long long unsigned int i = 0; i < p.size() - 1; i++) {
            m.send(__bank, parr[i], i + __location);
            std::cout << std::hex << i + __location << " <- " << std::hex << parr[i] << '\n';
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
            case 0xe5: errormsg(__code, "Instruction %02X not found", m.fetch(__gr(mb), __gr(ip)));
            default: errormsg(__code, "Error code not found, exiting...");
        }
    }
    void Processor::dbg() {
        std::cout << "\n";
        std::cout << "ip: " << __gr(ip) << "\n";
        std::cout << "mb: " << __gr(mb) << "\n";
        std::cout << "ar: " << __gr(ar) << "\n";
        std::cout << "br: " << __gr(br) << "\n";
        std::cout << "cr: " << __gr(cr) << "\n";
        std::cout << "dr: " << __gr(dr) << "\n";
        std::cout << "er: " << __gr(er) << "\n";
        std::cout << "fr: " << __gr(fr) << "\n";
        std::cout << "gr: " << __gr(gr) << "\n";
        std::cout << "hr: " << __gr(hr) << "\n";
        std::cout << "zr: " << __gr(zr) << "\n";
        std::cout << "jr: " << __gr(jr) << "\n";
    }
}
    