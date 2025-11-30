#include "BranchPredictor.h"

BranchPredictor::BranchPredictor(int table_size) : size(table_size) {
    prediction_table.resize(size, false); // Default: Not Taken
}

bool BranchPredictor::predict(int pc) {
    int index = pc % size;
    return prediction_table[index];
}

void BranchPredictor::update(int pc, bool actually_taken) {
    int index = pc % size;
    prediction_table[index] = actually_taken;
}
