#include "Vector.h"

Vector::Vector(const ValueType *rawArray, size_t size, float coef)
{
    _size = size;
    _capacity = size;
    _multiplicativeCoef = coef;
    _data = new ValueType[_size];
    for (int i = 0; i < size; i++)
    {
        _data[i] = rawArray[i];
    }
}

Vector::Vector(const Vector& other)
{
    if (other._data == nullptr)
    {
        throw "the pointer of ur array is null!\n";
    }

    _size = other._size;
    _capacity = _size;
    _multiplicativeCoef = other._multiplicativeCoef;
    _data = new ValueType[_size];
    for (int i = 0; i < _size; i++)
    {
        _data[i] = other._data[i];
    }
}

Vector& Vector::operator=(const Vector& other)
{
    if (this == &other)
    {
        return *this;
    }
    if (other._data == nullptr)
    {
        throw "the pointer of ur array is null!\n";
    }

    delete[] _data;
    _size = other._size;
    _capacity = _size;
    _multiplicativeCoef = other._multiplicativeCoef;
    ValueType* _data = new ValueType[_size];
    for (int i = 0; i < _size; i++)
    {
        _data[i] = other._data[i];
    }
    return *this;
}

Vector::Vector(Vector &&other) noexcept
{
    Vector();
    *this = std::move(other);
}

Vector &Vector::operator=(Vector &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }
    delete[] _data;
    _size = other._size;
    other._size = 0;
    _capacity = other._capacity;
    other._capacity = 0;
    _multiplicativeCoef = other._multiplicativeCoef;
    other._multiplicativeCoef = 0;
    other._data = nullptr;
    return *this;
}

Vector::~Vector()
{
    delete[] _data;
    _size = 0;
    _capacity = 0;
    _multiplicativeCoef = 0;
}

bool Vector::is_relatable(char a)
{
    bool rel_flag = false;
    if (a == '+')
    {
        if (_size + 1 > _capacity)
        {
            ValueType* temp = (ValueType*)realloc(_data, _capacity*_multiplicativeCoef*sizeof(ValueType));
            if (temp != nullptr)
            {
                rel_flag = true;
                _data = temp;
                _capacity *= _multiplicativeCoef;
                return true;
            }
            else
            {
                throw "can't allocate memory";
            }
        }
        else
        {
            rel_flag = false;
            return false;
        }
    }
    if (a == '-')
    {
        ValueType* temp = (ValueType*)realloc(_data, (_size-1)*sizeof(ValueType));
        if (temp != nullptr)
        {
            rel_flag = true;
            _size--;
            _capacity = _size;
            return true;
        }
        else
        {
            throw "can't allocate memory";
        }
    }
    return true;
}

void Vector::pushBack(const ValueType &value)
{
    is_relatable('+');
    _data[_size] = value;
    _size++;
    return;
}

void Vector::pushFront(const ValueType &value)
{
    is_relatable('+');
    for (int i = _size-1; i > 0; i--)//mb i = _size or i >= 0
    {
        _data[i+1] = _data[i];
    }
    _capacity*=_multiplicativeCoef;
    _data[0] = value;
    _size++;
    return;
}

void Vector::insert(const ValueType& value, size_t pos)
{
    if(pos > _capacity)
    {
        throw "wrong position\n";
    }
    if (pos = 0)
    {
        pushFront(value);
    }
    if (pos = _size)
    {
        pushBack(value);
    }
    is_relatable('+');
    for (int i = _size-1; i > pos; i--)
    {
        _data[i+1] = _data[i];
    }
    _size++;
    return;
}

void Vector::insert(const ValueType *values, size_t size, size_t pos)
{
    if (_size + size > _capacity)
    {
        int coef = _multiplicativeCoef;
        while (_size + size > _capacity)
        {
            coef *= _multiplicativeCoef;
        }
        ValueType* temp = (ValueType*)(_data, _capacity*coef*sizeof(ValueType));
        if (temp != nullptr)
        {
            _data = temp;
            _capacity = coef*_capacity;
            int j = 0;
            for(int i = size; i > pos; i--)
            {
                _data[i+size] = _data[i];
                _data[i] = values[j];
                j++;
                _size++;
            }
            return;
        }
        else
        {
            throw "can't allocate memory\n";
        }
    }
    else
    {
        int j = 0;
        for(int i = size; i > pos; i--)
        {
            _data[i+size] = _data[i];
            _data[i] = values[j];
            j++;
            _size++;
        }
        return;
    }
}

void Vector::insert(const Vector &vector, size_t pos)
{
    insert(vector._data, vector._size, pos);
    return;
}

void Vector::popBack()
{
    if (_size - 1 < 0)
    {
        throw "vector is too small\n";
    }
    if (_size - 1 == 0)
    {
        delete[] _data;
        ValueType* _data = nullptr;
        return;
    }
    is_relatable('-');
    return;   
}

void Vector::popFront()
{
    if (_size - 1 < 0)
    {
        throw "vector is too small\n";
    }
    if (_size - 1 == 0)
    {
        delete[] _data;
        ValueType* _data = nullptr;
        return;
    }
    for (int i = 0; i < _size; i++)
    {
        _data[i] = _data[i+1];
    }
    is_relatable('-');
    return;
}

void Vector::erase(size_t pos, size_t count)
{
    if ((pos + count) > _size)
    {
        ValueType* temp = (ValueType*)realloc(_data, pos*sizeof(ValueType));
        if (temp != nullptr)
        {
            _data = temp;
            _size = _size - (pos + count);
            _capacity = _size;
            return;
        }
        else
        {
            throw "can't allocate memory\n";
        }
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            _data[pos+i] = _data[pos+count+i];
        }
        ValueType* temp = (ValueType*)realloc(_data, (_size-count)*sizeof(ValueType));
        if (temp != nullptr)
        {
            _data = temp;
            _size = _size - count;
            _capacity = _size;
            return;
        }
        else
        {
            throw "can't allocate memory\n";
        }
    }
}

void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
    erase(beginPos, (endPos-beginPos+1));
    return;
}

size_t Vector::size() const
{
    return _size;
}

size_t Vector::capacity() const
{
    return _capacity;
}

ValueType Vector::loadFactor() const
{
    return _size/_capacity;
}

ValueType &Vector::operator[](size_t idx)
{
    return _data[idx];
}

const ValueType &Vector::operator[](size_t idx) const
{
    return _data[idx];
}

long long Vector::find(const ValueType &value) const
{
    int ans = 0;
    for (int i = 0; i < _size; i++)
    {
        if (_data[i] == value)
        {
            ans = i;
            break;
        }
    }
    return ans;
}

void Vector::reserve(size_t capacity)
{
    if (capacity >= _capacity)
    {
        ValueType* temp = (ValueType*)realloc(_data, capacity*sizeof(ValueType));
        if (temp != nullptr)
        {
            _data = temp;
            _capacity = capacity;
            return;
        }
        else
        {
            throw "can't allocate memory\n";
        }
    }
    else{
        return;
    }
}

void Vector::shrinkToFit()
{
    _capacity = _size;
    return;
}

Vector::Iterator::Iterator(ValueType* ptr)
    :_ptr(ptr){}

ValueType& Vector::Iterator::operator*()
{
    if (_ptr == nullptr)
    {
        ValueType&& ans = 0;
        return ans;
    }
    return *_ptr;
}

const ValueType& Vector::Iterator::operator*() const
{
    if (_ptr == nullptr)
    {
        ValueType&& ans = 0;
        return ans;
    }
    return *_ptr;
}

ValueType* Vector::Iterator::operator->()
{
    return _ptr;
}

const ValueType* Vector::Iterator::operator->() const
{
    return _ptr;
}

Vector::Iterator Vector::Iterator::operator++()
{   
    if (_ptr == nullptr)
    {
        return *this;
    }
    _ptr++;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int num)
{   
    if (_ptr == nullptr)
    {
        return *this;
    }
    _ptr + num;
    return *this;
}

bool Vector::Iterator::operator==(const Iterator &other) const
{
    if (_ptr == other._ptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Vector::Iterator::operator!=(const Iterator &other) const
{
    if (_ptr == other._ptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

Vector::Iterator Vector::begin()
{
    return Iterator(_data);
}

Vector::Iterator Vector::end()
{
    return Iterator(&_data[_size]);
}