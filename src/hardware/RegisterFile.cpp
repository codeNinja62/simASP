#include "RegisterFile.h"

RegisterFile::RegisterFile() {
    for (int i = 0; i < 32; i++) regs[i] = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 4; j++)
            vregs[i][j] = 0;
}

int RegisterFile::read(int reg_num) {
    if (reg_num == 0) return 0; // x0 hardwired to 0
    return regs[reg_num];
}

void RegisterFile::write(int reg_num, int value) {
    if (reg_num == 0) return; // x0 is read-only
    regs[reg_num] = value;
}

std::vector<int> RegisterFile::readVector(int reg_num) {
    std::vector<int> result(4);
    for (int i = 0; i < 4; i++) {
        result[i] = vregs[reg_num][i];
    }
    return result;
}

void RegisterFile::writeVector(int reg_num, const std::vector<int>& values) {
    for (int i = 0; i < 4 && i < values.size(); i++) {
        vregs[reg_num][i] = values[i];
    }
}

void RegisterFile::dump() {
    std::cout << "\n=== Register Dump ===" << std::endl;
    for (int i = 0; i < 32; i++) {
        if (regs[i] != 0) {
            std::cout << "x" << i << " : " << regs[i] << std::endl;
        }
    }
}
