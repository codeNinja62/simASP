#ifndef PIPELINE_REGISTERS_H
#define PIPELINE_REGISTERS_H

#include "../isa/Instruction.h"

// IF/ID Pipeline Register
struct IF_ID_Reg {
    Instruction instr;
    int pc;
    bool valid;
    
    IF_ID_Reg() : pc(0), valid(false) {}
};

#endif // PIPELINE_REGISTERS_H
