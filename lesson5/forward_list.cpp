#include "forward_list.h"

Node::Node(ValueType _value)
    :value(_value){}

forward_list::forward_list()
    :head(nullptr), tail(nullptr){}

forward_list::~forward_list()
{
    while(head != nullptr)
    {
        pop_back();
    }
    size = 0;
}

void forward_list::push_back(ValueType num)
{
    Node* new_el = new Node(num);
    if (tail == nullptr)
    {
        head = tail = new_el;
        size++;
    }
    else
    {
        tail -> next = new_el;
        tail = new_el;
        size++;
    }
    return;
}

void forward_list::pop_back()
{
    if (head == nullptr || tail == nullptr)
    {
        throw "can't delete bc ur list is empty";
    }
    else if(head == tail)
    {
        delete head;
        delete tail;
        head = tail = nullptr;
        size--;
    }
    else
    {
        Node* temp = head;
        while(temp != tail)
        {
            temp = temp -> next;
        }
        delete tail;
        tail = temp;
        size--;
    }
    return;
}

ValueType& forward_list::top() const
{
    ValueType num = tail->value;
    return num;
}

bool forward_list::is_empty()
{
    if (size == 0)
    {
        return true;
    }
    else{
        return false;
    }
}

size_t forward_list::get_size()
{
    return size;
}