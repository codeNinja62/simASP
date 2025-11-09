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
        stageWriteback();
        stageMemory();
        stageExecute();
        stageDecode();
        stageFetch();
        
        cycle_count++;
        
        // DEBUG: Print pipeline state
        std::cout << "Cycle " << cycle_count << ": ";
        std::cout << "IF_ID.valid=" << if_id.valid;
        std::cout << " ID_EX.valid=" << id_ex.valid;
        std::cout << " EX_MEM.valid=" << ex_mem.valid;
        std::cout << " MEM_WB.valid=" << mem_wb.valid << std::endl;
    }
    
    std::cout << "Cycles: " << cycle_count << std::endl;
    reg_file.dump();
}

void SparseFlowCore::stageFetch() {
    if (!stall_pipeline) {
        if_id.instr = memory.fetch(pc);
        if_id.pc = pc;
        if_id.valid = true;
        if_id.predicted_taken = false;
        pc++;
    }
}

void SparseFlowCore::stageDecode() {
    if (if_id.valid) {
        id_ex.instr = if_id.instr;
        id_ex.pc = if_id.pc;
        id_ex.rs1_val = reg_file.read(if_id.instr.rs1);
        id_ex.rs2_val = reg_file.read(if_id.instr.rs2);
        id_ex.imm = if_id.instr.imm;
        id_ex.rd = if_id.instr.rd;
        id_ex.valid = true;
    } else {
        id_ex.valid = false;
    }
}

void SparseFlowCore::stageExecute() {
    // TODO
}

void SparseFlowCore::stageMemory() {
    // TODO
}

void SparseFlowCore::stageWriteback() {
    if (mem_wb.valid && mem_wb.rd != 0) {
        if (mem_wb.instr.op == LW || mem_wb.instr.op == LNZ) {
            reg_file.write(mem_wb.rd, mem_wb.mem_data);
        } else {
            reg_file.write(mem_wb.rd, mem_wb.alu_result);
        }
    }
    
    if (mem_wb.instr.op == HALT && mem_wb.valid) {
        halted = true;
    }
}
