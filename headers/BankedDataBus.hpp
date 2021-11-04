#pragma once

#include "BankedMemory.hpp"
namespace AVM {
    class BankedDataBus {
        public:
            void send(int bank, int data, int addr);
            int  fetch(int bank, int addr);
        private:
            AVM::BankedMemory m;
    };
}