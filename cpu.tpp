#include "cpu.hpp"

template<uint64_t MEMORY_SIZE>
Riscv32i<MEMORY_SIZE>::Riscv32i(uint32_t start_address = 0x0)
{
    static_assert(MEMORY_SIZE <= (UINT32_MAX + 1), "[ERROR]:: OVER 2^32 size memory");

    this->opcode = 0x0;
    this->current_instr = 0x0;
    this->program_counter = start_address;
    this->current_address = start_address;
    this->reg_x.fill(0);
    this->memory_bus = std::make_unique<Memory<MEMORY_SIZE>>();
}

template<uint64_t MEMORY_SIZE>
Riscv32i<MEMORY_SIZE>::~Riscv32i()
{ }

//register X0 is hard constant 0, so if modification, put 0 on x0 register value
template<uint64_t MEMORY_SIZE>
Riscv32i<MEMORY_SIZE>::reset_x0()
{
    this->reg_x[0] = 0;
}