#include "SparseFlowCore.h"
#include <iostream>

SparseFlowCore::SparseFlowCore() 
    : pc(0), cycle_count(0), halted(false), single_cycle_mode(false), stall_pipeline(false) {
}

void SparseFlowCore::loadProgram(const std::vector<Instruction>& prog) {
    memory.loadProgram(prog);
}

void SparseFlowCore::writeDataMemory(int addr, int val) {
    memory.writeData(addr, val);
}

void SparseFlowCore::run() {
    while (!halted) {
        // Pipeline stages in reverse order (WB -> IF)
        stageWriteback();
        stageMemory();
        stageExecute();
        stageDecode();
        stageFetch();
        
        cycle_count++;
    }
    
    std::cout << "Cycles: " << cycle_count << std::endl;
    reg_file.dump();
}

void SparseFlowCore::stageFetch() {
    // TODO: Implement
}

void SparseFlowCore::stageDecode() {
    // TODO: Implement
}

void SparseFlowCore::stageExecute() {
    // TODO: Implement
}

void SparseFlowCore::stageMemory() {
    // TODO: Implement
}

void SparseFlowCore::stageWriteback() {
    // TODO: Implement
}
