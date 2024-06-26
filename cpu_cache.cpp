#include "cpu_cache.hpp"

Cache::Cache()
{
    this->cacheSize = 0;
}

Cache::~Cache()
{}

void
Cache::clearCache()
{
    this->cacheData.clear();
    this->cacheSize = 0;
}

bool
Cache::getInstruction(uint32_t address, uint32_t& instruction)
{
    auto it = this->cacheData.find(address);
    if (it == this->cacheData.end()) //not in cache
        return false;
    
    instruction = it->second;
    return true;
}

void
Cache::setInstruction(uint32_t address, uint32_t instruction)
{
    if (this->cacheSize + 1 >= CACHE_SIZE)
        this->cacheData.erase(this->cacheData.begin());
    else
        this->cacheSize++;
    
    this->cacheData[address] = instruction;
    return;
}