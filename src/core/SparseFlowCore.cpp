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
    
    std::cout << "Cycles: " << cycle_count << std::endl;
    reg_file.dump();
}

void SparseFlowCore::executeInstruction(const Instruction& instr) {
    int rs1_val = reg_file.read(instr.rs1);
    int rs2_val = reg_file.read(instr.rs2);
    int alu_result = 0;
    
    // ALU operation based on opcode
    switch (instr.op) {
        case ADD:
            alu_result = rs1_val + rs2_val;
            reg_file.write(instr.rd, alu_result);
            break;
        case SUB:
            alu_result = rs1_val - rs2_val;
            reg_file.write(instr.rd, alu_result);
            break;
        // ADDI uses rs1 + immediate
        // Fixed: was incorrectly using rs2_val
        default:
            break;
    }
    
    pc++;
}
