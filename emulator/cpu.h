#pragma once

#include <string>
#include <cinttypes>
#include "eflags.h"

namespace emul{

class Cpu
{
    public:
        std::string as_dbg_string();
        std::string regs_dbg_string();


        const size_t n_regs = sizeof(gp_regs) / sizeof(gp_regs[0]);

        uint64_t &RAX = gp_regs[0];
        uint64_t &RCX = gp_regs[1];
        uint64_t &RDX = gp_regs[2];
        uint64_t &RBX = gp_regs[3];
        uint64_t &RSP = gp_regs[4];
        uint64_t &RBP = gp_regs[5];
        uint64_t &RSI = gp_regs[6];
        uint64_t &RDI = gp_regs[7];
        uint64_t &R8 = gp_regs[8];
        uint64_t &R9 = gp_regs[9];
        uint64_t &R10 = gp_regs[10];
        uint64_t &R11 = gp_regs[11];
        uint64_t &R12 = gp_regs[12];
        uint64_t &R13 = gp_regs[13];
        uint64_t &R14 = gp_regs[14];
        uint64_t &R15 = gp_regs[15];

        Eflags EFLAGS;
    private:

        uint64_t gp_regs[16];
        uint64_t EIP; /* Instruction pointer */
        uint64_t RIP; /* Relative instruction pointer */
        uint64_t FLAGS; 

};

}