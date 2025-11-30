#include "Stats.h"
#include <iostream>
#include <iomanip>

Stats::Stats() {
    reset();
}

void Stats::reset() {
    total_cycles = 0;
    instructions_executed = 0;
    stall_cycles = 0;
    branch_predictions = 0;
    branch_mispredictions = 0;
    cache_hits = 0;
    cache_misses = 0;
    zero_skips = 0;
}

void Stats::addBranchPrediction(bool correct) {
    branch_predictions++;
    if (!correct) branch_mispredictions++;
}

void Stats::addCacheAccess(bool hit) {
    if (hit) cache_hits++;
    else cache_misses++;
}

double Stats::getCPI() const {
    if (instructions_executed == 0) return 0.0;
    return (double)total_cycles / instructions_executed;
}

double Stats::getBranchAccuracy() const {
    if (branch_predictions == 0) return 100.0;
    return 100.0 * (branch_predictions - branch_mispredictions) / branch_predictions;
}

double Stats::getCacheHitRate() const {
    long long total = cache_hits + cache_misses;
    if (total == 0) return 100.0;
    return 100.0 * cache_hits / total;
}

void Stats::printStats() const {
    std::cout << "\n========== Performance Statistics ==========\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total Cycles:        " << total_cycles << "\n";
    std::cout << "Instructions:        " << instructions_executed << "\n";
    std::cout << "CPI:                 " << getCPI() << "\n";
    std::cout << "Stall Cycles:        " << stall_cycles << "\n";
    std::cout << "Branch Predictions:  " << branch_predictions << "\n";
    std::cout << "Branch Accuracy:     " << getBranchAccuracy() << "%\n";
    std::cout << "Cache Hit Rate:      " << getCacheHitRate() << "%\n";
    std::cout << "Zero-Skip Ops:       " << zero_skips << "\n";
    std::cout << "=============================================\n";
}
