#include "BST.h"
#include <limits>

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
        if (right && right->keyValuePair.first != std::numeric_limits<Key>::max()){
			right->insert(key, value);
		}
		else{
			Node* oldRight = right;
			right = new Node(key, value, this);
			right->right = oldRight;
			if (oldRight){
				oldRight->parent = right;
			}
		}
	}
}

/*void BinarySearchTree::Node::erase(const Key &key)
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
        else if ((!left || !right))                 //                   0  NIL  else if bc condition in A is working in B or in C
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
}*/

void BinarySearchTree::Node::erase(const Key &key){
	if (key < keyValuePair.first && (left))
    {
		left->erase(key);
	}
	else if (key > keyValuePair.first && (right) && right->keyValuePair.first != std::numeric_limits<Key>::max())
    {
		right->erase(key);
	}
	else{
		if (key != keyValuePair.first)
        {
			return;
		}
		Node* tvar = nullptr;
		if (right && right->keyValuePair.first == std::numeric_limits<Key>::max())
        {
			tvar = right;
			right = nullptr;
		}
		if (!right && !left)
        {
			if (parent)
            {
				if (this == parent->left)
                {
					parent->left = nullptr;
				}
				else if (this == parent->right)
                {
					parent->right = nullptr;
				}
			}
			if (tvar)
            {
				Node* max = parent;
				while (max && max->right)
                {
					max = max->right;
				}
				if (max)
                {
					max->right = tvar;
					tvar->parent = max;
				}
			}
			delete this;
			return;
		}
		else if (right && !left)
        {
			if (parent)
            {
				if (this == parent->left)
                {
					parent->left = right;
					right->parent = parent;
				}
				else if (this == parent->right)
                {
					parent->right = right;
					right->parent = parent;
				}
			}
			delete this;
			return;
		}
		else if (left && !right)
        {
			if (parent)
            {
				if(this == parent->left)
                {
					parent->left = left;
					left->parent = parent;
				}
				else if (this == parent->right)
                {
					parent->right = left;
					left->parent = parent;
				}
			}
			if (tvar)
            {
				Node* max = left;
				while (max->right)
                {
					max = max->right;
				}
				max->right = tvar;
				tvar->parent = max;
			}
			delete this;
			return;
		}
		else
        {
			Node* temp = right;
			while (temp->left)
            {
				temp = temp->left;
			}
			if (temp->parent != this) 
            {
				temp->parent->left = temp->right;
				if (temp->right)
                {
					temp->right->parent = temp->parent;
				}
				temp->right = right;
				if (right)
                {
					right->parent = temp;
				}
			}
			temp->left = left;
			temp->parent = parent;
			if (left)
            {
				left->parent = temp;
			}
			if (parent)
            {
				if (this == parent->left)
                {
					parent->left = temp;
				}
				else if (this == parent->right)
                {
					parent->right = temp;
				}
			}
			delete this;
			return;
		}
	}
}

void BinarySearchTree::clear(Node* node){
	if (node == nullptr){
		return;
	}
	clear(node->left);
	clear(node->right);
	delete node;
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree &other)
    :_size(other._size)
{
    if(other._root)
    {
        _root = new Node(*other._root);
    }
    else
    {
        _root = nullptr;
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
    clear(_root);
    _root = nullptr;
    _size = 0;
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
    if(!_node)
    {
        throw "node does not exist";
    }
    if (_node->keyValuePair.first == std::numeric_limits<Key>::max() && !_node->right){
		throw "node does not exist";
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
        throw "node does not exist";
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
    if(!_node)
    {
        throw "node does not exist";
    }
    if (_node->keyValuePair.first == std::numeric_limits<Key>::max() && !_node->right){
		throw "node does not exist";
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
        const Node* par = _node -> parent;
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
        _root = new Node(key, value);
        _root->right = new Node(std::numeric_limits<Key>::max(), Value(), _root);
        _size++;
        return;
    }
    Node* cur = _root;
    while (cur->right && cur->right->keyValuePair.first != std::numeric_limits<Key>::max())
    {
        cur = cur->right;
    }
    Node* end = cur->right;
    _root->insert(key, value);
    cur = _root;
    while (cur->right && cur->right->keyValuePair.first != std::numeric_limits<Key>::max())
    {
		cur = cur->right;
	}
    if(!cur->right)
    {
        cur->right - end;
        end->parent = cur;
    }
    _size++;
}

void BinarySearchTree::erase(const Key &key)
{
    if(!_root)
    {
        return;
    }
    while(true)
    {
        Node* node = _root;
        while(node)
        {
            if(node->keyValuePair.first > key)
            {
                node = node->left;
            }
            else if(node->keyValuePair.first < key)
            {
                node = node->right;
            }
            else
            {
                break;
            }
        }
        if(!node)
        {
            break;
        }
        if (node->keyValuePair.first == std::numeric_limits<Key>::max())
        {
            break;
        }
        if (node == _root)
        {
            if (!_root->left && !_root->right){
				delete _root;
				_root = nullptr;
			}
            else if (_root->right && !_root->left)
            {
                Node* new_root = _root->right;
                if(new_root->keyValuePair.first == std::numeric_limits<Key>::max())
                {
                    delete new_root;
                    delete _root;
                    _root = nullptr;
                }
                else
                {
                    new_root->parent = nullptr;
                    delete _root;
                    _root = new_root;
                }
            }
            else if(_root->right && !_root->left)
            {
                Node* new_root = _root->left;
                new_root->parent = nullptr;
                delete _root;
                _root = new_root;
            }
            else
            {
                if(_root->right->keyValuePair.first == std::numeric_limits<Key>::max())
                {
                    Node* tvar = _root->right;
                    Node* new_root = _root->left;
                    new_root->parent = nullptr;
                    Node* max = new_root;
                    while (max->right)
                    {
                        max = max->right;
                    }
                    max->right = tvar;
                    tvar->parent = max;
                    delete _root;
                    _root = new_root;
                }
                else
                {
                    Node* temp = _root->right;
					while (temp->left)
                    {
						temp = temp->left;
					}
					if (temp->parent != _root){
						temp->parent->left = temp->right;
						if (temp->right)
                        {
							temp->right->parent = temp->parent;
						}
						temp->right = _root->right;
						_root->right->parent = temp;
					}
					temp->left = _root->left;
					if (_root->left)
                    {
						_root->left->parent = temp;
					}
					temp->parent = nullptr;
					delete _root;
					_root = temp;
				}
            }
        }
        else
        {
            node->erase(key);
        }
        --_size;
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
	Iterator first = find(key);
	if (first == end()){
		return std::make_pair(end(), end());
	}
	Iterator last = first;
	while (last != end() && last->first == key){
		++last;
	}
	return std::make_pair(first, last);
}

std::pair<BinarySearchTree::ConstIterator, BinarySearchTree::ConstIterator> BinarySearchTree::equalRange(const Key &key) const
{
   ConstIterator first = find(key);
	if (first == cend()){
		return std::make_pair(cend(), cend());
	}
	ConstIterator last = first;
	while (last != cend() && last->first == key){
		++last;
	}
	return std::make_pair(first, last); 
}

BinarySearchTree::ConstIterator BinarySearchTree::min() const
{
    return cbegin(); 
}

BinarySearchTree::ConstIterator BinarySearchTree::max() const
{
    if(!_root)
    {
        return cend();
    }
    return --cend();
}

BinarySearchTree::ConstIterator BinarySearchTree::min(const Key &key) const
{
    ConstIterator first = find(key);
	if (first == cend()){
		return cend();
	}
	ConstIterator second = first;
	++first;
	while (first != cend() && first->first == key){
		if (first->second < second->second){
			second = first;
		}
		++first;
	}
	return second;
}

BinarySearchTree::ConstIterator BinarySearchTree::max(const Key &key) const
{
    ConstIterator first = find(key);
	if (first == cend()){
		return cend();
	}
	ConstIterator second = first;
	++first;
	while (first != cend() && first->first == key){
		if (first->second > second->second){
			second = first;
		}
		++first;
	}
	return second;
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
    if (!_root)
    {
        return Iterator(nullptr);
    }
    Node* cur = _root;
    while(cur->right)
    {
        cur = cur->right;
    }
    return Iterator(cur);
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
    if (!_root){
		return ConstIterator(nullptr);
	}
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

//all done!