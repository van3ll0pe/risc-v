#pragma once
#ifndef __RISCV32I_HPP__
#define __RISCV32I_HPP__

#include "memory.hpp"
#include <memory>
#include <span>

template<uint64_t MEMORY_SIZE>
class Riscv32i {
    private:
        std::unique_ptr<Memory<MEMORY_SIZE>> memory_bus;
        std::array<uint32_t, 32> reg_x;
        uint32_t program_counter;
        uint32_t current_instr;
        uint32_t current_address;
        uint8_t opcode;

    public:
        Riscv32i(uint32_t start_address = 0x0);
        ~Riscv32i();
        void run();

    private: //fetch - decode - execute
        void fetch(); //get opcode
        void decode_general();
        void decode_R_type();
        void decode_I_type();
        void decode_S_type();
        void decode_B_type();
        void decode_U_type();
        void decode_J_type();
        void execute();
        void reset_x0();


    private: //all instructions of riscv32i
        void instr_add(uint8_t rd, uint8_t rs1, uint8_t rs2);
        void instr_sub(uint8_t rd, uint8_t rs1, uint8_t rs2);
        void instr_xor(uint8_t rd, uint8_t rs1, uint8_t rs2);
        void instr_or(uint8_t rd, uint8_t rs1, uint8_t rs2);
        void instr_and(uint8_t rd, uint8_t rs1, uint8_t rs2);
        void instr_sll(uint8_t rd, uint8_t rs1, uint8_t rs2);
        void instr_srl(uint8_t rd, uint8_t rs1, uint8_t rs2);
        void instr_sra(uint8_t rd, uint8_t rs1, uint8_t rs2);
        void instr_slt(uint8_t rd, uint8_t rs1, uint8_t rs2);
        void instr_sltu(uint8_t rd, uint8_t rs1, uint8_t rs2);

        void instr_addi(uint8_t rs1, uint8_t rd, uint32_t imm);
        void instr_xori(uint8_t rs1, uint8_t rd, uint32_t imm);
        void instr_ori(uint8_t rs1, uint8_t rd, uint32_t imm);
        void instr_andi(uint8_t rs1, uint8_t rd, uint32_t imm);
        void instr_slli(uint8_t rs1, uint8_t rd, uint8_t shamt);
        void instr_srli(uint8_t rs1, uint8_t rd, uint8_t shamt);
        void instr_srai(uint8_t rs1, uint8_t rd, uint8_t shamt);
        void instr_slti(uint8_t rs1, uint8_t rd, uint32_t imm);
        void instr_sltiu(uint8_t rs1, uint8_t rd, uint32_t imm);

        void instr_lb();
        void instr_lh();
        void instr_lw();
        void instr_lbu();
        void instr_lhu();

        void instr_sb();
        void instr_sh();
        void instr_sw();

        void instr_beq();
        void instr_bne();
        void instr_blt();
        void instr_bge();
        void instr_bltu();
        void instr_bgeu();

        void instr_jal();
        void instr_jalr();

        void instr_lui(uint8_t rd, uint32_t imm);
        void instr_auipc(uint8_t rd, uint32_t imm);

        void instr_ecall();
        void instr_ebreak();
};

#endif //__RISCV32I_HPP__