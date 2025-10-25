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
    RegisterFile reg_file;
    Memory memory;

    // Single-cycle execution
    void executeInstruction(const Instruction& instr);

public:
    SparseFlowCore();
    void loadProgram(const std::vector<Instruction>& prog);
    void run();
    void writeDataMemory(int addr, int val);
};

#endif // SPARSE_FLOW_CORE_H
