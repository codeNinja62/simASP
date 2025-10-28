#include "Memory.h"

Memory::Memory() : data_mem(1024, 0) {
}

void Memory::loadProgram(const std::vector<Instruction>& program) {
    instr_mem = program;
}

Instruction Memory::fetch(int pc) {
    if (pc >= 0 && pc < instr_mem.size()) {
        return instr_mem[pc];
    }
    Instruction nop;
    return nop;
}

int Memory::readData(int addr) {
    if (addr >= 0 && addr < data_mem.size()) {
        return data_mem[addr];
    }
    return 0;
}

void Memory::writeData(int addr, int value) {
    if (addr >= 0 && addr < data_mem.size()) {
        data_mem[addr] = value;
    }
}
