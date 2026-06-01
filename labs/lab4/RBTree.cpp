#include "BST.h"
#include <limits>

BinarySearchTree::Node::Node(Key key, Value value, bool color, BinarySearchTree::Node *parent, BinarySearchTree::Node *left, BinarySearchTree::Node *right)
    :keyValuePair{key, value}, color(color), parent(parent), left(left), right(right) {}

BinarySearchTree::Node::Node(const BinarySearchTree::Node &other)
    :keyValuePair(other.keyValuePair), color(other.color), parent(nullptr), left(nullptr), right(nullptr) {}

bool BinarySearchTree::Node::operator==(const BinarySearchTree::Node &other) const
{
    if (this->keyValuePair.first == other.keyValuePair.first)
    {
        return true;
    }
    return false;
}

void BinarySearchTree::Node::output_node_tree(int level) const
{
    if (left) //if left exist
    {
        left->output_node_tree(level+1); //left is outputting by recurse
    }
    if (this->keyValuePair.first == std::numeric_limits<Key>::max())
    {
        throw "walked to the edge";
    }
    std::cout << "Node - key: " << this->keyValuePair.first << ", value: " << this->keyValuePair.second << ";\t";
    if (right)
    {
        right->output_node_tree(level+1);
    }
}

void BinarySearchTree::Node::insert(const Key &key, const Value &value, BinarySearchTree::Node **root)
{
    if (!root)
    {
        throw std::runtime_error("the pointer is null");
    }
    if (keyValuePair.first >= key)
    {
        if (left)
        {
            left->insert(key, value, root);
            return;
        }
        left = new Node(key, value, true, this);
        left->rebalance_tree(root);
    }
    else
    {
        if (right)
        {
            right -> insert(key, value, root);
            return;
        }
        right = new Node(key, value, true, this);
        right->rebalance_tree(root);
    }
}



void BinarySearchTree::Node::erase(const Key &key, BinarySearchTree::Node **root)
{
    if (!root)
    {
        throw std::runtime_error("the pointer is NULL");
    }
    if (keyValuePair.first != key)
    {
        if (keyValuePair.first >= (left && key))
        {
            left -> erase(key, root);
        }
        else if (right)
        {
            right -> erase(key, root);
            return;
        }
    }
    if (left && right)
    {
        Node* cur = right;
        while (cur->left)
        {
            cur = cur->left;
        }
        this->keyValuePair = cur->keyValuePair;
        cur->erase(cur->keyValuePair.first, root);
        return;
    }
    if (color)
    {
        if (parent->left == this)
        {
            parent->left = nullptr;
        }
        else
        {
            parent->right = nullptr;
        }
        delete this;
        return;
    }
    Node* ptr = nullptr;
    if (left)
    {
        ptr = left;
    }
    else
    {
        ptr = right;
    }
    if (!ptr)
    {
        this->color = false;
        this->rebalance_tree(root);
        if (parent)
        {
            if (parent->left == this)
            {
                parent->left = ptr;
            }
            else
            {
                parent->right = ptr;
            }
        }
        if (this == *root)
        {
            *root = ptr;
        }
        delete this;
        return;
    }
    if (parent)
    {
        if (parent->left == this)
        {
            parent->left = ptr;
        }
        else
        {
            parent->right = ptr;
        }
    }
    ptr->parent = parent;
    if(ptr->color)
    {
        ptr->color = false;
    } 
    else
    {
        ptr->rebalance_tree(root);
    }
    if (this == *root)
    {
        *root = ptr;
    }
    delete this;
    return;
}

void BinarySearchTree::Node::left_rotation() {
    Node* pivot = this->right;
    pivot->parent = this->parent;
    if (this->parent)
    {
        if (this->parent->left == this)
        {
            this->parent->left = pivot;
        }
        else
        {
            this->parent->right = pivot;
        }
    }
    this->right = pivot->left;
    if (pivot->left)
    {
        pivot->left->parent = this;
    }
    this->parent = pivot;
    pivot->left = this;
}

void BinarySearchTree::Node::right_rotation() {
    Node* pivot = this->left;
    pivot->parent = this->parent;
    if (this->parent)
    {
        if (this->parent->left == this)
        {
            this->parent->left = pivot;
        }
        else
        {
            this->parent->right = pivot;
        }
    }
    this->left = pivot->right;
    if (pivot->right) pivot->right->parent = this;
    this->parent = pivot;
    pivot->right = this;
}

void BinarySearchTree::Node::rebalance_tree(Node** root) {
    if (!parent)
    {
        color = 0;
        *root = this;
        return;
    }
    if(parent->color == false) 
    {
        return;
    }
    Node* new_node = parent->parent->left == parent ? parent->parent->right : parent->parent->left;
    if (new_node && new_node->color)
    {
        parent->color = false;
        new_node->color = false;
        parent->parent->color = true;
        parent->parent->rebalance_tree(root);
        return;
    } 
    Node* temp = this;
    if (temp == parent->right && parent == parent->parent->left)
    {
        parent->left_rotation();
        temp = left;
    } else if (temp == parent->left && parent == parent->parent->right)
    {
        parent->right_rotation();
        temp = right;
    }
    temp->parent->color = false;
    temp->parent->parent->color = true;
    if ((temp == temp->parent->left) && (temp->parent == temp->parent->parent->left))
    {
        if(temp->parent->parent == *root)
        {
            *root = temp->parent->parent->left;
        }
        temp->parent->parent->right_rotation();
    }
    else
    {
        if(temp->parent->parent == *root)
        {
            *root = temp->parent->parent->right;
        }
        temp->parent->parent->left_rotation();
    }
}

void BinarySearchTree::Node::unrebalance(Node** root) {
    if (!parent)
    {
        throw std::runtime_error("the root is null");
    }
    Node* same;
    if (parent->left == this)
    {
        same = parent->right;
    }
    else
    {
        same = parent->left;
    }
    if (same->color)
    {
        parent->color = 1;
        same->color = 0;
        if (parent->left == this)
        {
            if (parent == *root)
            {   
                *root = parent->right;
            }
            parent->left_rotation();
        }
        else
        {
            if (parent == *root)
            {
                *root = parent->left;
            }
            parent->right_rotation();
        }
    }
    if (!parent->color && !same->color && (!same->left || !same->left->color) && (!same->right || !same->right->color))
    {
        same->color = 1;
        parent->unrebalance(root);
        return;
    }
    if (parent->color && !same->color && (!same->left || !same->left->color) && (!same->right || !same->right->color))
    {
        same->color = 1;
        parent->color = 0;
        return;
    }
    if (!same->color)
    {
        if (this == parent->left && (!same->right || !same->right->color) && (same->left && same->left->color))
        {
            same->color = 1;
            same->left->color = 0;
            same->right_rotation();
        }
        else if (this == parent->right && (same->right && same->right->color) && (!same->left || !same->left->color))
        {
            same->color = 1;
            same->right->color = 0;
            same->left_rotation();
        }
        return;
    }
    same->color = parent->color;
    parent->color = 0;
    if (this == parent->left)
    {
        if (same->right)
        {
            same->right->color = 0;
        }
        if (parent == *root)
        {
            *root = parent->right;
        }
        parent->left_rotation();
    }
    else
    {
        if (same->left)
        {
            same->left->color = 0;
        }
        if (parent == *root)
        {
            *root = parent->left;
        }
        parent->right_rotation();
    }
}

size_t BinarySearchTree::Node::get_hight() const {
    if (this->keyValuePair.first == std::numeric_limits<Key>::max())
    {
        return 0;
    }
    size_t left_hight = 0, right_hight = 0;
    if (left)
    {
        left_hight = left->get_hight();
    }
    if (right)
    {
        right_hight = right->get_hight();
    }
    return 1 + std::max(left_hight, right_hight);
}

BinarySearchTree::Node *BinarySearchTree::copy_subtree(const BinarySearchTree::Node *other)
{
    if (!other)
    {
        return nullptr;
    }
    Node* temp = new Node(*other);
    temp->left = copy_subtree(other->left);
    temp->right = copy_subtree(other->right);
    return temp;
}

void BinarySearchTree::delete_subtree(BinarySearchTree::Node *other)
{
    if (!other)
    {
        return;
    }
    delete_subtree(other->left);
    delete_subtree(other->right);
    delete other;
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree &other)
    : _root(copy_subtree(other._root)), _size(other._size) {}

BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &other)
{
    if (this == &other)
    {
        return *this;
    }
    delete_subtree(_root);
    _root = copy_subtree(other._root);
    _size = other._size;
    return* this;
}

BinarySearchTree::BinarySearchTree(BinarySearchTree &&other) noexcept
    :_size(other._size), _root(other._root)
{
    other._root = nullptr;
    other._size = 0;
}

BinarySearchTree &BinarySearchTree::operator=(BinarySearchTree &&other) noexcept
{
    if (this == &other) return *this;
    std::swap(this->_root, other._root);
    std::swap(this->_size, other._size);
    return *this;
}

BinarySearchTree::~BinarySearchTree()
{
    delete_subtree(_root);
}

BinarySearchTree::Iterator::Iterator(BinarySearchTree::Node *node)
    :_node(node){}

std::pair<Key, Value> &BinarySearchTree::Iterator::operator*()
{
    if (!_node)
    {
		throw "node does not exist";
	}
    return _node->keyValuePair;
}

const std::pair<Key, Value> &BinarySearchTree::Iterator::operator*() const
{
    if(!_node)
    {
        throw "node does not exist";
    }
    return _node->keyValuePair;
}

std::pair<Key, Value> *BinarySearchTree::Iterator::operator->()
{
    if(!_node)
    {
        throw "node does not exist";
    }
    return &(_node->keyValuePair);
}

const std::pair<Key, Value> *BinarySearchTree::Iterator::operator->() const
{
    if (!_node)
    {
        throw "node does not exist";
    }
    return &(_node->keyValuePair);
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++() //++it
{
    if (!_node)
    {
        throw std::runtime_error("the pointer is null");
    }
    if (_node->right)
    {
        _node = _node->right;
        while (_node->left)
        {
            _node = _node->left;
        }
        return *this;
    }
    while (_node->parent)
    {
        if (_node == _node->parent->left)
        {
            _node = _node->parent;
            return *this;
        }
        _node = _node->parent;
    }
    throw std::runtime_error("error");
}


BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++(int) //it++ i understood it at only 30%
{
    if (!_node)
    {
        throw std::runtime_error("the pointer is null");
    }
    Iterator i = *this;
    if (_node->right)
    {
        _node = _node->right;
        while (_node->left)
        {
            _node = _node->left;
        }
        return i;
    }
    while (_node->parent)
    {
        if (_node == _node->parent->left)
        {
            _node = _node->parent;
            return i;
        }
        _node = _node->parent;
    }
    throw std::runtime_error("error");
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--() //--it
{
    if (!_node)
    {
        throw std::runtime_error("the pointer is null");
    }
    if (_node->left)
    {
        _node = _node->left;
        while (_node->right)
        {
            _node = _node->right;
        }
        return *this;
    }
    while (_node->parent)
    {
        if (_node == _node->parent->right)
        {
            _node = _node->parent;
            return *this;
        }
        _node = _node->parent;
    }
    throw std::runtime_error("error");
}


BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--(int) //it--
{
    if (!_node)
    {
        throw std::runtime_error("the pointer is null");
    }
    Iterator i = *this;
    if (_node->left)
    {
        _node = _node->left;
        while (_node->right)
        {
            _node = _node->right;
        }
        return i;
    }
    while (_node->parent)
    {
        if (_node == _node->parent->right)
        {
            _node = _node->parent;
            return i;
        }
        _node = _node->parent;
    }

    throw std::runtime_error("error");
}

bool BinarySearchTree::Iterator::operator==(const BinarySearchTree::Iterator &other) const
{
    return _node->keyValuePair.first == other._node->keyValuePair.first;
}

bool BinarySearchTree::Iterator::operator!=(const BinarySearchTree::Iterator &other) const
{
    return _node->keyValuePair.first != other._node->keyValuePair.first;
}

BinarySearchTree::ConstIterator::ConstIterator(const BinarySearchTree::Node *node)
    :_node(node) {}

const std::pair<Key, Value> &BinarySearchTree::ConstIterator::operator*() const
{
    if (!_node)
    {
        throw "node does not exist";
    }
    return _node->keyValuePair;
}

const std::pair<Key, Value> *BinarySearchTree::ConstIterator::operator->() const
{
    if(!_node)
    {
        throw "node does not exist";
    }
    return &(_node->keyValuePair);
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++()
{
    if (!_node)
    {
        throw std::runtime_error("the pointer is null");
    }
    if (_node->right)
    {
        _node = _node->right;
        while (_node->left)
        {
            _node = _node->left;
        }
        return *this;
    }
    while (_node->parent)
    {
        if (_node == _node->parent->left)
        {
            _node = _node->parent;
            return *this;
        }
        _node = _node->parent;
    }
    throw std::runtime_error("error");
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++(int)
{
    if (!_node)
    {
        throw std::runtime_error("the pointer is null");
    }
    ConstIterator i = *this;

    if (_node->right)
    {
        _node = _node->right;
        while (_node->left)
        {
            _node = _node->left;
        }
        return i;
    }
    while (_node->parent)
    {
        if (_node == _node->parent->left)
        {
            _node = _node->parent;
            return i;
        }
        _node = _node->parent;
    }
    throw std::runtime_error("error");
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--()
{
    if (!_node)
    {
        throw std::runtime_error("Null iterator");
    }
    if (_node->left)
    {
        _node = _node->left;
        while (_node->right)
        {
            _node = _node->right;
        }
        return *this;
    }
    while (_node->parent)
    {
        if (_node == _node->parent->right)
        {
            _node = _node->parent;
            return *this;
        }
        _node = _node->parent;
    }
    throw std::runtime_error("error");
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--(int)
{
    if (!_node)
    {
        throw std::runtime_error("the pointer is null");
    }
    ConstIterator i = *this;
    if (_node->left)
    {
        _node = _node->left;
        while (_node->right)
        {
            _node = _node->right;
        }
        return i;
    }
    while (_node->parent)
    {
        if (_node == _node->parent->right)
        {
            _node = _node->parent;
            return i;
        }
        _node = _node->parent;
    }
    throw std::runtime_error("ERROR");
}

bool BinarySearchTree::ConstIterator::operator==(const BinarySearchTree::ConstIterator &other) const
{
    return _node->keyValuePair.first == other._node->keyValuePair.first;
}

bool BinarySearchTree::ConstIterator::operator!=(const BinarySearchTree::ConstIterator &other) const
{
    return _node->keyValuePair.first != other._node->keyValuePair.first;
}

void BinarySearchTree::insert(const Key &key, const Value &value)
{
    if (!_root) {
        _root = new Node(key, value);
        _root->right = new Node(std::numeric_limits<Key>::max(), value, false, _root);
        _size++;
        return;
    }
    Node* _end = end()._node;
    if (_end->parent)
    {
        _end->parent->right = nullptr;
    }
    _root->insert(key, value, &_root);
    _size++;    
    Node* cur = _root;
    while (cur->right) cur = cur->right;
    cur->right = _end;
    _end->parent = cur;
    return;
}

void BinarySearchTree::erase(const Key &key)
{
    if (!_root)
    {
        return;
    }
    Iterator i(_root);
    while ((i = find(key)) != end())
    {
        Node* _end = end()._node;
        _end->parent->right = nullptr;
        i._node->erase(key, &_root);
        _size--;
        if (!_root) {
            delete _end;
            return;
        }
        Node* cur = _root;
        while (cur->right) cur = cur->right;
        cur->right = _end;
        _end->parent = cur;
    }
}

BinarySearchTree::ConstIterator BinarySearchTree::find(const Key &key) const
{
    Node* cur = _root;
    while(cur)
    {
        if (cur->keyValuePair.first > key)
        {
            cur = cur->left;
        }
        else if(cur->keyValuePair.first < key)
        {
            cur = cur->right;
        }
        else
        {
            return ConstIterator(cur);
        }
    }
    return cend();
}

BinarySearchTree::Iterator BinarySearchTree::find(const Key &key)
{
    Node* cur= _root;
    while(cur)
    {
        if (cur->keyValuePair.first > key)
        {
            cur = cur->left;
        }
        else if(cur->keyValuePair.first < key)
        {
            cur = cur->right;
        }
        else
        {
            return Iterator(cur);
        }
    }
    return end(); //const end if we had not find
}

std::pair<BinarySearchTree::Iterator, BinarySearchTree::Iterator> BinarySearchTree::equalRange(const Key &key)
{
	Iterator i = end();
    Iterator cur = begin();
    while (cur != i && cur->first != key)
    {
        ++cur;
    }
    Iterator first = cur;
    while (cur != i && cur->first == key)
    {
        ++cur;
    }
    return {first, cur};
}

std::pair<BinarySearchTree::ConstIterator, BinarySearchTree::ConstIterator> BinarySearchTree::equalRange(const Key &key) const
{
    ConstIterator i = cend(); 
    ConstIterator cur = cbegin();
    while (cur != i && cur->first != key)
    {
        ++cur;
    }
    ConstIterator first = cur;
    while (cur != i && cur->first == key)
    {
        ++cur;
    }
    return {first, cur};
}

BinarySearchTree::ConstIterator BinarySearchTree::min() const
{
    return cbegin(); 
}

BinarySearchTree::ConstIterator BinarySearchTree::max() const
{
    return --cend();
}

BinarySearchTree::ConstIterator BinarySearchTree::min(const Key &key) const
{
    std::pair<ConstIterator, ConstIterator> range = equalRange(key);
    ConstIterator cur = range.first;
    ConstIterator min = cur;
    
    for (; cur != range.second; cur++) {
        if (cur->second < min->second) min = cur;
    }
    return min;
}


BinarySearchTree::ConstIterator BinarySearchTree::max(const Key &key) const
{
    std::pair<ConstIterator, ConstIterator> range = equalRange(key);
    ConstIterator cur = range.first;
    ConstIterator max = cur;
    
    for (; cur != range.second; ++cur) {
        if (cur->second > max->second) max = cur;
    }

    return max;
}

BinarySearchTree::Iterator BinarySearchTree::begin()
{
    Node* cur = _root;
    while (cur->left != nullptr)
    {
        cur = cur->left;
    }
    return Iterator(cur);
}

BinarySearchTree::Iterator BinarySearchTree::end()
{
    Node* cur = _root;
    while(cur->right)
    {
        cur = cur->right;
    }
    return Iterator(cur);
}

BinarySearchTree::ConstIterator BinarySearchTree::cbegin() const
{
    const Node* cur = _root;
    while(cur->left != nullptr)
    {
        cur = cur->left;
    }
    return ConstIterator(cur);
}

BinarySearchTree::ConstIterator BinarySearchTree::cend() const
{
	Node* cur = _root;
	while (cur->right){
		cur = cur->right;
	}
	return ConstIterator(cur);
}

size_t BinarySearchTree::size() const
{
    return _size;
}

void BinarySearchTree::output_tree() const
{
    if(!_root)
    {
        std::cout << "empty tree" << std::endl;
        return;
    }
    _root->output_node_tree();
    std::cout << std::endl;
}

size_t BinarySearchTree::max_height() const {
    return _root->get_hight();
}
//all done!