#include "instruction_decoder.h"


bool emul_NS::prefixes_NS::is_legacy_prefix(uint8_t byte)
{
    using namespace emul_NS;
    using namespace emul_NS::prefixes_NS;
    
    auto el = set_of_prefixes.find(byte);
    bool ans = el != set_of_prefixes.cend();
    
    return ans;
}

bool emul_NS::rex_NS::is_REX_byte(uint8_t byte)
{
    return byte <= 0x4F && byte >= 0x40;
}

emul_NS::rex_NS::Rex emul_NS::rex_NS::rex_from_named_bits(bool W, bool R, bool X, bool B)
{
    uint8_t value = 0b01000000U | ((uint8_t)W << 3) | ((uint8_t)R << 2) | ((uint8_t)X << 1) | ((uint8_t)B);

    return emul_NS::rex_NS::Rex(value);
}

emul_NS::rex_NS::Rex::Rex()
{
    value = 0b01000000U;
}

emul_NS::rex_NS::Rex::Rex(uint8_t byte)
{
    value = byte;
}

bool emul_NS::rex_NS::Rex::get_W()
{
    return value & 0b1000U;
}

bool emul_NS::rex_NS::Rex::get_R()
{
    return value & 0b100U;
}

bool emul_NS::rex_NS::Rex::get_X()
{
    return value & 0b10U;
}

bool emul_NS::rex_NS::Rex::get_B()
{
    return value & 0b1U;
}

emul_NS::decode_instruction_NS::Instruction 
emul_NS::decode_instruction_NS::decode_instruction(std::vector<uint8_t>::const_iterator instruction_start, std::vector<uint8_t>::const_iterator instructionbuffer_end)
{
    using namespace emul_NS;
    using namespace decode_instruction_NS;

    Instruction resulting_instruction{instruction_start,instructionbuffer_end, opcode_NS::INVALID_INSTRUCTION_E};
    uint32_t n = 0;

    auto iter_tmp = instruction_start;

    while(n < 15 && iter_tmp == instructionbuffer_end) {
        auto byte = *iter_tmp;
        if(prefixes_NS::is_legacy_prefix(byte))
            iter_tmp++, n++;
        else
            break;
    }

    if(n == 15 || iter_tmp == instructionbuffer_end){ /* Can't be 15 prefixes */
        return resulting_instruction;
    }

    if(rex_NS::is_REX_byte(*iter_tmp)) /* After prefixes there an optional REX byte */
        iter_tmp++, n++;
    
    if(n == 15 || iter_tmp == instructionbuffer_end) { /* Need an OP code too */
        return resulting_instruction;
    }

    if(opcode_NS::twobyte_opcode_first_byte == *iter_tmp) { /* It's a two byte opcode instruction */
        if(++n == 15 || iter_tmp == instructionbuffer_end) { /* Need an second OP code too */
            return resulting_instruction;
        }
        auto opcode_E = opcode_NS::as_2b_opcode(*++iter_tmp);
        if(opcode_E != opcode_NS::INVALID_INSTRUCTION_E) /* It's not a valid opcode byte */
            resulting_instruction.op_type_E = opcode_E;
    } else { /* It's one or three bytes */
        auto opcode_E = opcode_NS::as_1b_opcode(*iter_tmp);
        if(opcode_E != opcode_NS::INVALID_INSTRUCTION_E) /* It's not a valid opcode byte */
            resulting_instruction.op_type_E = opcode_E;
        else
            ; /* TODO: 3byte opcodes here */
    }

    return resulting_instruction;
}

emul_NS::opcode_NS::GROUPING_OPCODE_Es emul_NS::opcode_NS::as_1b_opcode(uint8_t byte)
{
    auto pair = opcode_NS::map_byte_to_opcode1b_group.find(byte);
    return pair != opcode_NS::map_byte_to_opcode1b_group.cend() ? pair->second : emul_NS::opcode_NS::INVALID_INSTRUCTION_E;
}

emul_NS::opcode_NS::GROUPING_OPCODE_Es emul_NS::opcode_NS::as_2b_opcode(uint8_t second_byte)
{
    auto pair = opcode_NS::map_byte_to_opcode2b_group.find(second_byte);
    return pair != opcode_NS::map_byte_to_opcode2b_group.cend() ? pair->second : emul_NS::opcode_NS::INVALID_INSTRUCTION_E;
}

uint8_t emul_NS::modrm_NS::get_mod_bf(uint8_t modrm_byte)
{
    return (modrm_byte & 0b11000000U) >> 6U;
}

uint8_t emul_NS::modrm_NS::get_rm_bf(uint8_t modrm_byte)
{
    return (modrm_byte & 0b111U);
}

uint8_t emul_NS::modrm_NS::get_reg_bf(uint8_t modrm_byte)
{
    return (modrm_byte & 0b111000U) >> 3;
}
