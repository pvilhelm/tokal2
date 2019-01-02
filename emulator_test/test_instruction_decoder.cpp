#include <map>

#include "catch.hpp"
#include "instruction_decoder.h"

TEST_CASE("Instructioner decoder")
{
    using namespace emul_NS;
    SECTION("Legacy prefixes_NS")
    {
        {/* Testa om har 0x26 funkar */
            REQUIRE(prefixes_NS::set_of_prefixes.find(prefixes_NS::LEGACY_PREFIXES_Es::NULL_PREFIX_CS_E) != prefixes_NS::set_of_prefixes.cend());
        }
    }

    SECTION("prefixes_NS::is_legacy_prefix")
    {
        using namespace emul_NS::prefixes_NS;
        
        REQUIRE(is_legacy_prefix(0xF0));
    }

    SECTION("rex_NS::is_REX_byte()")
    {
        using namespace emul_NS::rex_NS;
        REQUIRE(is_REX_byte(0x44));
        REQUIRE(!is_REX_byte(0x50));
    }

    SECTION("rex_NS::rex_from_named_bits")
    {
        using namespace emul_NS::rex_NS;

        Rex r = rex_from_named_bits(1,1,0,0);
        REQUIRE(r.value == 0b01001100U);
        r = rex_from_named_bits(0, 0, 0, 0);
        REQUIRE(r.value == 0b01000000U);
        r = rex_from_named_bits(0, 0, 1, 1);
        REQUIRE(r.value == 0b01000011U);
    }

    SECTION("opcode_NS::map_byte_to_opcode1b_group")
    {
        using namespace emul_NS::opcode_NS;

        auto el = map_byte_to_opcode1b_group.find(0x2U);
        REQUIRE(el->second == GROUPING_OPCODE_Es::ADD_E);
        el = map_byte_to_opcode1b_group.find(0x80U);
        REQUIRE(el->second == GROUPING_OPCODE_Es::IMMIDIATE_GROUP_1_E);
    }

    SECTION("decode_instruction()")
    {
        {
            using namespace emul_NS;
            using namespace decode_instruction_NS;

            std::vector<uint8_t> test {0x8BU, 0x45U, 0x24U}; /* mov eax, dword ptr [b]*/

            Instruction ans = decode_instruction(test.cbegin(),test.cend());

            REQUIRE(ans.op_type_E == opcode_NS::MOV_E);
        }
        {
            using namespace emul_NS;
            using namespace decode_instruction_NS;

            std::vector<uint8_t> test{0x03,0xC8}; /* add ecx,eax */

            Instruction ans = decode_instruction(test.cbegin(), test.cend());

            REQUIRE(ans.op_type_E == opcode_NS::ADD_E);
        }
        {
            using namespace emul_NS;
            using namespace decode_instruction_NS;

            std::vector<uint8_t> test{0x0F, 0xAF, 0x45, 0x24}; /* imul eax,dword ptr [b] */

            Instruction ans = decode_instruction(test.cbegin(), test.cend());

            REQUIRE(ans.op_type_E == opcode_NS::IMUL_E);
        }
        {
            using namespace emul_NS;
            using namespace decode_instruction_NS;

            std::vector<uint8_t> test{0xF7, 0x7D, 0x24}; /* idiv eax,dword ptr [b] */

            Instruction ans = decode_instruction(test.cbegin(), test.cend());

            REQUIRE(ans.op_type_E == opcode_NS::UNARY_GROUP_3_E);
        }
        {
            using namespace emul_NS;
            using namespace decode_instruction_NS;

            std::vector<uint8_t> test{0xD3, 0xE0}; /* shl eax,cl */

            Instruction ans = decode_instruction(test.cbegin(), test.cend());

            REQUIRE(ans.op_type_E == opcode_NS::SHIFT_GROUP_2_E);
        }
        {
            using namespace emul_NS;
            using namespace decode_instruction_NS;

            std::vector<uint8_t> test{0x36, 0x36}; /* two prefixes */

            Instruction ans = decode_instruction(test.cbegin(), test.cend());

            REQUIRE(ans.op_type_E == opcode_NS::INVALID_INSTRUCTION_E);
        }
    }

    SECTION("decode modR/M byte")
    {
        using namespace emul_NS;
        using namespace decode_instruction_NS;

        {
            uint8_t rex_byte = 0;
            uint8_t modrm_byte = 00;

            auto [reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = 0;
            uint8_t modrm_byte = 0x08;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::C_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = 0;
            uint8_t modrm_byte = 0x10;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::D_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = 0;
            uint8_t modrm_byte = 0x18;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::B_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = 0;
            uint8_t modrm_byte = 0x20;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::SP_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = 0;
            uint8_t modrm_byte = 0x28;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::BP_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = 0;
            uint8_t modrm_byte = 0x30;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::SI_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = 0;
            uint8_t modrm_byte = 0x38;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::DI_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        //rex.B = 1
        {
            uint8_t rex_byte = 0b0100'0100;
            uint8_t modrm_byte = 00;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::R8_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = 0b0100'0100;
            uint8_t modrm_byte = 0x08;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::R9_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = 0b0100'0100;
            uint8_t modrm_byte = 0x10;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::R10_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = 0b0100'0100;
            uint8_t modrm_byte = 0x18;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::R11_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = 0b0100'0100;
            uint8_t modrm_byte = 0x20;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::R12_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = 0b0100'0100;
            uint8_t modrm_byte = 0x28;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::R13_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = 0b0100'0100;
            uint8_t modrm_byte = 0x30;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::R14_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = 0b0100'0100;
            uint8_t modrm_byte = 0x38;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::R15_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }


        //
        {
            uint8_t rex_byte = 0;
            uint8_t modrm_byte = 00;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = 0;
            uint8_t modrm_byte = 0x49;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::C_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::C_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_8_E);
        }
        {
            uint8_t rex_byte = 0;
            uint8_t modrm_byte = 0x8A;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::C_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::D_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_32_E);
        }
        {
            uint8_t rex_byte = 0;
            uint8_t modrm_byte = 0x1B;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::B_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::B_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = 0;
            uint8_t modrm_byte = 0x24;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::SP_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::SIB_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = 0;
            uint8_t modrm_byte = 0x2D;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::BP_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::IP_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = 0;
            uint8_t modrm_byte = 0x36;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::SI_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::SI_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = 0;
            uint8_t modrm_byte = 0x3f;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::DI_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::DI_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        //rex.B = 1 rex.R = 1
        {
            uint8_t rex_byte = rex_NS::rex_from_named_bits(false, true, false, true).value;
            uint8_t modrm_byte = 00;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::R8_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::R8_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = rex_NS::rex_from_named_bits(false, true, false, true).value;
            uint8_t modrm_byte = 0x09;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::R9_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::R9_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = rex_NS::rex_from_named_bits(false, true, false, true).value;
            uint8_t modrm_byte = 0x12;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::R10_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::R10_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = rex_NS::rex_from_named_bits(false, true, false, true).value;
            uint8_t modrm_byte = 0x1b;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::R11_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::R11_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = rex_NS::rex_from_named_bits(false, true, false, true).value;
            uint8_t modrm_byte = 0x24;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::R12_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::SIB_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = rex_NS::rex_from_named_bits(false, true, false, true).value;
            uint8_t modrm_byte = 0x2D;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::R13_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::IP_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = rex_NS::rex_from_named_bits(false, true, false, true).value;
            uint8_t modrm_byte = 0x36;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::R14_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::R14_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        {
            uint8_t rex_byte = rex_NS::rex_from_named_bits(false, true, false, true).value;
            uint8_t modrm_byte = 0x3f;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::R15_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::R15_GROUP_E);
            REQUIRE(effective_address);
            REQUIRE(disp == MODRM_DISP_Es::disp_0_E);
        }
        /////////////////////////////////////////////
        {
            uint8_t rex_byte = rex_NS::rex_from_named_bits(false, false, false, false).value;
            uint8_t modrm_byte = 0xc0;

            auto[reg, mod, disp, effective_address] = decode_modrm_and_rex(rex_byte, modrm_byte);
            REQUIRE(reg == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(mod == MODRM_SRC_DST_GROUP_Es::A_GROUP_E);
            REQUIRE(effective_address == false);
            REQUIRE(disp == MODRM_DISP_Es::INVALID_DISP_E);
        }

    }
}