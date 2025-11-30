#ifndef STATS_H
#define STATS_H

#include <iostream>
#include <iomanip>
#include <string>

class Stats {
private:
    long long total_cycles;
    long long instructions_retired;
    long long stall_cycles;
    long long branch_flushes;
    long long zero_skips;
    
    // Instruction Mix
    long long alu_ops;
    long long memory_ops;
    long long branch_ops;
    
    // Cache Stats
    long long cache_hits;
    long long cache_misses;
    
    // Branch Prediction Stats
    long long branch_predictions;
    long long branch_correct;

public:
    Stats();

    void addCycle() { total_cycles++; }
    void addInstructionRetired() { instructions_retired++; }
    void addStall() { stall_cycles++; }
    void addBranchFlush() { branch_flushes++; }
    void addZeroSkip() { zero_skips++; }
    
    void addAluOp() { alu_ops++; }
    void addMemoryOp() { memory_ops++; }
    void addBranchOp() { branch_ops++; }
    
    void setCacheStats(long long hits, long long misses) { cache_hits = hits; cache_misses = misses; }
    void addBranchPrediction(bool correct) { branch_predictions++; if (correct) branch_correct++; }

    void printReport();
};

#endif // STATS_H
