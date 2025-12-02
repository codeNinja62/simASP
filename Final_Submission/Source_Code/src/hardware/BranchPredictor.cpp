#include "BranchPredictor.h"

using namespace std;

BranchPredictor::BranchPredictor(int table_size) : size(table_size) {
    // Initialize all to "Weakly Not Taken" - a neutral starting point
    prediction_table.resize(size, WEAKLY_NOT_TAKEN);
}

bool BranchPredictor::predict(int pc) {
    int index = pc % size;
    State state = prediction_table[index];
    // Predict taken if state >= 2 (WEAKLY_TAKEN or STRONGLY_TAKEN)
    return state >= WEAKLY_TAKEN;
}

void BranchPredictor::update(int pc, bool actually_taken) {
    int index = pc % size;
    State current = prediction_table[index];
    
    // 2-Bit Saturating Counter Logic:
    // If taken: increment (but saturate at STRONGLY_TAKEN)
    // If not taken: decrement (but saturate at STRONGLY_NOT_TAKEN)
    if (actually_taken) {
        if (current < STRONGLY_TAKEN) {
            prediction_table[index] = static_cast<State>(current + 1);
        }
    } else {
        if (current > STRONGLY_NOT_TAKEN) {
            prediction_table[index] = static_cast<State>(current - 1);
        }
    }
}

const char* BranchPredictor::stateName(State s) {
    switch (s) {
        case STRONGLY_NOT_TAKEN: return "Strongly Not Taken";
        case WEAKLY_NOT_TAKEN:   return "Weakly Not Taken";
        case WEAKLY_TAKEN:       return "Weakly Taken";
        case STRONGLY_TAKEN:     return "Strongly Taken";
        default:                 return "Unknown";
    }
}
