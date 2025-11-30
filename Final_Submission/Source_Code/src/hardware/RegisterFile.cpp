#include "RegisterFile.h"

using namespace std;

RegisterFile::RegisterFile() {
    for(int i=0; i<32; i++) regs[i] = 0;
    for(int i=0; i<8; i++) {
        for(int j=0; j<4; j++) vregs[i][j] = 0;
    }
}

int RegisterFile::read(int reg_num) {
    if (reg_num < 0 || reg_num > 31) return 0;
    return regs[reg_num];
}

void RegisterFile::write(int reg_num, int value) {
    if (reg_num == 0) return; // R0 is always 0
    if (reg_num > 0 && reg_num < 32) regs[reg_num] = value;
}

std::vector<int> RegisterFile::readVector(int reg_num) {
    std::vector<int> vec(4, 0);
    if (reg_num >= 0 && reg_num < 8) {
        for(int i=0; i<4; i++) vec[i] = vregs[reg_num][i];
    }
    return vec;
}

void RegisterFile::writeVector(int reg_num, const std::vector<int>& values) {
    if (reg_num >= 0 && reg_num < 8 && values.size() == 4) {
        for(int i=0; i<4; i++) vregs[reg_num][i] = values[i];
    }
}

void RegisterFile::dump() {
    cout << "\n[Register File State]:" << endl;
    for (int i = 0; i < 32; i++) { // Print all 32
        string name = "x" + to_string(i);
        if (REG_ABI.count(i)) name += "(" + REG_ABI.at(i) + ")";
        cout << left << setw(10) << name << ": " << regs[i] << endl;
    }
    
    cout << "\n[Vector Register File State]:" << endl;
    for (int i = 0; i < 8; i++) {
        cout << "v" << i << ": [" 
             << vregs[i][0] << ", " << vregs[i][1] << ", " 
             << vregs[i][2] << ", " << vregs[i][3] << "]" << endl;
    }
}
