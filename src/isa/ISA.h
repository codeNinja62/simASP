#ifndef ISA_H
#define ISA_H

#include <map>
#include <string>

// Register ABI Aliases (t0=x5, a0=x10, etc.)
const std::map<int, std::string> REG_ABI = {
    {0, "zero"}, {1, "ra"}, {2, "sp"},
    {5, "t0"}, {6, "t1"}, {7, "t2"},
    {10, "a0"}, {11, "a1"}
};

// Vector register names
const std::string VREG_NAMES[] = {"v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7"};

#endif // ISA_H
