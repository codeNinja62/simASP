#include "BranchPredictor.h"

using namespace std;

BranchPredictor::BranchPredictor(int table_size) : size(table_size) {
    // Initialize all to "Not Taken" (False)
    prediction_table.resize(size, false);
}

bool BranchPredictor::predict(int pc) {
    int index = pc % size;
    return prediction_table[index];
}

void BranchPredictor::update(int pc, bool actually_taken) {
    int index = pc % size;
    // 1-Bit: Just copy the actual outcome
    prediction_table[index] = actually_taken;
}
