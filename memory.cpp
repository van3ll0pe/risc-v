#include "memory.hpp"

template<uint64_t MEMORY_SIZE>
Memory<MEMORY_SIZE>::Memory()
{
    this->memory_array.fill(0);
}

template<uint64_t MEMORY_SIZE>
Memory<MEMORY_SIZE>::~Memory()
{}

template<uint64_t MEMORY_SIZE>
void
Memory<MEMORY_SIZE>::write8(uint32_t address, uint8_t data)
{
    this->memory_array[address] = data;
}

template<uint64_t MEMORY_SIZE>
uint8_t
Memory<MEMORY_SIZE>::read8(uint32_t address)
{
    return this->memory_array[address];
}

template<uint64_t MEMORY_SIZE>
void
Memory<MEMORY_SIZE>::write16(uint32_t address, uint16_t data)
{
    for (int i = 0; i < 2; i++) {
        this->memory_array[address] = ((data >> (i * 8)) & 0xFF);
        address++;
    }
}

template<uint64_t MEMORY_SIZE>
void
Memory<MEMORY_SIZE>::write32(uint32_t address, uint32_t data)
{
    for (int i = 0; i < 4; i++) {
        this->memory_array[address] = ((data >> (i * 8)) & 0xFF)
        address++;
    }
}

template<uint64_t MEMORY_SIZE>
uint16_t
Memory<MEMORY_SIZE>::read16(uint32_t address)
{
    uint16_t data = 0;

    for (int i = 0; i < 2; i++) {
        data |= (this->memory_array[address] << (i * 8));
        address++;
    }
    
    return data;
}

template<uint64_t MEMORY_SIZE>
uint32_t
Memory<MEMORY_SIZE>::read32(uint32_t address)
{
    uint32_t data = 0;

    for (int i = 0; i < 4; i++) {
        data |= (this->memory_array[address] << (i * 8));
        address++;
    }
    
    return data;
}