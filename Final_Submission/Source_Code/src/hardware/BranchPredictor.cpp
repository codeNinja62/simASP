#include "BranchPredictor.h"

BranchPredictor::BranchPredictor(int size) 
    : table_size(size), predictions(0), mispredictions(0) {
    // Initialize all entries to Weakly Not Taken (01)
    pht.resize(size, 1);
}

bool BranchPredictor::predict(int pc) {
    int index = pc % table_size;
    // Predict taken if counter >= 2 (Weakly Taken or Strongly Taken)
    return pht[index] >= 2;
}

void BranchPredictor::update(int pc, bool taken) {
    int index = pc % table_size;
    predictions++;
    
    bool predicted = pht[index] >= 2;
    if (predicted != taken) {
        mispredictions++;
    }
    
    // Update 2-bit saturating counter
    if (taken) {
        if (pht[index] < 3) pht[index]++;
    } else {
        if (pht[index] > 0) pht[index]--;
    }
}

double BranchPredictor::getAccuracy() const {
    if (predictions == 0) return 0.0;
    return 100.0 * (predictions - mispredictions) / predictions;
}

void BranchPredictor::reset() {
    std::fill(pht.begin(), pht.end(), 1);
    predictions = 0;
    mispredictions = 0;
}
