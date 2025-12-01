#include "Memory.h"

using namespace std;

Memory::Memory() : cache(1024, 32) { // 1KB Cache, 32B Blocks (match report)
    // Main memory: 512K words to accommodate 512x512 benchmarks
    data_mem.resize(512 * 1024, 0); // 512K words (~2MB assuming 4B words)
}

void Memory::loadProgram(const vector<Instruction>& program) {
    instr_mem = program;
}

Instruction Memory::fetch(int pc) {
    if (pc < 0 || pc >= instr_mem.size()) return Instruction(); // Return HALT/NOP
    return instr_mem[pc];
}

int Memory::requestAccess(int addr) {
    // Check Cache
    bool hit = cache.access(addr);
    return hit ? HIT_LATENCY : MISS_LATENCY;
}

int Memory::readData(int addr) {
    if (addr < 0 || addr >= data_mem.size()) return 0;
    return data_mem[addr];
}

void Memory::writeData(int addr, int value) {
    if (addr >= 0 && addr < data_mem.size()) data_mem[addr] = value;
    // Note: We do NOT call cache.access() here.
    // The pipeline calls requestAccess() separately to simulate latency/cache effects.
    // This function is purely for the physical memory write.
}
