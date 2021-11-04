#pragma once

#include "Memory.hpp"
namespace AVM {
    class DataBus {
        public:
            void send(int data, int addr);
            int  fetch(int addr);
        private:
            AVM::Memory m;
    };
}