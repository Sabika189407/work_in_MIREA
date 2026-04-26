#include "StackImplementation.h"

void Vector_container::push(const ValueType &value)
{
    container.pushBack(value);
    return;
}

void Vector_container::pop()
{
    container.popBack();
    return;
}

const ValueType &Vector_container::top() const
{
    return container[container.size()-1];
}

bool Vector_container::isEmpty() const
{
    if (container.size() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t Vector_container::size() const
{
    return container.size();
}

void List_container::push(const ValueType &value)
{
    container.push_back(value);
    return;
}

void List_container::pop()
{
    container.pop_back();
    return;
}

bool List_container::isEmpty() const
{
    return container.is_empty();
}

size_t List_container::size() const
{
    return container.get_size();
}

const ValueType& List_container::top() const
{
    return container.top();
}