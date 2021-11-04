#pragma once

#include "Memory.hpp"
namespace AVM {
    class BankedMemory {
        public:
            AVM::Memory banks[16];
    }; 
}