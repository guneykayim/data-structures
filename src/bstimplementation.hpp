using std::make_shared;

template <typename T>
BST<T>::BST(const BST &another) { 
    if(another.isEmpty()) {
        return;
    }
    this->root = make_shared<BSTNode<T>>(*another.root);
}

template <typename T>
bool BST<T>::isEmpty() const { 
    return this->root == nullptr;
}

template <typename T>
bool BST<T>::add(string key, T value) { 
    if(isEmpty()) {
        this->root = make_shared<BSTNode<T>>(key, value);
        return true;
    } else if(key.compare(this->root->key) == 0) {
        return false;
    } else if(key.compare(this->root->key) < 0 ) {
        return this->root->left.add(key, value);
    } else {
        return this->root->right.add(key, value);
    }
}

template <typename T>
bool BST<T>::remove(string key) { 
    if(isEmpty()){
        return false;
    } else if(key.compare(this->root->key) == 0){
        if(this->root->left.root == nullptr && this->root->right.root == nullptr){ // no BSTs in right or left
            this->root = nullptr;            
        } else if(this->root->left.root != nullptr && this->root->right.root == nullptr){ // there is a BST in left
            shared_ptr<BSTNode<T>> tmp = this->root->left.root;
            this->root = make_shared<BSTNode<T>>(tmp->key, tmp->value);
            this->root->left.root = tmp->left.root;
            this->root->right.root = tmp->right.root; 
        } else if(this->root->left.root == nullptr && this->root->right.root != nullptr){ // there is a BST in right
            shared_ptr<BSTNode<T>> tmp = this->root->right.root;
            this->root = make_shared<BSTNode<T>>(tmp->key, tmp->value);
            this->root->left.root = tmp->left.root;
            this->root->right.root = tmp->right.root;
        } else{
            const BST<T>* rightMinTree = this->root->right.findMin();
            string tempkey = rightMinTree->root->key;
            T tempvalue = rightMinTree->root->value;
            this->root->right.remove(rightMinTree->root->key);
            this->root->key = tempkey;
            this->root->value = tempvalue;
        }
        
        return true;
        
    } else if(key.compare(this->root->key) < 0){
        return this->root->left.remove(key);
    } else{
        return this->root->right.remove(key);
    }
}

template <typename T>
T *BST<T>::get(string key) const {
    if(this->root == nullptr) {
        return nullptr;
    }
    if(this->root->key.compare(key) == 0) {
        return &this->root->value;
    } else if(key.compare(this->root->key) < 0){
        return this->root->left.get(key);
    } else{
        return this->root->right.get(key);
    }
}
template <typename T>
T *BST<T>::getRootValue() const {
    if(isEmpty()) {
        return nullptr;
    } else {
        return &this->root->value;
    }
}

template <typename T>
string *BST<T>::getRootKey() const {
    if(isEmpty()) {
        return nullptr;
    } else {
        return &this->root->key;
    }
}

template <typename T>
list <pair<string, T>> *BST<T>::getBetweenRange(string start, string end) const {
    if (start > end) {
        string temp = end;
        end = start;
        start = temp;
    }
    list<pair<string, T>> *resultList = new list<pair<string, T>>;
    this->getBetweenRangeHelper(this, start, end, resultList);

    return resultList;
}

template <typename T>
const BST<T>* BST<T>::findMin() const { 
    if(this->root == nullptr) {
        return nullptr;
    } else if(this->root->left.root == nullptr) {
        return this;
    } else {
        return this->root->left.findMin();
    }
}

template <typename T>
const BST<T>* BST<T>::findMax() const { 
    if(this->root == nullptr) {
        return nullptr;
    } else if(this->root->right.root == nullptr) {
        return this;
    } else {
        return this->root->right.findMax();
    }
}

template <typename T>
void BST<T>::getBetweenRangeHelper(const BST<T> *current_bst, string start, string end, list<pair<string, T>> *resultList) const {
    if(current_bst->root == nullptr) {
        return;
    }
    getBetweenRangeHelper(&(current_bst->root->left), start, end, resultList);
    if(current_bst->root->key.compare(start) >= 0 && current_bst->root->key.compare(end) <= 0) {
        resultList->push_back({current_bst->root->key, current_bst->root->value});
    }
    getBetweenRangeHelper(&(current_bst->root->right), start, end, resultList);
}
