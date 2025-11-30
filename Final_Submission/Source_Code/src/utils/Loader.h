#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <string>
#include <map>
#include "../isa/Instruction.h"

class Loader {
private:
    std::map<std::string, int> label_map;
    
    int parseRegister(std::string reg_str);
    Opcode parseOpcode(std::string op_str);
    void parseOperands(Instruction& instr, const std::string& op_part, int current_pc);
    std::string trim(const std::string& str);

public:
    std::vector<Instruction> loadFromFile(const std::string& filename);
};

#endif // LOADER_H
