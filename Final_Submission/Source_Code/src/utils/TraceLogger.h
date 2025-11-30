#ifndef TRACE_LOGGER_H
#define TRACE_LOGGER_H

#include <string>
#include <fstream>

class TraceLogger {
private:
    std::ofstream file;
    bool enabled;

public:
    TraceLogger(const std::string& filename);
    ~TraceLogger();
    
    void logCycle(int cycle, 
                  const std::string& fetch_instr, 
                  const std::string& decode_instr, 
                  const std::string& execute_instr, 
                  const std::string& memory_instr, 
                  const std::string& writeback_instr,
                  const std::string& event);
};

#endif // TRACE_LOGGER_H
