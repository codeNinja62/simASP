#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include <vector>
#include <iostream>

class RegisterFile {
private:
    int regs[32];
    int vregs[8][4];

public:
    RegisterFile();
    
    // Scalar access
    int read(int reg_num);
    void write(int reg_num, int value);
    
    // Vector access
    std::vector<int> readVector(int reg_num);
    void writeVector(int reg_num, const std::vector<int>& values);
    
    void dump();
};

#endif // REGISTER_FILE_H
