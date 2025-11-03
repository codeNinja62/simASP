#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include "../isa/Instruction.h"
#include "Cache.h"

class Memory {
private:
    std::vector<int> data_mem;
    std::vector<Instruction> instr_mem;
    Cache cache;

    const int HIT_LATENCY = 1;
    const int MISS_LATENCY = 10;

public:
    Memory();
    void loadProgram(const std::vector<Instruction>& program);
    Instruction fetch(int pc);
    
    int requestAccess(int addr);
    int readData(int addr);
    void writeData(int addr, int value);

    long long getCacheHits() const { return cache.getHits(); }
    long long getCacheMisses() const { return cache.getMisses(); }
};

#endif // MEMORY_H
