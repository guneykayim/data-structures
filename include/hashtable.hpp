#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

using std::unique_ptr;
using std::shared_ptr;

enum class Mode {
   LINEAR, 
   QUADRATIC, 
   DOUBLE 
};

template <typename K, typename T>
class HashTable {
public:
    HashTable(int size, int (*h)(K), int (*h2)(int), Mode mode, double loadLimit);

    HashTable(const HashTable &another);

    ~HashTable();

    int count() const;

    int size() const;

    void operator=(const HashTable& another);

    int add(K key, shared_ptr<T> data);

    bool remove(K key);

    shared_ptr<T> get(K key) const;

private:
   enum class CellStatus {
       EMPTY, 
       ACTIVE, 
       DELETED 
   };

   struct Cell {
       K key; 
       shared_ptr<T> data; 
       CellStatus status; 
   };

    int _size; 
    Mode _mode; 
    unique_ptr<Cell[]> _table;
    int (*_h)(K);
    int (*_h2)(int); 
    int _count; 
    double _loadLimit;

    int getHashIndex(int h1index, int i, int sizeFactor = 1) const;

    void deleteHashTable();

    void deepCopyHashTable(const HashTable& another);
};

#include "hashtableimplementation.hpp"

#endif //HASHTABLE_HPP
