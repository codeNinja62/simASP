#include <iostream>
#include <vector>
#include "core/SparseFlowCore.h"
#include "isa/Instruction.h"
#include "utils/Loader.h"

using namespace std;

int main(int argc, char* argv[]) {
    SparseFlowCore core;
    Loader loader;

    // Initialize Memory for Load Test
    core.writeDataMemory(10, 99); // Mem[10] = 99

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

    if (single_cycle) {
        cout << "Mode: Single-Cycle (Serialized Pipeline)" << endl;
        core.setSingleCycleMode(true);
    } else {
        cout << "Mode: Pipelined" << endl;
    }

    cout << "Loading program from: " << filename << endl;
    vector<Instruction> program = loader.loadFromFile(filename);

    if (program.empty()) {
        cout << "Error: Program is empty or file not found." << endl;
        return 1;
    }

    core.loadProgram(program);
    core.run();

    return 0;
}
