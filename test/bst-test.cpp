#include "gtest/gtest.h"
#include "bst.hpp"

TEST(BSTTestIsEmpty, testIsEmpty1) {
    BST<int> bst;
    EXPECT_TRUE(bst.isEmpty());
}

TEST(BSTTestAdd, testAdd1) {
    BST<int> bst;
    EXPECT_TRUE(bst.add("1", 1));
}

TEST(BSTTestIsEmpty, testIsEmpty2) {
    BST<int> bst;
    EXPECT_TRUE(bst.isEmpty());
    EXPECT_TRUE(bst.add("1", 1));
    EXPECT_FALSE(bst.isEmpty());
}

TEST(BSTTestRemove, testRemove1) {
    BST<int> bst;
    EXPECT_TRUE(bst.add("1", 1));
    EXPECT_TRUE(bst.remove("1"));
}

TEST(BSTTestIsEmpty, testIsEmpty3) {
    BST<int> bst;
    EXPECT_TRUE(bst.isEmpty());
    EXPECT_TRUE(bst.add("1", 1));
    EXPECT_TRUE(bst.remove("1"));
    EXPECT_TRUE(bst.isEmpty());
}

TEST(BSTTestAdd, testAdd2) {
    BST<int> bst;
    EXPECT_TRUE(bst.add("1", 1));
    EXPECT_FALSE(bst.add("1", 1));
}

TEST(BSTTestRemove, testRemove2) {
    BST<int> bst;
    EXPECT_FALSE(bst.remove("1"));
}

TEST(BSTTestMin, testMin1) {
    BST<int> bst;
    string s[] = {"g", "u", "n", "e", "y", "k", "a", "y", "i", "m"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    
    EXPECT_TRUE(bst.findMin()->getRootKey()->compare("a") == 0);
}

TEST(BSTTestMin, testMin2) {
    BST<int> bst;
    string s[] = {"g", "u", "n", "e", "y", "k", "a", "y", "i", "m"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    bst.remove("a");
    auto res = bst.findMin()->getRootKey();
    EXPECT_FALSE(res->compare("a") == 0);
    EXPECT_TRUE(res->compare("e") == 0);
}

TEST(BSTTestMax, testMax1) {
    BST<int> bst;
    string s[] = {"g", "u", "n", "e", "y", "k", "a", "y", "i", "m"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    
    EXPECT_TRUE(bst.findMax()->getRootKey()->compare("y") == 0);
}

TEST(BSTTestMax, testMax2) {
    BST<int> bst;
    string s[] = {"g", "u", "n", "e", "y", "k", "a", "y", "i", "m"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    bst.remove("y");
    auto res = bst.findMax()->getRootKey();
    EXPECT_FALSE(res->compare("y") == 0);
    EXPECT_TRUE(res->compare("u") == 0);
}

TEST(BSTTestRange, testBetweenRange1) {
    BST<int> bst;
    string s[] = {"g", "u", "n", "e", "y", "k", "a", "y", "i", "m"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    auto r = bst.getBetweenRange("a", "z");
    auto s_size = sizeof(s)/sizeof(s[0]);
    EXPECT_TRUE(r->size() == s_size - 1); // -1 because s[] has "y" 2 times, one of them is not added
}

TEST(BSTTestRange, testBetweenRange2) {
    BST<int> bst;
    string s[] = {"g", "u", "n", "e", "y", "k", "a", "y", "i", "m"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    bst.remove("g");
    auto r = bst.getBetweenRange("a", "z");
    auto s_size = sizeof(s)/sizeof(s[0]);
    EXPECT_TRUE(r->size() == s_size-2);
}

TEST(BSTTestRange, testBetweenRange3) {
    BST<int> bst;
    string s[] = {"g", "u", "n", "e", "y", "k", "a", "y", "i", "m"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    auto r = bst.getBetweenRange("a", "e");
    EXPECT_TRUE(r->size() == 2);
}

TEST(BSTTestRange, testBetweenRange4) {
    BST<int> bst;
    string s[] = {"g", "u", "n", "e", "y", "k", "a", "y", "i", "m"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    auto r = bst.getBetweenRange("a", "k");
    EXPECT_TRUE(r->size() == 5);
}

TEST(BSTTestRange, testBetweenRange5) {
    BST<int> bst;
    string s[] = {"g", "u", "n", "e", "y", "k", "a", "y", "i", "m"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    bst.remove("y");
    auto r = bst.getBetweenRange("h", "z");
    EXPECT_TRUE(r->size() == 5);
}

TEST(BSTTestRange, testBetweenRange6) {
    BST<int> bst;
    string s[] = {"g", "u", "n", "e", "y", "k", "a", "y", "i", "m"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    auto r = bst.getBetweenRange("a", "z");
    
    bool isAscending = true;
    string p = r->front().first, c;
    for(int i = 1; i < r->size(); ++i) {
        r->pop_front();
        c = r->front().first;
        isAscending &= c > p;
        p = c;
    }

    EXPECT_TRUE(isAscending);
}