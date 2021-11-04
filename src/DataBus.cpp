#include "../headers/DataBus.hpp"
#include <iostream>
namespace AVM {
    void DataBus::send(int data, int addr) {
        m.mem[addr] = data;
    }
    int DataBus::fetch(int addr) {
        return m.mem[addr];
    }
}