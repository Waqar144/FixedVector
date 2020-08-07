#include "catch2/catch.hpp"
#include "fixed_vector.h"

#include <iostream>
#include <vector>

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

TEST_CASE("insert")
{
    SECTION("insert(iterator, value)") {
        FixedVector<int, 5> v;
        auto it = v.insert(v.begin(), 1);
        v.insert(v.begin() + 1, 2);
        v.insert(v.begin() + 2, 3);
        v.insert(v.begin() + 3, 4);
        v.insert(v.begin() + 4, 5);

        REQUIRE (*it == 1);

        REQUIRE(v.at(0) == 1);
        REQUIRE(v.at(1) == 2);
        REQUIRE(v.at(2) == 3);
        REQUIRE(v.at(3) == 4);
        REQUIRE(v.at(4) == 5);
    }

    SECTION("insert(iterator, iter first, iter last") {
        FixedVector<int, 10> v;
        FixedVector<int, 4> c;
        c[0] = 1;
        c[1] = 2;
        c[2] = 3;
        c[3] = 4;

        v.insert(v.begin(), c.begin(), c.end());
        REQUIRE(v.at(0) == 1);
        REQUIRE(v.at(1) == 2);
        REQUIRE(v.at(2) == 3);
        REQUIRE(v.at(3) == 4);

        std::vector<int> vec {5,6,7,8};
        v.insert(v.begin() + 4, vec.end(), vec.begin());
        REQUIRE(v.at(4) == 5);
        REQUIRE(v.at(5) == 6);
        REQUIRE(v.at(6) == 7);
        REQUIRE(v.at(7) == 8);
    }
}
