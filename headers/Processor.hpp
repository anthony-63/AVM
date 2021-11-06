#pragma once

#include "Registers.hpp"
#include "BankedDataBus.hpp"

namespace AVM {
    class Processor {
        private:
            AVM::Registers regs;
            AVM::BankedDataBus m;
        public:
        Processor(int __bank_count) {
            m = AVM::BankedDataBus(__bank_count);
        }
            void run(int __location, bool __dbg);
            void load(int *__prog, int __psize, int __bank, int __location);
            void dbg();
        private:
            int execute(int __instruction);
            void herror(int __code);
            int getFromIP();
            void step();

        private:
            int __movir();
            int __movrr();
            int __movrm();
            int __movim();
            int __movmr();

            int __addir();
            int __addrr();
            int __subir();
            int __subrr();
            int __mulir();
            int __mulrr();

            int __inc();
            int __dec();

            int __cmprr();
            int __cmpir();

            int __je ();
            int __jne();
            int __jg ();
            int __jl ();
            int __jge();
            int __jle();
    };
}