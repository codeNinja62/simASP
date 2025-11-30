#include "Cache.h"

Cache::Cache(int size, int block) : size_bytes(size), block_size(block), hits(0), misses(0) {
    num_lines = size_bytes / block_size;
    lines.resize(num_lines, {false, 0});
}

bool Cache::access(int addr) {
    // Simple Direct Mapped Logic
    // Address: [ Tag | Index | Offset ]
    
    int offset_bits = (int)log2(block_size);
    int index_bits = (int)log2(num_lines);
    
    int index_mask = (1 << index_bits) - 1;
    int index = (addr >> offset_bits) & index_mask;
    int tag = addr >> (offset_bits + index_bits);

    if (lines[index].valid && lines[index].tag == tag) {
        hits++;
        return true; // Hit
    } else {
        misses++;
        // Install line
        lines[index].valid = true;
        lines[index].tag = tag;
        return false; // Miss
    }
}
