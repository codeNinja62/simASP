#include <iostream>
#include <vector>
#include "core/SparseFlowCore.h"
#include "utils/Loader.h"

using namespace std;

int main(int argc, char* argv[]) {
    string filename = "test_program.asm";
    bool single_cycle = false;
    
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--single-cycle") {
            single_cycle = true;
        } else {
            filename = arg;
        }
    }
    
    SparseFlowCore core;
    Loader loader;
    
    cout << "SparseFlow Simulator" << endl;
    cout << "Loading: " << filename << endl;
    
    vector<Instruction> program = loader.loadFromFile(filename);
    
    if (program.empty()) {
        cout << "Error: Program is empty or file not found." << endl;
        return 1;
    }
    
    core.loadProgram(program);
    core.run();
    
    return 0;
}
