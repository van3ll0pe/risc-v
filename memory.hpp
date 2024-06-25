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
        void write8(uint32_t address, uint8_t data);
        uint8_t read8(uint32_t address);
        void write16(uint32_t address, uint16_t data);
        uint16_t read16(uint32_t address);
        void write32(uint32_t address, uint32_t data);
        uint32_t read32(uint32_t address);

};

#endif //__MEMORY_HPP__