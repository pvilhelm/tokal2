#pragma once


namespace emul_NS{
    enum Cpu_exception_Es
    {
        None_E = -1,
        Dive_by_zero_error_E,
        Debug_E,
        Non_maskable_interrupt_E,
        Breakpoint_E,
        Overflow_E,
        Bound_range_exceeded_E,
        Invalid_Opcode_E,
        Device_not_avaible_E,
        Double_fault_E,
        Invalid_TSS_E,
        Segment_not_present_E,
        Stack_segment_fault_E,
        General_procetion_fault_E,
        Page_fault_E,
        Reserved_E,
        x87_float_exception_E,
        Alignment_check_E,
        Machine_check_E,
        Simd_float_exception_E,
        Virtualization_exception_E,
        Reserved_2_E,
        Security_exception_E,
        Reserved_3_E,
        Triple_fault_E,
        
        Invalid_instruction_E = 256

    };
}