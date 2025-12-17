#include "Loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <regex>

using namespace std;

// Helper to trim whitespace
string Loader::trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

int Loader::parseRegister(string reg_str) {
    reg_str = trim(reg_str);
    if (reg_str.empty()) return 0;
    
    // Remove comma if present
    if (reg_str.back() == ',') reg_str.pop_back();

    // Handle x0-x31
    if (reg_str[0] == 'x') {
        return stoi(reg_str.substr(1));
    }

    // Handle ABI names
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
    if (reg_str == "a2") return 12;
    if (reg_str == "a3") return 13;
    if (reg_str == "a4") return 14;
    if (reg_str == "a5") return 15;
    if (reg_str == "a6") return 16;
    if (reg_str == "a7") return 17;
    if (reg_str == "t3") return 28;
    if (reg_str == "t4") return 29;
    if (reg_str == "t5") return 30;
    if (reg_str == "t6") return 31;
    
    // Vector Registers
    if (reg_str[0] == 'v') {
        try {
            int v_idx = stoi(reg_str.substr(1));
            if (v_idx >= 0 && v_idx < 8) return v_idx; // Return 0-7 for v0-v7
        } catch (...) { return 0; }
    }
    
    return 0; // Default to 0 if unknown
}

Opcode Loader::parseOpcode(string op_str) {
    transform(op_str.begin(), op_str.end(), op_str.begin(), ::toupper);
    if (op_str == "ADD") return ADD;
    if (op_str == "SUB") return SUB;
    if (op_str == "JMP") return JMP;
    if (op_str == "LW") return LW;
    if (op_str == "SW") return SW;
    if (op_str == "BEQ") return BEQ;
    if (op_str == "BNE") return BNE;
    if (op_str == "SLT") return SLT;
    if (op_str == "SLTI") return SLTI;
    if (op_str == "ADDI") return ADDI;
    if (op_str == "JR") return JR;
    if (op_str == "LNZ") return LNZ;
    if (op_str == "ZMUL") return ZMUL;
    if (op_str == "ZMAC") return ZMAC;
    if (op_str == "VLOAD") return VLOAD;
    if (op_str == "BZERO") return BZERO;
    if (op_str == "MOV") return MOV;
    if (op_str == "HALT") return HALT;
    return HALT;
}

vector<Instruction> Loader::loadFromFile(const string& filename) {
    vector<Instruction> program;
    ifstream file(filename);
    string line;
    vector<string> raw_lines;
    vector<int> pc_map; // Map line index to PC

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return program;
    }

    // PASS 1: Read lines, strip comments, identify labels
    int current_pc = 0;
    while (getline(file, line)) {
        // Strip comments
        size_t comment_pos = line.find('#');
        if (comment_pos == string::npos) comment_pos = line.find("//");
        if (comment_pos == string::npos) comment_pos = line.find(";");
        if (comment_pos != string::npos) line = line.substr(0, comment_pos);

        line = trim(line);
        if (line.empty()) continue;

        // Check for Label
        if (line.back() == ':') {
            string label = line.substr(0, line.size() - 1);
            label_map[label] = current_pc;
            // cout << " [Loader] Label: " << label << " -> PC: " << current_pc << endl;
            continue; // Labels don't take up instruction space
        }

        raw_lines.push_back(line);
        pc_map.push_back(current_pc);
        // cout << " [Loader] PC: " << current_pc << " Line: " << line << endl;
        current_pc++;
    }

    // PASS 2: Parse Instructions
    for (int i = 0; i < raw_lines.size(); i++) {
        string raw = raw_lines[i];
        stringstream ss(raw);
        string opcode_str, operands_str;
        
        ss >> opcode_str;
        getline(ss, operands_str); // Get the rest of the line

        Instruction instr;
        instr.op = parseOpcode(opcode_str);
        instr.raw_asm = raw;

        // Parse Operands based on Opcode Type
        // Simple tokenizer for operands (split by comma)
        vector<string> tokens;
        stringstream os(operands_str);
        string token;
        while (getline(os, token, ',')) {
            tokens.push_back(trim(token));
        }

        // R-Type: OP rd, rs1, rs2 (ADD, SUB, ZMUL, ZMAC, SLT)
        if (instr.op == ADD || instr.op == SUB || instr.op == ZMUL || instr.op == ZMAC || instr.op == SLT) {
            if (tokens.size() >= 3) {
                instr.rd = parseRegister(tokens[0]);
                instr.rs1 = parseRegister(tokens[1]);
                instr.rs2 = parseRegister(tokens[2]);
            }
        }
        // I-Type: OP rd, rs1, imm (ADDI, SLTI)
        else if (instr.op == ADDI || instr.op == SLTI) {
             if (tokens.size() >= 3) {
                instr.rd = parseRegister(tokens[0]);
                instr.rs1 = parseRegister(tokens[1]);
                instr.imm = stoi(tokens[2]);
            }
        }
        // I-Type: OP rd, imm (MOV)
        else if (instr.op == MOV) {
            if (tokens.size() >= 2) {
                instr.rd = parseRegister(tokens[0]);
                string val_str = tokens[1];
                
                bool is_number = true;
                try { 
                    size_t idx; 
                    stoi(val_str, &idx); 
                    // Check if the whole string was parsed (to avoid "5a" being parsed as 5)
                    if(idx != val_str.size()) is_number = false; 
                } catch(...) { is_number = false; }

                if (is_number) {
                    instr.imm = stoi(val_str);
                } else if (label_map.count(val_str)) {
                    instr.imm = label_map[val_str]; // Absolute Address
                } else {
                    // Assume it's a register copy: MOV rd, rs -> ADDI rd, rs, 0
                    instr.op = ADDI;
                    instr.rs1 = parseRegister(val_str);
                    instr.imm = 0;
                }
            }
        }
        // Memory: OP rd, offset(rs1) (LW, LNZ, VLOAD)
        else if (instr.op == LW || instr.op == LNZ || instr.op == VLOAD) {
            if (tokens.size() >= 2) {
                instr.rd = parseRegister(tokens[0]);
                // Parse offset(base)
                string mem_op = tokens[1];
                size_t open_paren = mem_op.find('(');
                size_t close_paren = mem_op.find(')');
                if (open_paren != string::npos && close_paren != string::npos) {
                    instr.imm = stoi(mem_op.substr(0, open_paren));
                    instr.rs1 = parseRegister(mem_op.substr(open_paren + 1, close_paren - open_paren - 1));
                }
            }
        }
        // Store: OP rs2, offset(rs1) (SW)
        else if (instr.op == SW) {
            if (tokens.size() >= 2) {
                instr.rs2 = parseRegister(tokens[0]); // Source for store is rs2
                // Parse offset(base)
                string mem_op = tokens[1];
                size_t open_paren = mem_op.find('(');
                size_t close_paren = mem_op.find(')');
                if (open_paren != string::npos && close_paren != string::npos) {
                    instr.imm = stoi(mem_op.substr(0, open_paren));
                    instr.rs1 = parseRegister(mem_op.substr(open_paren + 1, close_paren - open_paren - 1));
                }
            }
        }
        // Branch: OP rs1, rs2, label (BEQ, BNE)
        else if (instr.op == BEQ || instr.op == BNE) {
            if (tokens.size() >= 3) {
                instr.rs1 = parseRegister(tokens[0]);
                instr.rs2 = parseRegister(tokens[1]);
                string label = tokens[2];
                if (label_map.count(label)) {
                    instr.imm = label_map[label] - pc_map[i]; // Relative Offset
                    // cout << " [Loader] Branch at PC " << pc_map[i] << " to Label " << label << " (PC " << label_map[label] << ") -> Offset " << instr.imm << endl;
                } else {
                    try { instr.imm = stoi(label); } catch(...) { instr.imm = 0; }
                }
            }
        }
        // Branch Zero: OP rs1, label (BZERO)
        else if (instr.op == BZERO) {
            if (tokens.size() >= 2) {
                instr.rs1 = parseRegister(tokens[0]);
                string label = tokens[1];
                if (label_map.count(label)) {
                    instr.imm = label_map[label] - pc_map[i]; // Relative Offset
                } else {
                    try { instr.imm = stoi(label); } catch(...) { instr.imm = 0; }
                }
            }
        }
        // Unconditional Jump: OP label (JMP)
        else if (instr.op == JMP) {
            if (tokens.size() >= 1) {
                string label = tokens[0];
                if (label_map.count(label)) {
                    instr.imm = label_map[label] - pc_map[i]; // Relative Offset
                } else {
                    try { instr.imm = stoi(label); } catch(...) { instr.imm = 0; }
                }
            }
        }
        // Jump Register: OP rs1 (JR)
        else if (instr.op == JR) {
            if (tokens.size() >= 1) {
                instr.rs1 = parseRegister(tokens[0]);
            }
        }

        program.push_back(instr);
    }

    return program;
}
