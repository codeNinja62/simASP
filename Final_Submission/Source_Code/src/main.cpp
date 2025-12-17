#include <iostream>
#include <vector>
#include "core/SparseFlowCore.h"
#include "isa/Instruction.h"
#include "utils/Loader.h"

using namespace std;

void printUsage(const char* progName) {
    cout << "Usage: " << progName << " [options] <assembly_file.asm>\n";
    cout << "Options:\n";
    cout << "  --single-cycle    Run in single-cycle (non-pipelined) mode\n";
    cout << "  --show-pipeline   Display ASCII pipeline diagram after execution\n";
    cout << "  --interactive     Interactive step-by-step mode (for demos)\n";
    cout << "  --help            Show this help message\n";
}

int main(int argc, char* argv[]) {
    SparseFlowCore core;
    Loader loader;

    // Initialize Memory for Load Test
    core.writeDataMemory(10, 99); // Mem[10] = 99

    string filename = "test_program.asm";
    bool single_cycle = false;
    bool show_pipeline = false;
    bool interactive = false;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--single-cycle") {
            single_cycle = true;
        } else if (arg == "--show-pipeline") {
            show_pipeline = true;
        } else if (arg == "--interactive" || arg == "-i") {
            interactive = true;
        } else if (arg == "--help" || arg == "-h") {
            printUsage(argv[0]);
            return 0;
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
    
    if (show_pipeline) {
        core.setShowPipeline(true);
    }

    cout << "Loading program from: " << filename << endl;
    vector<Instruction> program = loader.loadFromFile(filename);

    if (program.empty()) {
        cout << "Error: Program is empty or file not found." << endl;
        return 1;
    }

    core.loadProgram(program);
    
    if (interactive) {
        core.runInteractive();
    } else {
        core.run();
    }

    return 0;
}
