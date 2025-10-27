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
        Instruction instr = memory.fetch(pc);
        executeInstruction(instr);
        cycle_count++;
    }
    
    std::cout << "Execution complete. Cycles: " << cycle_count << std::endl;
    reg_file.dump();
}

void SparseFlowCore::executeInstruction(const Instruction& instr) {
    int rs1_val = reg_file.read(instr.rs1);
    int rs2_val = reg_file.read(instr.rs2);
    int result = 0;
    
    switch (instr.op) {
        case ADD:
            result = rs1_val + rs2_val;
            reg_file.write(instr.rd, result);
            break;
        case SUB:
            result = rs1_val - rs2_val;
            reg_file.write(instr.rd, result);
            break;
        default:
            break;
    }
    
    pc++;
}
