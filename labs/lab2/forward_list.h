#include <iostream>

using ValueType = double;

struct Node
{
    Node() = default;
    Node(ValueType);
    Node* next = nullptr;
    ValueType value = 0.0;
};

class forward_list
{
public:
    forward_list();
    forward_list(const forward_list& other);
    forward_list& operator=(const forward_list& other);
    ~forward_list();    
    void push_back(ValueType);
    void pop_back();
    ValueType& top() const;
    bool is_empty() const;
    size_t get_size() const; //likely functions can't have the same name of parameters 
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;
};