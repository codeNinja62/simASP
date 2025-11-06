#ifndef PIPELINE_REGISTERS_H
#define PIPELINE_REGISTERS_H

#include "../isa/Instruction.h"

// IF/ID Pipeline Register
struct IF_ID_Reg {
    Instruction instr;
    int pc;
    bool predicted_taken;
    bool valid;
    
    IF_ID_Reg() : pc(0), predicted_taken(false), valid(false) {}
};

// ID/EX Pipeline Register
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

#endif // PIPELINE_REGISTERS_H
