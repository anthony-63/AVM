#pragma once

#include <vector>
#include <cstdlib>
namespace AVM {
    class Memory {
        public:
            int *mem = new int[0xFFFF];
            ~Memory() {
                delete mem;
            }
    };
}