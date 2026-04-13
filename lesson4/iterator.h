#include <iostream>

using ValueType = int;


class Iterator
{
    private:
        ValueType* ptr;

    public:
        explicit Iterator(ValueType*);
        ValueType& operator*();
        const ValueType& operator*() const;
        ValueType* operator->();
        const ValueType* operator->() const;
        Iterator operator++();
        Iterator operator++(int);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
};