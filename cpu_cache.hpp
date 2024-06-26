#pragma once
#ifndef __CPU_CACHE__
#define __CPU_CACHE__

#include <stdint.h>
#include <map>

#define CACHE_SIZE 250000

class Cache {
    private:
        std::map<uint32_t, uint32_t> cacheData;
        uint32_t cacheSize;
    public:
        Cache();
        ~Cache();
        bool getInstruction(uint32_t address, uint32_t& instruction);
        void setInstruction(uint32_t address, uint32_t instruction);
        void clearCache();
};

#endif //__CPU_CACHE