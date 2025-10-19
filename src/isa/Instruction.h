#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

enum Opcode {
    ADD, SUB, LW, SW, JMP, BEQ,
    LNZ, ZMUL, VLOAD, BZERO
};

struct Instruction {
    Opcode op;
    int rd;     // Destination register
    int rs1;    // Source register 1
    int rs2;    // Source register 2
    int imm;    // Immediate value
    std::string raw_asm;

    Instruction() : op(JMP), rd(0), rs1(0), rs2(0), imm(0), raw_asm("") {}
};

#endif // INSTRUCTION_H
