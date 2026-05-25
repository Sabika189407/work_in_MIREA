#include "BST.h"

BinarySearchTree::Node::Node(Key key, Value value, BinarySearchTree::Node *parent, BinarySearchTree::Node *left, BinarySearchTree::Node *right)
    :keyValuePair{key, value}, parent(parent), left(left), right(right) {}

BinarySearchTree::Node::Node(const BinarySearchTree::Node &other)
    :keyValuePair{other.keyValuePair.first, other.keyValuePair.second}, parent(nullptr)
{
    if (other.left) //if in that tree is subtrees
    {
        left = new Node(*other.left); //if it is, copying it our's tree
        left->parent = this;
    }
    else
    {
        left = nullptr; //if not, making nullptr
    }
    if (other.right)
    {
        right = new Node(*other.right);
        right->parent = this;
    }
    else
    {
        right = nullptr;
    }
}

bool BinarySearchTree::Node::operator==(const BinarySearchTree::Node &other) const
{
    if (this->keyValuePair.first == other.keyValuePair.first)
    {
        return true;
    }
    return false;
}

void BinarySearchTree::Node::output_node_tree() const
{
    if (left) //if left exist
    {
        left->output_node_tree(); //left is outputting by recurse
    }
    std::cout << "Node - key: " << this->keyValuePair.first << ", value: " << this->keyValuePair.second << ";\t"; //after that this tree is outputting
    if  (right) //if right exist
    {
        right->output_node_tree(); //right is outputting by recurse
    }
    return; //for example "... left - key: 15, value: 3;    this - key: 61, value: 0;   right - key: 115, value: -16;   ...
}

void BinarySearchTree::Node::insert(const Key &key, const Value &value)
{
    if (keyValuePair.first > key) //if our key > tah key
    {
        if (!left) //working with left - if left does nos exist
        {
            left = new Node(key, value, this); //making new
        }
        else
        {
            left->insert(key, value); //or if exist left is inserting
        }
    }
    else //working the same with right
    {
        if (!right)
        {
            right = new Node(key, value, this);
        }
        else
        {
            right->insert(key, value);
        }
    }
}

void BinarySearchTree::Node::erase(const Key &key)
{
    if (keyValuePair.first > key) //if this key > other key - working with left
    {
        if(left)
        {
            left->erase(key); //the left is working by recurse
        }
        return;
        
    }
    else if (keyValuePair.first < key) //the same way with right
    {
        if(right)
        {
            right->erase(key);
        }
        return;
    }
    if(keyValuePair.first == key)                        //                0
    {                                                   //                / \    
        if (!left && !right)                            //              NIL NIL                
        {
            if(parent)
            {
                if (parent->left == this) //if we're left
                {
                    parent->left = nullptr;
                }
                else //if we're right
                {
                    parent->right = nullptr;
                }
            }
            delete this;
            return;
        }                                           //                     0
                                                    //                    / \ 
        else if ((!left || !right))                 //                   0  NIL  else if bc codition in A is working in B or in C
        {
            Node* child = (left != nullptr) ? left : right; //if left exist -> child = left, else -> child = right
            if (parent)
            {
                if (parent->left == this) //if we're left
                {
                    parent->left = child;
                }
                else //if we're right
                {
                    parent->right = child;
                }
            }
            child->parent = parent;
            left = nullptr;
            right = nullptr;
            delete this;
            return;
        }                                           //                     0
                                                    //                    / \ 
        else if (left && right)                     //                   0   0
        {
            Node* next = right; //goint to the right side
            while(next->left) //while node will not have left child
            {
                next = next->left;
            }
            keyValuePair = next->keyValuePair; //copy that node to the erasing node
            Node* child = next->right; 
            if (next->parent->left == next) //like in previous times we are cheking it's left or right
            {
                next->parent->left = child;
            }
            else
            {
                next->parent->right = child;
            }
            if (child)
            {
                child->parent = next->parent; //connecting child and grandparent
            }
            next->left = nullptr; //deleteing
            next->right = nullptr;
            delete next;
            return;
        }
    }
    return;
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree &other)
    :_size(other._size)
{
    if(other._root)
    {
        _root = new Node(*other._root);
    }
}

BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &other)
{
    if (this == &other)
    {
        return *this;
    }
    delete _root;
    _size = other._size;
    _root = new Node(*other._root);
    return *this;
}

BinarySearchTree::BinarySearchTree(BinarySearchTree &&other) noexcept
    :_size(other._size), _root(other._root)
{
    other._root = nullptr;
    other._size = 0;
}

BinarySearchTree &BinarySearchTree::operator=(BinarySearchTree &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }
    delete _root;
    _root = other._root;
    _size = other._size;
    other._root = nullptr;
    other._size = 0;
    return *this;
}

BinarySearchTree::~BinarySearchTree()
{
    delete _root;
}

BinarySearchTree::Iterator::Iterator(BinarySearchTree::Node *node)
    :_node(node){}

std::pair<Key, Value> &BinarySearchTree::Iterator::operator*()
{
    return _node->keyValuePair;
}

const std::pair<Key, Value> &BinarySearchTree::Iterator::operator*() const
{
    return _node->keyValuePair;
}

std::pair<Key, Value> *BinarySearchTree::Iterator::operator->()
{
    return &(_node->keyValuePair);
}

const std::pair<Key, Value> *BinarySearchTree::Iterator::operator->() const
{
    return &(_node->keyValuePair);
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++() //++it
{
    if(!_node)
    {
        return *this;
    }

    if (_node->right) //if right side exist
    {
        _node = _node->right;
        while(_node->left)
        {
            _node = _node->left;
        }
    }
    else //if right side does not exist -> we are going upper while left will exist
    {
        Node* par = _node -> parent;
        while(par && _node == par->right)
        {
            _node = par;
            par = par->parent;
        }
        _node = par;
    }
    return *this;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++(int) //it++ i understood it at only 30%
{
    Iterator old = *this;
    ++(*this);
    return old;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--() //--it
{
    if(!_node)
    {
        return *this;
    }
    if (_node->left)
    {
        _node = _node->left;
        while(_node->right)
        {
            _node = _node->right;
        }
    }
    else
    {
        Node* par = _node->parent;
        while(par && _node == par->left)
        {
            _node = par;
            par = par->parent;
        }
        _node = par;
    }
    return *this;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--(int) //it--
{
    Iterator old = *this;
    --(*this);
    return old;
}

bool BinarySearchTree::Iterator::operator==(const BinarySearchTree::Iterator &other) const
{
    if(this->_node == other._node)
    {
        return true;
    }
    return false;
}

bool BinarySearchTree::Iterator::operator!=(const BinarySearchTree::Iterator &other) const
{
    if(this->_node == other._node)
    {
        return false;
    }
    return true;
}

BinarySearchTree::ConstIterator::ConstIterator(const BinarySearchTree::Node *node)
    :_node(node) {}

const std::pair<Key, Value> &BinarySearchTree::ConstIterator::operator*() const
{
    return _node->keyValuePair;
}

const std::pair<Key, Value> *BinarySearchTree::ConstIterator::operator->() const
{
    return &(_node->keyValuePair);
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++()
{
    if(!_node)
    {
        return *this;
    }

    if (_node->right) //if right side exist
    {
        _node = _node->right;
        while(_node->left)
        {
            _node = _node->left;
        }
    }
    else //if right side does not exist -> we are going upper while left will exist
    {
        Node* par = _node -> parent;
        while(par && _node == par->right)
        {
            _node = par;
            par = par->parent;
        }
        _node = par;
    }
    return *this;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++(int)
{
    ConstIterator old = *this;
    ++(*this);
    return old;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--()
{
    if(!_node)
    {
        return *this;
    }
    if (_node->left)
    {
        _node = _node->left;
        while(_node->right)
        {
            _node = _node->right;
        }
    }
    else
    {
        Node* par = _node->parent;
        while(par && _node == par->left)
        {
            _node = par;
            par = par->parent;
        }
        _node = par;
    }
    return *this;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--(int)
{
    ConstIterator old = *this;
    --(*this);
    return old;
}

bool BinarySearchTree::ConstIterator::operator==(const BinarySearchTree::ConstIterator &other) const
{
    if(this->_node == other._node)
    {
        return true;
    }
    return false;
}

bool BinarySearchTree::ConstIterator::operator!=(const BinarySearchTree::ConstIterator &other) const
{
    if(this->_node == other._node)
    {
        return false;
    }
    return true;
}

void BinarySearchTree::insert(const Key &key, const Value &value)
{
    if(!_root)
    {
        _root = new Node(key, value, _root);
    }
    else
    {
        _root->insert(key, value);
    }
    _size++;
}

void BinarySearchTree::erase(const Key &key)
{
    if(!_root)
    {
        return;
    }
    int count = 0;
    while(find(key) != end()) //while we will have this element in our tree
    {
        if (_root->keyValuePair.first == key && (!_root->left || !_root->right)) //if we are deleting the root of this tree and it has 0 or 1 children
        {
            Node* old = _root;
            if (_root->left) //_root will be the child (or nullptr if we have 0 children)
            {
                _root = _root->left;
                _root->parent = nullptr;
            }
            else if(_root->right)
            {
                _root = _root->right;
                _root->parent = nullptr;
            }
            else
            {
                _root = nullptr;
            }
            old->left = nullptr;
            old->right = nullptr;
            delete old;
        }
        else
        {
            _root->erase(key);
        }
        count++;
    }
    _size-=count;
}

BinarySearchTree::ConstIterator BinarySearchTree::find(const Key &key) const
{
    Node* current = _root;
    while(current)
    {
        if (current->keyValuePair.first == key)
        {
            return ConstIterator(current);
        }
        else if(current->keyValuePair.first > key)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return cend(); //const end if we had not find
}

BinarySearchTree::Iterator BinarySearchTree::find(const Key &key)
{
    Node* current = _root;
    while(current)
    {
        if (current->keyValuePair.first == key)
        {
            return Iterator(current);
        }
        else if(current->keyValuePair.first > key)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return end(); //const end if we had not find
}

std::pair<BinarySearchTree::Iterator, BinarySearchTree::Iterator> BinarySearchTree::equalRange(const Key &key)
{
    Iterator first = find(key);
    if(first == end())
    {
        return std::make_pair(end(), end());
    }
    Iterator second = first;
    while(second != end() && (*second).first == key)
    {
        ++second;
    }
    return std::make_pair(first, second);
}

std::pair<BinarySearchTree::ConstIterator, BinarySearchTree::ConstIterator> BinarySearchTree::equalRange(const Key &key) const
{
   ConstIterator first = find(key);
    if(first == cend())
    {
        return std::make_pair(cend(), cend());
    }
    ConstIterator second = first;
    while(second != cend() && (*second).first == key)
    {
        ++second;
    }
    return std::make_pair(first, second); 
}

BinarySearchTree::ConstIterator BinarySearchTree::min() const
{
    if (!_root)
    {
        return cend();
    }
    const Node* cur = _root;
    while(cur->left)
    {
        cur = cur->left;
    }
    return ConstIterator(cur);  
}

BinarySearchTree::ConstIterator BinarySearchTree::max() const
{
    if(!_root)
    {
        return cend();
    }
    const Node* cur = _root;
    while(cur->right)
    {
        cur = cur->right;
    }
    return ConstIterator(cur);
}

BinarySearchTree::ConstIterator BinarySearchTree::min(const Key &key) const
{
    return find(key);
}

BinarySearchTree::ConstIterator BinarySearchTree::max(const Key &key) const
{
    ConstIterator first = find(key);
    if (first == cend())
    {
        return cend();
    }
    ConstIterator cur = first;
    ConstIterator next = first;
    next++;
    while(next != cend() && (*next).first == key)
    {
        cur = next;
        next++;
    }
    return cur;
}

BinarySearchTree::Iterator BinarySearchTree::begin()
{
    if (!_root)
    {
        return end();
    }
    Node* cur = _root;
    while (cur->left != nullptr)
    {
        cur = cur->left;
    }
    return Iterator(cur);
}

BinarySearchTree::Iterator BinarySearchTree::end()
{
    return Iterator(nullptr);
}

BinarySearchTree::ConstIterator BinarySearchTree::cbegin() const
{
    if (!_root)
    {
        return cend();
    }
    const Node* cur = _root;
    while(cur->left != nullptr)
    {
        cur = cur->left;
    }
    return ConstIterator(cur);
}

BinarySearchTree::ConstIterator BinarySearchTree::cend() const
{
    return ConstIterator(nullptr);
}

size_t BinarySearchTree::size() const
{
    return _size;
}

void BinarySearchTree::output_tree()
{
    if(!_root)
    {
        std::cout << "empty tree" << std::endl;
        return;
    }
    _root->output_node_tree();
    std::cout << std::endl;
}