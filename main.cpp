#include "cpu.hpp"
#include <iostream>

int main(int ac, char** av)
{
    if (ac != 2) {
        std::cerr << "[error] : arguments" << std::endl;
        return 1;
    }

    Riscv32i<UINT32_MAX + 1> cpu {};
    cpu.run();

    return 0;
}
