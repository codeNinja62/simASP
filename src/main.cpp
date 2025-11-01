#include <iostream>
#include <vector>
#include "core/SparseFlowCore.h"
#include "utils/Loader.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Argument parsing
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
    
    // Initialize components
    SparseFlowCore core;
    Loader loader;
    
    cout << "SparseFlow Simulator" << endl;
    cout << "Loading: " << filename << endl;
    
    return 0;
}
