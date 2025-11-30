#ifndef BRANCH_PREDICTOR_H
#define BRANCH_PREDICTOR_H

#include <vector>
#include <iostream>

// Simple 1-Bit Branch Predictor (Direct Mapped)
class BranchPredictor {
private:
    // Table of 1-bit counters (Taken/Not Taken)
    // Indexed by PC % TableSize
    std::vector<bool> prediction_table;
    int size;

public:
    BranchPredictor(int table_size = 1024);

    // Get prediction for a PC (True = Taken, False = Not Taken)
    bool predict(int pc);

    // Update predictor after branch resolution
    void update(int pc, bool actually_taken);
};

#endif // BRANCH_PREDICTOR_H
