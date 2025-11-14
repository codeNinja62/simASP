#ifndef BRANCH_PREDICTOR_H
#define BRANCH_PREDICTOR_H

#include <vector>

class BranchPredictor {
private:
    std::vector<int> pht;    // Pattern History Table (2-bit counters)
    int table_size;
    int predictions;
    int mispredictions;

public:
    BranchPredictor(int size = 64);
    
    bool predict(int pc);
    void update(int pc, bool taken);
    
    double getAccuracy() const;
    int getPredictions() const { return predictions; }
    int getMispredictions() const { return mispredictions; }
    void reset();
};

#endif // BRANCH_PREDICTOR_H
