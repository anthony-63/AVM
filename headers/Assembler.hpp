#pragma once

#include "Instructions.hpp"
#include "Processor.hpp"
#include <vector>
namespace AVM {
    class Assembler {
        public:
            void assemble(const char* filename, const char* outname);
    };
}