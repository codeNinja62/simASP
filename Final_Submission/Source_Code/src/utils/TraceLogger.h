#ifndef TRACE_LOGGER_H
#define TRACE_LOGGER_H

#include <string>
#include <fstream>


class TraceLogger {
private:
    std::ofstream file;
    bool enabled;
    bool ascii_enabled;
    
    // Store history for ASCII diagram
    struct CycleRecord {
        int cycle;
        std::string if_instr;
        std::string id_instr;
        std::string ex_instr;
        std::string mem_instr;
        std::string wb_instr;
        std::string event;
    };
    std::vector<CycleRecord> history;
    
    std::string truncate(const std::string& s, size_t maxLen) const;

public:
    TraceLogger(const std::string& filename);
    ~TraceLogger();
    
    void setAsciiMode(bool enable) { ascii_enabled = enable; }
    
    void logCycle(int cycle, 
                  const std::string& fetch_instr, 
                  const std::string& decode_instr, 
                  const std::string& execute_instr, 
                  const std::string& memory_instr, 
                  const std::string& writeback_instr,
                  const std::string& event);
    
    void printAsciiDiagram(int lastN = 20) const;
    void printAsciiDiagramToFile(const std::string& filename) const;
};

#endif // TRACE_LOGGER_H
