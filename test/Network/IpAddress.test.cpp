#include <CSFML/Network/IpAddress.h>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("[Network] sfIpAddress")
{
    SECTION("Constants")
    {
        CHECK(sfIpAddress_toInteger(sfIpAddress_None) == 0);
        CHECK(sfIpAddress_toInteger(sfIpAddress_Any) == 0);
        CHECK(sfIpAddress_toInteger(sfIpAddress_LocalHost) == 0x7F000001);
        CHECK(sfIpAddress_toInteger(sfIpAddress_Broadcast) == 0xFFFFFFFF);
    }

    SECTION("sfIpAddress_fromString")
    {
        CHECK(sfIpAddress_toInteger(sfIpAddress_fromString("")) == 0);
        CHECK(sfIpAddress_toInteger(sfIpAddress_fromString("invalid address")) == 0);
        CHECK(sfIpAddress_toInteger(sfIpAddress_fromString("192.168.0.1")) == 0xC0A80001);
        CHECK(sfIpAddress_toInteger(sfIpAddress_fromString("8.8.8.8")) == 0x08080808);
    }

    SECTION("sfIpAddress_fromBytes")
    {
        CHECK(sfIpAddress_toInteger(sfIpAddress_fromBytes(0, 0, 0, 0)) == 0);
        CHECK(sfIpAddress_toInteger(sfIpAddress_fromBytes(192, 168, 0, 1)) == 0xC0A80001);
        CHECK(sfIpAddress_toInteger(sfIpAddress_fromBytes(8, 8, 8, 8)) == 0x08080808);
    }

    SECTION("sfIpAddress_fromInteger")
    {
        CHECK(sfIpAddress_toInteger(sfIpAddress_fromInteger(0)) == 0);
        CHECK(sfIpAddress_toInteger(sfIpAddress_fromInteger(0xC0A80001)) == 0xC0A80001);
        CHECK(sfIpAddress_toInteger(sfIpAddress_fromInteger(0x08080808)) == 0x08080808);
    }
}