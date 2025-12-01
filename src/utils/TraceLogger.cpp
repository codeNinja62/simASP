#include "TraceLogger.h"
#include <iostream>

using namespace std;

TraceLogger::TraceLogger(const string& filename) {
    file.open(filename);
    if (file.is_open()) {
        enabled = true;
        // CSV Header
        file << "Cycle,IF,ID,EX,MEM,WB,Event\n";
    } else {
        enabled = false;
        cerr << "Warning: Could not open trace file " << filename << endl;
    }
}

TraceLogger::~TraceLogger() {
    if (file.is_open()) file.close();
}

void TraceLogger::logCycle(int cycle, 
              const string& fetch_instr, 
              const string& decode_instr, 
              const string& execute_instr, 
              const string& memory_instr, 
              const string& writeback_instr,
              const string& event) {
    if (!enabled) return;
    
    // Helper to wrap in quotes to handle commas in assembly
    file << cycle << ","
         << "\"" << fetch_instr << "\","
         << "\"" << decode_instr << "\","
         << "\"" << execute_instr << "\","
         << "\"" << memory_instr << "\","
         << "\"" << writeback_instr << "\","
         << "\"" << event << "\"\n";
}
