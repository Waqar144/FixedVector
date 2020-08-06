#include "catch2/catch.hpp"
#include "fixed_vector.h"

TEST_CASE("Size")
{
    FixedVector<int, 5> v;
    REQUIRE(v.size() == 0);
}

TEST_CASE("push_back")
{
    FixedVector<int, 5> s = {};
    s.push_back(1);
    s.push_back(2);
    REQUIRE(s.size() == 2);
}
