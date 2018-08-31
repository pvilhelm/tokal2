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
}