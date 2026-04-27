#include "forward_list.h"

Node::Node(ValueType _value)
    :value(_value){}

forward_list::forward_list()
    :head(nullptr), tail(nullptr), size(0){}

forward_list::forward_list(const forward_list &other) 
{
    head = nullptr;
    tail = nullptr;
    size = 0;
    Node* temp = other.head;
    while (temp != nullptr)
    {
       	push_back(temp->value);
        temp = temp->next;
    }
}

forward_list &forward_list::operator=(const forward_list &other)
{
    if (this == &other)
    {
        return *this;
    }
    delete head;
    delete tail;
    head = nullptr;
    tail = nullptr;
    size = 0;
    if (other.head == nullptr)
    {
        return *this;
    }
    else
    {
        head = other.head;
        tail = other.tail;
        size = other.size;
    }
    return *this;
}

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
        head = tail = nullptr;
        size--;
    }
    else
    {
        Node* temp = head;
        while(temp->next !=  tail)
        {
            temp = temp -> next;
        }
        delete tail;
        tail = temp;
	tail->next = nullptr;
        size--;
    }
    return;
}

ValueType& forward_list::top() const
{
    return tail->value;
}

bool forward_list::is_empty() const
{
    if (size == 0)
    {
        return true;
    }
    else{
        return false;
    }
}

size_t forward_list::get_size() const
{
    return size;
}
