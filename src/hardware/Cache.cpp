#include "Cache.h"

Cache::Cache(int size_bytes, int block_size) 
    : size_bytes(size_bytes), block_size(block_size), hits(0), misses(0) {
    num_lines = size_bytes / block_size;
    lines.resize(num_lines);
    for (auto& line : lines) {
        line.valid = false;
        line.tag = 0;
    }
}

bool Cache::access(int addr) {
    // Fixed: Correct tag/index calculation for direct-mapped cache
    int index = (addr / block_size) % num_lines;
    int tag = addr / (block_size * num_lines);
    
    if (lines[index].valid && lines[index].tag == tag) {
        hits++;
        return true;
    } else {
        misses++;
        lines[index].valid = true;
        lines[index].tag = tag;
        return false;
    }
}
