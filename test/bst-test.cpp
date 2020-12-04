#include "gtest/gtest.h"
#include "bst.hpp"

TEST(BSTTestBasic, testIsEmpty1) {
    BST<int> bst;
    EXPECT_TRUE(bst.isEmpty());
}

TEST(BSTTestBasic, testAdd1) {
    BST<int> bst;
    EXPECT_TRUE(bst.add("1", 1));
}

TEST(BSTTestBasic, testIsEmpty2) {
    BST<int> bst;
    EXPECT_TRUE(bst.isEmpty());
    EXPECT_TRUE(bst.add("1", 1));
    EXPECT_FALSE(bst.isEmpty());
}

TEST(BSTTestBasic, testRemove1) {
    BST<int> bst;
    EXPECT_TRUE(bst.add("1", 1));
    EXPECT_TRUE(bst.remove("1"));
}

TEST(BSTTestBasic, testIsEmpty3) {
    BST<int> bst;
    EXPECT_TRUE(bst.isEmpty());
    EXPECT_TRUE(bst.add("1", 1));
    EXPECT_TRUE(bst.remove("1"));
    EXPECT_TRUE(bst.isEmpty());
}

TEST(BSTTestBasic, testAdd2) {
    BST<int> bst;
    EXPECT_TRUE(bst.add("1", 1));
    EXPECT_FALSE(bst.add("1", 1));
}

TEST(BSTTestBasic, testRemove2) {
    BST<int> bst;
    EXPECT_FALSE(bst.remove("1"));
}

TEST(BSTTestBasic, testMin1) {
    BST<int> bst;
    string s[] = {"s", "c", "e", "b", "d", "g", "z", "w", "y"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    
    EXPECT_TRUE(bst.findMin()->getRootKey()->compare("b") == 0);
}

TEST(BSTTestBasic, testMin2) {
    BST<int> bst;
    string s[] = {"s", "c", "e", "b", "d", "g", "z", "w", "y"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    bst.remove("b");
    auto res = bst.findMin()->getRootKey();
    EXPECT_FALSE(res->compare("b") == 0);
    EXPECT_TRUE(res->compare("c") == 0);
}

TEST(BSTTestBasic, testMax1) {
    BST<int> bst;
    string s[] = {"s", "c", "e", "b", "d", "g", "z", "w", "y"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    
    EXPECT_TRUE(bst.findMax()->getRootKey()->compare("z") == 0);
}

TEST(BSTTestBasic, testMax2) {
    BST<int> bst;
    string s[] = {"s", "c", "e", "b", "d", "g", "z", "w", "y"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    bst.remove("z");
    auto res = bst.findMax()->getRootKey();
    EXPECT_FALSE(res->compare("z") == 0);
    EXPECT_TRUE(res->compare("y") == 0);
}
