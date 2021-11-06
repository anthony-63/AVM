#pragma once

#include "BankedMemory.hpp"
namespace AVM {
    class BankedDataBus {
        private:
            AVM::BankedMemory m;
        public:
            void send(int bank, int data, int addr);
            int  fetch(int bank, int addr);
            void clean() {
                m.clean();
            }
        public:
        BankedDataBus() {
            m = AVM::BankedMemory();
        }
        BankedDataBus(int __bank_count) {
            m = AVM::BankedMemory();
        }
    };
}