template <typename K, typename T>
HashTable<K,T>::HashTable(int m, int (*h)(K), int (*h2)(int), Mode mode, double loadLimit, bool isReferenceOnly)
    : m(m), h(h), h2(h2), mode(mode), loadLimit(loadLimit),isReferenceOnly(isReferenceOnly)
{ 
    _count = 0;
    table = new Cell[m];
    for(int i = 0; i < m; ++i) {
        table[i] = Cell();
    }
}


template <typename K, typename T>
HashTable<K,T>::~HashTable()
{ 
    if(isReferenceOnly == false) {
        for(int i = 0; i < m; ++i) {
            delete table[i].data;
            table[i].data = nullptr;
        }
    } 
    delete[] table;
}

template <typename K, typename T>
HashTable<K,T>::HashTable(const HashTable& another)
{ 
    m = another.m;
    mode = another.mode;
    h = another.h;
    h2 = another.h2;
    _count = another._count;
    loadLimit = another.loadLimit;
    isReferenceOnly = another.isReferenceOnly;

    table = new Cell[m];
    for(int i = 0; i < m; ++i) {
        if(another.table[i].status == CellStatus::ACTIVE) {
            table[i].key = another.table[i].key;
            table[i].status = another.table[i].status;
            table[i].data = new T(*(another.table[i].data));
        }
    }
}

template <typename K, typename T>
int HashTable<K,T>::count() const {
    return _count;
}

template <typename K, typename T>
int HashTable<K,T>::size() const {
    return m;
}

template <typename K, typename T>
void HashTable<K,T>::operator=(const HashTable& another)
{ 
    if (this != &another) { 
        if(table != nullptr){
            if(isReferenceOnly == false) {
                for(int i = 0; i < m; ++i) {
                    delete table[i].data;
                    table[i].data = nullptr;
                }
            } 
            delete[] table;
            table = nullptr;
        }

        m = another.m;
        mode = another.mode;
        h = another.h;
        h2 = another.h2;
        _count = another._count;
        loadLimit = another.loadLimit;
        isReferenceOnly = another.isReferenceOnly;

        table = new Cell[m];
        for(int i = 0; i < m; ++i) {
            if(another.table[i].status == CellStatus::ACTIVE) {
                table[i].key = another.table[i].key;
                table[i].status = another.table[i].status;
                table[i].data = new T(*(another.table[i].data));
            }
        }
    } 
}


template <typename K, typename T>
int HashTable<K,T>::add(K key, T* data)
{
    int plus1 = (get(key) == nullptr);
    if(_count+plus1 > loadLimit * m) {
        int _m = 2*m;
        Cell* biggerTable = new Cell[_m];
        for(int i = 0; i < _m; ++i) {
            biggerTable[i] = Cell();
        }

        //copy everything from table to biggerTable by rehashing
        for(int i = 0; i < m; ++i) {
            if(table[i].status == CellStatus::ACTIVE) {
                K _key = table[i].key;
                T* _data = table[i].data;
                
                int index = h(_key);
                int hash_index = -1;
                for (int i = 0; i < _m; ++i) {
                    if(mode == Mode::LINEAR) {
                    hash_index = (index + i) % _m;
                    } else if(mode == Mode::QUADRATIC) {
                        hash_index = (index + (i*i)) % _m;
                    } else if(mode == Mode::DOUBLE) {
                        hash_index = (index + i * h2(i)) % _m;                        
                    }
                    if (biggerTable[hash_index].status != CellStatus::ACTIVE) {
                        biggerTable[hash_index].status = CellStatus::ACTIVE;
                        biggerTable[hash_index].key = _key;
                    }

                    if (biggerTable[hash_index].key == _key) {
                        biggerTable[hash_index].data = _data;
                        break;
                    }
                }                
            }
        }

        // Delete table        
        delete[] table;
        
        // reassign bigger table
        m = _m;
        table = biggerTable;

    }
    int collision_count = 0;
    
    int index = h(key);
    int hash_index = -1;
    for (int i = 0; i < m; ++i) {
        if(mode == Mode::LINEAR) {
            hash_index = (index + i) % m;
        } else if(mode == Mode::QUADRATIC) {
            hash_index = (index + (i*i)) % m;
        } else if(mode == Mode::DOUBLE) {
            hash_index = (index + i * h2(i)) % m;    
        }
        if (table[hash_index].status != CellStatus::ACTIVE) {
            table[hash_index].status = CellStatus::ACTIVE;
            table[hash_index].key = key;
            _count++;
        } else {
            ++collision_count;
            if(collision_count >= m) {
                collision_count = -1;
                break;
            }
        }

        if (table[hash_index].key == key) {
            ///TODO: before overriding data, delete it if necessary
            table[hash_index].data = data;
            break;
        }
    }

    return collision_count;
}


template <typename K, typename T>
bool HashTable<K,T>::remove(K key)
{ 
    int index = h(key);
    int hash_index = -1;
    for (int i = 0; i < m; ++i) {
        if(mode == Mode::LINEAR) {
            hash_index = (index + i) % m;
        } else if(mode == Mode::QUADRATIC) {
            hash_index = (index + (i*i)) % m;
        } else if(mode == Mode::DOUBLE) {
            hash_index = (index + i * h2(i)) % m;    
        }
        if (table[hash_index].status == CellStatus::ACTIVE) {                
            if(table[hash_index].key == key) {
                table[hash_index].status = CellStatus::DELETED;
                if(isReferenceOnly == false) {
                    delete table[hash_index].data;
                    table[hash_index].data = nullptr;
                }
                _count--;
                return true;
            }
        } else {
            return false;
        }
    }
    return false;
}


template <typename K, typename T>
T* HashTable<K,T>::get(K key) const
{ 
    int index = h(key);
    int hash_index = -1;
    for (int i = 0; i < m; ++i) {
        if(mode == Mode::LINEAR) {
            hash_index = (index + i) % m;
        } else if(mode == Mode::QUADRATIC) {
            hash_index = (index + (i*i)) % m;
        } else if(mode == Mode::DOUBLE) {
            hash_index = (index + i * h2(i)) % m;    
        }
        if (table[hash_index].status == CellStatus::ACTIVE) {                
            if(table[hash_index].key == key) {
                return table[hash_index].data;
            }
        } else {
            return nullptr;
        }
    }
    return nullptr;
}
