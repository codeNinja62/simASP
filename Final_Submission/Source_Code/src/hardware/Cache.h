#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <cmath>

class Cache {
private:
    struct CacheLine {
        bool valid;
        int tag;
    };

    std::vector<CacheLine> lines;
    int size_bytes;
    int block_size;
    int num_lines;

    // Stats
    long long hits;
    long long misses;

public:
    Cache(int size_bytes = 1024, int block_size = 64); // Default 1KB, 64B blocks

    // Returns true if Hit, false if Miss
    bool access(int addr);

    long long getHits() const { return hits; }
    long long getMisses() const { return misses; }
};

#endif // CACHE_H
