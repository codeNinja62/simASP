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
    void logCycle(int cycle, const std::string& stage_info);
};

#endif // TRACE_LOGGER_H
