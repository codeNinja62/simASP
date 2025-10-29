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
    int mem_addr = 0;
    
    switch (instr.op) {
        case ADD:
            alu_result = rs1_val + rs2_val;
            reg_file.write(instr.rd, alu_result);
            break;
        case SUB:
            alu_result = rs1_val - rs2_val;
            reg_file.write(instr.rd, alu_result);
            break;
        case LW:
            // Fixed: Use word-aligned address calculation
            mem_addr = rs1_val + instr.imm;
            alu_result = memory.readData(mem_addr);
            reg_file.write(instr.rd, alu_result);
            break;
        case SW:
            mem_addr = rs1_val + instr.imm;
            memory.writeData(mem_addr, rs2_val);
            break;
        default:
            break;
    }
    
    pc++;
}
