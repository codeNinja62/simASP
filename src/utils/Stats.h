#ifndef STATS_H
#define STATS_H

#include <iostream>

class Stats {
private:
    long long total_cycles;
    long long instructions_retired;

public:
    Stats();
    void addCycle() { total_cycles++; }
    void addInstructionRetired() { instructions_retired++; }
    void printReport();
};

#endif // STATS_H
