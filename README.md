# data-structures

[![License](https://img.shields.io/badge/licence-MIT-5a8d81)](https://github.com/guneykayim/data-structures/blob/master/LICENSE)
[![Build Status](https://github.com/guneykayim/data-structures/workflows/build/badge.svg)](https://github.com/guneykayim/data-structures)

C++ implementations of various data structures

## Data structures

### Binary Search Tree

* BST is constructed using a `string` key. Along with the key, values of any type can be stored.

### Hash Table

* Both keys and values can be any type.
* The hash function needs to be specified by the user for the given key data type.
* Open addressing is being used.
* Collision resolving can be `linear probing`, `quadratic probing` or `double hashing`.
* User can start off with a small table size and as more items are added to the table, it will auto-resize and re-hash.

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
