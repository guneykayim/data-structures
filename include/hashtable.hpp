#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

enum class Mode {
   LINEAR, 
   QUADRATIC, 
   DOUBLE 
};

template <typename K, typename T>
class HashTable {
public:
    HashTable(int size, int (*h)(K), int (*h2)(int), Mode mode, double loadLimit, bool isReferenceOnly = false);

    HashTable(const HashTable &another);

    ~HashTable();

    int count() const;

    int size() const;

    void operator=(const HashTable& another);

    int add(K key, T *data);

    bool remove(K key);

    T* get(K key) const;

private:
   enum class CellStatus {
       EMPTY, 
       ACTIVE, 
       DELETED 
   };

   struct Cell {
       K key; 
       T* data; 
       CellStatus status; 
   };

    int _size; 
    Mode _mode; 
    Cell* _table;
    int (*_h)(K);
    int (*_h2)(int); 
    int _count; 
    double _loadLimit;
    bool _isReferenceOnly;

    int getHashIndex(int h1index, int i, int sizeFactor = 1) const;

    void deleteHashTable();

    void deepCopyHashTable(const HashTable& another);
};

#include "hashtableimplementation.hpp"

#endif //HASHTABLE_HPP
