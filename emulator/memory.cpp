#include "memory.h"

using namespace emul_NS;

emul_NS::Memory::Memory()
{

}

bool Memory::is_address_nonwritable(uint64_t address)
{
    if(address < this->cdata_address || address >= this->cdata_address + this->cdata_size)
        if(address < this->text_address || address >= this->text_address + this->text_size)
            return false;
    return true;
}

bool Memory::write_to_address08(uint64_t address, uint8_t value)
{
    if(address >= cdata_address && address < cdata_address + cdata_size) {
        return false;
    } else if(address >= data_address && address < data_address + data_size) {
        uint64_t index = address - data_address;
        v_data[index] = value;
        return true;
    } else if(address >= stack_address && address < stack_address + stack_size) {
        uint64_t index = address - stack_address;
        v_stack[index] = value;
        return true;
    } else if(address >= text_address && address < text_address + text_size) {
        uint64_t index = address - text_address;
        v_text[index] = value;
        return true;
    }

    return false;
}

std::tuple<uint8_t, bool> emul_NS::Memory::read_from_address08(uint64_t address)
{
    bool sucess;
    uint8_t value;

    if(address >= cdata_address && address < cdata_address + cdata_size) {
        sucess = true;

    } else if(address >= data_address && address < data_address + data_size) {
        uint64_t index = address - data_address;
        v_data[index] = value;
        return true;
    } else if(address >= stack_address && address < stack_address + stack_size) {
        uint64_t index = address - stack_address;
        v_stack[index] = value;
        return true;
    } else if(address >= text_address && address < text_address + text_size) {
        uint64_t index = address - text_address;
        v_text[index] = value;
        return true;
    }

}

void emul_NS::Memory::load_text(std::vector<uint8_t> v_text, uint64_t text_address)
{
    this->v_text = v_text;
    this->text_size = v_text.size();
    this->text_address = text_address;
}

void emul_NS::Memory::load_data(std::vector<uint8_t> v_data, uint64_t data_address)
{
    this->v_data = v_data;
    this->data_size = v_data.size();
    this->data_address = data_address;
}

void emul_NS::Memory::load_stack(std::vector<uint8_t> v_stack, uint64_t stack_address)
{
    this->v_stack = v_stack;
    this->stack_size = v_stack.size();
    this->stack_address = stack_address;
}

void emul_NS::Memory::load_cdata(std::vector<uint8_t> v_cdata, uint64_t cdata_address)
{
    this->v_cdata = v_cdata;
    this->cdata_size = v_cdata.size();
    this->cdata_address = cdata_address;
}
