#pragma once

#define ip 0
#define sp 1
#define mb 2
#define ar 3
#define br 4
#define cr 5
#define dr 6
#define er 7
#define fr 8
#define gr 9
#define hr 10
#define zr 11
#define jr 12
namespace AVM {
    class Registers {
        public:
            int regs[12]{};
            void setRegister(int reg, int val) {
                regs[reg] = val;
            }
            int getRegister(int reg) {
                return regs[reg];
            }
            
        

    };
}