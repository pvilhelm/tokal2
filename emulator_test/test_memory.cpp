#include "catch.hpp"
#include "memory.h"

TEST_CASE("Test memory")
{
    SECTION("Test write_to_address")
    {
        using namespace emul_NS;

        { //v_data
            Memory m;
            std::vector<uint8_t> arr{0, 0, 0, 0};
            m.load_data(arr, 0x1000);

            REQUIRE(m.write_to_address08(0x1000, 1));
            REQUIRE(m.write_to_address08(0x1001, 2));
            REQUIRE(m.write_to_address08(0x1002, 3));
            REQUIRE(m.write_to_address08(0x1003, 4));
            REQUIRE(m.write_to_address08(0x1004, 4) == false);

            REQUIRE(m.v_data[0] == 1);
            REQUIRE(m.v_data[1] == 2);
            REQUIRE(m.v_data[2] == 3);
            REQUIRE(m.v_data[3] == 4);

        }
        { //v_data
            Memory m;
            std::vector<uint8_t> arr{1, 2, 3, 4};
            m.load_cdata(arr, 0x1000);

            REQUIRE(m.write_to_address08(0x1000, 1) == false);
            REQUIRE(m.write_to_address08(0x1004, 4) == false);

            REQUIRE(m.v_cdata[0] == 1);
            REQUIRE(m.v_cdata[1] == 2);
            REQUIRE(m.v_cdata[2] == 3);
            REQUIRE(m.v_cdata[3] == 4);
        }
        { //v_text
            Memory m;
            std::vector<uint8_t> arr{1, 2, 3, 4};
            m.load_text(arr, 0x1000);

            REQUIRE(m.write_to_address08(0x1000, 99));
            REQUIRE(m.write_to_address08(0x1004, 4) == false);

            REQUIRE(m.v_text[0] == 99); 
        }
        { //v_text
            Memory m;
            std::vector<uint8_t> arr{1, 2, 3, 4};
            m.load_stack(arr, 0x1000);

            REQUIRE(m.write_to_address08(0x1000, 99));
            REQUIRE(m.write_to_address08(0x1004, 4) == false);

            REQUIRE(m.v_stack[0] == 99);
        }
    }

}