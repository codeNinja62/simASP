#include "TraceLogger.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

TraceLogger::TraceLogger(const string& filename) : ascii_enabled(false) {
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

string TraceLogger::truncate(const string& s, size_t maxLen) const {
    if (s.length() <= maxLen) return s;
    return s.substr(0, maxLen - 2) + "..";
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
    
    // Store for ASCII diagram
    CycleRecord rec;
    rec.cycle = cycle;
    rec.if_instr = fetch_instr;
    rec.id_instr = decode_instr;
    rec.ex_instr = execute_instr;
    rec.mem_instr = memory_instr;
    rec.wb_instr = writeback_instr;
    rec.event = event;
    history.push_back(rec);
}

void TraceLogger::printAsciiDiagram(int lastN) const {
    if (history.empty()) {
        cout << "No cycles recorded." << endl;
        return;
    }
    
    const int COL_WIDTH = 14;
    
    // Header - Using ASCII only for maximum compatibility
    cout << "\n";
    cout << "+=======================================================================================+\n";
    cout << "|                           PIPELINE EXECUTION DIAGRAM                                  |\n";
    cout << "+-------+--------------+--------------+--------------+--------------+--------------+----+\n";
    cout << "| Cycle |      IF      |      ID      |      EX      |     MEM      |      WB      |Evt |\n";
    cout << "+-------+--------------+--------------+--------------+--------------+--------------+----+\n";
    
    // Determine range to print
    size_t start = 0;
    if (lastN > 0 && history.size() > (size_t)lastN) {
        start = history.size() - lastN;
    }
    
    for (size_t i = start; i < history.size(); ++i) {
        const CycleRecord& r = history[i];
        
        // Truncate instruction names to fit columns
        string if_str = truncate(r.if_instr, COL_WIDTH - 2);
        string id_str = truncate(r.id_instr, COL_WIDTH - 2);
        string ex_str = truncate(r.ex_instr, COL_WIDTH - 2);
        string mem_str = truncate(r.mem_instr, COL_WIDTH - 2);
        string wb_str = truncate(r.wb_instr, COL_WIDTH - 2);
        
        // Event indicator
        string evt = "";
        if (r.event.find("Stall") != string::npos) evt = " S ";
        else if (r.event.find("Flush") != string::npos) evt = " F ";
        else evt = "   ";
        
        // Color coding would be nice but not portable, so use markers
        // [STALL] or [BUBBLE] indicators
        if (id_str == "BUBBLE") id_str = "   ----   ";
        if (ex_str == "BUBBLE") ex_str = "   ----   ";
        if (mem_str == "BUBBLE") mem_str = "   ----   ";
        if (wb_str == "BUBBLE") wb_str = "   ----   ";
        
        cout << "| " << setw(5) << r.cycle << " | "
             << setw(COL_WIDTH - 2) << left << if_str << " | "
             << setw(COL_WIDTH - 2) << left << id_str << " | "
             << setw(COL_WIDTH - 2) << left << ex_str << " | "
             << setw(COL_WIDTH - 2) << left << mem_str << " | "
             << setw(COL_WIDTH - 2) << left << wb_str << " |"
             << evt << "|\n";
    }
    
    cout << "+-------+--------------+--------------+--------------+--------------+--------------+----+\n";
    cout << "Legend: S = Stall, F = Flush, ---- = Bubble (no instruction)\n";
    cout << "Total Cycles Recorded: " << history.size() << "\n\n";
}

void TraceLogger::printAsciiDiagramToFile(const string& filename) const {
    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Could not open file: " << filename << endl;
        return;
    }
    
    const int COL_WIDTH = 14;
    
    out << "\n";
    out << "+-------+--------------+--------------+--------------+--------------+--------------+-----+\n";
    out << "| Cycle |      IF      |      ID      |      EX      |     MEM      |      WB      | Evt |\n";
    out << "+-------+--------------+--------------+--------------+--------------+--------------+-----+\n";
    
    for (const auto& r : history) {
        string if_str = truncate(r.if_instr, COL_WIDTH - 2);
        string id_str = truncate(r.id_instr, COL_WIDTH - 2);
        string ex_str = truncate(r.ex_instr, COL_WIDTH - 2);
        string mem_str = truncate(r.mem_instr, COL_WIDTH - 2);
        string wb_str = truncate(r.wb_instr, COL_WIDTH - 2);
        
        string evt = "";
        if (r.event.find("Stall") != string::npos) evt = " S ";
        else if (r.event.find("Flush") != string::npos) evt = " F ";
        else evt = "   ";
        
        if (id_str == "BUBBLE") id_str = "  ----  ";
        if (ex_str == "BUBBLE") ex_str = "  ----  ";
        if (mem_str == "BUBBLE") mem_str = "  ----  ";
        if (wb_str == "BUBBLE") wb_str = "  ----  ";
        
        out << "| " << setw(5) << r.cycle << " | "
            << setw(COL_WIDTH - 2) << left << if_str << " | "
            << setw(COL_WIDTH - 2) << left << id_str << " | "
            << setw(COL_WIDTH - 2) << left << ex_str << " | "
            << setw(COL_WIDTH - 2) << left << mem_str << " | "
            << setw(COL_WIDTH - 2) << left << wb_str << " |"
            << evt << "|\n";
    }
    
    out << "+-------+--------------+--------------+--------------+--------------+--------------+-----+\n";
    out << "Legend: S = Stall, F = Flush, ---- = Bubble\n";
    out << "Total Cycles: " << history.size() << "\n";
    
    out.close();
    cout << "Pipeline diagram saved to: " << filename << endl;
}
