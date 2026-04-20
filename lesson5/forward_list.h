#include <iostream>

using ValueType = double;

struct Node
{
    Node() = default;
    Node(ValueType);
    Node* next = nullptr;
    int value = 0;
};

class forward_list
{
public:
    forward_list();
    ~forward_list();    
    void push_back(ValueType);
    void pop_back();
    ValueType& top() const;
    bool is_empty();
    size_t get_size(); //likely functions can't have the same name of parameters 
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;
};