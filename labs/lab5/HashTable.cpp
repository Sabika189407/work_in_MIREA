#include "HashTable.h"
#include <functional>

HashTable::HashTable(size_t size) noexcept
    : _capacity(size), _filled(0), table(size) {}

HashTable::~HashTable() {}

void HashTable::insert(const KeyType &key, const ValueType &value)
{
    size_t index = hash_function(key);
    std::list<std::pair<KeyType, ValueType>>::iterator i;
    for (i = table[index].begin(); i != table[index].end(); ++i)
    {
        if (i->first == key)
        {
            i->second = value;
            return;
        }
    }
    bool was_empty = table[index].empty();
    table[index].push_back(std::make_pair(key, value));
    if (was_empty)
    {
        _filled++;
    }
    if (getLoadFactor() > 0.75)
    {
        int old_cap = _capacity;
        std::vector<std::list<std::pair<KeyType, ValueType>>> old_table = table;
        _capacity *= 2;
        table.clear();
        table.resize(_capacity);
        _filled = 0;
        for (int i = 0; i < old_cap; i++)
        {
            std::list<std::pair<KeyType, ValueType>>::iterator iter;
            for (iter = old_table[i].begin(); iter != old_table[i].end(); ++iter)
            {
                size_t newIndex = hash_function(iter->first);
                bool emptyBucket = table[newIndex].empty();
                table[newIndex].push_back(*iter);
                if (emptyBucket)
                {
                    _filled++;
                }
            }
        }
    }
}

bool HashTable::find(const KeyType &key, ValueType &value) const
{
    size_t index = hash_function(key);
    std::list<std::pair<KeyType, ValueType>>::const_iterator i;
    for (i = table[index].begin(); i != table[index].end(); ++i)
    {
        if (i->first == key)
        {
            value = i->second;
            return true;
        }
    }
    return false;
}

void HashTable::remove(const KeyType &key)
{
    size_t index = hash_function(key);
    std::list<std::pair<KeyType, ValueType>>::iterator i;
    for (i = table[index].begin(); i != table[index].end(); ++i)
    {
        if (i->first == key)
        {
            table[index].erase(i);
            if (table[index].empty())
            {
                _filled--;
            }
            return;
        }
    }
}

ValueType& HashTable::operator[](const KeyType &key)
{
    size_t index = hash_function(key);
    std::list<std::pair<KeyType, ValueType>>::iterator i;
    for (i = table[index].begin(); i != table[index].end(); ++i)
    {
        if (i->first == key)
        {
            return i->second;
        }
    }
    bool was_empty = table[index].empty();
    table[index].push_back(std::make_pair(key, 0.0));
    if (was_empty)
    {
        _filled++;
    }
    return table[index].back().second;
}

double HashTable::getLoadFactor()
{
    return static_cast<double>(_filled) / _capacity;
}

size_t HashTable::hash_function(const KeyType &key) const
{
    std::size_t hash = 0;
    for (char c : key)
    {
        hash = hash * 31 + static_cast<unsigned char>(c);
    }
    return hash % _capacity;
}