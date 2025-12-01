#ifndef SPARSE_FLOW_CORE_H
#define SPARSE_FLOW_CORE_H

#include <vector>
#include "../hardware/RegisterFile.h"
#include "../hardware/Memory.h"
#include "../hardware/BranchPredictor.h"
#include "../utils/Stats.h"
#include "../utils/TraceLogger.h"
#include "PipelineRegisters.h"

class SparseFlowCore {
private:
    int pc;
    long long cycle_count;
    bool halted;

    // Hardware Units
    RegisterFile reg_file;
    Memory memory;
    BranchPredictor branch_predictor;
    Stats stats;
    TraceLogger trace_logger;

    // Pipeline Registers
    IF_ID_Reg  if_id;
    ID_EX_Reg  id_ex;
    EX_MEM_Reg ex_mem;
    MEM_WB_Reg mem_wb;
    MEM_WB_Reg wb_shadow; // Shadow register for Forwarding from WB

    // Stats
    int zero_skips;
    bool stall_pipeline;
    int mem_stall_cycles; // Added for Memory Latency

    // Pipeline Stages
    void stageFetch();
    void stageDecode();
    void stageExecute();
    void stageMemory();
    void stageWriteback();

public:
    SparseFlowCore();
    void loadProgram(const std::vector<Instruction>& prog);
    void writeDataMemory(int addr, int val);
    void run();
    void setSingleCycleMode(bool enable) { single_cycle_mode = enable; }
    void setShowPipeline(bool enable) { show_pipeline = enable; }
    void printPipelineDiagram(int lastN = 20) { trace_logger.printAsciiDiagram(lastN); }
    void savePipelineDiagram(const std::string& filename) { trace_logger.printAsciiDiagramToFile(filename); }

private:
    bool single_cycle_mode;
    bool show_pipeline;
    bool isPipelineEmpty() const;
};

#endif // SPARSE_FLOW_CORE_H
