#include "Stack.h"
#include "StackImplementation.h"

Stack::Stack(StackContainer container)
    :_containerType(container)
{
    switch (container)
    {
    case StackContainer::Vector:
        _pimpl = new Vector_container();
        break;
    
    case StackContainer::List:
        _pimpl = new List_container();
        break;
    }
}

Stack::Stack(const ValueType *valueArray, size_t arraySize, StackContainer container)
    :_containerType(container)
{
    switch (container)
    {
    case StackContainer::Vector:
        _pimpl = new Vector_container();
        break;
    
    case StackContainer::List:
        _pimpl = new List_container();
        break;
    }
    for (int i = 0; i < arraySize; i++)
    {
        _pimpl->push(valueArray[i]);
    }
}

Stack::Stack(const Stack &copyStack)
    :_containerType(copyStack._containerType)
{
    if (copyStack._pimpl == nullptr)
    {
        throw "the pointer is null";
    }
    
    switch (_containerType)
    {
    case StackContainer::Vector:
        _pimpl = new Vector_container(*dynamic_cast<Vector_container*>(copyStack._pimpl));
        break;
    case StackContainer::List:
        _pimpl = new List_container(*dynamic_cast<List_container*>(copyStack._pimpl));
        break;
    }
}

Stack &Stack::operator=(const Stack &copyStack)
{
    if (this == &copyStack)
    {
        return *this;
    }
    _containerType = copyStack._containerType;
    delete _pimpl;
    _pimpl = nullptr;
    
    if (copyStack._pimpl == nullptr)
    {
        return *this;
    }
    else
    {
        switch (_containerType)
        {
            case StackContainer::Vector:
                _pimpl = new Vector_container(*dynamic_cast<Vector_container*>(copyStack._pimpl));
                break;
            case StackContainer::List:
                _pimpl = new List_container(*dynamic_cast<List_container*>(copyStack._pimpl));
                break;
        }
    }
    return *this;
}

Stack::Stack(Stack &&moveStack) noexcept
    :_containerType(moveStack._containerType), _pimpl(moveStack._pimpl)
{
    moveStack._pimpl = nullptr;
}

Stack &Stack::operator=(Stack &&moveStack) noexcept
{
    if (this == &moveStack)
    {
        return *this;
    }
    _containerType = moveStack._containerType;
    delete _pimpl;
    _containerType = moveStack._containerType;
    _pimpl = moveStack._pimpl;
    moveStack._pimpl = nullptr;
    return *this;
}

Stack::~Stack()
{
    delete _pimpl;
}

void Stack::push(const ValueType &value)
{
    _pimpl->push(value);
    return;
}

void Stack::pop()
{
    if ((_pimpl == nullptr) || _pimpl->size() == 0)
    {
        throw "can't delete - ur stack is empty";
    }
    _pimpl->pop();
    return;
}

const ValueType &Stack::top() const
{
    if ((_pimpl == nullptr) || _pimpl->size() == 0)
    {
        throw "can't take an element of empty stack";
    }
    return _pimpl->top();
}

bool Stack::isEmpty() const
{
    if ((_pimpl == nullptr) || _pimpl->size() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t Stack::size() const
{
    if (_pimpl == nullptr)
    {
        return 0;
    }
    else
    {
        return _pimpl->size();
    }
}
