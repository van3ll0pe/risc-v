#pragma once
#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

#include <cstdint>
#include <array>

template<uint64_t MEMORY_SIZE>
class Memory {
    private:
        std::array<uint8_t, MEMORY_SIZE> memory_array;
    
    public:
        Memory();
        ~Memory();
        void write(uint32_t address, uint8_t data);
        uint8_t read(uint32_t address);
};

#endif //__MEMORY_HPP__