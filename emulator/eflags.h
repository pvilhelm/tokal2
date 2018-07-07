#pragma once

#include <cinttypes>

namespace emul {

class Eflags
{
    public:
        uint32_t value = 2U;

        bool get_carry(){return value & 0x1U;}
        void set_carry(){value |= 0x1U;}
        void clear_carry(){value &= ~0x1U;}

        bool get_parity(){return value & (1U << 2); }
        void set_parity(){value |= 1U << 2;}
        void clear_parity(){value &= ~(1U << 2);}

        bool get_auxcarry() { return value & (1U << 4); }
        void set_auxcarry() { value |= 1U << 4; }
        void clear_auxcarry() { value &= ~(1U << 4); }

        bool get_zero() { return value & (1U << 6); }
        void set_zero() { value |= 1U << 6; }
        void clear_zero() { value &= ~(1U << 6); }

        bool get_sign() { return value & (1U << 7); }
        void set_sign() { value |= 1U << 7; }
        void clear_sign() { value &= ~(1U << 7); }
        
        bool get_trap() { return value & (1U << 8); }
        void set_trap() { value |= 1U << 8; }
        void clear_trap() { value &= ~(1U << 8); }

        bool get_intenable() { return value & (1U << 9); }
        void set_intenable() { value |= 1U << 9; }
        void clear_intenable() { value &= ~(1U << 9); }
        
        bool get_direction() { return value & (1U << 10); }
        void set_direction() { value |= 1U << 10; }
        void clear_direction() { value &= ~(1U << 10); }
        
        bool get_overflow() { return value & (1U << 11); }
        void set_overflow() { value |= 1U << 11; }
        void clear_overflow() { value &= ~(1U << 11); }

        bool get_ioprivilege_l() { return value & (1U << 12); }
        void set_ioprivilege_l() { value |= 1U << 12; }
        void clear_ioprivilege_l() { value &= ~(1U << 12); }

        bool get_ioprivilege_h() { return value & (1U << 13); }
        void set_ioprivilege_h() { value |= 1U << 13; }
        void clear_ioprivilege_h() { value &= ~(1U << 13); }

        bool get_nestedtask() { return value & (1U << 14); }
        void set_nestedtask() { value |= 1U << 14; }
        void clear_nestedtask() { value &= ~(1U << 14); }

        bool get_resume() { return value & (1U << 16); }
        void set_resume() { value |= 1U << 16; }
        void clear_resume() { value &= ~(1U << 16); }

        bool get_virtualmode() { return value & (1U << 17); }
        void set_virtualmode() { value |= 1U << 17; }
        void clear_virtualmode() { value &= ~(1U << 17); }

        bool get_aligncheck() { return value & (1U << 18); }
        void set_aligncheck() { value |= 1U << 18; }
        void clear_aligncheck() { value &= ~(1U << 18); }

        bool get_virtualint() { return value & (1U << 19); }
        void set_virtualint() { value |= 1U << 19; }
        void clear_virtualint() { value &= ~(1U << 19); }

        bool get_virtualint_pending() { return value & (1U << 20); }
        void set_virtualint_pending() { value |= 1U << 20; }
        void clear_virtualint_pending() { value &= ~(1U << 20); }

        bool get_id() { return value & (1U << 21); }
        void set_id() { value |= 1U << 21; }
        void clear_id() { value &= ~(1U << 21); }
    private:
};

}