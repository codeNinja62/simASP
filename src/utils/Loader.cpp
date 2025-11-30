#include "Loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

string Loader::trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

int Loader::parseRegister(string reg_str) {
    reg_str = trim(reg_str);
    if (reg_str.empty()) return 0;
    if (reg_str.back() == ',') reg_str.pop_back();

    if (reg_str[0] == 'x') return stoi(reg_str.substr(1));

    // ABI names
    if (reg_str == "zero") return 0;
    if (reg_str == "ra") return 1;
    if (reg_str == "sp") return 2;
    if (reg_str == "t0") return 5;
    if (reg_str == "t1") return 6;
    if (reg_str == "t2") return 7;
    if (reg_str == "s0") return 8;
    if (reg_str == "s1") return 9;
    if (reg_str == "a0") return 10;
    if (reg_str == "a1") return 11;
    if (reg_str == "t3") return 28;
    if (reg_str == "t4") return 29;
    if (reg_str == "t5") return 30;
    if (reg_str == "t6") return 31;
    
    return 0;
}

Opcode Loader::parseOpcode(string op_str) {
    transform(op_str.begin(), op_str.end(), op_str.begin(), ::toupper);
    if (op_str == "ADD") return ADD;
    if (op_str == "SUB") return SUB;
    if (op_str == "LW") return LW;
    if (op_str == "SW") return SW;
    if (op_str == "BEQ") return BEQ;
    if (op_str == "JMP") return JMP;
    if (op_str == "LNZ") return LNZ;
    if (op_str == "ZMUL") return ZMUL;
    if (op_str == "VLOAD") return VLOAD;
    if (op_str == "MOV") return MOV;
    if (op_str == "HALT") return HALT;
    return HALT;
}

vector<Instruction> Loader::loadFromFile(const string& filename) {
    vector<Instruction> program;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return program;
    }

    // Pass 1: Read lines, strip comments, identify labels
    int current_pc = 0;
    while (getline(file, line)) {
        size_t comment_pos = line.find('#');
        if (comment_pos != string::npos) line = line.substr(0, comment_pos);

        line = trim(line);
        if (line.empty()) continue;

        if (line.back() == ':') {
            string label = line.substr(0, line.size() - 1);
            label_map[label] = current_pc;
            continue;
        }

        current_pc++;
    }

    // Pass 2: Parse instructions
    file.clear();
    file.seekg(0);
    
    while (getline(file, line)) {
        // Parse instruction...
        Instruction instr;
        program.push_back(instr);
    }

    return program;
}
