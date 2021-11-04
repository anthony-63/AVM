#include "../headers/BankedDataBus.hpp"
#include <iostream>
namespace AVM {
    void BankedDataBus::send(int bank, int data, int addr) {
        m.banks[bank].mem[addr] = data;
    }
    int BankedDataBus::fetch(int bank, int addr) {
        return m.banks[bank].mem[addr];
    }
}