#include "gtest/gtest.h"
#include "hashtable.hpp"
#include <string>

using std::string;

int (*hash_func_str)(string) = [](string s) { return 5 - ((int) s.length()) % 5; };
int (*hash_func_int)(int) = [](int n) { return n * 2; };

TEST(HashTableTestIsEmpty, testIsEmpty1) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5);
    EXPECT_EQ(ht.size(), size);
    EXPECT_EQ(ht.count(), 0);
}

TEST(HashTableTestAdd, testAdd1) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5);
    int *i = new int(5);
    EXPECT_EQ(ht.add("guney", i), 0);
}

TEST(HashTableTestIsEmpty, testIsEmpty2) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5);
    int *i = new int(5);
    ht.add("guney", i);
    EXPECT_EQ(ht.count(), 1);
}

TEST(HashTableTestAdd, testAdd2) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5);
    int *i = new int(5);
    int *i2 = new int(10);
    ht.add("guney", i), 0;
    EXPECT_EQ(ht.add("yenug", i2), 1); // 1 collision as both strings will have the same hash
}

TEST(HashTableTestRemove, testRemove1) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5);
    EXPECT_EQ(ht.remove("guney"), false);
}

TEST(HashTableTestRemove, testRemove2) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5);
    int *i = new int(5);
    ht.add("guney", i);
    EXPECT_EQ(ht.remove("guney"), true);
}

TEST(HashTableTestIsEmpty, testIsEmpty3) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5);
    int *i = new int(5);
    ht.add("guney", i);
    ht.remove("guney");
    EXPECT_EQ(ht.count(), 0);
}

TEST(HashTableTestResize, testResize1) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5);
    string s[] = {"g", "u", "n", "e", "y"};
    for (string e : s) {
        int *i = new int(e[0] - 'a' + 1);
        ht.add(e, i);
    }
    EXPECT_EQ(ht.count(), 5);
    EXPECT_EQ(ht.size(), 10);
    
    int *i = new int(100);
    ht.add("G", i);
    
    EXPECT_EQ(ht.count(), 6);
    EXPECT_EQ(ht.size(), 20);
}

TEST(HashTableTestAdd, testAdd3) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5);
    int *i = new int(5);
    int *i2 = new int(10);
    ht.add("guney", i), 0;
    EXPECT_EQ(ht.add("guney", i2), 1); 
    EXPECT_EQ(*ht.get("guney"), *i2);
}

TEST(HashTableMemoryManagement, testMemoryManagement1) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5, false);
    int *i = new int(5);
    ht.add("guney", i);
    EXPECT_NE(i, ht.get("guney"));
    EXPECT_EQ(*i, *ht.get("guney"));
}

TEST(HashTableMemoryManagement, testMemoryManagement2) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5, true);
    int *i = new int(5);
    ht.add("guney", i);
    EXPECT_EQ(i, ht.get("guney"));
    EXPECT_EQ(*i, *ht.get("guney"));
}