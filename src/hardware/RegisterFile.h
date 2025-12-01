#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include "../isa/ISA.h"

class RegisterFile {
private:
    int regs[32];
    int vregs[8][4]; // 8 Vector Registers, 4 elements each
public:
    RegisterFile();
    int read(int reg_num) const;
    void write(int reg_num, int value);
    
    // Vector Access
    std::vector<int> readVector(int reg_num) const;
    void writeVector(int reg_num, const std::vector<int>& values);

    void dump() const;
};

#endif // REGISTER_FILE_H
