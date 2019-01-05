#pragma once

/** @file test */


#include <cinttypes>
#include <vector>
#include <set>
#include <map>

#include "cpu.h"

/**
 *  Namespace for the emulator module.
 */
namespace emul_NS {

/**
 *  reg bitfield namespace.
 */
namespace reg_NS {
    /** 
     *  Enumeration constants of all the different registers. 
     */
    enum REG_Es
    {
        RAX_E,
        EAX_E,
        AX_E,
        AL_E,
        RCX_E,
        ECX_E,
        CX_E,
        CL_E,
        RDX_E,
        EDX_E,
        DX_E,
        DL_E,
        RBX_E,
        EBX_E,
        BX_E,
        BL_E,
        RSP_E,
        ESP_E,
        SP_E,
        SPL_E,
        RBP_E,
        EBP_E,
        BP_E,
        BPL_E,
        RSI_E,
        ESI_E,
        SI_E,
        SIL_E,
        RDI_E,
        EDI_E,
        DI_E,
        DIL_E,
        R08_E,
        R08D_E,
        R08W_E,
        R08B_E,
        R09_E,
        R09D_E,
        R09W_E,
        R09B_E,
        R10_E,
        R10D_E,
        R10W_E,
        R10B_E,
        R11_E, 
        R11D_E,
        R11W_E,
        R11B_E, 
        R12_E,
        R12D_E,
        R12W_E,
        R12B_E,
        R13_E,
        R13D_E,
        R13W_E,
        R13B_E,
        R14_E,
        R14D_E,
        R14W_E,
        R14B_E,
        R15_E,
        R15D_E,
        R15W_E,
        R15B_E,
        MM00_E,
        MM01_E,
        MM02_E,
        MM03_E,
        MM04_E,
        MM05_E,
        MM06_E,
        MM07_E,
        MM08_E,
        MM09_E,
        MM10_E,
        MM11_E,
        MM12_E,
        MM13_E,
        MM14_E,
        MM15_E,
        XMM00_E,
        XMM01_E,
        XMM02_E,
        XMM03_E,
        XMM04_E,
        XMM05_E,
        XMM06_E,
        XMM07_E,
        XMM08_E,
        XMM09_E,
        XMM10_E,
        XMM11_E,
        XMM12_E,
        XMM13_E,
        XMM14_E,
        XMM15_E,

        /* Legacy registers */
        AH_E,
        CH_E,
        DH_E,
        BH_E,
    };
}

/** 
 * Name space for OP-code functionality.
 */
namespace opcode_NS {

        /**
         * The magic number 0x0F which as primary op-code specifies it's a two byte op-code.
         */
        const uint8_t twobyte_opcode_first_byte = 0x0FU;

        /**
         * Enumerations constants for all the different op-code groups.
         */
        enum GROUPING_OPCODE_Es
        {
            INVALID_INSTRUCTION_E,
            ADC_E,
            ADD_E,
            AND_E,
            BND_E,
            BSF_TZCNT_E,
            BSR_LZCNT_E,
            BSWAP_E,
            BT_E,
            CALL_E,
            CBW_E,
            CLC_E,
            CLD_E,
            CLI_E,
            CLTS_E,
            CMC_E,
            CMOV_E,
            CMPS_E,
            CMPXCHG_E,
            CMP_E,
            COMIS_E,
            CPUID_E,
            CVT_E,
            CWD_E,
            EMMS_E,
            ENTER_E,
            F87_ESCAPE_E,
            FWAIT_E,
            GETSEC_E,
            GROUP_10_E,
            GROUP_12_E,
            GROUP_13_E,
            GROUP_14_E,
            GROUP_15_E,
            GROUP_16_E,
            GROUP_1_E,
            GROUP_5_E,
            GROUP_6_E,
            GROUP_7_E,
            GROUP_8_E,
            GROUP_9_E,
            HLT_E,
            IMMIDIATE_GROUP_1_E,
            IMUL_E,
            INCDEC_GROUP_4_E,
            INS_E,
            INTO_E,
            INT_E,
            INVD_E,
            IN_E,
            IRET_E,
            JMPEMUL_POPCNT_E,
            JMPLONG_E,
            JMPSHORT_E,
            LAHF_E,
            LAR_E,
            LDDQU_E,
            LEAVE_E,
            LEA_E,
            LFS_E,
            LGS_E,
            LODS_E,
            LOOP_E,
            LSL_E,
            LSS_E,
            MASKM_E,
            MOVSXD_E,
            MOVSX_E,
            MOVS_E,
            MOVZX_E,
            MOV_E,
            MOV_GROUP_11_E,
            NOP_E,
            OR_E,
            OUTS_E,
            OUT_E,
            POPQ_E,
            POP_E,
            PREFETCH_E,
            PSLL_E,
            PUSHQ_E,
            PUSH_E,
            RCP_E,
            RDMSR_E,
            RDPMC_E,
            RDTSC_E,
            RESERVED_NOP_E,
            RETF_E,
            RETN_E,
            RSM_E,
            RSQRT_E,
            SAHF_E,
            SBB_E,
            SCAS_E,
            SETCC_E,
            SHIFT_GROUP_2_E,
            SHLD_E,
            SHRD_E,
            SQRT_E,
            STC_E,
            STD_E,
            STI_E,
            STOS_E,
            SUB_E,
            SYSCALL_E,
            SYSENTER_E,
            SYSEXIT_E,
            SYSRET_E,
            TEST_E,
            UCOMI_E,
            UD2_E,
            UNARY_GROUP_3_E,
            VADDSUB_E,
            VADD_E,
            VANDN_E,
            VAND_E,
            VAVG_E,
            VCMP_E,
            VCVT_E,
            VDIV_E,
            VEXTR_E,
            VINSR_E,
            VMAD_E,
            VMAX_E,
            VMIN_E,
            VMOVAPS_E,
            VMOV_E,
            VMREAD_E,
            VMULH_E,
            VMULL_E,
            VMUL_E,
            VMWRITE_E,
            VOR_E,
            VPACK_E,
            VSADB_E,
            VSHUF_E,
            VSRA_E,
            VSRL_E,
            VSUB_E,
            VUNPCK_E,
            VUNPC_E,
            VXOR_E,
            WBINVD_E,
            WRMSR_E,
            XADD_E,
            XCHG_E,
            XLAT_E,
            XOR_E,
        };

        /**
         *  A map which maps the key *secondary op-code* from a two byte op-code to the corresponding value op-code group as a GROUPING_OPCODE_Es. 
         *
         *  Key: Second op-code byte in a two byte op-code.
         *
         *  Value: op-code group as a GROUPING_OPCODE_Es.
         */
        const std::map<uint8_t, GROUPING_OPCODE_Es> map_byte_to_opcode2b_group{
            {0x00U, GROUP_6_E},
            {0x01U, GROUP_7_E},
            {0x02U, LAR_E},
            {0x03U, LSL_E},
            {0x05U, SYSCALL_E},
            {0x06U, CLTS_E},
            {0x07U, SYSRET_E},
            {0x08U, INVD_E},
            {0x09U, WBINVD_E},
            {0x0BU, UD2_E},
            {0x0DU, PREFETCH_E},
            {0x10U, VMOV_E},
            {0x11U, VMOV_E},
            {0x12U, VMOV_E},
            {0x13U, VMOV_E},
            {0x14U, VUNPC_E},
            {0x15U, VUNPC_E},
            {0x16U, VMOV_E},
            {0x17U, VMOV_E},
            {0x18U, GROUP_16_E},
            {0x19U, RESERVED_NOP_E},
            {0x1AU, BND_E},
            {0x1BU, BND_E},
            {0x1CU, RESERVED_NOP_E},
            {0x1DU, RESERVED_NOP_E},
            {0x1EU, RESERVED_NOP_E},
            {0x1FU, NOP_E},
            {0x20U, MOV_E},
            {0x21U, MOV_E},
            {0x22U, MOV_E},
            {0x23U, MOV_E},
            {0x28U, VMOVAPS_E},
            {0x29U, VMOVAPS_E},
            {0x2AU, CVT_E},
            {0x2BU, VMOV_E},
            {0x2CU, CVT_E},
            {0x2DU, CVT_E},
            {0x2EU, UCOMI_E},
            {0x2EU, UCOMI_E},
            {0x2FU, COMIS_E},
            {0x30U, WRMSR_E},
            {0x31U, RDTSC_E},
            {0x32U, RDMSR_E},
            {0x33U, RDPMC_E},
            {0x34U, SYSENTER_E},
            {0x35U, SYSEXIT_E},
            {0x37U, GETSEC_E},
            {0x40U, CMOV_E},
            {0x41U, CMOV_E},
            {0x42U, CMOV_E},
            {0x43U, CMOV_E},
            {0x44U, CMOV_E},
            {0x45U, CMOV_E},
            {0x46U, CMOV_E},
            {0x47U, CMOV_E},
            {0x48U, CMOV_E},
            {0x49U, CMOV_E},
            {0x4AU, CMOV_E},
            {0x4BU, CMOV_E},
            {0x4CU, CMOV_E},
            {0x4DU, CMOV_E},
            {0x4EU, CMOV_E},
            {0x4FU, CMOV_E},
            {0x50U, VMOV_E},
            {0x51U, SQRT_E},
            {0x52U, RSQRT_E},
            {0x53U, RCP_E},
            {0x54U, VAND_E},
            {0x55U, VAND_E},
            {0x56U, VOR_E},
            {0x57U, VXOR_E},
            {0x58U, VADD_E},
            {0x59U, VMUL_E},
            {0x5AU, VCVT_E},
            {0x5BU, VCVT_E},
            {0x5CU, VSUB_E},
            {0x5DU, VMIN_E},
            {0x5EU, VDIV_E},
            {0x5FU, VMAX_E},
            {0x60U, VUNPCK_E},
            {0x61U, VUNPCK_E},
            {0x62U, VUNPCK_E},
            {0x63U, VPACK_E},
            {0x64U, VCMP_E},
            {0x65U, VCMP_E},
            {0x66U, VCMP_E},
            {0x67U, VPACK_E},
            {0x68U, VUNPCK_E},
            {0x69U, VUNPCK_E},
            {0x6AU, VUNPCK_E},
            {0x6BU, VPACK_E},
            {0x6CU, VUNPCK_E},
            {0x6DU, VUNPCK_E},
            {0x6EU, VMOV_E},
            {0x6FU, VMOV_E},
            {0x70U, VSHUF_E},
            {0x71U, GROUP_12_E},
            {0x72U, GROUP_13_E},
            {0x73U, GROUP_14_E},
            {0x74U, VCMP_E},
            {0x75U, VCMP_E},
            {0x76U, VCMP_E},
            {0x77U, EMMS_E},
            {0x78U, VMREAD_E},
            {0x79U, VMWRITE_E},
            {0x7CU, VADD_E},
            {0x7DU, VSUB_E},
            {0x7EU, VMOV_E},
            {0x7FU, VMOV_E},
            {0x80U, JMPLONG_E},
            {0x81U, JMPLONG_E},
            {0x82U, JMPLONG_E},
            {0x83U, JMPLONG_E},
            {0x84U, JMPLONG_E},
            {0x85U, JMPLONG_E},
            {0x86U, JMPLONG_E},
            {0x87U, JMPLONG_E},
            {0x88U, JMPLONG_E},
            {0x89U, JMPLONG_E},
            {0x8AU, JMPLONG_E},
            {0x8BU, JMPLONG_E},
            {0x8CU, JMPLONG_E},
            {0x8DU, JMPLONG_E},
            {0x8EU, JMPLONG_E},
            {0x8FU, JMPLONG_E},
            {0x90U, SETCC_E},
            {0x91U, SETCC_E},
            {0x92U, SETCC_E},
            {0x93U, SETCC_E},
            {0x94U, SETCC_E},
            {0x95U, SETCC_E},
            {0x96U, SETCC_E},
            {0x97U, SETCC_E},
            {0x98U, SETCC_E},
            {0x99U, SETCC_E},
            {0x9AU, SETCC_E},
            {0x9BU, SETCC_E},
            {0x9CU, SETCC_E},
            {0x9DU, SETCC_E},
            {0x9EU, SETCC_E},
            {0x9FU, SETCC_E},
            {0xA0U, PUSH_E},
            {0xA1U, POP_E},
            {0xA2U, CPUID_E},
            {0xA3U, BT_E},
            {0xA4U, SHLD_E},
            {0xA5U, SHLD_E},
            {0xA8U, PUSH_E},
            {0xA9U, POP_E},
            {0xAAU, RSM_E},
            {0xABU, BT_E},
            {0xACU, SHRD_E},
            {0xADU, SHRD_E},
            {0xAEU, GROUP_15_E},
            {0xAFU, IMUL_E},
            {0xB0U, CMPXCHG_E},
            {0xB1U, CMPXCHG_E},
            {0xB2U, LSS_E},
            {0xB3U, BT_E},
            {0xB4U, LFS_E},
            {0xB5U, LGS_E},
            {0xB6U, MOVZX_E},
            {0xB7U, MOVZX_E},
            {0xB8U, JMPEMUL_POPCNT_E},
            {0xB9U, GROUP_10_E},
            {0xBAU, GROUP_8_E},
            {0xBBU, BT_E},
            {0xBCU, BSF_TZCNT_E},
            {0xBDU, BSR_LZCNT_E},
            {0xBEU, MOVSX_E},
            {0xBFU, MOVSX_E},
            {0xC0U, XADD_E},
            {0xC1U, XADD_E},
            {0xC2U, VCMP_E},
            {0xC3U, VMOV_E},
            {0xC4U, VINSR_E},
            {0xC5U, VEXTR_E},
            {0xC6U, VSHUF_E},
            {0xC7U, GROUP_9_E},
            {0xC8U, BSWAP_E},
            {0xC9U, BSWAP_E},
            {0xCAU, BSWAP_E},
            {0xCBU, BSWAP_E},
            {0xCCU, BSWAP_E},
            {0xCDU, BSWAP_E},
            {0xCEU, BSWAP_E},
            {0xCFU, BSWAP_E},
            {0xD0U, VADDSUB_E},
            {0xD1U, VSRL_E},
            {0xD2U, VSRL_E},
            {0xD3U, VSRL_E},
            {0xD4U, VADD_E},
            {0xD5U, VMULL_E},
            {0xD6U, VMOV_E},
            {0xD7U, VMOV_E},
            {0xD8U, VSUB_E},
            {0xD9U, VSUB_E},
            {0xDAU, VMIN_E},
            {0xDBU, VAND_E},
            {0xDCU, VADD_E},
            {0xDDU, VADD_E},
            {0xDEU, VMAX_E},
            {0xDFU, VANDN_E},
            {0xE0U, VAVG_E},
            {0xE1U, VSRA_E},
            {0xE2U, VSRA_E},
            {0xE3U, VAVG_E},
            {0xE4U, VMULH_E},
            {0xE5U, VMULH_E},
            {0xE6U, CVT_E},
            {0xE7U, VMOV_E},
            {0xE8U, VSUB_E},
            {0xE9U, VSUB_E},
            {0xEAU, VMIN_E},
            {0xEBU, VOR_E},
            {0xECU, VADD_E},
            {0xEDU, VADD_E},
            {0xEEU, VMAX_E},
            {0xEFU, VXOR_E},
            {0xF0U, LDDQU_E},
            {0xF1U, PSLL_E},
            {0xF2U, PSLL_E},
            {0xF3U, PSLL_E},
            {0xF4U, VMUL_E},
            {0xF5U, VMAD_E},
            {0xF6U, VSADB_E},
            {0xF7U, MASKM_E},
            {0xF8U, VSUB_E},
            {0xF9U, VSUB_E},
            {0xFAU, VSUB_E},
            {0xFBU, VSUB_E},
            {0xFCU, VADD_E},
            {0xFDU, VADD_E},
            {0xFEU, VADD_E},
        };

        /**
        *  A map which maps the key *primary op-code* from an one byte op-code to the corresponding value op-code group as a GROUPING_OPCODE_Es.
        *
        *  Key:
        *      First op-code byte in a one byte op-code.
        *
        *  Value:
        *      op-code group as a GROUPING_OPCODE_Es.
        */
        const std::map<uint8_t, GROUPING_OPCODE_Es> map_byte_to_opcode1b_group{
            {0x00U, ADD_E},
            {0x01U, ADD_E},
            {0x02U, ADD_E},
            {0x03U, ADD_E},
            {0x04U, ADD_E},
            {0x05U, ADD_E},
            {0x08U, OR_E},
            {0x09U, OR_E},
            {0x0AU, OR_E},
            {0x0BU, OR_E},
            {0x0CU, OR_E},
            {0x0DU, OR_E},
            {0x10U, ADC_E},
            {0x11U, ADC_E},
            {0x12U, ADC_E},
            {0x13U, ADC_E},
            {0x14U, ADC_E},
            {0x15U, ADC_E},
            {0x18U, SBB_E},
            {0x19U, SBB_E},
            {0x1AU, SBB_E},
            {0x1BU, SBB_E},
            {0x1CU, SBB_E},
            {0x1DU, SBB_E},
            {0x20U, AND_E},
            {0x21U, AND_E},
            {0x22U, AND_E},
            {0x23U, AND_E},
            {0x24U, AND_E},
            {0x25U, AND_E},
            {0x28U, SUB_E},
            {0x29U, SUB_E},
            {0x2AU, SUB_E},
            {0x2BU, SUB_E},
            {0x2CU, SUB_E},
            {0x2DU, SUB_E},
            {0x30U, XOR_E},
            {0x31U, XOR_E},
            {0x32U, XOR_E},
            {0x33U, XOR_E},
            {0x34U, XOR_E},
            {0x35U, XOR_E},
            {0x38U, CMP_E},
            {0x39U, CMP_E},
            {0x3AU, CMP_E},
            {0x3BU, CMP_E},
            {0x3CU, CMP_E},
            {0x3DU, CMP_E},
            {0x50U, PUSH_E},
            {0x51U, PUSH_E},
            {0x52U, PUSH_E},
            {0x53U, PUSH_E},
            {0x54U, PUSH_E},
            {0x55U, PUSH_E},
            {0x56U, PUSH_E},
            {0x57U, PUSH_E},
            {0x58U, POP_E},
            {0x59U, POP_E},
            {0x5AU, POP_E},
            {0x5BU, POP_E},
            {0x5CU, POP_E},
            {0x5DU, POP_E},
            {0x5EU, POP_E},
            {0x5FU, POP_E},
            {0x63U, MOVSXD_E},
            {0x68U, PUSH_E},
            {0x69U, IMUL_E},
            {0x6AU, PUSH_E},
            {0x6BU, IMUL_E},
            {0x6CU, INS_E},
            {0x6DU, INS_E},
            {0x6EU, OUTS_E},
            {0x6FU, OUTS_E},
            {0x70U, JMPSHORT_E},
            {0x71U, JMPSHORT_E},
            {0x72U, JMPSHORT_E},
            {0x73U, JMPSHORT_E},
            {0x74U, JMPSHORT_E},
            {0x75U, JMPSHORT_E},
            {0x76U, JMPSHORT_E},
            {0x77U, JMPSHORT_E},
            {0x78U, JMPSHORT_E},
            {0x79U, JMPSHORT_E},
            {0x7AU, JMPSHORT_E},
            {0x7BU, JMPSHORT_E},
            {0x7CU, JMPSHORT_E},
            {0x7DU, JMPSHORT_E},
            {0x7EU, JMPSHORT_E},
            {0x7FU, JMPSHORT_E},
            {0x80U, IMMIDIATE_GROUP_1_E},
            {0x81U, IMMIDIATE_GROUP_1_E},
            {0x83U, IMMIDIATE_GROUP_1_E},
            {0x84U, TEST_E},
            {0x85U, TEST_E},
            {0x86U, XCHG_E},
            {0x87U, XCHG_E},
            {0x88U, MOV_E},
            {0x89U, MOV_E},
            {0x8AU, MOV_E},
            {0x8BU, MOV_E},
            {0x8CU, MOV_E},
            {0x8DU, LEA_E},
            {0x8EU, MOV_E},
            {0x8FU, GROUP_1_E},
            {0x90U, XCHG_E},
            {0x91U, XCHG_E},
            {0x92U, XCHG_E},
            {0x93U, XCHG_E},
            {0x94U, XCHG_E},
            {0x95U, XCHG_E},
            {0x96U, XCHG_E},
            {0x97U, XCHG_E},
            {0x98U, CBW_E},
            {0x99U, CWD_E},
            {0x9BU, FWAIT_E},
            {0x9CU, PUSHQ_E},
            {0x9DU, POPQ_E},
            {0x9EU, SAHF_E},
            {0x9FU, LAHF_E},
            {0xA0U, MOV_E},
            {0xA1U, MOV_E},
            {0xA2U, MOV_E},
            {0xA3U, MOV_E},
            {0xA4U, MOVS_E},
            {0xA5U, MOVS_E},
            {0xA6U, CMPS_E},
            {0xA7U, CMPS_E},
            {0xA8U, TEST_E},
            {0xA9U, TEST_E},
            {0xAAU, STOS_E},
            {0xABU, STOS_E},
            {0xACU, LODS_E},
            {0xADU, LODS_E},
            {0xAEU, SCAS_E},
            {0xAFU, SCAS_E},
            {0xB0U, MOV_E},
            {0xB1U, MOV_E},
            {0xB2U, MOV_E},
            {0xB3U, MOV_E},
            {0xB4U, MOV_E},
            {0xB5U, MOV_E},
            {0xB6U, MOV_E},
            {0xB7U, MOV_E},
            {0xB8U, MOV_E},
            {0xB9U, MOV_E},
            {0xBAU, MOV_E},
            {0xBBU, MOV_E},
            {0xBCU, MOV_E},
            {0xBDU, MOV_E},
            {0xBEU, MOV_E},
            {0xBFU, MOV_E},
            {0xC0U, SHIFT_GROUP_2_E},
            {0xC1U, SHIFT_GROUP_2_E},
            {0xC2U, RETN_E},
            {0xC3U, RETN_E},
            {0xC6U, MOV_GROUP_11_E},
            {0xC7U, MOV_GROUP_11_E},
            {0xC8U, ENTER_E},
            {0xC9U, LEAVE_E},
            {0xCAU, RETF_E},
            {0xCBU, RETF_E},
            {0xCCU, INT_E},
            {0xCDU, INT_E},
            {0xCEU, INTO_E},
            {0xCFU, IRET_E},
            {0xD0U, SHIFT_GROUP_2_E},
            {0xD1U, SHIFT_GROUP_2_E},
            {0xD2U, SHIFT_GROUP_2_E},
            {0xD3U, SHIFT_GROUP_2_E},
            {0xD7U, XLAT_E},
            {0xD8U, F87_ESCAPE_E},
            {0xD9U, F87_ESCAPE_E},
            {0xDAU, F87_ESCAPE_E},
            {0xDBU, F87_ESCAPE_E},
            {0xDCU, F87_ESCAPE_E},
            {0xDDU, F87_ESCAPE_E},
            {0xDEU, F87_ESCAPE_E},
            {0xDFU, F87_ESCAPE_E},
            {0xE0U, LOOP_E},
            {0xE1U, LOOP_E},
            {0xE2U, LOOP_E},
            {0xE3U, JMPSHORT_E},
            {0xE4U, IN_E},
            {0xE5U, IN_E},
            {0xE6U, OUT_E},
            {0xE7U, OUT_E},
            {0xE8U, CALL_E},
            {0xE9U, JMPSHORT_E},
            {0xEBU, JMPSHORT_E},
            {0xECU, IN_E},
            {0xEDU, IN_E},
            {0xEEU, OUT_E},
            {0xEFU, OUT_E},
            {0xF1U, INT_E},
            {0xF4U, HLT_E},
            {0xF5U, CMC_E},
            {0xF6U, UNARY_GROUP_3_E},
            {0xF7U, UNARY_GROUP_3_E},
            {0xF8U, CLC_E},
            {0xF9U, STC_E},
            {0xFAU, CLI_E},
            {0xFBU, STI_E},
            {0xFCU, CLD_E},
            {0xFDU, STD_E},
            {0xFEU, INCDEC_GROUP_4_E},
            {0xFFU,	GROUP_5_E}
        };
        /* TODO: Gör klart
        enum GROUPING_OPCODE3B_Es
        {
        VSHUF_E,
        VHADD_E,
        VMADD_E,
        VHSUB_E,
        VBLEND_E,
        VCVT_E,
        VPERM_E,
        VTEST_E,
        VMOV_E,
        VCMP_E,
        VMULL_E,
        VMIN_E,
        VSRL_E,
        VSRA_E,
        VSLL_E,
        INVEPT_E,
        INVVPID_E,
        INVPCID_E,
        VGATHER_E,
        VFMADDSUB_E,
        MOVBE_E,
        ANDN_E,
        BZHI_E

        };*/

        /**
         *  Tries to return an op-code group for a given byte assuming it's an one byte op-code.
         *
         *  \param byte
         *      The first byte of the op-code
         *
         *  \returns
         *      Returns the corresponding group or \ref ::GROUPING_OPCODE_Es ::INVALID_INSTRUCTION_E if the byte is not a one byte op-code
         */
        GROUPING_OPCODE_Es as_1b_opcode(uint8_t byte);

       /**
        *   Tries to return an op-code group for a given byte assuming it's a two byte op-code.
        *
        *   \param byte
        *       The second byte of an op-code
        *
        *   \returns
        *      Returns the corresponding group or \ref ::GROUPING_OPCODE_Es ::INVALID_INSTRUCTION_E if the byte is not a two byte op-code
        */
        GROUPING_OPCODE_Es as_2b_opcode(uint8_t byte);
        GROUPING_OPCODE_Es as_3b_opcode(uint8_t byte);
    }
    
/** Namespace for the ModR/M byte functionality.
 */
namespace modrm_NS {
    /**
     * Extracts the Mod bitfield from the addressing-form specifier byte, the ModR/M byte.
     *
     * The Mod bitfield together with the R/M field specifies 32 values; 8 registers and 24 addressing modes.
     *
     * Parameters:
     *  modrm_byte - The ModR/M byte to extract the bitfield from.
     *
     * Returns:
     *  The mod bitfield in the given ModR/M byte.
     */
    uint8_t get_mod_bf(uint8_t modrm_byte);

   /**
    * Extracts the R/M bitfield from the addressing-form specifier byte, the ModR/M byte.
    *
    * The R/M bitfield specifies a register as an operand or in combination with the Mod bitfield
    * to encode an addressing mode.
    *
    * Parameters:
    *  modrm_byte - The ModR/M byte to extract the bitfield from.
    *
    * Returns:
    *  The R/M bitfield in the given ModR/M byte.
    */
    uint8_t get_rm_bf(uint8_t modrm_byte);

   /**
    * Extracts the reg/op-code bitfield from the addressing-form specifier byte, the ModR/M byte.
    *
    * The reg bitfield specifies a register or 3 bits of op-code info. The primary opcode governs the meaning of
    * the reg/op-code bitfield.
    *
    * Parameters:
    *  modrm_byte - The ModR/M byte to extract the bitfield from.
    *
    * Returns:
    *  The reg/op-code bitfield in the given ModR/M byte.
    */
    uint8_t get_reg_bf(uint8_t modrm_byte);
}

/**  Name space for decode instruction functionality.
 */
namespace decode_instruction_NS {

    /**
     * Container for pointers and type to an instruction placed somewhere in memory.
     *
     */
    struct Instruction
    {
        /** Pointer to start of instruction.
         */
        std::vector<uint8_t>::const_iterator ins_start;
        /** Pointer to end of instruction (one byte past the last byte).
         */
        std::vector<uint8_t>::const_iterator insbuffer_end;
        /** Op-code group the instruction belongs to. 
         */
        opcode_NS::GROUPING_OPCODE_Es op_type_E;
    };

    /** Decodes and returns the type of and memory boundarys of the first instruction from the specified memory location
     *
     * \returns An Instruction struct with instruction boundarys and the corrensponding group of the instruction, or GROUPING_OPCODE_Es :: INVALID_INSTRUCTION_E.
     */
    Instruction decode_instruction(std::vector<uint8_t>::const_iterator instruction_start,//< Memory position to start decoding from.
                                   std::vector<uint8_t>::const_iterator instructionbuffer_end);//< The end of the memory buffer (to determine how far to possibly decode).

    /* Enumeration of different groups of register/effective address (R/M) and register (reg) operands. */
    enum class MODRM_SRC_DST_GROUP_Es
    {
        INVALID_GROUP_E,
        A_GROUP_E,
        C_GROUP_E,
        D_GROUP_E,
        B_GROUP_E,
        SP_GROUP_E,
        BP_GROUP_E,
        IP_GROUP_E,
        SI_GROUP_E,
        DI_GROUP_E,
        R8_GROUP_E,
        R9_GROUP_E,
        R10_GROUP_E,
        R11_GROUP_E,
        R12_GROUP_E,
        R13_GROUP_E,
        R14_GROUP_E,
        R15_GROUP_E,
        SIB_E,
    };

    /** Enumeration of displacements for effective addresses. */
    enum class MODRM_DISP_Es
    {
        INVALID_DISP_E,
        disp_0_E,
        disp_8_E,
        disp_32_E,
    };

    /** Decode a ModR/M byte and an optional rex byte to yield a target and source register or effective address as groups.
     *
     * \param rex_byte The rex byte, or 0 if no such exists.
     * \param modrm_byte The modR/M byte.
     *
     * \returns A tuple with target, source register/effective address and a displacement, as enums, and a boolean 
     * indicating whether the R/M group is a effective address or not.
     */
    std::tuple<MODRM_SRC_DST_GROUP_Es /*reg*/, MODRM_SRC_DST_GROUP_Es /*R/M*/, MODRM_DISP_Es /* displacement */, bool /* R/M is effective address*/> 
    decode_modrm_and_rex(uint8_t rex_byte, uint8_t modrm_byte);
}

/** Namespace for rex prefix byte functionality */
namespace rex_NS {

    /** Determines if a byte is a rex prefix byte
     *
     *  \param byte The byte to test.
     *
     * \returns Whether the byte is a rex prefix byte.
     */
    bool is_REX_byte(uint8_t byte);

    /** Class to represent the rex prefix byte 
     *
     */
    struct Rex
    {
        Rex();
        /** Ctor with specified rex prefix value 
         *
         * The argument needs to be a valid rex prefix byte, or an runtime_error will be thrown.
         *
         * \param byte The rex prefix byte to assign to the object.
         */
        Rex(uint8_t byte);

        /** Gets the W bit from the rex prefix byte. 
         *
         * The W bit determines whether the operand size is CS.D(efault) or 64 bits.
         */
        bool get_W(); /* bit 3, w == 1 operand size determined by CS.D, w == 0 gives 64 bit operand size */
        /** Gets the R bit from the rex prefix byte.
         *
         *  The R bit is an extension to the reg field in the ModR/M byte.
         */
        bool get_R(); /* bit 2, extension to ModR/M reg field */
        /** Gets the X bit from the rex prefix byte.
         *
         *  The X bit is an extension to the SIB byte.
         */
        bool get_X(); /* bit 1, extension to SIB field */
        /** Gets the B bit from the rex prefix byte.
         *
         *  The B bit is an extension to the R/M field in the ModR/M byte, or the SIB base field or the Op-code reg field.
         */
        bool get_B(); /* bit 0 extension to ModR/M r/m field, SIB base field or OPcode reg field */

        uint8_t value;
    };

    /** Constructs a Rex object from the named bits */
    Rex rex_from_named_bits(bool W, bool R, bool X, bool B);
}


namespace prefixes_NS{
    const std::set<uint8_t> set_of_prefixes{
        0x26,
        0x2E,
        0x36,
        0x3E,
        0x64,
        0x65,
        0x66,
        0x67,
        0xF0,
        0xF2,
        0xF3,
    };

    enum LEGACY_PREFIXES_Es
    {
        NULL_PREFIX_ES_E = 0x26, /* ES segment override. Branchpredicition usage reserved. */
        NULL_PREFIX_CS_E = 0x2E,
        NULL_PREFIX_SS_E = 0x36,
        NULL_PREFIX_DS_E = 0x3E,
        NULL_PREFIX_FS_E = 0x64,
        NULL_PREFIX_GS_E = 0x65,
        OPERAND_SIZE_OVERRIDE_E = 0x66,
        ADDRESS_SIZE_OVERRIDE_E = 0x67,
        LOCK_E = 0xF0,
        REPNE_REPNZ_BND_E = 0xF2,
        REP_REPE_REPZ_E = 0xF3,
    };

    bool is_legacy_prefix(uint8_t byte);
}

}