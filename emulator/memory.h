#pragma once

#include <cinttypes>
#include <tuple>
#include <vector>

namespace emul_NS{

class Memory
{
    public:
        Memory();

        bool is_address_nonwritable(uint64_t address);

        bool write_to_address64(uint64_t address, uint64_t value);
        bool write_to_address32(uint64_t address, uint32_t value);
        bool write_to_address16(uint64_t address, uint16_t value);
        bool write_to_address08(uint64_t address, uint8_t value);

        std::tuple<uint64_t, bool> read_from_address64(uint64_t address);
        std::tuple<uint32_t, bool> read_from_address32(uint64_t address);
        std::tuple<uint16_t, bool> read_from_address16(uint64_t address);
        std::tuple<uint8_t, bool>  read_from_address08(uint64_t address);

        uint64_t data_address = 0;
        uint64_t data_size = 0;
        uint64_t cdata_address = 0;
        uint64_t cdata_size = 0;
        uint64_t text_address = 0;
        uint64_t text_size = 0;
        uint64_t stack_address = 0;
        uint64_t stack_size = 0;

        void load_text(std::vector<uint8_t> v_text, uint64_t text_address);
        void load_data(std::vector<uint8_t> v_data, uint64_t data_address);
        void load_stack(std::vector<uint8_t> v_stack, uint64_t stack_address);
        void load_cdata(std::vector<uint8_t> v_cdata, uint64_t cdata_address);
   
        std::vector<uint8_t> v_text;
        std::vector<uint8_t> v_cdata;
        std::vector<uint8_t> v_data;
        std::vector<uint8_t> v_stack;
};
}