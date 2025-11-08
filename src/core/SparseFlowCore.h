#ifndef SPARSE_FLOW_CORE_H
#define SPARSE_FLOW_CORE_H

#include <vector>
#include "../hardware/RegisterFile.h"
#include "../hardware/Memory.h"
#include "../hardware/BranchPredictor.h"
#include "PipelineRegisters.h"

class SparseFlowCore {
private:
    int pc;
    long long cycle_count;
    bool halted;
    bool single_cycle_mode;
    bool stall_pipeline;
    
    RegisterFile reg_file;
    Memory memory;
    BranchPredictor branch_predictor;

    // Pipeline Registers
    IF_ID_Reg if_id;
    ID_EX_Reg id_ex;
    EX_MEM_Reg ex_mem;
    MEM_WB_Reg mem_wb;

    // Pipeline stage methods
    void stageFetch();
    void stageDecode();
    void stageExecute();
    void stageMemory();
    void stageWriteback();

public:
    SparseFlowCore();
    void loadProgram(const std::vector<Instruction>& prog);
    void run();
    void writeDataMemory(int addr, int val);
    void setSingleCycleMode(bool enable) { single_cycle_mode = enable; }
};

#endif // SPARSE_FLOW_CORE_H
