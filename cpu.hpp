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
        void run(std::span program);

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
        void instr_add();
        void instr_sub();
        void instr_xor();
        void instr_or();
        void instr_and();
        void instr_sll();
        void instr_srl();
        void instr_sra();
        void instr_slt();
        void instr_sltu();

        void instr_addi(uint8_t rs1, uint8_t rd, uint32_t imm);
        void instr_xori(uint8_t rs1, uint8_t rd, uint32_t imm);
        void instr_ori(uint8_t rs1, uint8_t rd, uint32_t imm);
        void instr_andi(uint8_t rs1, uint8_t rd, uint32_t imm);
        void instr_slli();
        void instr_srli();
        void instr_srai();
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

        void instr_lui();
        void instr_auipc();

        void instr_ecall();
        void instr_ebreak();
};

#include "cpu.tpp"
#include "cpu_fdx.tpp"
#include "cpu_instr.tpp"

#endif //__RISCV32I_HPP__