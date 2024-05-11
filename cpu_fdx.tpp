#include "cpu.hpp"

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::fetch()
{
    this->current_instr = 0x0;

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
        case 0b0110011: this->decode_R_type();
                        break; //R
        case 0b0010011: this->decode_I_type();
                        break; //I
        case 0b0000011: this->decode_I_type();
                        break; //I
        case 0b0100011: this->decode_S_type();
                        break; //S
        case 0b1100011: this->decode_B_type();
                        break; //B
        case 0b1101111: this->decode_J_type();
                        break; //J
        case 0b1100111: this->decode_I_type();
                        break; //I
        case 0b0110111: this->decode_U_type();
                        break; //U
        case 0b0010111: this->decode_U_type();
                        break; //U
        case 0b1110011: this->decode_I_type();
                        break; //I
        default: break;
    }
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::decode_R_type()
{
    uint8_t rd = (this->current_instr & 0b111110000000) >> 7;
    uint8_t funct_3 = (this->current_instr & 0b111000000000000) >> 12;
    uint8_t rs1 = (this->current_instr & 0b11111000000000000000) >> 15;
    uint8_t rs2 = (this->current_instr & 0b1111100000000000000000000) >> 20;
    uint8_t funct_7 = (this->current_instr & 0b11111110000000000000000000000000) >> 25;

    switch (funct_3) {
        case 0x0:   //ADD or SUB
                    if (funct_7 == 0x00) // ADD
                    else if (funct_7 == 0x20) // SUB
                    break;
        case 0x1:   break; // SLL
        case 0x2:   break; // SLT
        case 0x3:   break; //SLTU
        case 0x4:   break; // XOR
        case 0x5:   // SRL or SRA
                    if (funct_7 == 0x00) // SRL
                    else if (funct_7 == 0x20) // SRA
                    break;
        case 0x6:   break; // OR
        case 0x7:   break; //AND
        default :   break;
    }
}

template<uint64_t MEMORY_SIZE>
void
Riscv32i<MEMORY_SIZE>::decode_I_type()
{
    
}