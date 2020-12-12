#include "gtest/gtest.h"
#include "hashtable.hpp"
#include <string>

using std::string;

int (*hash_func_str)(string) = [](string s) { 
    int sum = 0;
    for(char c : s) {
        sum += c;
    }
    return sum % INT16_MAX;
};
int (*hash_func_int)(int) = [](int n) { return n * 2; };

TEST(HashTableIsEmpty, test1) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5);
    EXPECT_EQ(ht.size(), size);
    EXPECT_EQ(ht.count(), 0);
}

TEST(HashTableAdd, test1) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5);
    int *i = new int(5);
    EXPECT_EQ(ht.add("guney", i), 0);
}

TEST(HashTableIsEmpty, test2) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5);
    int *i = new int(5);
    ht.add("guney", i);
    EXPECT_EQ(ht.count(), 1);
}

TEST(HashTableAdd, test2) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5);
    int *i = new int(5);
    int *i2 = new int(10);
    ht.add("guney", i), 0;
    EXPECT_EQ(ht.add("yenug", i2), 1); // 1 collision as both strings will have the same hash
}

TEST(HashTableRemove, test1) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5);
    EXPECT_EQ(ht.remove("guney"), false);
}

TEST(HashTableRemove, test2) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5);
    int *i = new int(5);
    ht.add("guney", i);
    EXPECT_EQ(ht.remove("guney"), true);
}

TEST(HashTableIsEmpty, test3) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5);
    int *i = new int(5);
    ht.add("guney", i);
    ht.remove("guney");
    EXPECT_EQ(ht.count(), 0);
}

TEST(HashTableResize, test1) {
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

TEST(HashTableAdd, test3) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5);
    int *i = new int(5);
    int *i2 = new int(10);
    ht.add("guney", i), 0;
    EXPECT_EQ(ht.add("guney", i2), 1); 
    EXPECT_EQ(*ht.get("guney"), *i2);
}

TEST(HashTableMemoryManagement, test1) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5, false);
    int *i = new int(5);
    ht.add("guney", i);
    EXPECT_NE(i, ht.get("guney"));
    EXPECT_EQ(*i, *ht.get("guney"));
}

TEST(HashTableMemoryManagement, test2) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5, true);
    int *i = new int(5);
    ht.add("guney", i);
    EXPECT_EQ(i, ht.get("guney"));
    EXPECT_EQ(*i, *ht.get("guney"));
}

TEST(HashTableCollision, test1) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5);
    string s = "guneykayimimplementshashtable";
    string expectedResult = "00001012001100111100011111011";
    string actualResult = "";
    for (char c : s) {
        int *i = new int(c - 'a' + 1);
        actualResult.append(std::to_string(ht.add(string(1, c), i)));
    }
    EXPECT_EQ(expectedResult, actualResult);
}

TEST(HashTableCollision, test2) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::QUADRATIC, 0.5);
    string s = "guneykayimimplementshashtable";
    string expectedResult = "00001012001100111100011111011";
    string actualResult = "";
    for (char c : s) {
        int *i = new int(c - 'a' + 1);
        actualResult.append(std::to_string(ht.add(string(1, c), i)));
    }
    EXPECT_EQ(expectedResult, actualResult);
}

TEST(HashTableCollision, test3) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::DOUBLE, 0.5);
    string s = "guneykayimimplementshashtable";
    string expectedResult = "00002013011200111100011111011";
    string actualResult = "";
    for (char c : s) {
        int *i = new int(c - 'a' + 1);
        actualResult.append(std::to_string(ht.add(string(1, c), i)));
    }
    EXPECT_EQ(expectedResult, actualResult);
}

TEST(HashTableDeepCopy, test1) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5, true);
    string cities[] = {"istanbul", "nottingham", "manchester", "cambridge", "london", "zurich", "los angeles"};
    int n = sizeof(cities)/sizeof(*cities);
    for(int i = 0; i < n; ++i){
        ht.add(cities[i], new int(i));
    }
    
    HashTable<string, int> htCopy(ht);
    for(int i = 0; i < n; ++i){
        EXPECT_EQ(*ht.get(cities[i]), *htCopy.get(cities[i]));
        EXPECT_NE(ht.get(cities[i]), htCopy.get(cities[i]));
    }
}

// TEST(HashTableDeepCopy, test2) {
//     int size = 10;
//     HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5, false);
//     string cities[] = {"istanbul", "nottingham", "manchester", "cambridge", "london", "zurich", "los angeles"};
//     int n = sizeof(cities)/sizeof(*cities);
//     for(int i = 0; i < n; ++i){
//         ht.add(cities[i], new int(i));
//     }
    
//     HashTable<string, int> htCopy(ht);
//     for(int i = 0; i < n; ++i){
//         EXPECT_EQ(*ht.get(cities[i]), *htCopy.get(cities[i]));
//         EXPECT_NE(ht.get(cities[i]), htCopy.get(cities[i]));
//     }
// }

TEST(HashTableDeepCopy, test3) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5, true);
    string cities[] = {"istanbul", "nottingham", "manchester", "cambridge", "london", "zurich", "los angeles"};
    int n = sizeof(cities)/sizeof(*cities);
    for(int i = 0; i < n; ++i){
        ht.add(cities[i], new int(i));
    }
    
    HashTable<string, int> htCopy(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5, true);
    htCopy = ht;
    for(int i = 0; i < n; ++i){
        EXPECT_EQ(*ht.get(cities[i]), *htCopy.get(cities[i]));
        EXPECT_NE(ht.get(cities[i]), htCopy.get(cities[i]));
    }
}

// TEST(HashTableDeepCopy, test4) {
//     int size = 10;
//     HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5, false);
//     string cities[] = {"istanbul", "nottingham", "manchester", "cambridge", "london", "zurich", "los angeles"};
//     int n = sizeof(cities)/sizeof(*cities);
//     for(int i = 0; i < n; ++i){
//         ht.add(cities[i], new int(i));
//     }
    
//     HashTable<string, int> htCopy(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5, false);
//     htCopy = ht;
//     for(int i = 0; i < n; ++i){
//         EXPECT_EQ(*ht.get(cities[i]), *htCopy.get(cities[i]));
//         EXPECT_NE(ht.get(cities[i]), htCopy.get(cities[i]));
//     }
// }

TEST(HashTableDeepCopy, test5) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5, true);
    string cities[] = {"istanbul", "nottingham", "manchester", "cambridge", "london", "zurich", "los angeles"};
    int n = sizeof(cities)/sizeof(*cities);
    for(int i = 0; i < n; ++i){
        ht.add(cities[i], new int(i));
    }
    
    HashTable<string, int> htCopy(ht);

    for(int i = 0; i < n; ++i){
        ht.remove(cities[i]);
    }

    for(int i = 0; i < n; ++i){
        EXPECT_EQ(*htCopy.get(cities[i]), i);
    }
}

// TEST(HashTableDeepCopy, test6) {
//     int size = 10;
//     HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5, false);
//     string cities[] = {"istanbul", "nottingham", "manchester", "cambridge", "london", "zurich", "los angeles"};
//     int n = sizeof(cities)/sizeof(*cities);
//     for(int i = 0; i < n; ++i){
//         ht.add(cities[i], new int(i));
//     }
    
//     HashTable<string, int> htCopy(ht);

//     for(int i = 0; i < n; ++i){
//         ht.remove(cities[i]);
//     }

//     for(int i = 0; i < n; ++i){
//         EXPECT_EQ(*htCopy.get(cities[i]), i);
//     }
// }

TEST(HashTableDeepCopy, test7) {
    int size = 10;
    HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5, true);
    string cities[] = {"istanbul", "nottingham", "manchester", "cambridge", "london", "zurich", "los angeles"};
    int n = sizeof(cities)/sizeof(*cities);
   
    for(int i = 0; i < n; ++i){
        ht.add(cities[i], new int(i));
    }
    
    HashTable<string, int> htCopy(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5, true);
    htCopy = ht;

    for(int i = 0; i < n; ++i){
        ht.remove(cities[i]);
    }

    for(int i = 0; i < n; ++i){
        EXPECT_EQ(*htCopy.get(cities[i]), i);
    }
}

// TEST(HashTableDeepCopy, test8) {
//     int size = 10;
//     HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5, false);
//     string cities[] = {"istanbul", "nottingham", "manchester", "cambridge", "london", "zurich", "los angeles"};
//     int n = sizeof(cities)/sizeof(*cities);

//     for(int i = 0; i < n; ++i){
//         ht.add(cities[i], new int(i));
//     }
    
//     HashTable<string, int> htCopy(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5, false);
//     htCopy = ht;

//     for(int i = 0; i < n; ++i){
//         ht.remove(cities[i]);
//     }

//     for(int i = 0; i < n; ++i){
//         EXPECT_EQ(*htCopy.get(cities[i]), i);
//     }
// }