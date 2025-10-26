#include "Loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

int parseRegister(string reg_str) {
    reg_str = trim(reg_str);
    if (reg_str.empty()) return 0;
    if (reg_str.back() == ',') reg_str.pop_back();
    if (reg_str[0] == 'x') return stoi(reg_str.substr(1));
    return 0;
}

vector<Instruction> Loader::loadFromFile(const string& filename) {
    vector<Instruction> program;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return program;
    }

    // Pass 1: Labels
    int current_pc = 0;
    while (getline(file, line)) {
        size_t comment_pos = line.find('#');
        if (comment_pos != string::npos) line = line.substr(0, comment_pos);
        line = trim(line);
        if (line.empty()) continue;
        if (line.back() == ':') {
            label_map[line.substr(0, line.size()-1)] = current_pc;
            continue;
        }
        current_pc++;
    }

    // Pass 2: Parse instructions
    file.clear();
    file.seekg(0);
    current_pc = 0;
    
    while (getline(file, line)) {
        size_t comment_pos = line.find('#');
        if (comment_pos != string::npos) line = line.substr(0, comment_pos);
        line = trim(line);
        if (line.empty() || line.back() == ':') continue;

        Instruction instr;
        instr.raw_asm = line;
        
        istringstream iss(line);
        string opcode;
        iss >> opcode;
        transform(opcode.begin(), opcode.end(), opcode.begin(), ::toupper);
        
        // R-Type: ADD rd, rs1, rs2
        if (opcode == "ADD" || opcode == "SUB") {
            string rd, rs1, rs2;
            iss >> rd >> rs1 >> rs2;
            instr.op = (opcode == "ADD") ? ADD : SUB;
            instr.rd = parseRegister(rd);
            instr.rs1 = parseRegister(rs1);
            instr.rs2 = parseRegister(rs2);
        }
        // I-Type will be added
        
        program.push_back(instr);
        current_pc++;
    }

    return program;
}
