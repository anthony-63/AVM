#include "../headers/Assembler.hpp"
#include "../headers/Instructions.hpp"
#include "../headers/Registers.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstring>

#define __p(X) program.push_back(X)
int line = 0;
namespace AVM {
    void err(std::string inst) {
        std::cout << "\nInstruction '" << inst << "' does not exist on line '" << line << "'\n";
        exit(-1);
    }
    void expect(int val, std::string expect) {
        if(val < 0) {
            std::cout << "\nExpected " << expect << " on line " << line << "\n";
            exit(-1);
        }
    }
    int get_reg_index(std::string reg) {
        if(reg == "ar") return ar;
        else if(reg == "br") return br;
        else if(reg == "cr") return cr;
        else if(reg == "dr") return dr;
        else if(reg == "er") return er;
        else if(reg == "fr") return fr;
        else if(reg == "gr") return gr;
        else if(reg == "hr") return hr;
        else if(reg == "zr") return zr;
        else if(reg == "jr") return jr;
        else if(reg == "ip") return ip;
        else if(reg == "mb") return mb;
        else {
            std::cout << "\nRegister '" << reg << "' does not exist on line " << line << std::endl;
            exit(-1);
        }
        return 0;
    }
    std::string cline;
    int consume_hex_first() {
        int floc = cline.find("$");
        int sloc = cline.find(",");
        int hlen = sloc - floc;
        expect(floc, "hex");
        std::string hexs = cline.substr(floc + 1, hlen);
        return stoi(hexs, 0, 16);
    }
    int consume_hex_second() {
        int floc = cline.find(", $");
        int sloc = cline.find(";");
        int hlen = sloc - floc;
        expect(floc, "hex");
        std::string hexs = cline.substr(floc + 1, hlen);
        return stoi(hexs, 0, 16);
    }
    int consume_hex_single() {
        int floc = cline.find("$");
        int sloc = cline.find(";");
        int hlen = sloc - floc;
        expect(floc, "hex");
        std::string hexs = cline.substr(floc + 1, hlen);
        return stoi(hexs, 0, 16);
    }
    int consume_addr_first() {
        int floc = cline.find("@");
        int sloc = cline.find(",");
        int hlen = sloc - floc;
        expect(floc, "address");
        std::string hexs = cline.substr(floc + 1, hlen);
        return stoi(hexs, 0, 16);
    }
    int consume_addr_second() {
        int floc = cline.find(", @");
        int sloc = cline.find(";");
        int hlen = sloc - floc;
        expect(floc, "address");
        std::string hexs = cline.substr(floc + 1, hlen);
        return stoi(hexs, 0, 16);
    }
    int consume_addr_single() {
        int floc = cline.find("@");
        int sloc = cline.find(";");
        int hlen = sloc - floc;
        expect(floc, "address");
        std::string hexs = cline.substr(floc + 1, hlen);
        return stoi(hexs, 0, 16);
    }
    int consume_reg_first() {
        int floc = cline.find("%");
        expect(floc, "register");
        std::string reg = cline.substr(floc + 1, 2);
        return get_reg_index(reg);
    }
    int consume_reg_second() {
        int floc = cline.find(", %");
        expect(floc, "register");
        std::string reg = cline.substr(floc + 3, 2);
        return get_reg_index(reg);
    }
    void Assembler::assemble(const char* filename, const char* outname) {
        std::ifstream file(filename);
        std::stringstream buf;
        buf << file.rdbuf();
        std::string prog(buf.str());
        std::vector<int> program;
        std::vector<std::string> strs;
        std::istringstream iss(prog);
        program.push_back(0xf9);
        
        while(std::getline(iss, cline, '\n')) {
            line++;
            std::string inst = cline.substr(0, 3);
            std::for_each(inst.begin(), inst.end(), [](char & c) {
                c = ::tolower(c);
            });
            if(cline.substr(cline.length() - 1) != ";") {
                std::cout << "Expected ';' on line " << line << "\n";
                exit(-1);
            }
            if(inst == "mov") {
                std::cout << "MOV ";
                std::string ty1 = cline.substr(3, 1);
                std::string ty2 = cline.substr(4, 1);
                if(ty1 == "i" && ty2 == "r") {
                    std::cout << "IMM, REG";
                    __p(movir);
                    __p(consume_hex_first());
                    __p(consume_reg_second());
                }else if(ty1 == "r" && ty2 == "r") {
                    std::cout << "REG, REG";
                    __p(movrr);
                    __p(consume_reg_first());
                    __p(consume_reg_second());
                }else if(ty1 == "r" && ty2 == "m") {
                    std::cout << "REG, MEM";
                    __p(movrm);
                    __p(consume_reg_first());
                    __p(consume_addr_second());
                }else if(ty1 == "i" && ty2 == "m") {
                    std::cout << "IMM, MEM";
                    __p(movim);
                    __p(consume_hex_first());
                    __p(consume_addr_second());
                }else if(ty1 == "m" && ty2 == "r") {
                    std::cout << "MEM, REG";
                    __p(movmr);
                    __p(consume_addr_first());
                    __p(consume_reg_second());
                }else {
                    err(inst);
                }
            }else if(inst == "add") {
                std::cout << "ADD ";
                std::string ty1 = cline.substr(3, 1);
                std::string ty2 = cline.substr(4, 1);
                if(ty1 == "i" && ty2 == "r") {
                    std::cout << "IMM, REG";
                    __p(addir);
                    __p(consume_hex_first());
                    __p(consume_reg_second());
                }else if(ty1 == "r" && ty2 == "r") {
                    std::cout << "REG, REG";
                    __p(addrr);
                    __p(consume_reg_first());
                    __p(consume_reg_second());
                }else {
                    err(inst);
                }
            }else if(inst == "sub") {
                std::cout << "SUB ";
                std::string ty1 = cline.substr(3, 1);
                std::string ty2 = cline.substr(4, 1);
                if(ty1 == "i" && ty2 == "r") {
                    std::cout << "IMM, REG";
                    __p(subir);
                    __p(consume_hex_first());
                    __p(consume_reg_second());
                }else if(ty1 == "r" && ty2 == "r") {
                    std::cout << "REG, REG";
                    __p(subrr);
                    __p(consume_reg_first());
                    __p(consume_reg_second());
                }else {
                    err(inst);
                }
            }else if(inst == "mul") {
                std::cout << "MUL ";
                std::string ty1 = cline.substr(3, 1);
                std::string ty2 = cline.substr(4, 1);
                if(ty1 == "i" && ty2 == "r") {
                    std::cout << "IMM, REG";
                    __p(mulir);
                    __p(consume_hex_first());
                    __p(consume_reg_second());
                }else if(ty1 == "r" && ty2 == "r") {
                    std::cout << "REG, REG";
                    __p(mulrr);
                    __p(consume_reg_first());
                    __p(consume_reg_second());
                }else {
                    err(inst);
                }
            }else if(inst == "inc") {
                std::cout << "INC ";
                std::string ty = cline.substr(3, 1);
                if(ty == "r") {
                    std::cout << "REG";
                    __p(incr);
                    __p(consume_reg_first());
                }else {
                    err(inst);
                }
            }else if(inst == "dec") {
                std::cout << "DEC ";
                std::string ty = cline.substr(3, 1);
                if(ty == "r") {
                    std::cout << "REG";
                    __p(decr);
                    __p(consume_reg_first());
                }else {
                    err(inst);
                }    
            }else if(inst == "cmp") {
                std::cout << "CMP ";
                std::string ty1 = cline.substr(3, 1);
                std::string ty2 = cline.substr(4, 1);
                if(ty1 == "i" && ty2 == "r") {
                    std::cout << "IMM, REG";
                    __p(cmpir);
                    __p(consume_hex_first());
                    __p(consume_reg_second());
                }else if(ty1 == "r" && ty2 == "r") {
                    std::cout << "REG, REG";
                    __p(cmprr);
                    __p(consume_reg_first());
                    __p(consume_reg_second());
                }else {
                    err(inst);
                }
            }else if(inst == "jeq") {
                std::cout << "JEQ ";
                __p(je);
                __p(consume_addr_single());
            }else if(inst == "jne") {
                std::cout << "JNE ";
                __p(jne);
                __p(consume_addr_single());
            }else if(inst == "jgt") {
                std::cout << "JGT ";
                __p(jg);
                __p(consume_addr_single());
            }else if(inst == "jlt") {
                std::cout << "JLT ";
                __p(jl);
                __p(consume_addr_single());
            }else if(inst == "jge") {
                std::cout << "JGE ";
                __p(jge);
                __p(consume_addr_single());
            }else if(inst == "jle") {
                std::cout << "JLE ";
                __p(jle);
                __p(consume_addr_single());
            }else if(inst == "hlt") {
                std::cout << "HLT ";
                __p(hlt);
            }else if(inst == "psh") {
                std::cout << "PSH ";
                std::string ty = cline.substr(3, 1);
                if(ty == "i") {
                    std::cout << "IMM";
                    __p(pushi);
                    __p(consume_hex_single());
                }else if(ty == "r") {
                    std::cout << "REG";
                    __p(pushr);
                    __p(consume_reg_first());
                }else {
                    err(inst);
                }
            }else if(inst == "pop") {
                std::cout << "POP ";
                std::string ty = cline.substr(3, 1);
                if(ty == "d") {
                    std::cout << "DEL";
                    __p(popd);
                }else if(ty == "r") {
                    std::cout << "REG";
                    __p(popr);
                    __p(consume_reg_first());
                }else {
                    err(inst);
                }
            }else if(inst == "mbi") {
                std::cout << "MBIR ";
                std::string ty = cline.substr(3, 1);
                if(ty == "r") {
                    std::cout << "RESET";
                    __p(mbir);
                }else {
                    err(inst);
                }
            }else if(inst == "nop") {
                std::cout << "NOP ";
                __p(nop);
            }else {
                err(inst);
            }
            std::cout << " INSTRUCTION\n";
        }
        int parr[program.size()];
        std::copy(program.begin(), program.end(), parr);
        std::cout << "program hex: ";
        for(long long unsigned int i = 0; i < program.size(); i++) {
            std::cout << std::hex << parr[i] << " ";
        }
        std::fstream outf;
        outf.open(outname, std::ios::out | std::ios::binary);
        for(long long unsigned int i = 0; i < program.size(); i++) {
            outf.write(reinterpret_cast<const char *>(&parr[i]), sizeof(parr[i]));
        }
        std::cout << "\n";
    }
}