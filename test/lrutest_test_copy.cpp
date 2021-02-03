#include "gtest/gtest.h"
#include "lru.hpp"

#include <chrono>

struct LRU_Base : public ::testing::Test {
    /*void SetUp() {
    }
    void TearDown() {
    }*/
};

TEST_F(LRU_Base, ShouldReturnNullOpt) {
    //EXPECT_FALSE(TimeConverter<>::convert("").has_value());
}

TEST_F(LRU_Base, ShouldReturnValid) {
    v1::LRUCache<std::string,4> ca;

    ca.refer("1");
    ca.refer("2");
    ca.refer("3");
    ca.refer("4");
    ca.refer("5");
    ca.refer("6");
    ca.refer("4");

    auto it = std::cbegin(ca);
    EXPECT_EQ(*it, "4");
    std::advance(it,1);
    EXPECT_EQ(*it, "6");
    std::advance(it,1);
    EXPECT_EQ(*it, "5");
    std::advance(it,1);
    EXPECT_EQ(*it, "3");
}

TEST_F(LRU_Base, ShouldConvertString) {
}
