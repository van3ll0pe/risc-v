#include "cpu.hpp"
#include <iostream>

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::fetch()
{
    if (this->cache.getInstruction(this->program_counter, this->current_instr)) //true so address already in cache
        return;
    else { //not find in cache so need to read memory
        this->current_instr = this->memory.read32(this->program_counter);
        this->cache.setInstruction(this->program_counter, this->current_instr);
    }
    this->opcode = this->current_instr & 0x7F; //the first 7 bits of the instruction to get opcode
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::decode_general()
{
    switch(this->opcode) {
        case 0b0110011: this->decode_R_type(); //R
                        break;
        case 0b0010011: this->decode_I_type(); //I
                        break;
        case 0b0000011: this->decode_I_type(); //I
                        break;
        case 0b0100011: this->decode_S_type(); //S
                        break;
        case 0b1100011: this->decode_B_type(); //B
                        break;
        case 0b1101111: this->decode_J_type(); //J
                        break;
        case 0b1100111: this->decode_I_type(); //I
                        break;
        case 0b0110111: this->decode_U_type(); //U
                        break;
        case 0b0010111: this->decode_U_type(); //U
                        break;
        case 0b1110011: this->decode_I_type(); //I
                        break;
        default: break;
    }
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::decode_R_type()
{
    uint8_t rd = (this->current_instr & 0xF80) >> 7;
    uint8_t funct_3 = (this->current_instr & 0x7000) >> 12;
    uint8_t rs1 = (this->current_instr & 0xF8000) >> 15;
    uint8_t rs2 = (this->current_instr & 0x1F00000) >> 20;
    uint8_t funct_7 = (this->current_instr & 0xFE000000) >> 25;

    if (funct_3 ==  0x0 && funct_7 == 0x0) //ADD
        instr_add(rd, rs1, rs2);
    else if (funct_3 == 0x0 && funct_7 == 0x20) //SUB
        instr_sub(rd, rs1, rs2);
    else if (funct_3 == 0x4 && funct_7 == 0x0) //XOR
        instr_xor(rd, rs1, rs2);
    else if (funct_3 == 0x6 && funct_7 == 0x0) //OR
        instr_or(rd, rs1, rs2);
    else if (funct_3 == 0x7 && funct_7 == 0x0) //AND
        instr_and(rd, rs1, rs2);
    else if (funct_3 == 0x1 && funct_7 == 0x0) //SLL
        instr_sll(rd, rs1, rs2);
    else if (funct_3 == 0x5 && funct_7 == 0x0) //SRL
        instr_srl(rd, rs1, rs2);
    else if (funct_3 == 0x5 && funct_7 == 0x20) //SRA
        instr_sra(rd, rs1, rs2);
    else if (funct_3 == 0x2 && funct_7 == 0x0) //SLT
        instr_slt(rd, rs1, rs2);
    else if (funct_3 == 0x3 && funct_7 == 0x0) //SLTU
        instr_sltu(rd, rs1, rs2);
    else {
        std::cerr << "illegal instruction" << std::endl;
        exit(1);
    }
    
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::decode_I_type()
{
    uint8_t rd = (this->current_instr & 0xF80) >> 7;
    uint8_t funct_3 = (this->current_instr & 0x7000) >> 12;
    uint8_t rs1 = (this->current_instr & 0xF8000) >> 15;
    uint32_t imm = (this->current_instr & 0xFFF00000) >> 20;

    if (imm & 0x800) //negative number signed 12 bits (11:0) signed in bit 11
        imm |= 0xFFFFF000;

    switch(this->opcode) {
        case 0b0010011:  //calcul immediate operation
                        if (funct_3 == 0x0) //ADDI
                            instr_addi(rs1, rd, imm);
                        else if (funct_3 == 0x1 && ((imm & 0xFE0) == 0x0)) //SLLI
                            instr_slli(rs1, rd, (imm & 0x1F));
                        else if (funct_3 == 0x2) //SLTI
                            instr_slti(rs1, rd, imm);
                        else if (funct_3 == 0x3) //SLTI U
                            instr_sltiu(rs1, rd, imm);
                        else if (funct_3 == 0x4) //XORI
                            instr_xori(rs1? rd, imm);
                        else if (funct_3 == 0x5 && ((imm & 0xFE0) == 0x0)) // SRLI
                            instr_srli(rs1, rd, (imm & 0x1F));
                        else if (funct_3 == 0x5 && ((imm & 0xFE0) == 0x400)) // SRAI, 400 revient à 0x20 s'il y a un décalage de 5bits
                            instr_srai(rs1, rd, (imm & 0x1F));
                        else if (funct_3 == 0x6) //ORI
                            instr_ori(rs1, rd, imm);
                        else if (funct_3 == 0x7) //ANDI
                            instr_andi(rs1, rd, imm);
                        else {
                            std::cerr << "illegal instruction" << std::endl;
                            exit(1);
                        }
                        break;

        case 0b0000011: //load operation
                        if (funct_3 == 0x0) //LOAD BYTE
                            instr_lb(rd, rs1, imm);
                        else if (funct_3 == 0x1) ///LOAD HALF
                            instr_lh(rd, rs1, imm);
                        else if (funct_3 == 0x2) //LOAD WORD
                            instr_lw(rd, rs1, imm);
                        else if (funct_3 == 0x4) //LOAD BYTE U
                            instr_lbu(rd, rs1, imm);
                        else if (funct_3 == 0x5) //LOAD HALF U
                            instr_lhu(rd, rs1, imm);
                        else {
                            std::cerr << "illegal instruction" << std::endl;
                            exit(1);
                        }
                        break;

        case 0b1100111: //jump and link reg
                        if (funct_3 == 0x0) //JALR
                            instr_jalr(rd, rs1, imm);
                        else {
                            std::cerr << "illegal instruction" << std::endl;
                            exit(1);
                        }
                        break; 

        case 0b1110011: //ecall & ebreak
                        if (funct_3 == 0x0 && imm == 0x0) //ecall
                            instr_ecall();
                        else if (funct_3 == 0x0 && imm == 0x1) //ebreak
                            instr_ebreak();
                        else {
                            std::cerr << "illegal instruction" << std::endl;
                            exit(1);
                        }
                        break;
        default: break;
    }
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::decode_S_type()
{
    uint8_t funct_3 = (this->current_instr & 0x7000) >> 12;
    uint8_t rs1 = (this->current_instr & 0xF8000) >> 15;
    uint8_t rs2 = (this->current_instr & 0x1F00000) >> 20;
    uint32_t imm = ((this->current_instr & 0xF80) >> 7) | ((this->current_instr & 0xFE000000) >> 20);

    if (imm & 0x800)
        imm |= 0xFFFFF000;

    if (funct_3 == 0x0) //STORE BYTE
        instr_sb(rs1, rs2, imm);
    else if (funct_3 == 0x1) //STORE HALF
        instr_sh(rs1, rs2, imm);
    else if (funct_3 == 0x2) //STORE WORD
        instr_sw(rs1, rs2, imm);
    else {
        std::cerr << "illegal instruction" << std::endl;
        exit(1);
    }
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::decode_B_type()
{
    uint8_t funct_3 = (this->current_instr & 0x7000) >> 12;
    uint8_t rs1 = (this->current_instr & 0xF8000) >> 15;
    uint8_t rs2 = (this->current_instr & 0x1F00000) >> 20;
    uint32_t imm = (this->current_instr & 0xF00) >> 7 | (this->current_instr & 0x7E000000) >> 20 | (this->current_instr & 0x80) << 4 | (this->current_instr & 0x80000000) >> 19;

    if (imm & 0x1000) //signed 13bits (12-0) 0 ignored
        imm |= 0xFFFFE000;


    if (funct_3 == 0x0) //BEQ
        instr_beq(rs1, rs2, imm);
    else if (funct_3 == 0x1) //Bne
        instr_bne(rs1, rs2, imm);
    else if (funct_3 == 0x4) //BLT
        instr_blt(rs1, rs2, imm);
    else if (funct_3 == 0x5) //BGE
        instr_bge(rs1, rs2, imm);
    else if (funct_3 == 0x6) //BLTU
        instr_bltu(rs1, rs2, imm);
    else if (funct_3 == 0x7) //BGEU
        instr_bgeu(rs1, rs2, imm);
    else {
        std::cerr << "illegal instruction" << std::endl;
        exit(1);
    }
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::decode_U_type()
{
    uint8_t rd = (this->current_instr & 0xF80) >> 7;
    uint32_t imm = (this->current_instr & 0xFFFFF000);

    if (this->opcode == 0b0110111) //LUI
        instr_lui(rd, imm);
    else if (this->opcode == 0b0010111) //AUIPC
        instr_auipc(rd, imm);
    else {
        std::cerr << "illegal instruction" << std::endl;
        exit(1);
    }
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::decode_J_type()
{
    uint8_t rd = (this->current_instr & 0xF80) >> 7;
    uint32_t imm = ((this->current_instr & 0x7FE00000) >> 20) | ((this->current_instr & 0x100000) >> 9) | (this->current_instr & 0xFF000) | ((this->current_instr & 0x80000000) >> 11);

    if (imm & 0x100000) //negative number signed in bit 20 (20:1)
        imm |= 0xFFE00000;

    //JAL instruction
    instr_jal(rd, imm);
}

