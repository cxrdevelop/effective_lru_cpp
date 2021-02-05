#include "gtest/gtest.h"
#include "lru_v1.h"

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

    ca.put("1");
    ca.put("2");
    ca.put("3");
    ca.put("4");
    ca.put("5");
    ca.put("6");
    ca.put("4");

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
