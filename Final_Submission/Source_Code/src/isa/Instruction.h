#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

enum Opcode {
    ADD, SUB, JMP, LW, SW, BEQ, SLT, ADDI, JR, // Base RISC-V Subset
    LNZ, ZMUL, ZMAC, VLOAD, BZERO, MOV, HALT // Custom Sparse Extensions
};

struct Instruction {
    Opcode op;
    int rd;     // Destination Register
    int rs1;    // Source Register 1
    int rs2;    // Source Register 2
    int imm;    // Immediate value
    std::string raw_asm; // For debug printing

    Instruction() : op(HALT), rd(0), rs1(0), rs2(0), imm(0), raw_asm("NOP") {}
};

#endif // INSTRUCTION_H
