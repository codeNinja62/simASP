#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include <vector>

class RegisterFile {
private:
    int regs[32];           // 32 scalar registers
    int vregs[8][4];        // 8 vector registers, 4 elements each

public:
    RegisterFile();
};

#endif // REGISTER_FILE_H
