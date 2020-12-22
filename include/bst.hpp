#ifndef BST_HPP
#define BST_HPP

#include <list>
#include <string>

using std::string;
using std::list;
using std::pair;
using std::shared_ptr;

template <typename T>
class BST
{
public:

    BST() = default;

    BST(const BST &another);

    bool isEmpty() const;

    bool add(string key, T value);

    bool remove(string key);

    T *get(string key) const;

    T *getRootValue() const;

    string *getRootKey() const;

    list <pair<string, T>> *getBetweenRange(string start, string end) const;

    const BST *findMin() const;

    const BST *findMax() const;

private:
    template <typename S>
    struct BSTNode
    {
        string key;
        S value;

        BST<S> left; // left sub-tree (left child)
        BST<S> right; // right sub-tree (right child)
        BSTNode(string key, S value) : key(key), value(value) {};
    };

    shared_ptr<BSTNode<T>> root;
    void getBetweenRangeHelper(const BST<T> *current_bst, string start, string end, list <pair<string, T>> *resultList) const;
};

#include "bstimplementation.hpp"

#endif //BST_HPP
