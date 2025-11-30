#include "Stats.h"

using namespace std;

Stats::Stats() : 
    total_cycles(0), instructions_retired(0), stall_cycles(0), 
    branch_flushes(0), zero_skips(0),
    alu_ops(0), memory_ops(0), branch_ops(0),
    cache_hits(0), cache_misses(0),
    branch_predictions(0), branch_correct(0) {}

void Stats::printReport() {
    double cpi = (instructions_retired > 0) ? (double)total_cycles / instructions_retired : 0.0;
    double ipc = (total_cycles > 0) ? (double)instructions_retired / total_cycles : 0.0;

    cout << "\n================================================================================" << endl;
    cout << "                       SPARSEFLOW PERFORMANCE REPORT                            " << endl;
    cout << "================================================================================" << endl;
    
    cout << left << setw(30) << "Total Cycles:" << total_cycles << endl;
    cout << left << setw(30) << "Instructions Retired:" << instructions_retired << endl;
    cout << left << setw(30) << "CPI (Cycles Per Instr):" << fixed << setprecision(2) << cpi << endl;
    cout << left << setw(30) << "IPC (Instr Per Cycle):" << fixed << setprecision(2) << ipc << endl;
    
    cout << "\n[Pipeline Events]" << endl;
    cout << left << setw(30) << "Stall Cycles (Hazards/Mem):" << stall_cycles << " cycles lost" << endl;
    cout << left << setw(30) << "Branch Mispredict Flushes:" << branch_flushes << " times" << endl;
    cout << left << setw(30) << "Zero-Skipping Savings:" << zero_skips << " ops skipped" << endl;

    cout << "\n[Instruction Mix]" << endl;
    cout << left << setw(30) << "ALU / Compute:" << alu_ops << endl;
    cout << left << setw(30) << "Memory (Load/Store):" << memory_ops << endl;
    cout << left << setw(30) << "Control Flow:" << branch_ops << endl;
    
    cout << "\n[Cache Performance]" << endl;
    long long cache_total = cache_hits + cache_misses;
    double hit_rate = (cache_total > 0) ? (100.0 * cache_hits / cache_total) : 0.0;
    cout << left << setw(30) << "Cache Hits:" << cache_hits << endl;
    cout << left << setw(30) << "Cache Misses:" << cache_misses << endl;
    cout << left << setw(30) << "Cache Hit Rate:" << fixed << setprecision(1) << hit_rate << "%" << endl;
    
    cout << "\n[Branch Prediction]" << endl;
    double bp_accuracy = (branch_predictions > 0) ? (100.0 * branch_correct / branch_predictions) : 0.0;
    cout << left << setw(30) << "Predictions Made:" << branch_predictions << endl;
    cout << left << setw(30) << "Correct Predictions:" << branch_correct << endl;
    cout << left << setw(30) << "Prediction Accuracy:" << fixed << setprecision(1) << bp_accuracy << "%" << endl;
    cout << "================================================================================" << endl;
}
