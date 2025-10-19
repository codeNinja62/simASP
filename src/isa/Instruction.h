#ifndef INSTRUCTION_H
#define INSTRUCTION_H

// Basic Opcodes
enum Opcode {
    ADD,
    SUB,
    LW,
    SW,
    JMP,
    BEQ,
    // Custom Sparse Extensions
    LNZ,    // Load Non-Zero
    ZMUL,   // Zero-Skip Multiply
    VLOAD,  // Vector Load
    BZERO   // Branch if Zero
};

#endif // INSTRUCTION_H
