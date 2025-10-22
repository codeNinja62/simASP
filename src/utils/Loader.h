#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <string>
#include <map>
#include "../isa/Instruction.h"

class Loader {
private:
    std::map<std::string, int> label_map;

public:
    std::vector<Instruction> loadFromFile(const std::string& filename);
};

#endif // LOADER_H
