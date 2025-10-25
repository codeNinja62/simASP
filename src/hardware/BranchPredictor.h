#ifndef BRANCH_PREDICTOR_H
#define BRANCH_PREDICTOR_H

#include <vector>

class BranchPredictor {
private:
    std::vector<bool> prediction_table;
    int size;

public:
    BranchPredictor(int table_size = 1024);
    bool predict(int pc);
    void update(int pc, bool actually_taken);
};

#endif // BRANCH_PREDICTOR_H
