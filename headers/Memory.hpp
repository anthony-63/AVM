#pragma once

#include <vector>
#include <cstdlib>
namespace AVM {
    class Memory {
        public:
            int *mem = (int*)malloc(sizeof(int) * 0xFFFF);
    };
}