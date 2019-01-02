#include "instruction_decoder.h"
#include <exception>
/** @file test */

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
    if(!rex_NS::is_REX_byte(byte)) {
        throw std::runtime_error("Byte is not rex prefix byte");
    }
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

    if(rex_NS::is_REX_byte(*iter_tmp)) /* After prefixes there is an optional REX byte */
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

std::tuple<emul_NS::decode_instruction_NS::MODRM_SRC_DST_GROUP_Es /*target*/, 
           emul_NS::decode_instruction_NS::MODRM_SRC_DST_GROUP_Es /*source */, 
           emul_NS::decode_instruction_NS::MODRM_DISP_Es /* displacement */,
           bool /*rm_is_effective_address */>
emul_NS::decode_instruction_NS::decode_modrm_and_rex(uint8_t rex_byte, uint8_t modrm_byte)
{
    using namespace emul_NS;
    using namespace decode_instruction_NS;
    using namespace rex_NS;

    /* Output temps */
    MODRM_SRC_DST_GROUP_Es reg_group = MODRM_SRC_DST_GROUP_Es::INVALID_GROUP_E;
    MODRM_SRC_DST_GROUP_Es rm_group = MODRM_SRC_DST_GROUP_Es::INVALID_GROUP_E;
    MODRM_DISP_Es disp_group = MODRM_DISP_Es::INVALID_DISP_E;
    bool rm_is_effective_address = false;

    uint8_t rm = modrm_NS::get_rm_bf(modrm_byte);
    uint8_t reg = modrm_NS::get_reg_bf(modrm_byte);
    uint8_t mod = modrm_NS::get_mod_bf(modrm_byte);
    
    /* Validate rex_byte */
    if(rex_byte)/* A zero means no rex byte */
        if(!rex_NS::is_REX_byte(rex_byte))
            return std::make_tuple(reg_group, rm_group, MODRM_DISP_Es::INVALID_DISP_E, false);

    Rex rex;
    if(rex_byte)
        rex = Rex(rex_byte);


    uint8_t rreg = reg + (rex.get_R() << 3); // rex.R is an extension bit to reg
    switch(rreg) {
        case 0:
            reg_group = MODRM_SRC_DST_GROUP_Es::A_GROUP_E;
            break;
        case 1:
            reg_group = MODRM_SRC_DST_GROUP_Es::C_GROUP_E;
            break;
        case 2:
            reg_group = MODRM_SRC_DST_GROUP_Es::D_GROUP_E;
            break;
        case 3:
            reg_group = MODRM_SRC_DST_GROUP_Es::B_GROUP_E;
            break;
        case 4:
            reg_group = MODRM_SRC_DST_GROUP_Es::SP_GROUP_E;
            break;
        case 5:
            reg_group = MODRM_SRC_DST_GROUP_Es::BP_GROUP_E;
            break;
        case 6:
            reg_group = MODRM_SRC_DST_GROUP_Es::SI_GROUP_E;
            break;
        case 7:
            reg_group = MODRM_SRC_DST_GROUP_Es::DI_GROUP_E;
            break;
        case 8:
            reg_group = MODRM_SRC_DST_GROUP_Es::R8_GROUP_E;
            break;
        case 9:
            reg_group = MODRM_SRC_DST_GROUP_Es::R9_GROUP_E;
            break;
        case 10:
            reg_group = MODRM_SRC_DST_GROUP_Es::R10_GROUP_E;
            break;
        case 11:
            reg_group = MODRM_SRC_DST_GROUP_Es::R11_GROUP_E;
            break;
        case 12:
            reg_group = MODRM_SRC_DST_GROUP_Es::R12_GROUP_E;
            break;
        case 13:
            reg_group = MODRM_SRC_DST_GROUP_Es::R13_GROUP_E;
            break;
        case 14:
            reg_group = MODRM_SRC_DST_GROUP_Es::R14_GROUP_E;
            break;
        case 15:
            reg_group = MODRM_SRC_DST_GROUP_Es::R15_GROUP_E;
            break;
        default:
            throw std::runtime_error("Reg byte not a reg value:" + std::to_string(reg));
    }
    
    uint8_t brm = rm + (rex.get_B() << 3); // rex.B is an extension bit to rm
    switch(brm) {
        case 0:
            rm_group = MODRM_SRC_DST_GROUP_Es::A_GROUP_E;
            break;
        case 1:
            rm_group = MODRM_SRC_DST_GROUP_Es::C_GROUP_E;
            break;
        case 2:
            rm_group = MODRM_SRC_DST_GROUP_Es::D_GROUP_E;
            break;
        case 3:
            rm_group = MODRM_SRC_DST_GROUP_Es::B_GROUP_E;
            break;
        case 4:
            rm_group = MODRM_SRC_DST_GROUP_Es::SIB_E;
            break;
        case 5:
            if(mod == 0)
                rm_group = MODRM_SRC_DST_GROUP_Es::IP_GROUP_E;
            else 
                rm_group = MODRM_SRC_DST_GROUP_Es::BP_GROUP_E;
            break;
        case 6:
            rm_group = MODRM_SRC_DST_GROUP_Es::SI_GROUP_E;
            break;
        case 7:
            rm_group = MODRM_SRC_DST_GROUP_Es::DI_GROUP_E;
            break;
        case 8:
            rm_group = MODRM_SRC_DST_GROUP_Es::R8_GROUP_E;
            break;
        case 9:
            rm_group = MODRM_SRC_DST_GROUP_Es::R9_GROUP_E;
            break;
        case 10:
            rm_group = MODRM_SRC_DST_GROUP_Es::R10_GROUP_E;
            break;
        case 11:
            rm_group = MODRM_SRC_DST_GROUP_Es::R11_GROUP_E;
            break;
        case 12:
            rm_group = MODRM_SRC_DST_GROUP_Es::SIB_E;
            break;
        case 13:
            if(mod == 0)
                rm_group = MODRM_SRC_DST_GROUP_Es::IP_GROUP_E;
            else
                rm_group = MODRM_SRC_DST_GROUP_Es::R13_GROUP_E;
            break;
        case 14:
            rm_group = MODRM_SRC_DST_GROUP_Es::R14_GROUP_E;
            break;
        case 15:
            rm_group = MODRM_SRC_DST_GROUP_Es::R15_GROUP_E;
            break;
        default:
            throw std::runtime_error("R/M byte not a R/M value:" + std::to_string(rm));
    }

    if(mod != 0b11)
        rm_is_effective_address = true;
    
    switch(mod) {
        case 0:
            disp_group = MODRM_DISP_Es::disp_0_E;
            break;
        case 1:
            disp_group = MODRM_DISP_Es::disp_8_E;
            break;
        case 2:
            disp_group = MODRM_DISP_Es::disp_32_E;
            break;
        case 3:
            disp_group = MODRM_DISP_Es::INVALID_DISP_E;
            break;
        default:
            throw std::runtime_error("Mod byte not a Mod value:" + std::to_string(mod));
    }

    return std::make_tuple(reg_group, rm_group, disp_group, rm_is_effective_address);
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
