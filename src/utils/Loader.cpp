#include "Loader.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

vector<Instruction> Loader::loadFromFile(const string& filename) {
    vector<Instruction> program;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return program;
    }

    // Pass 1: Strip comments and detect labels
    int current_pc = 0;
    while (getline(file, line)) {
        // Remove comments
        size_t comment_pos = line.find('#');
        if (comment_pos != string::npos) {
            line = line.substr(0, comment_pos);
        }
        
        // TODO: Trim whitespace
        if (line.empty()) continue;

        // Check for labels
        if (line.back() == ':') {
            string label = line.substr(0, line.size() - 1);
            label_map[label] = current_pc;
            continue;
        }
        current_pc++;
    }

    // Pass 2 will be implemented next
    return program;
}
