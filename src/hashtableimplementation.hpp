using std::unique_ptr;

template <typename K, typename T>
HashTable<K,T>::HashTable(int size, int (*h)(K), int (*h2)(int), Mode mode, double loadLimit, bool isReferenceOnly)
    : _size(size), _h(h), _h2(h2), _mode(mode), _loadLimit(loadLimit), _isReferenceOnly(isReferenceOnly)
{ 
    _count = 0;
    _table = unique_ptr<Cell[]>(new Cell[_size]);
    for(int i = 0; i < _size; ++i) {
        _table[i] = Cell();
    }
}

template <typename K, typename T>
HashTable<K,T>::~HashTable() { 
    deleteHashTable();
}

template <typename K, typename T>
HashTable<K,T>::HashTable(const HashTable& another) { 
    deepCopyHashTable(another);
}

template <typename K, typename T>
int HashTable<K,T>::count() const {
    return _count;
}

template <typename K, typename T>
int HashTable<K,T>::size() const {
    return _size;
}

template <typename K, typename T>
void HashTable<K,T>::operator=(const HashTable& another) { 
    if (this != &another) { 
        if(_table != nullptr){
            deleteHashTable();
        }

        deepCopyHashTable(another);
    } 
}

template <typename K, typename T>
int HashTable<K,T>::add(K key, T* data)
{
    int plus1 = (get(key) == nullptr);
    if(_count+plus1 > _loadLimit * _size) {
        int newSize = 2*_size;
        auto biggerTable = unique_ptr<Cell[]>(new Cell[newSize]);
        for(int i = 0; i < newSize; ++i) {
            biggerTable[i] = Cell();
        }

        //copy everything from table to biggerTable by rehashing
        for(int i = 0; i < _size; ++i) {
            if(_table[i].status == CellStatus::ACTIVE) {
                K k = _table[i].key;
                T* d = _table[i].data;
                
                int index = _h(k);
                int hash_index = -1;
                for (int i = 0; i < newSize; ++i) {
                    hash_index = getHashIndex(index, i, 2);
                    if (biggerTable[hash_index].status != CellStatus::ACTIVE) {
                        biggerTable[hash_index].status = CellStatus::ACTIVE;
                        biggerTable[hash_index].key = k;
                    }

                    if (biggerTable[hash_index].key == k) {
                        biggerTable[hash_index].data = d;
                        break;
                    }
                }                
            }
        }

        // reassign bigger table
        _size = newSize;
        _table.swap(biggerTable);

    }
    int collision_count = 0;
    
    int index = _h(key);
    int hash_index = -1;
    for (int i = 0; i < _size; ++i) {
        hash_index = getHashIndex(index, i);
        if (_table[hash_index].status != CellStatus::ACTIVE) {
            _table[hash_index].status = CellStatus::ACTIVE;
            _table[hash_index].key = key;
            _count++;
        } else {
            ++collision_count;
            if(collision_count >= _size) {
                collision_count = -1;
                break;
            }
        }

        if (_table[hash_index].key == key) {
            if(_isReferenceOnly == false) {
                if(_table[hash_index].data != nullptr) {            
                    delete _table[hash_index].data;
                    _table[hash_index].data = nullptr;
                }
                _table[hash_index].data = new T(*data);
            } else {
                _table[hash_index].data = data;
            }
            break;
        }
    }

    return collision_count;
}


template <typename K, typename T>
bool HashTable<K,T>::remove(K key)
{ 
    int index = _h(key);
    int hash_index = -1;
    for (int i = 0; i < _size; ++i) {
        hash_index = getHashIndex(index, i);
        if (_table[hash_index].status == CellStatus::ACTIVE) {                
            if(_table[hash_index].key == key) {
                _table[hash_index].status = CellStatus::DELETED;
                if(_isReferenceOnly == false) {
                    delete _table[hash_index].data;
                    _table[hash_index].data = nullptr;
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
    int index = _h(key);
    int hash_index = -1;
    for (int i = 0; i < _size; ++i) {
        hash_index = getHashIndex(index, i);
        if (_table[hash_index].status == CellStatus::ACTIVE) {                
            if(_table[hash_index].key == key) {
                return _table[hash_index].data;
            }
        } else {
            return nullptr;
        }
    }
    return nullptr;
}

template <typename K, typename T>
int HashTable<K,T>::getHashIndex(int h1index, int i, int sizeFactor) const {
    if(_mode == Mode::LINEAR) {
        return (h1index + i) % (_size * sizeFactor);
    } else if(_mode == Mode::QUADRATIC) {
        return (h1index + (i*i)) % (_size * sizeFactor);
    } else if(_mode == Mode::DOUBLE) {
        return (h1index + i * _h2(i)) % (_size * sizeFactor);    
    } else {
        return -1;
    }
}

template <typename K, typename T>
void HashTable<K,T>::deleteHashTable() {
    if(_isReferenceOnly == false) {
        for(int i = 0; i < _size; ++i) {
            if(_table[i].status != CellStatus::EMPTY && _table[i].data != nullptr) {
                delete _table[i].data;
                _table[i].data = nullptr;
            }
        }
    } 
}

template <typename K, typename T>
void HashTable<K,T>::deepCopyHashTable(const HashTable& another) {
    _size = another._size;
    _mode = another._mode;
    _h = another._h;
    _h2 = another._h2;
    _count = another._count;
    _loadLimit = another._loadLimit;
    _isReferenceOnly = another._isReferenceOnly;

    _table = unique_ptr<Cell[]>(new Cell[_size]);
    for(int i = 0; i < _size; ++i) {
        if(another._table[i].status == CellStatus::ACTIVE) {
            _table[i].key = another._table[i].key;
            _table[i].status = another._table[i].status;
            _table[i].data = new T(*(another._table[i].data));
        }
    }
}
