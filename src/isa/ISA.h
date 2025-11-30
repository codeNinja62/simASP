#ifndef ISA_H
#define ISA_H

#include <map>
#include <string>

// Register ABI Aliases for display and debugging
const std::map<int, std::string> REG_ABI = {
    {0, "zero"}, {1, "ra"}, {2, "sp"}, 
    {5, "t0"}, {6, "t1"}, {7, "t2"}, 
    {10, "a0"}, {11, "a1"}
};

#endif // ISA_H
