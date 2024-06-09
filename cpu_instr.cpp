#include "cpu.hpp"

/******************* IMMEDIATE OPERATION INSTRUCTION *************************/
template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_addi(uint8_t rs1, uint8_t rd, uint32_t imm)
{
    this->reg_x[rd] = this->reg_x[rs1] + imm;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_xori(uint8_t rs1, uint8_t rd, uint32_t imm)
{
    this->reg_x[rd] = this->reg_x[rs1] ^ imm;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_ori(uint8_t rs1, uint8_t rd, uint32_t imm)
{
    this->reg_x[rd] = this->reg_x[rs1] | imm;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_andi(uint8_t rs1, uint8_t rd, uint32_t imm)
{
    this->reg_x[rd] = this->reg_x[rs1] & imm;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_slti(uint8_t rs1, uint8_t rd, uint32_t imm)
{
    this->reg_x[rd] = ((signed int)this->reg_x[rs1] < (signed int)imm) ? 1 : 0; //cast to signed int
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_sltiu(uint8_t rs1, uint8_t rd, uint32_t imm)
{
    this->reg_x[rd] = (this->reg_x[rs1] < imm) ? 1 : 0; //already unsigned, no need to cast
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_slli(uint8_t rs1, uint8_t rd, uint8_t shamt)
{
    this->reg_x[rd] = this->reg_x[rs1] << shamt;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_srli(uint8_t rs1, uint8_t rd, uint8_t shamt)
{
    this->reg_x[rd] = this->reg_x[rs1] >> shamt;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_srai(uint8_t rs1, uint8_t rd, uint8_t shamt)
{
    this->reg_x[rd] = this->reg_x[rs1] >> shamt;
 
    if (this->reg_x[rs1] & 0x80000000) {//negative number
        for(uint8_t i = 0; i < shamt; i++) {
            this->reg_x[rd] |= (0x80000000 >> i); //decale le bit 31 vers le bit non décaler pour y mettre un 0
        }
    }
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_lui(uint8_t rd, uint32_t imm)
{
    this->reg_x[rd] = imm;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_auipc(uint8_t rd, uint32_t imm)
{
    this->reg_x[rd] = this->current_address + imm;
}

/************************************************************************/

/********* REGISTER REGISTER INSTRUCTION *******************************/

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_add(uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    this->reg_x[rd] = this->reg_x[rs1] + this->reg_x[rs2];
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_sub(uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    this->reg_x[rd] = this->reg_x[rs1] + this->reg_x[rs2];
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_xor(uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    this->reg_x[rd] = this->reg_x[rs1] ^ this->reg_x[rs2];
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_or(uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    this->reg_x[rd] = this->reg_x[rs1] | this->reg_x[rs2];
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_and(uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    this->reg_x[rd] = this->reg_x[rs1] & this->reg_x[rs2];
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_slt(uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    this->reg_x[rd] = ((signed int)this->reg_x[rs1] < (signed int)this->reg_x[rs2]) ? 1 : 0;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_sltu(uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    this->reg_x[rd] = (this->reg_x[rs1] < this->reg_x[rs2]) ? 1 : 0;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_sll(uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    this->reg_x[rd] = this->reg_x[rs1] << (this->reg_x[rs2] & 0x1F);
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_srl(uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    this->reg_x[rd] = this->reg_x[rs1] >> (this->reg_x[rs2] & 0x1F);
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_sra(uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    this->reg_x[rd] = this->reg_x[rs1] >> (this->reg_x[rs2] & 0x1F);

     if (this->reg_x[rs1] & 0x80000000) {//negative number
        for(uint8_t i = 0; i < (this->reg_x[rs2] & 0x1F); i++) {
            this->reg_x[rd] |= (0x80000000 >> i); //decale le bit 31 vers le bit non décaler pour y mettre un 0
        }
    }
}

/***************************************************************** */