# data-structures

[![License](https://img.shields.io/badge/licence-MIT-5a8d81)](https://github.com/guneykayim/data-structures/blob/master/LICENSE)
[![Build Status](https://github.com/guneykayim/data-structures/workflows/build/badge.svg)](https://github.com/guneykayim/data-structures)

C++ implementations of various data structures

## Data structures

### Binary Search Tree

* BST is constructed using a `string` key. Along with the key, values of any type can be stored.

#### Sample usage

```cpp
// create the binary search tree object
BST<int> bst;

// add data
bst.add("mykey", 1);
```

### Hash Table

* Both keys and values can be any type.
* The hash function needs to be specified by the user for the given key data type.
* Open addressing is being used.
* Collision resolving can be `linear probing`, `quadratic probing` or `double hashing`.
* User can start off with a small table size and as more items are added to the table, it will auto-resize and re-hash.

#### Sample usage

```cpp
// define hash functions
int (*hash_func_str)(string) = [](string s) { 
    int sum = 0;
    for(char c : s) {
        sum += c;
    }
    return sum % INT16_MAX;
};

int (*hash_func_int)(int) = [](int n) { return n * 2; };

// create the hash table object
int size = 10;
HashTable<string, int> ht(size, hash_func_str, hash_func_int, Mode::LINEAR, 0.5);

// add data
ht.add("mykey", new int(5));
```

## Building

```sh
mkdir build && cd build
cmake ..
make -j4
```

## Running the tests

```sh
./bin/data_structures_test
```
