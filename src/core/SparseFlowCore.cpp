#include "SparseFlowCore.h"
#include <iostream>

SparseFlowCore::SparseFlowCore() : pc(0), cycle_count(0), halted(false) {
}

void SparseFlowCore::loadProgram(const std::vector<Instruction>& prog) {
    memory.loadProgram(prog);
}

void SparseFlowCore::writeDataMemory(int addr, int val) {
    memory.writeData(addr, val);
}

void SparseFlowCore::run() {
    while (!halted) {
        // Fetch
        Instruction instr = memory.fetch(pc);
        
        // Decode & Execute
        executeInstruction(instr);
        
        cycle_count++;
    }
    
    std::cout << "Execution complete. Cycles: " << cycle_count << std::endl;
    reg_file.dump();
}

void SparseFlowCore::executeInstruction(const Instruction& instr) {
    // TODO: Implement
    pc++;
}
