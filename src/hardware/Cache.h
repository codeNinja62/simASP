#ifndef CACHE_H
#define CACHE_H

#include <vector>

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

    long long hits;
    long long misses;

public:
    Cache(int size_bytes = 1024, int block_size = 64);
    
    bool access(int addr);
    
    long long getHits() const { return hits; }
    long long getMisses() const { return misses; }
};

#endif // CACHE_H
