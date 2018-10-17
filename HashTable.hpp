//
// Created by Эдуард on 19.09.2018.
//

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include <string>
#include <iostream>
#include <utility>
#include "stdio.h"
#include "value.hpp"
#include "vector"

#define MAP std::vector<std::vector<std::pair<Key, TYPE>>>

typedef unsigned long Hash;

template<class TYPE>
class HashTable {
private:

    std::pair<unsigned int, unsigned int> tableSize; //first -- in all, second -- now
    MAP table;

public:
    Hash hashCalculate(const Key &k) const;

    HashTable();

    bool insert(const Key &k, const TYPE &v);

    void resizeHashTable();

    MAP getTable();

    void clear();

    bool erase(const Key &k); //TODO

    bool contains(const Key &k) const;

    size_t size() const;

    bool empty() const;

    Value& at(const Key& k);

    const Value& at(const Key& k) const;

    void swap(HashTable &b); //TODO

    HashTable(const HashTable& b); //TODO

    friend bool operator==(const HashTable & a, const HashTable & b); //TODO

    friend bool operator!=(const HashTable & a, const HashTable & b); //TODO

    HashTable& operator=(const HashTable& b); //TODO

    TYPE& operator[](const Key& k);
};

template<class TYPE>
MAP HashTable<TYPE>::getTable() {
    return table;
}

template<class TYPE>
HashTable<TYPE>::HashTable() {
    tableSize.first = 10;
    tableSize.second = 0;
    table.resize(tableSize.first);
}

template<class TYPE>
void HashTable<TYPE>::swap(HashTable &b) {
    auto tmp = this->table;
    this->table = b.table;
    b.table = this->table;
}

template<class TYPE>
bool HashTable<TYPE>::insert(const Key &k, const TYPE &v) {
    Hash hashV = hashCalculate(k);
    this->table[hashV].push_back(make_pair(k, v));
    if (++tableSize.second > tableSize.first / 2)
        resizeHashTable();
    return true;
}

template<class TYPE>
Hash HashTable<TYPE>::hashCalculate(const Key &key) const {
    Hash hash = 137;
    for (char i : key) {
        hash = i + (hash << 6) + (hash << 16) - hash;
    }
    return hash % tableSize.first;
}

template<class TYPE>
void HashTable<TYPE>::resizeHashTable() {
    tableSize.first *= 2;
    MAP oldMap = this->table;
    table.clear();
    table.resize(tableSize.first);
    for (int i = tableSize.first / 2 - 1; i >= 0; --i) {
        while (!oldMap[i].empty()) {
            this->table[hashCalculate(oldMap[i].back().first)].push_back(\
                   make_pair(oldMap[i].back().first, oldMap[i].back().second));
            oldMap[i].pop_back();
        }
        oldMap.pop_back();
    }
}

template<class TYPE>
void HashTable<TYPE>::clear() {
    this->table.clear();
    tableSize.first = 10;
    table.resize(tableSize.first);
    tableSize.second = 0;
}

template<class TYPE>
bool HashTable<TYPE>::erase(const Key &k) {
    Hash hashKey = hashCalculate(k);
    if (table[hashKey].size() == 0) return false;

    if (table[hashKey].size() == 1) {
        if (table[hashKey].back().first != k)
            table[hashKey].pop_back();
        return true;
    } else {
        for (int i = 0; i < table[hashKey].size(); ++i) {
            if (table[hashKey][i].first == k) {
                table[hashKey].erase(table[hashKey].begin() + i);
                return true;
            }
        }
        return false;
    }
}

template<class TYPE>
bool HashTable<TYPE>::contains(const Key &k) const {
    Hash hashKey = hashCalculate(k);
    if (table[hashKey].size() == 0) return false;

    if (table[hashKey].size() >= 1) {
        for (int i = 0; i < table[hashKey].size(); ++i) {
            if (table[hashKey][i].first == k)
                return true;
        }
        return false;
    }
}

template<class TYPE>
bool HashTable<TYPE>::empty() const {
    for(auto line : table){
        if(line.size() != 0)
            return false;
    }
    return true;
}

template<class TYPE>
size_t HashTable<TYPE>::size() const {
    size_t size = 0;
    for(auto line : table){
        if(line.size() != 0)
            size+=line.size();
    }
    return size;
}

template<class TYPE>
TYPE & HashTable<TYPE>::operator[](const Key &k) {
    Hash hashKey = hashCalculate(k);
    if (table[hashKey].size() == 0){
        TYPE a;
        insert(k,a);
        return a;
    }
    if (table[hashKey].size() >= 1) {
        for (int i = 0; i < table[hashKey].size(); ++i) {
            if (table[hashKey][i].first == k)
                return table[hashKey][i].second;
        }
    }
    TYPE a;
    insert(k,a);
    return a;
}

template<class TYPE>
Value &HashTable<TYPE>::at(const Key &k) {
    Hash hashKey = hashCalculate(k);
    if (table[hashKey].size() == 0){
        throw std::invalid_argument("wrong Key");
    }
    if (table[hashKey].size() >= 1) {
        for (int i = 0; i < table[hashKey].size(); ++i) {
            if (table[hashKey][i].first == k)
                return table[hashKey][i].second;
        }
    }
    throw std::invalid_argument("wrong Key");
}

template<class TYPE>
const Value &HashTable<TYPE>::at(const Key &k) const {

}

template<class TYPE>
HashTable<TYPE>::HashTable(const HashTable &b) {

}
/*
template<class TYPE>
HashTable &HashTable<TYPE>::operator=(const HashTable &b) {

}

bool operator==(const HashTable &a, const HashTable &b) {
    return false;
}

bool operator!=(const HashTable &a, const HashTable &b) {
    return false;
}*/

#endif //HASHTABLE_HASHTABLE_H