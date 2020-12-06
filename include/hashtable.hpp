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
    HashTable(int m, int (*h)(K), int (*h2)(int), Mode mode, double loadLimit, bool isReferenceOnly = false);

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

    int m; 
    Mode mode; 
    Cell* table;
    int (*h)(K);
    int (*h2)(int); 
    int _count; 
    double loadLimit;
    bool isReferenceOnly;
};

#include "hashtableimplementation.hpp"

#endif //HASHTABLE_HPP
