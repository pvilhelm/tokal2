#pragma once

#include <string>
#include <exception>
#include <memory>

#include "cpu.h"
#include "instruction_decoder.h"

namespace emul_NS{
namespace ins_NS{

    class Instruction_exception : std::exception
    {
        explicit Instruction_exception(const char* message) :
            msg_(message)
        {}

        /** Constructor (C++ STL strings).
         *  @param message The error message.
         */
        explicit Instruction_exception(const std::string& message) :
            msg_(message)
        {}

        /** Destructor.
         * Virtual to allow for subclassing.
         */
        virtual ~Instruction_exception() throw () {}

        /** Returns a pointer to the (constant) error description.
         *  @return A pointer to a const char*. The underlying memory
         *          is in posession of the Exception object. Callers must
         *          not attempt to free the memory.
         */
        virtual const char* what() const throw ()
        {
            return msg_.c_str();
        }

        std::vector<uint8_t>::const_iterator search_start;
        std::vector<uint8_t>::const_iterator buffer_end;
    protected:
        /** Error message.
         */
        std::string msg_;
    };

    /** This is a interface class for all instruction groups */
    class Instruction_group
    {
    public:
        Instruction_group(){};
        virtual ~Instruction_group(){};


        virtual std::string get_group_name() = 0;
        virtual opcode_NS::GROUPING_OPCODE_Es get_opcode_group() = 0;
        virtual const std::shared_ptr<const Instruction> decode_data_to_instruction(std::vector<uint8_t>::const_iterator search_start,
            std::vector<uint8_t>::const_iterator buffer_end) = 0;

    private:
        std::string group_name;
        opcode_NS::GROUPING_OPCODE_Es group_opcode_E;

    };

    class Instruction
    {
    public:
        void execute(cpu_NS::Cpu &cpu);
    };

    class Add_instruction_group : public Instruction_group
    {
    public:
        Add_instruction_group(){};
        virtual ~Add_instruction_group(){};

        std::string get_group_name() override;
        opcode_NS::GROUPING_OPCODE_Es get_opcode_group() override;
        const std::shared_ptr<const Instruction> decode_data_to_instruction(std::vector<uint8_t>::const_iterator search_start,
            std::vector<uint8_t>::const_iterator buffer_end) override;
    };
}
}