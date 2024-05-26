#include "cpu.hpp"

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::fetch()
{
    this->current_instr = 0x0;

    this->current_address = this->program_counter;

    //little endian extraction
    for (int i = 0; i < 4; i++) {
        this->current_instr += (this->memory_bus->read(this->program_counter) << (8 * i));
        this->program_counter++;
    }
    //program_counter ready to read the next instruction

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
    else if (funct_3 == 0x0 && funct_7 == 0x20) //SUB
    else if (funct_3 == 0x4 && funct_7 == 0x0) //XOR
    else if (funct_3 == 0x6 && funct_7 == 0x0) //OR
    else if (funct_3 == 0x7 && funct_7 == 0x0) //AND
    else if (funct_3 == 0x1 && funct_7 == 0x0) //SLL
    else if (funct_3 == 0x5 && funct_7 == 0x0) //SRL
    else if (funct_3 == 0x5 && funct_7 == 0x20) //SRA
    else if (funct_3 == 0x2 && funct_7 == 0x0) //SLT
    else if (funct_3 == 0x3 && funct_7 == 0x0) //SLTU
    
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::decode_I_type()
{
    uint8_t rd = (this->current_instr & 0xFFF00000) >> 7;
    uint8_t funct_3 = (this->current_instr & 0x7000) >> 12;
    uint8_t rs1 = (this->current_instr & 0xF8000) >> 15;
    uint32_t imm = (this->current_instr & 0xFFF00000) >> 20;

    if (imm & 0x800) //negative number signed 12 bits (11:0) signed in bit 11
        imm |= 0xFFFFF000;

    switch(this->opcode) {
        case 0b0010011:  //calcul immediate operation
                        if (funct_3 == 0x0) //ADDI
                        else if (funct_3 == 0x1 && ((imm11_0 & 0xFE0)) == 0x0) //SLLI
                        else if (funct_3 == 0x2) //SLTI
                        else if (funct_3 == 0x3) //SLTI U
                        else if (funct_3 == 0x4) //XORI
                        else if (funct_3 == 0x5 && ((imm11_0 & 0xFE0)) == 0x0) // SRLI
                        else if (funct_3 == 0x5 && ((imm11_0 & 0xFE0)) == 0x20) // SRAI
                        else if (funct_3 == 0x6) //ORI
                        else if (funct_3 == 0x7) //ANDI
                        
                        break;

        case 0b0000011: //load operation
                        if (funct_3 == 0x0) //LOAD BYTE
                        else if (funct_3 == 0x1) ///LOAD HALF
                        else if (funct_3 == 0x2) //LOAD WORD
                        else if (funct_3 == 0x4) //LOAD BYTE U
                        else if (funct_3 == 0x5) //LOAD HALF U
                       
                        break;

        case 0b1100111: //jump and link reg
                        if (funct_3 == 0x0) //JALR

                        break; 

        case 0b1110011: //ecall & ebreak
                        if (funct_3 == 0x0 && imm11_0 == 0x0) //ecall
                        else if (funct_3 == 0x0 && imm11_0 == 0x1) //ebreak

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
    else if (funct_3 == 0x1) //STORE HALF
    else if (funct_3 == 0x2) //STORE WORD
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
    else if (funct_3 == 0x1) //Bne
    else if (funct_3 == 0x4) //BLT
    else if (funct_3 == 0x5) //BGE
    else if (funct_3 == 0x6) //BLTU
    else if (funct_3 == 0x7) //BGEU
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::decode_U_type()
{
    uint8_t rd = (this->current_instr & 0xF80) >> 7;
    uint32_t imm = (this->current_instr & 0xFFFFF000);

    if (this->opcode == 0b0110111) //LUI
    else if (this->opcode == 0b0010111) //AUIPC
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
}

