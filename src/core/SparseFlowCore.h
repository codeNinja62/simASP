#ifndef SPARSE_FLOW_CORE_H
#define SPARSE_FLOW_CORE_H

#include <vector>
#include "../hardware/RegisterFile.h"
#include "../hardware/Memory.h"

class SparseFlowCore {
private:
    int pc;
    long long cycle_count;
    RegisterFile reg_file;
    Memory memory;

public:
    SparseFlowCore();
    void loadProgram(const std::vector<Instruction>& prog);
    void run();
};

#endif // SPARSE_FLOW_CORE_H
