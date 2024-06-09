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
Memory<MEMORY_SIZE>::write(uint32_t address, uint8_t data)
{
    this->memory_array[address] = data;
}

template<uint64_t MEMORY_SIZE>
uint8_t
Memory<MEMORY_SIZE>::read(uint32_t address)
{
    return this->memory_array[address];
}