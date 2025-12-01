#ifndef BRANCH_PREDICTOR_H
#define BRANCH_PREDICTOR_H

#include <vector>
#include <iostream>

// 2-Bit Saturating Counter Branch Predictor (Direct Mapped)
// States: 00=Strongly Not Taken, 01=Weakly Not Taken, 10=Weakly Taken, 11=Strongly Taken
class BranchPredictor {
public:
    enum State {
        STRONGLY_NOT_TAKEN = 0,  // 00
        WEAKLY_NOT_TAKEN = 1,    // 01
        WEAKLY_TAKEN = 2,        // 10
        STRONGLY_TAKEN = 3       // 11
    };
    
private:
    // Table of 2-bit counters
    std::vector<State> prediction_table;
    int size;

public:
    BranchPredictor(int table_size = 1024);

    // Get prediction for a PC (True = Taken, False = Not Taken)
    bool predict(int pc);

    // Update predictor after branch resolution
    void update(int pc, bool actually_taken);
    
    // Get state name for debugging
    static const char* stateName(State s);
};

#endif // BRANCH_PREDICTOR_H
