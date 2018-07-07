#include "catch.hpp"

#include "eflags.h"

TEST_CASE("eflags test")
{ 
    
    using namespace emul;

    auto BITGET = [](Eflags f, uint32_t n) {return ((f.value) & (1 << (n)) ? 1 : 0);};

    SECTION("Test default value")
    {
        Eflags f;
        REQUIRE(f.value == 2);
    }

    SECTION("Carry register")
    {
        {
            Eflags f;
            REQUIRE(f.get_carry() == 0);
            f.set_carry();
            REQUIRE(BITGET(f, 1) == 1);
            REQUIRE((f.value & ~1) == 2);
            REQUIRE(f.get_carry()  == 1);
            f.clear_carry();
            REQUIRE(f.get_carry() == 0);

        }
    }

    SECTION("Parity flag")
    {
        {
            Eflags f;
            REQUIRE(f.get_parity() == 0);
            f.set_parity();
            REQUIRE(BITGET(f, 2) == 1);
            REQUIRE((f.value & ~(1<<2)) == 2);
            REQUIRE(f.get_parity() == 1);
            f.clear_parity();
            REQUIRE(f.get_parity() == 0);

        }
    }

    SECTION("Auxiliary carry flag")
    {
        {
            Eflags f;
            REQUIRE(f.get_auxcarry() == 0);
            f.set_auxcarry();
            REQUIRE(BITGET(f, 4) == 1);
            REQUIRE((f.value & ~(1<<4)) == 2);
            REQUIRE(f.get_auxcarry() == 1);
            f.clear_auxcarry();
            REQUIRE(f.get_auxcarry() == 0);
        }
    }

    SECTION("Zero flag")
    {
        {
            Eflags f;
            REQUIRE(f.get_zero() == 0);
            f.set_zero();
            REQUIRE(BITGET(f, 6) == 1);
            REQUIRE((f.value & ~(1<<6)) == 2);
            REQUIRE(f.get_zero() == 1);
            f.clear_zero();
            REQUIRE(f.get_zero() == 0);
        }
    }

    SECTION("Sign flag")
    {
        {
            Eflags f;
            REQUIRE(f.get_sign() == 0);
            f.set_sign();
            REQUIRE(BITGET(f, 7) == 1);
            REQUIRE((f.value & ~(1 << 7)) == 2);
            REQUIRE(f.get_sign() == 1);
            f.clear_sign();
            REQUIRE(f.get_sign() == 0);
        }
    }
}