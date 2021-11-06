#pragma once

#include "Memory.hpp"
namespace AVM {
    class BankedMemory {
        public:
            AVM::Memory *banks;
        public:
            BankedMemory() {
                banks = new AVM::Memory[16];
            }
            BankedMemory(int __bank_count) {
                banks = new AVM::Memory[__bank_count];
            }
            void clean() {
                delete banks;
            }
    }; 
}