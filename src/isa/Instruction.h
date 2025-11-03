#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

enum Opcode {
    ADD, SUB, LW, SW, JMP, BEQ, SLT, ADDI, JR,  // Base RISC-V
    LNZ, ZMUL, VLOAD, BZERO, MOV, HALT          // Custom Sparse
};

struct Instruction {
    Opcode op;
    int rd;
    int rs1;
    int rs2;
    int imm;
    std::string raw_asm;

    Instruction() : op(HALT), rd(0), rs1(0), rs2(0), imm(0), raw_asm("NOP") {}
};

#endif // INSTRUCTION_H
