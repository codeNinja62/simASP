#include "Memory.h"

using namespace std;

Memory::Memory() : cache(1024, 64) { // 1KB Cache, 64B Blocks
    data_mem.resize(1024 * 1024, 0); // 1M words (4MB), sufficient for 512x512
}

void Memory::loadProgram(const vector<Instruction>& program) {
    instr_mem = program;
}

Instruction Memory::fetch(int pc) const {
    if (pc < 0 || pc >= (int)instr_mem.size()) return Instruction(); // Return HALT/NOP
    return instr_mem[pc];
}

int Memory::requestAccess(int addr) {
    // Check Cache
    bool hit = cache.access(addr);
    return hit ? HIT_LATENCY : MISS_LATENCY;
}

int Memory::readData(int addr) const {
    if (addr < 0 || addr >= (int)data_mem.size()) return 0;
    return data_mem[addr];
}

void Memory::writeData(int addr, int value) {
    if (addr >= 0 && addr < data_mem.size()) data_mem[addr] = value;
    // Note: We do NOT call cache.access() here.
    // The pipeline calls requestAccess() separately to simulate latency/cache effects.
    // This function is purely for the physical memory write.
}
