/*#include "Vector.h"

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
}*/

#include "Vector.h"
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

Vector::Vector(const ValueType* rawArray, const size_t size, float coef){
 _size = size;
 _capacity = size;
 _multiplicativeCoef = coef;
 _data = new ValueType[_capacity];
 for (size_t i = 0; i<size; i++){
  _data[i]=rawArray[i];
 }
}
Vector::Vector(const Vector& other){
 /*
 _size = other._size;
 _capacity = other._size;
 _multiplicativeCoef = other._multiplicativeCoef;
 _data = new ValueType[_capacity];
 for (size_t i = 0; i<_size; i++){
  _data[i]=other._data[i];
 }
 */
 *this = other;
}
Vector& Vector::operator=(const Vector& other){
 if (this!=&other){
  delete[] _data;
  _size = other._size;
  _capacity = other._size;
  _multiplicativeCoef = other._multiplicativeCoef;
  _data = new ValueType[_capacity];
  for (size_t i = 0; i<_size; i++){
   _data[i]=other._data[i];
  }
 }
 return *this;
}
Vector::Vector(Vector&& other) noexcept{
 
 *this = std::move(other);
 /*
 _size = other._size;
 _capacity = other._capacity;
 _data = other._data;
 _multiplicativeCoef = other._multiplicativeCoef;
 other._data = nullptr;
 other._size = 0;
 other._capacity = 0;
 other._multiplicativeCoef = 0;
 */
}
Vector& Vector::operator=(Vector&& other) noexcept{
 if (this!=&other){ 
  delete[] _data;
  _size = other._size;
  _capacity = other._capacity;
  _data = other._data;
  _multiplicativeCoef = other._multiplicativeCoef;
  other._data = nullptr;
  other._size = 0;
  other._capacity = 0;
  other._multiplicativeCoef = 0;
 }
 return *this;
}
Vector::~Vector(){
 delete[] _data;
 _size = 0;
 _capacity = 0;
 _multiplicativeCoef = 0;
}
void Vector::pushBack(const ValueType& value){
 if (_size+1<=_capacity){
  _data[_size] = value;
  _size++;
 }
 else{
  if (_capacity == 0){
   _capacity = std::ceil(_multiplicativeCoef);
  }
  else{
   _capacity = std::ceil(_capacity * _multiplicativeCoef); ///ТУТ ПРИКОЛ
  }
  ValueType* newdata = new ValueType[_capacity];
  for (size_t i = 0; i<_size; i++){
   newdata[i]=_data[i];
  }
  delete [] _data;
  _data = newdata;
  _data[_size] = value;
  _size++;
 }
}
void Vector::pushFront(const ValueType& value){
 if (_size+1<=_capacity){
  for (size_t i = _size; i>0; i--){
   _data[i]=_data[i-1];
  }
  _data[0] = value;
  _size++;
 }
 else{
  if (_capacity == 0){
   _capacity = ceil(_multiplicativeCoef);
  }
  else{
   _capacity = ceil(_capacity * _multiplicativeCoef); ///ТУТ ПРИКОЛ
  }
  ValueType* newdata = new ValueType[_capacity];
  for (size_t i = 0; i<_size; i++){
   newdata[i+1]=_data[i];
  }
  delete[] _data;
  _data = newdata;
  _data[0] = value;
  _size++;
 }
}
void Vector::insert(const ValueType& value, size_t pos){
 if (_size+1<=_capacity){
  for (size_t i = _size; i>pos; i--){
   _data[i]=_data[i-1];
  }
  _data[pos] = value;
  _size++;
 }
 else{
  if (_capacity == 0){
   _capacity = ceil(_multiplicativeCoef);
  }
  else{
   _capacity = ceil(_capacity * _multiplicativeCoef); ///ТУТ ПРИКОЛ
  }
  ValueType* newdata = new ValueType[_capacity];
  for (size_t i = 0; i<pos; i++){
   newdata[i]=_data[i];
  }
  newdata[pos] = value;
  for (size_t i = pos; i<_size; i++){
   newdata[i+1]=_data[i];
  }
  _size++;
  delete[] _data;
  _data = newdata;
 }
}
void Vector::insert(const ValueType* values, size_t size, size_t pos){
 if (_size+size<=_capacity){
  //pos = 7
  //[0,1,2,3,4,5,[1,2,3],6,7,8,9,10]
  for (size_t i = _size; i > pos; --i) {
   _data[i + size - 1] = _data[i - 1];
  }
  for (size_t i = 0; i<size; i++){
   _data[i+pos]=values[i];
  }
  _size+=size;
 }
 else{
  if (_capacity == 0){
   _capacity = ceil(_multiplicativeCoef);
  }
  while(_capacity < _size + size){
   _capacity = ceil(_capacity * _multiplicativeCoef); ///ТУТ ПРИКОЛ
  }
  ValueType* newdata = new ValueType[_capacity];
  for (size_t i = 0; i<pos; i++){
   newdata[i]=_data[i];
  }
  for (size_t i = pos; i<_size; i++){
   newdata[i+size]=_data[i];
  }
  delete[] _data;
  for (size_t i = 0; i<size; i++){
   newdata[i+pos]=values[i];
  }
  _size+=size;
  _data = newdata;
 }
}
void Vector::insert(const Vector& vector, size_t pos){
 if (vector._data == nullptr){
  cout<<"empty vector"<<"\n";
  return;
 }
 if (_size+vector._size<=_capacity){for (size_t i = _size; i > pos; --i) {
   _data[i + vector._size - 1] = _data[i - 1];
  }
  for (size_t i = 0; i<vector._size; i++){
   _data[i+pos]=vector._data[i];
  }
  _size+=vector._size;
 }
 else{
  if (_capacity == 0){
   _capacity = ceil(_multiplicativeCoef);
  }
  while(_capacity < _size + vector._size){
   _capacity = ceil(_capacity * _multiplicativeCoef); ///ТУТ ПРИКОЛ
  }
  ValueType* newdata = new ValueType[_capacity];
  for (size_t i = 0; i<pos; i++){
   newdata[i]=_data[i];
  }
  for (size_t i = pos; i<_size; i++){
   newdata[i+vector._size]=_data[i];
  }
  delete[] _data;
  for (size_t i = 0; i<vector._size; i++){
   newdata[i+pos]=vector._data[i];
  }
  _size+=vector._size;
  _data = newdata;
 }
}
void Vector::popBack(){
 if (_size == 0){
  throw out_of_range("Массив уже пустой");
 }
 else{
  _size--;
  _data[_size]=0;
 }
}
void Vector::popFront(){
 if (_size == 0){
  throw out_of_range("Массив уже пустой");
 }
 else{
  for (size_t i = 1; i<_size; i++){
   _data[i-1] = _data[i];
  }
  _size --;
 }
}
void Vector::erase(size_t pos, size_t count){
 if (pos>=_size){
  return;
 }
 if (pos + count > _size){
  _size=pos;
 }
 else{
  for (size_t i = pos+count; i<_size; i++){
   _data[i - count] = _data[i];
  }
  _size-=count;
 }
}
void Vector::eraseBetween(size_t beginPos, size_t endPos){
 if (beginPos>=_size){
  return;
 } 
 if (endPos > _size) endPos = _size;
 size_t count = endPos-beginPos;
 erase(beginPos,count);
}
size_t Vector::size() const{
 return _size;
}
size_t Vector::capacity() const{
 return _capacity;
}
double Vector::loadFactor() const{
 if (_capacity == 0){
  return 0.0;
 }
 return static_cast<double>(_size) / _capacity;
}
ValueType& Vector::operator[](size_t idx){
 return _data[idx];
}
const ValueType& Vector::operator[](size_t idx) const{
 return _data[idx];
}
long long Vector::find(const ValueType& value) const{
 for (size_t i = 0; i<_size; i++){
  if (_data[i] == value){
   return i;
  }
 }
 return -1;
}
void Vector::reserve(size_t capacity){
 if (capacity>_capacity){
  ValueType* newdata = new ValueType[capacity];
  for (size_t i = 0; i<_size; i++){
   newdata[i] = _data[i];
  }
  delete[] _data;
  _data = newdata;
  _capacity = capacity;
 }
}
void Vector::shrinkToFit(){
 if (_capacity > _size){
  ValueType* newdata = new ValueType[_size];
  for (size_t i = 0; i<_size; i++){
   newdata[i] = _data[i];
  }
  delete[] _data;
  _data = newdata;
  _capacity = _size;
 }
}
Vector::Iterator::Iterator(ValueType* ptr): _ptr(ptr){}
ValueType& Vector::Iterator::operator*(){
 return *_ptr;
}
const ValueType& Vector::Iterator::operator*() const{
 return *_ptr;
}
ValueType* Vector::Iterator::operator->(){
 return _ptr;
}
const ValueType* Vector::Iterator::operator->() const{
 return _ptr;
}
Vector::Iterator Vector::Iterator::operator++(){
 ++_ptr;
 return *this;
}
Vector::Iterator Vector::Iterator::operator++(int){
 Iterator tmp=*this;
 ++_ptr;
 return tmp;
}
bool Vector::Iterator::operator==(const Iterator& other) const{
 if (_ptr==other._ptr){
  return true;
 }
 return false;
}
bool Vector::Iterator::operator!=(const Iterator& other) const{
 if (_ptr!=other._ptr){
  return true;
 }
 return false;
}
Vector::Iterator Vector::begin(){
 return Iterator(_data);
}
Vector::Iterator Vector::end(){
 return Iterator(_data+_size);
}