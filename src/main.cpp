#include <iostream>
#include <vector>
#include "core/SparseFlowCore.h"
#include "utils/Loader.h"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "SparseFlow Simulator" << endl;
    
    if (argc < 2) {
        cout << "Usage: simulator <program.asm>" << endl;
        return 1;
    }
    
    SparseFlowCore core;
    Loader loader;
    
    string filename = argv[1];
    cout << "Loading: " << filename << endl;
    
    return 0;
}
