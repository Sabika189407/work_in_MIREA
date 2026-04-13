#include "iterator.h"

Iterator::Iterator(ValueType* _ptr)
    :ptr(_ptr){}

ValueType& Iterator::operator*()
{
    if (ptr == nullptr)
    {
        ValueType&& ans = 0;
        return ans;
    }
    return *ptr;
}

const ValueType& Iterator::operator*() const
{
    if (ptr == nullptr)
    {
        ValueType&& ans = 0;
        return ans;
    }
    return *ptr;
}

ValueType* Iterator::operator->()
{
    return ptr;
}

const ValueType* Iterator::operator->() const
{
    return ptr;
}

Iterator Iterator::operator++()
{   
    if (ptr == nullptr)
    {
        return;
    }
    ptr++;
    return;
}

Iterator Iterator::operator++(int num)
{   
    if (ptr == nullptr)
    {
        return;
    }
    ptr + num;
    return;
}

bool Iterator::operator==(const Iterator &other) const
{
    if (ptr == other.ptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Iterator::operator!=(const Iterator &other) const
{
    if (ptr == other.ptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}