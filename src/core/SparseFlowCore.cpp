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
    // Load-Use Hazard Detection
    bool load_use_hazard = false;
    
    if (id_ex.valid && (id_ex.instr.op == LW || id_ex.instr.op == LNZ)) {
        // Check if ID stage needs the value being loaded
        if (id_ex.rd == if_id.instr.rs1 || id_ex.rd == if_id.instr.rs2) {
            load_use_hazard = true;
        }
    }
    
    if (load_use_hazard) {
        // Stall: Insert bubble into ID/EX
        stall_pipeline = true;
        id_ex.valid = false;
    } else {
        stall_pipeline = false;
        
        if (if_id.valid) {
            id_ex.instr = if_id.instr;
            id_ex.pc = if_id.pc;
            id_ex.rs1_val = reg_file.read(if_id.instr.rs1);
            id_ex.rs2_val = reg_file.read(if_id.instr.rs2);
            id_ex.imm = if_id.instr.imm;
            id_ex.rd = if_id.instr.rd;
            id_ex.predicted_taken = if_id.predicted_taken;
            id_ex.valid = true;
        } else {
            id_ex.valid = false;
        }
    }
}

void SparseFlowCore::stageExecute() {
    if (id_ex.valid) {
        ex_mem.instr = id_ex.instr;
        ex_mem.rd = id_ex.rd;
        ex_mem.write_data = id_ex.rs2_val;
        
        switch (id_ex.instr.op) {
            case ADD:
                ex_mem.alu_result = id_ex.rs1_val + id_ex.rs2_val;
                break;
            case SUB:
                ex_mem.alu_result = id_ex.rs1_val - id_ex.rs2_val;
                break;
            case LW:
            case SW:
                ex_mem.alu_result = id_ex.rs1_val + id_ex.imm;
                break;
            default:
                ex_mem.alu_result = 0;
                break;
        }
        ex_mem.valid = true;
    } else {
        ex_mem.valid = false;
    }
}

void SparseFlowCore::stageMemory() {
    if (ex_mem.valid) {
        mem_wb.instr = ex_mem.instr;
        mem_wb.rd = ex_mem.rd;
        mem_wb.alu_result = ex_mem.alu_result;
        
        if (ex_mem.instr.op == LW) {
            mem_wb.mem_data = memory.readData(ex_mem.alu_result);
        } else if (ex_mem.instr.op == SW) {
            memory.writeData(ex_mem.alu_result, ex_mem.write_data);
        }
        mem_wb.valid = true;
    } else {
        mem_wb.valid = false;
    }
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
