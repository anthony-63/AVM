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
            int __addrr();
    };
}