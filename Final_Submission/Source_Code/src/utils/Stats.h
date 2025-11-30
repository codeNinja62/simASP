#ifndef STATS_H
#define STATS_H

#include <string>

class Stats {
private:
    long long total_cycles;
    long long instructions_executed;
    long long stall_cycles;
    long long branch_predictions;
    long long branch_mispredictions;
    long long cache_hits;
    long long cache_misses;
    long long zero_skips;  // Sparse optimization: skipped zero operations

public:
    Stats();
    
    void addCycle() { total_cycles++; }
    void addInstruction() { instructions_executed++; }
    void addStall() { stall_cycles++; }
    void addBranchPrediction(bool correct);
    void addCacheAccess(bool hit);
    void addZeroSkip() { zero_skips++; }
    
    double getCPI() const;
    double getBranchAccuracy() const;
    double getCacheHitRate() const;
    
    void printStats() const;
    void reset();
};

#endif // STATS_H
