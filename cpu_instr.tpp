#include "cpu.hpp"

template<uint64_t MEMORY_SIZE>
void
Riscv32i::instr_addi(uint8_t rs1, uint8_t rd, uint32_t imm)
{
    this->reg_x[rd] = this->reg_x[rs1] + imm;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i::instr_xori(uint8_t rs1, uint8_t rd, uint32_t imm)
{
    this->reg_x[rd] = this->reg_x[rs1] ^ imm;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i::instr_ori(uint8_t rs1, uint8_t rd, uint32_t imm)
{
    this->reg_x[rd] = this->reg_x[rs1] | imm;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i::instr_andi(uint8_t rs1, uint8_t rd, uint32_t imm)
{
    this->reg_x[rd] = this->reg_x[rs1] & imm;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i::instr_slti(uint8_t rs1, uint8_t rd, uint32_t imm)
{
    this->reg_x[rd] = ((signed int)this->reg_x[rs1] < (signed int)imm) ? 1 : 0; //cast to signed int
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i::instr_sltiu(uint8_t rs1, uint8_t rd, uint32_t imm)
{
    this->reg_x[rd] = (this->reg_x[rs1] < imm) ? 1 : 0; //already unsigned, no need to cast
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i::instr_slli(uint8_t rs1, uint8_t rd, uint8_t shamt)
{
    this->reg_x[rd] = this->reg_x[rs1] << shamt;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i::instr_srli(uint8_t rs1, uint8_t rd, uint8_t shamt)
{
    this->reg_x[rd] = this->reg_x[rs1] >> shamt;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i::instr_srai(uint8_t rs1, uint8_t rd, uint8_t shamt)
{
    this->reg_x[rd] = this->reg_x[rs1] >> shamt;
 
    if (this->reg_x[rs1] & 0x80000000) {//negative number
        for(uint8_t i = 0; i < shamt; i++) {
            this->reg_x[rd] |= (0x80000000 >> i); //decale le bit 31 vers le bit non décaler pour y mettre un 0
        }
    }
}

