#include "gtest/gtest.h"
#include "bst.hpp"


TEST(BSTTest, simpleTest1) {
    BST<string> bst;
    EXPECT_TRUE(bst.isEmpty());
    bst.add("1", "1");
    EXPECT_FALSE(bst.isEmpty());
}
