#include "SparseFlowCore.h"
#include <iostream>

using namespace std;

SparseFlowCore::SparseFlowCore() 
    : pc(0), cycle_count(0), halted(false), zero_skips(0), stall_pipeline(false), mem_stall_cycles(0),
      trace_logger("pipeline_trace.csv"), single_cycle_mode(false) 
{
    // Initialize pipeline registers to invalid
    if_id.valid = false;
    id_ex.valid = false;
    ex_mem.valid = false;
    mem_wb.valid = false;
}

bool SparseFlowCore::isPipelineEmpty() const {
    return !if_id.valid && !id_ex.valid && !ex_mem.valid && !mem_wb.valid;
}

void SparseFlowCore::loadProgram(const vector<Instruction>& prog) {
    memory.loadProgram(prog);
}

void SparseFlowCore::writeDataMemory(int addr, int val) {
    memory.writeData(addr, val);
}

// ------------------------------------------------------------------------
// STAGE 1: FETCH (IF)
// ------------------------------------------------------------------------
void SparseFlowCore::stageFetch() {
    if (halted) return;
    if (stall_pipeline) return; // Stall: Do not fetch new instruction

    // Single-Cycle Mode: Only fetch if the pipeline is completely empty
    if (single_cycle_mode && !isPipelineEmpty()) {
        return;
    }

    Instruction fetched = memory.fetch(pc);
    
    if (fetched.op == BEQ) {
        // cout << " [DEBUG] Fetching BEQ at PC " << pc << " Imm=" << fetched.imm << endl;
    }

    // Branch Prediction
    bool predict_taken = false;
    if (fetched.op == BEQ || fetched.op == BZERO || fetched.op == JMP) {
        predict_taken = branch_predictor.predict(pc);
    }

    // Update IF/ID Pipeline Register
    if_id.instr = fetched;
    if_id.pc = pc;
    if_id.predicted_taken = predict_taken;
    if_id.valid = true;

    // Update PC based on prediction
    if (predict_taken && fetched.op != HALT) {
        // Speculative Fetch!
        // Note: For JMP/BEQ, we need the target. 
        // In a real CPU, we'd have a BTB (Branch Target Buffer).
        // Here, we'll cheat slightly and calculate target if it's an immediate jump,
        // or just stall if it's register-based (JALR).
        // For simplicity in this phase, let's assume we know the target if it's immediate.
        pc = pc + fetched.imm; 
    } else if (fetched.op != HALT) {
        pc++; 
    }
}

// ------------------------------------------------------------------------
// STAGE 2: DECODE (ID)
// ------------------------------------------------------------------------
void SparseFlowCore::stageDecode() {
    if (!if_id.valid) {
        id_ex.valid = false;
        return;
    }

    Instruction instr = if_id.instr;

    // Read Registers
    int val1 = reg_file.read(instr.rs1);
    int val2 = reg_file.read(instr.rs2);

    // Hazard Detection Unit (Load-Use Stall)
    // Check if instruction currently in MEM stage (just finished EX) is a Load
    // and its destination matches source of this instruction.
    bool ex_is_load = (ex_mem.valid && (ex_mem.instr.op == LW || ex_mem.instr.op == LNZ || ex_mem.instr.op == VLOAD));
    if (ex_is_load && ex_mem.rd != 0) {
        // Note: VLOAD writes to Vector Regs, so it won't hazard with Scalar Regs (rs1/rs2)
        // UNLESS we implement Vector ALU instructions that use v-regs.
        // For now, VLOAD only hazards if we try to use the vector register immediately, 
        // but our ISA doesn't have Vector ALU yet.
        // However, standard LW/LNZ hazard logic applies to scalar registers.
        if (ex_mem.instr.op != VLOAD) { 
             if (ex_mem.rd == instr.rs1 || ex_mem.rd == instr.rs2) {
                stall_pipeline = true;
                id_ex.valid = false; // Insert Bubble into EX
                stats.addStall(); // Track Stall
                // cout << " [Hazard] Load-Use Stall inserted." << endl;
                return; // Do not advance ID stage
            }
        }
    }

    // LNZ Auto-Increment Hazard
    // If preceding instruction is LNZ and uses the same base register, we must stall
    // until it finishes and writes back the updated pointer.
    bool hazard_lnz = false;
    if (ex_mem.valid && ex_mem.instr.op == LNZ && (ex_mem.instr.rs1 == instr.rs1 || ex_mem.instr.rs1 == instr.rs2)) hazard_lnz = true;
    if (mem_wb.valid && mem_wb.instr.op == LNZ && (mem_wb.instr.rs1 == instr.rs1 || mem_wb.instr.rs1 == instr.rs2)) hazard_lnz = true;

    if (hazard_lnz) {
        stall_pipeline = true;
        id_ex.valid = false;
        stats.addStall();
        // cout << " [Hazard] LNZ Auto-Increment Stall." << endl;
        return;
    }

    stall_pipeline = false; // Reset stall if no hazard

    // Update ID/EX Pipeline Register
    id_ex.instr = instr;
    id_ex.pc = if_id.pc;
    id_ex.rs1_val = val1;
    id_ex.rs2_val = val2;
    id_ex.imm = instr.imm;
    id_ex.rd = instr.rd;
    id_ex.predicted_taken = if_id.predicted_taken;
    id_ex.valid = true;

    // Consume the instruction from IF/ID
    if_id.valid = false;

    if (instr.op == HALT) {
        // Propagate halt, but don't stop immediately until WB sees it
    }
}

// ------------------------------------------------------------------------
// STAGE 3: EXECUTE (EX)
// ------------------------------------------------------------------------
void SparseFlowCore::stageExecute() {
    if (!id_ex.valid) {
        ex_mem.valid = false;
        return;
    }

    // Forwarding Unit
    int op1 = id_ex.rs1_val;
    int op2 = id_ex.rs2_val;

        // Forward from MEM stage (EX/MEM) - Priority 1
        bool ex_mem_writes = (ex_mem.instr.op != BEQ && ex_mem.instr.op != BZERO && ex_mem.instr.op != SW && ex_mem.instr.op != HALT);
        if (ex_mem.valid && ex_mem_writes && ex_mem.rd != 0) {
            if (ex_mem.rd == id_ex.instr.rs1) {
                op1 = ex_mem.alu_result;
                // cout << " [Forwarding] EX->EX (rs1): " << op1 << endl;
            }
            if (ex_mem.rd == id_ex.instr.rs2) {
                op2 = ex_mem.alu_result;
                // cout << " [Forwarding] EX->EX (rs2): " << op2 << endl;
            }
        }    // Forward from WB stage (MEM/WB) - Priority 2
    // Use wb_shadow because mem_wb has been updated by stageMemory for the *next* cycle
    bool mem_wb_writes = (wb_shadow.instr.op != BEQ && wb_shadow.instr.op != BZERO && wb_shadow.instr.op != SW && wb_shadow.instr.op != HALT);
    if (wb_shadow.valid && mem_wb_writes && wb_shadow.rd != 0) {
        int wb_val = (wb_shadow.instr.op == LW || wb_shadow.instr.op == LNZ) ? wb_shadow.mem_data : wb_shadow.alu_result;
        
        // Only forward if not already forwarded from EX (EX has priority)
        if (wb_shadow.rd == id_ex.instr.rs1 && !(ex_mem.valid && ex_mem_writes && ex_mem.rd == id_ex.instr.rs1)) {
            op1 = wb_val;
            // cout << " [Forwarding] MEM->EX (rs1): " << op1 << endl;
        }
        if (wb_shadow.rd == id_ex.instr.rs2 && !(ex_mem.valid && ex_mem_writes && ex_mem.rd == id_ex.instr.rs2)) {
            op2 = wb_val;
            // cout << " [Forwarding] MEM->EX (rs2): " << op2 << endl;
        }
    }

    int result = 0;
    bool branch_taken = false;
    int branch_target = 0;

        // --------------------------------------------------------------------
        // THE INNOVATION: ZERO-SKIPPING LOGIC
        // ZMUL uses a "fast-path" design: zero-detection in 1 cycle saves
        // the 4-cycle multiply. This is modeled as cycle savings rather than
        // stalls, representing dedicated zero-detect hardware in the ALU.
        // --------------------------------------------------------------------
        if (id_ex.instr.op == ZMUL) {
            if (op1 == 0 || op2 == 0) {
                // FAST PATH: Zero detected, skip multiply entirely (1 cycle)
                result = 0;
                zero_skips++;
                stats.addZeroSkip(); // Track Zero Skip
                // cout << " [Hardware] Zero-Skip detected at PC " << id_ex.pc << "! Saving cycles." << endl;
            } else {
                // SLOW PATH: Normal multiply (single-cycle for simplicity,
                // but in real hardware would be 4 cycles in a pipelined multiplier)
                result = op1 * op2;
            }
        } 
        else if (id_ex.instr.op == ADD) {
            result = op1 + op2;
        }
        else if (id_ex.instr.op == ADDI) {
            result = op1 + id_ex.imm;
        }
        else if (id_ex.instr.op == SLT) {
            result = (op1 < op2) ? 1 : 0;
        }
        else if (id_ex.instr.op == SLTI) {
            result = (op1 < id_ex.imm) ? 1 : 0;
        }
        else if (id_ex.instr.op == SUB) {
            result = op1 - op2;
        }
        else if (id_ex.instr.op == MOV) {
            result = id_ex.imm;
            // cout << " [EX] MOV Result: " << result << " (imm=" << id_ex.imm << ")" << endl;
        }
        else if (id_ex.instr.op == LW || id_ex.instr.op == LNZ || id_ex.instr.op == SW || id_ex.instr.op == VLOAD) {
            result = op1 + id_ex.imm; // Address calc
        }
        else if (id_ex.instr.op == BEQ) {
            if (op1 == op2) {
                branch_taken = true;
                branch_target = id_ex.pc + id_ex.imm;
            }
        }
        else if (id_ex.instr.op == BNE) {
            if (op1 != op2) {
                branch_taken = true;
                branch_target = id_ex.pc + id_ex.imm;
            }
        }
        else if (id_ex.instr.op == BZERO) {
            if (op1 == 0) {
                branch_taken = true;
                branch_target = id_ex.pc + id_ex.imm;
            }
        }
        else if (id_ex.instr.op == JMP) {
            branch_taken = true;
            branch_target = id_ex.pc + id_ex.imm;
        }
        else if (id_ex.instr.op == JR) {
            branch_taken = true;
            branch_target = op1;
        }

        // Track Instruction Mix
        if (id_ex.instr.op == LW || id_ex.instr.op == SW || id_ex.instr.op == LNZ || id_ex.instr.op == VLOAD) {
            stats.addMemoryOp();
        } else if (id_ex.instr.op == BEQ || id_ex.instr.op == BZERO || id_ex.instr.op == JMP || id_ex.instr.op == JR) {
            stats.addBranchOp();
        } else if (id_ex.instr.op != HALT) {
            stats.addAluOp();
        }

        // Handle Branching (Control Hazard)
        bool misprediction = false;
        if (id_ex.instr.op == BEQ || id_ex.instr.op == BZERO || id_ex.instr.op == JMP || id_ex.instr.op == JR) {
            // Update Predictor
            branch_predictor.update(id_ex.pc, branch_taken);
            
            // Track prediction accuracy
            stats.addBranchPrediction(branch_taken == id_ex.predicted_taken);

            // Check for Misprediction
            if (branch_taken != id_ex.predicted_taken) {
                misprediction = true;
                stats.addBranchFlush();
                // cout << " [Branch] Misprediction! Correct: " << (branch_taken ? "Taken" : "Not Taken") << endl;
                
                // Flush Pipeline (IF/ID)
                if_id.valid = false; 

                // Correct PC
                if (branch_taken) {
                    pc = branch_target;
                } else {
                    pc = id_ex.pc + 1; // Fallthrough
                }
            }
        }

        // Update EX/MEM Pipeline Register
        ex_mem.instr = id_ex.instr;
        ex_mem.alu_result = result;
        ex_mem.write_data = op2; // For SW
        ex_mem.rd = id_ex.rd;
        ex_mem.valid = true;

        if (misprediction) {
            ex_mem.valid = false; // Branch doesn't produce a result for MEM/WB
        }
}

// ------------------------------------------------------------------------
// STAGE 4: MEMORY (MEM)
// ------------------------------------------------------------------------
void SparseFlowCore::stageMemory() {
    if (!ex_mem.valid) {
        mem_wb.valid = false;
        return;
    }

    // Check if we are already stalling for memory
    if (mem_stall_cycles > 0) {
        // Still waiting...
        return;
    }

    // If this is a new memory request, calculate latency
    if (ex_mem.instr.op == LW || ex_mem.instr.op == LNZ || ex_mem.instr.op == SW || ex_mem.instr.op == VLOAD) {
        int latency = memory.requestAccess(ex_mem.alu_result);
        
        // Debug Print for Memory Access
        // cout << " [Memory] Access Addr: " << ex_mem.alu_result << " Latency: " << latency << endl;

        if (latency > 1) {
            mem_stall_cycles = latency - 1;
            // cout << " [Memory] Cache Miss! Stalling for " << mem_stall_cycles << " cycles." << endl;
            stats.addStall(); // Count the first stall cycle here
            mem_wb.valid = false; // Insert Bubble into WB to prevent duplicate writeback
            return; // STALL!
        }
    }

    int mem_val = 0;
    vector<int> vec_val;

    // --------------------------------------------------------------------
    // LNZ (Load Non-Zero) Logic - Hardware Zero Skipping
    // --------------------------------------------------------------------
    if (ex_mem.instr.op == LNZ) {
        int current_addr = ex_mem.alu_result;
        int val = memory.readData(current_addr);
        
        if (val == 0) {
            // Found a zero! Skip it.
            // cout << " [LNZ] Skipping Zero at " << current_addr << "..." << endl;
            ex_mem.alu_result++; // Advance pointer
            mem_stall_cycles = 1; // Stall 1 cycle to simulate check
            stats.addStall();
            stats.addZeroSkip(); // Track this as a zero skip!
            mem_wb.valid = false; // Bubble
            return; // STALL!
        } else {
            // Found non-zero!
            mem_val = val;
            // cout << " [LNZ] Found Non-Zero " << val << " at " << current_addr << endl;
        }
    }
    else if (ex_mem.instr.op == LW) {
        mem_val = memory.readData(ex_mem.alu_result);
    } else if (ex_mem.instr.op == VLOAD) {
        // Vector Load: Read 4 consecutive words
        for(int i=0; i<4; i++) {
            vec_val.push_back(memory.readData(ex_mem.alu_result + i));
        }
        // cout << " [VLOAD] Loaded Vector from " << ex_mem.alu_result << ": [" 
        //      << vec_val[0] << ", " << vec_val[1] << ", " << vec_val[2] << ", " << vec_val[3] << "]" << endl;
    } else if (ex_mem.instr.op == SW) {
        memory.writeData(ex_mem.alu_result, ex_mem.write_data);
        // cout << " [SW] Wrote " << ex_mem.write_data << " to Mem[" << ex_mem.alu_result << "]" << endl;
    }

    // Update MEM/WB Pipeline Register
    mem_wb.instr = ex_mem.instr;
    mem_wb.mem_data = mem_val;
    mem_wb.vec_data = vec_val;
    mem_wb.alu_result = ex_mem.alu_result;
    mem_wb.rd = ex_mem.rd;
    mem_wb.valid = true;
}

// ------------------------------------------------------------------------
// STAGE 5: WRITEBACK (WB)
// ------------------------------------------------------------------------
void SparseFlowCore::stageWriteback() {
    wb_shadow = mem_wb; // Capture state for Forwarding Unit before it's overwritten

    if (!mem_wb.valid) return;

    // cout << " [WB] Op: " << mem_wb.instr.op << " ASM: " << mem_wb.instr.raw_asm << endl;

    if (mem_wb.instr.op == HALT) {
        halted = true;
        return;
    }

    int write_val = 0;
    bool write_enable = false;

    // Mux for Writeback Data
    if (mem_wb.instr.op == LW) {
        write_val = mem_wb.mem_data;
        write_enable = true;
    } else if (mem_wb.instr.op == VLOAD) {
        reg_file.writeVector(mem_wb.rd, mem_wb.vec_data);
        // cout << " [WB] Wrote Vector v" << mem_wb.rd << endl;
        write_enable = false; // Handled separately
    } else if (mem_wb.instr.op == LNZ) {
        write_val = mem_wb.mem_data;
        write_enable = true;
        
        // LNZ Auto-Increment Feature: Update the pointer register
        // We write the NEXT address (alu_result + 1) back to rs1
        int next_ptr = mem_wb.alu_result + 1;
        if (mem_wb.instr.rs1 != mem_wb.rd && mem_wb.instr.rs1 != 0) {
             reg_file.write(mem_wb.instr.rs1, next_ptr);
             // cout << " [WB] LNZ Auto-Increment: Updated x" << mem_wb.instr.rs1 << " to " << next_ptr << endl;
        }
    } else if (mem_wb.instr.op == ADD || mem_wb.instr.op == SUB || mem_wb.instr.op == ZMUL || mem_wb.instr.op == MOV || mem_wb.instr.op == ADDI || mem_wb.instr.op == SLT) {
        write_val = mem_wb.alu_result;
        write_enable = true;
    }

    if (write_enable) {
        reg_file.write(mem_wb.rd, write_val);
        // cout << " [WB] Writing Reg " << mem_wb.rd << " Val: " << write_val << endl;
    }

    // Instruction Retired!
    stats.addInstructionRetired();
}

// ------------------------------------------------------------------------
// MAIN LOOP
// ------------------------------------------------------------------------
void SparseFlowCore::run() {
    cout << "Starting SparseFlow Simulation..." << endl;
    
    while (!halted && cycle_count < 1000000) { // Safety limit 1M cycles for large sparse tests
        // cout << "--- Cycle " << cycle_count << " ---" << endl;
        stats.addCycle();

        // Log Pipeline State (Before execution of this cycle's logic)
        // Note: We log what is currently sitting in the pipeline registers waiting to be processed.
        // IF: Instruction at PC (approximate)
        // ID: if_id.instr
        // EX: id_ex.instr
        // MEM: ex_mem.instr
        // WB: mem_wb.instr
        
        string event = "";
        if (mem_stall_cycles > 0) event = "Stall (Memory)";
        else if (stall_pipeline) event = "Stall (Hazard)";
        
        Instruction fetch_instr = memory.fetch(pc); // Peek at what IF is about to fetch
        
        trace_logger.logCycle(cycle_count,
            fetch_instr.raw_asm,
            if_id.valid ? if_id.instr.raw_asm : "BUBBLE",
            id_ex.valid ? id_ex.instr.raw_asm : "BUBBLE",
            ex_mem.valid ? ex_mem.instr.raw_asm : "BUBBLE",
            mem_wb.valid ? mem_wb.instr.raw_asm : "BUBBLE",
            event
        );

        // Handle Memory Stall
        if (mem_stall_cycles > 0) {
            mem_stall_cycles--;
            stats.addStall();
            // Allow WB to finish if it has something? 
            // For strict in-order stall, we freeze everything.
            // But usually WB is independent. Let's freeze all to be safe/simple.
            cycle_count++;
            continue; 
        }

        // Reverse order to simulate parallel hardware updates correctly
        // (WB happens at end of cycle, but reads happen at start)
        stageWriteback();
        stageMemory();
        
        // If Memory stage initiated a stall, freeze the pipeline immediately
        // to prevent earlier stages (EX) from overwriting pipeline registers (ex_mem).
        if (mem_stall_cycles == 0) {
            stageExecute();
            stageDecode();
            stageFetch();
        }

        cycle_count++;
    }

    cout << "\nSimulation Finished." << endl;
    stats.setCacheStats(memory.getCacheHits(), memory.getCacheMisses());
    stats.printReport();
    reg_file.dump();
}
