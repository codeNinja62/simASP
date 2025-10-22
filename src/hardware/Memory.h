#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include "../isa/Instruction.h"

class Memory {
private:
    std::vector<int> data_mem;
    std::vector<Instruction> instr_mem;
    // Cache object will be added later

public:
    Memory();
    void loadProgram(const std::vector<Instruction>& program);
    Instruction fetch(int pc);
    int readData(int addr);
    void writeData(int addr, int value);
};

#endif // MEMORY_H
