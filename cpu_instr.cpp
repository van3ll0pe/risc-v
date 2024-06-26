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
    this->reg_x[rd] = this->program_counter + imm;
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
    this->reg_x[rd] = this->reg_x[rs1] - this->reg_x[rs2];
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

/*************** UNCONDITIONAL JUMPS ******************************/

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_jal(uint8_t rd, uint32_t imm) //imm value ignore bit 0, no need to put bit 0 to 0
{
    this->reg_x[rd] = this->program_counter + 4; //pc + 4 to be on the next instruction

    this->program_counter += imm;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_jalr(uint8_t rd, uint8_t rs1, uint32_t imm) //imm value need to put bit 0 to 0
{
    this->reg_x[rd] = this->program_counter; // pc is already to the next instruction (no need to add +4)

    this->program_counter = (this->reg_x[rs1] + imm) & 0xFFFFFFFE; // put the bit 0 of the result to 0
}

/****************************************************************/

/****************** CONDITIONAL BRANCH *************************/

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_beq(uint8_t rs1, uint8_t rs2, uint32_t imm)
{
    if (this->reg_x[rs1] == this->reg_x[rs2])
        this->program_counter += imm;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_bne(uint8_t rs1, uint8_t rs2, uint32_t imm)
{
    if (this->reg_x[rs1] != this->reg_x[rs2])
        this->program_counter += imm;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_blt(uint8_t rs1, uint8_t rs2, uint32_t imm)
{
     if ((signed int)this->reg_x[rs1] < (signed int)this->reg_x[rs2])
        this->program_counter += imm;

}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_bltu(uint8_t rs1, uint8_t rs2, uint32_t imm)
{
    if (this->reg_x[rs1] < this->reg_x[rs2]) //already unsigned type
        this->program_counter += imm;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_bge(uint8_t rs1, uint8_t rs2, uint32_t imm)
{
    if ((signed int)this->reg_x[rs1] >= (signed int)this->reg_x[rs2])
        this->program_counter += imm;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_bgeu(uint8_t rs1, uint8_t rs2, uint32_t imm)
{
    if (this->reg_x[rs1] >= this->reg_x[rs2]) //already unsigned type
        this->program_counter += imm;
}

/***********************************************************************************/

/************ LOAD / STORE INSTRUCTIONS *********************************************/

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_lw(uint8_t rd, uint8_t rs1, uint32_t imm)
{
    uint32_t address = (imm + this->reg_x[rs1]) & 0xFFFFFFFC;
    uint32_t data = this->memory.read32(address);
    this->reg_x[rd] = data;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_lh(uint8_t rd, uint8_t rs1, uint32_t imm)
{
    uint32_t address = (imm + this->reg_x[rs1]) & 0xFFFFFFFE;
    uint32_t data = this->memory.read16(address);

    if (data & 0x8000) //signed extends
        data |= 0xFFFF0000;
    
    this->reg_x[rd] = data;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_lhu(uint8_t rd, uint8_t rs1, uint32_t imm)
{
    uint32_t address = (imm + this->reg_x[rs1]) & 0xFFFFFFFE;
    uint32_t data = this->memory.read16(address);
    //zero extends
    this->reg_x[rd] = data;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_lb(uint8_t rd, uint8_t rs1, uint32_t imm)
{
    uint32_t address = (imm + this->reg_x[rs1]);
    uint32_t data = this->memory.read8(address);

    if (data & 0x80) //signed extends 8bits value
        data |= 0xFFFFFF00;
    
    this->reg_x[rd] = data;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_lbu(uint8_t rd, uint8_t rs1, uint32_t imm)
{
    uint32_t address = (imm + this->reg_x[rs1]);
    uint32_t data = this->memory.read8(address);
    //zero extends
    this->reg_x[rd] = data;
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_sw(uint8_t rs1, uint8_t rs2, uint32_t imm)
{
    uint32_t  address = (this-reg_x[rs1] + imm) & 0xFFFFFFFC;

    this->memory.write32(address, this->reg_x[rs2]);
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_sh(uint8_t rs1, uint8_t rs2, uint32_t imm)
{
    uint32_t address = (this->reg_x[rs1] + imm) & 0xFFFFFFFE;

    this->memory.write16(address, (uint16_t)this->reg_x[rs2]);
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_sb(uint8_t rs1, uint8_t rs2, uint32_t imm)
{
    this->memory.write8(this->reg_x[rs1] + imm, (uint8_t)this->reg_x[rs2]);
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_ebreak()
{
    exit(0);
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_ecall()
{
    //NOP currently
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_fence()
{
    std::atomic_thread_fence(std::memory_order_seq_cst);
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_fencei()
{
    this->cache.clearCache();
}

template<uint64_t MEMORY_SIZE>
void 
Riscv32i<MEMORY_SIZE>::instr_csrrw()
{

}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_csrrs()
{

}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_csrrc()
{

}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_csrrwi()
{

}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_csrrsi()
{

}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_csrrci()
{

}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_rdcycle()
{

}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_rdtime()
{

}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::instr_rdinstret()
{
    
}