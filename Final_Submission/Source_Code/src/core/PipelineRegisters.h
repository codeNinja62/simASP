#ifndef PIPELINE_REGISTERS_H
#define PIPELINE_REGISTERS_H

#include <vector>
#include "../isa/Instruction.h"

struct IF_ID_Reg {
    Instruction instr;
    int pc;
    bool predicted_taken;
    bool valid;
    
    IF_ID_Reg() : pc(0), predicted_taken(false), valid(false) {}
};

struct ID_EX_Reg {
    Instruction instr;
    int pc;
    int rs1_val;
    int rs2_val;
    int imm;
    int rd;
    bool predicted_taken;
    bool valid;
    
    ID_EX_Reg() : pc(0), rs1_val(0), rs2_val(0), imm(0), rd(0),
                  predicted_taken(false), valid(false) {}
};

struct EX_MEM_Reg {
    Instruction instr;
    int alu_result;
    int write_data;
    int rd;
    bool valid;
    
    EX_MEM_Reg() : alu_result(0), write_data(0), rd(0), valid(false) {}
};

struct MEM_WB_Reg {
    Instruction instr;
    int mem_data;
    std::vector<int> vec_data;
    int alu_result;
    int rd;
    bool valid;
    
    MEM_WB_Reg() : mem_data(0), alu_result(0), rd(0), valid(false) {}
};

#endif // PIPELINE_REGISTERS_H
