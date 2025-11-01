#ifndef SPARSE_FLOW_CORE_H
#define SPARSE_FLOW_CORE_H

#include <vector>
#include "../hardware/RegisterFile.h"
#include "../hardware/Memory.h"

class SparseFlowCore {
private:
    int pc;
    long long cycle_count;
    bool halted;
    bool single_cycle_mode;
    
    RegisterFile reg_file;
    Memory memory;

    void executeInstruction(const Instruction& instr);

public:
    SparseFlowCore();
    void loadProgram(const std::vector<Instruction>& prog);
    void run();
    void writeDataMemory(int addr, int val);
    void setSingleCycleMode(bool enable) { single_cycle_mode = enable; }
};

#endif // SPARSE_FLOW_CORE_H
