#include "TraceLogger.h"

TraceLogger::TraceLogger(const std::string& filename) : enabled(true) {
    file.open(filename);
    if (file.is_open()) {
        file << "Cycle,IF,ID,EX,MEM,WB,Event" << std::endl;
    }
}

TraceLogger::~TraceLogger() {
    if (file.is_open()) {
        file.close();
    }
}

void TraceLogger::logCycle(int cycle, 
                           const std::string& fetch_instr,
                           const std::string& decode_instr,
                           const std::string& execute_instr,
                           const std::string& memory_instr,
                           const std::string& writeback_instr,
                           const std::string& event) {
    if (file.is_open() && enabled) {
        file << cycle << ","
             << fetch_instr << ","
             << decode_instr << ","
             << execute_instr << ","
             << memory_instr << ","
             << writeback_instr << ","
             << event << std::endl;
    }
}
