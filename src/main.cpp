#include <iostream>
#include "../headers/DataBus.hpp"
#include "../headers/BankedDataBus.hpp"
int main() {
    AVM::DataBus db;
    std::cout << "----------DATA BUS TEST----------\n";
    std::cout << "Moving data 3000 to address 0x3000\n";
    db.send(3000, 0x3000);
    std::cout << "Data at 0x3000 is '" << db.fetch(0x3000) << "'\n";

    AVM::BankedDataBus bdb;
    std::cout << "----------BANKED DATA BUS TEST----------\n";
    std::cout << "Moving data 3000 to address 0x3000 in bank one\n";
    bdb.send(1, 3000, 0x3000);
    std::cout << "Moving data 3001 to address 0x3000 in bank two\n";
    bdb.send(2, 3001, 0x3000);
    std::cout << "Data at 0x3000 bank 1 is '" << bdb.fetch(1, 0x3000) << "'\n";
    std::cout << "Data at 0x0000 bank 2 is '" << bdb.fetch(2, 0x3000) << "'\n";
    return 0;
}