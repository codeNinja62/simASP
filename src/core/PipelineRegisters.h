#ifndef PIPELINE_REGISTERS_H
#define PIPELINE_REGISTERS_H

#include <vector>
#include "../isa/Instruction.h"

struct IF_ID_Reg {
    Instruction instr;
    int pc;
    bool predicted_taken; // Added for Branch Prediction
    bool valid;
};

struct ID_EX_Reg {
    Instruction instr;
    int pc;
    int rs1_val;
    int rs2_val;
    int imm;
    int rd;
    bool predicted_taken; // Propagate prediction
    bool valid;
};

struct EX_MEM_Reg {
    Instruction instr;
    int alu_result;
    int write_data; // For Store instructions
    int rd;
    bool valid;
};

struct MEM_WB_Reg {
    Instruction instr;
    int mem_data;
    std::vector<int> vec_data; // For Vector Loads
    int alu_result;
    int rd;
    bool valid;
};

#endif // PIPELINE_REGISTERS_H
