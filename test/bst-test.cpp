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

TEST(BSTTestBetweenRange, testBetweenRange1) {
    BST<int> bst;
    string s[] = {"g", "u", "n", "e", "y", "k", "a", "y", "i", "m"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    auto r = bst.getBetweenRange("a", "z");
    auto s_size = sizeof(s)/sizeof(s[0]);
    EXPECT_TRUE(r->size() == s_size - 1); // -1 because s[] has "y" 2 times, one of them is not added
}

TEST(BSTTestBetweenRange, testBetweenRange2) {
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

TEST(BSTTestBetweenRange, testBetweenRange3) {
    BST<int> bst;
    string s[] = {"g", "u", "n", "e", "y", "k", "a", "y", "i", "m"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    auto r = bst.getBetweenRange("a", "e");
    EXPECT_TRUE(r->size() == 2);
}

TEST(BSTTestBetweenRange, testBetweenRange4) {
    BST<int> bst;
    string s[] = {"g", "u", "n", "e", "y", "k", "a", "y", "i", "m"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    auto r = bst.getBetweenRange("a", "k");
    EXPECT_TRUE(r->size() == 5);
}

TEST(BSTTestBetweenRange, testBetweenRange5) {
    BST<int> bst;
    string s[] = {"g", "u", "n", "e", "y", "k", "a", "y", "i", "m"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    bst.remove("y");
    auto r = bst.getBetweenRange("h", "z");
    EXPECT_TRUE(r->size() == 5);
}

TEST(BSTTestBetweenRange, testBetweenRange6) {
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

TEST(BSTTestCopyConstructor, testCopyConstructor1) {
    BST<int> bst;
    string s[] = {"g", "u", "n", "e", "y", "k", "a", "y", "i", "m"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    
    BST<int> bst2(bst);

    EXPECT_EQ(bst.isEmpty(), bst2.isEmpty());
    EXPECT_NE(bst.findMax(), bst2.findMax()); 
    EXPECT_TRUE(bst.findMax()->getRootKey()->compare(*(bst2.findMax()->getRootKey())) == 0);
    EXPECT_NE(bst.findMax()->getRootKey(), bst2.findMax()->getRootKey()); 
    EXPECT_EQ(*(bst.findMax()->getRootValue()), *(bst2.findMax()->getRootValue()));
    EXPECT_NE(bst.findMax()->getRootValue(), bst2.findMax()->getRootValue());
    EXPECT_TRUE(bst.findMin()->getRootKey()->compare(*(bst2.findMin()->getRootKey())) == 0);
    EXPECT_NE(bst.findMin()->getRootKey(), bst2.findMin()->getRootKey()); 
    EXPECT_EQ(*(bst.findMin()->getRootValue()), *(bst2.findMin()->getRootValue()));
    EXPECT_NE(bst.findMin()->getRootValue(), bst2.findMin()->getRootValue());
}

TEST(BSTTestCopyConstructor, testCopyConstructor2) {
    BST<int> bst;
    string s[] = {"g", "u", "n", "e", "y", "k", "a", "y", "i", "m"};
    for (string e : s) {
        bst.add(e, e[0] - 'a' + 1);
    }
    
    BST<int> bst2(bst);
    bst.remove("a");

    EXPECT_FALSE(bst.findMin()->getRootKey()->compare(*(bst2.findMin()->getRootKey())) == 0);
    EXPECT_NE(*(bst.findMin()->getRootValue()), *(bst2.findMin()->getRootValue()));
}

TEST(BSTTestCopyConstructor, testCopyConstructor3) {
    BST<int> *bst = new BST<int>();
    string s[] = {"g", "u", "n", "e", "y", "k", "a", "y", "i", "m"};
    for (string e : s) {
        bst->add(e, e[0] - 'a' + 1);
    }
    
    BST<int> bst2(*bst);
    
    delete bst;

    EXPECT_FALSE(bst2.isEmpty());
    EXPECT_TRUE(bst2.findMin()->getRootKey()->compare("a") == 0);
    EXPECT_TRUE(bst2.findMax()->getRootKey()->compare("y") == 0);
}