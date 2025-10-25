#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    cout << "SparseFlow Simulator" << endl;
    
    if (argc < 2) {
        cout << "Usage: simulator <program.asm>" << endl;
        return 1;
    }
    
    return 0;
}
