#include "SparseFlowCore.h"
#include <iostream>

SparseFlowCore::SparseFlowCore() : pc(0), cycle_count(0), halted(false), single_cycle_mode(false) {
}

void SparseFlowCore::loadProgram(const std::vector<Instruction>& prog) {
    memory.loadProgram(prog);
}

void SparseFlowCore::writeDataMemory(int addr, int val) {
    memory.writeData(addr, val);
}

void SparseFlowCore::run() {
    while (!halted) {
        // Pipeline stages executed in reverse order
        stageWriteback();
        stageMemory();
        stageExecute();
        stageDecode();
        stageFetch();
        
        cycle_count++;
        stats.addCycle();
    }
    
    stats.setCacheStats(memory.getCacheHits(), memory.getCacheMisses());
    stats.printReport();
    reg_file.dump();
}

bool SparseFlowCore::isPipelineEmpty() const {
    return !if_id.valid && !id_ex.valid && !ex_mem.valid && !mem_wb.valid;
}

void SparseFlowCore::stageFetch() {
    // Fetch instruction from memory
    if (!stall_pipeline) {
        if_id.instr = memory.fetch(pc);
        if_id.pc = pc;
        if_id.valid = true;
        
        // Branch prediction
        if (if_id.instr.op == BEQ || if_id.instr.op == BZERO) {
            if_id.predicted_taken = branch_predictor.predict(pc);
            if (if_id.predicted_taken) {
                pc = pc + if_id.instr.imm;
            } else {
                pc++;
            }
        } else if (if_id.instr.op == JMP) {
            pc = pc + if_id.instr.imm;
        } else {
            pc++;
        }
    }
}

void SparseFlowCore::stageDecode() {
    // Decode and read registers
}

void SparseFlowCore::stageExecute() {
    // ALU operations and forwarding
}

void SparseFlowCore::stageMemory() {
    // Memory access
}

void SparseFlowCore::stageWriteback() {
    // Write back to registers
    if (mem_wb.valid && mem_wb.rd != 0) {
        if (mem_wb.instr.op == LW || mem_wb.instr.op == LNZ) {
            reg_file.write(mem_wb.rd, mem_wb.mem_data);
        } else {
            reg_file.write(mem_wb.rd, mem_wb.alu_result);
        }
        stats.addInstructionRetired();
    }
    
    // Update shadow for forwarding
    wb_shadow = mem_wb;
}
