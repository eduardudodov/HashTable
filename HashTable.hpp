//
// Created by Эдуард on 19.09.2018.
//

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include <string>
#include <iostream>
#include <utility>
#include "value.hpp"

#define DEFAULT_SIZE 10
#define DOUBLE 2
#define HALF 2
#define HASH_TABLE std::vector<std::vector<std::pair<Key, TYPE>>>

template<class TYPE>
using hash_line = std::vector<std::pair<Key, TYPE>>;

template<class TYPE>
using hash_table = std::vector<hash_line<TYPE>>;
//typedef std::vector<std::pair<Key, TYPE>> line;


typedef unsigned long Hash;

template<class TYPE>
class HashTable {
private:
    size_t sizeInAll = 10;
    size_t sizeNow = 0;

    hash_table<TYPE> table;

public:
    Hash hashCalculate(const Key &k) const;

    HashTable();

    bool insert(const Key &k, const TYPE &v);

    void resizeHashTable();

    hash_table<TYPE> getTable() const;

    void clear();

    bool erase(const Key &k); 

    bool contains(const Key &k) const;

    size_t size() const;

    bool empty() const;

    Value& at(const Key& k);

    const Value& at(const Key& k) const;

    void swap(HashTable &b);

    HashTable(const HashTable& b);
    friend bool operator== (const HashTable<TYPE> & a, const HashTable<TYPE> & b){
        return a.sizeNow == b.sizeNow && a.table == b.table;
    }

    friend bool operator!=(const HashTable<TYPE> & a, const HashTable<TYPE> & b) {
        return a.sizeNow != b.sizeNow && a.table != b.table;
    }

    void operator=(const HashTable<TYPE>& b);

    TYPE& operator[](const Key& k);
};



template<class TYPE>
hash_table<TYPE> HashTable<TYPE>::getTable() const{
    return table;
}

template<class TYPE>
HashTable<TYPE>::HashTable() {
    table.resize(sizeInAll);
}



template<class TYPE>
void HashTable<TYPE>::swap(HashTable &b) {
    std::swap(table, b.table);
    std::swap(sizeInAll, b.sizeInAll);
    std::swap(sizeNow, b.sizeNow);
}

template<class TYPE>
bool HashTable<TYPE>::insert(const Key &k, const TYPE &v) {
    Hash hashV = hashCalculate(k);
    table[hashV].push_back(make_pair(k, v));
    if (++sizeNow > sizeInAll / HALF)
        resizeHashTable();
    return true;
}

//http://www.cyberforum.ru/algorithms/thread111126.html
template<class TYPE>
Hash HashTable<TYPE>::hashCalculate(const Key &key) const {
    Hash hash = 137;
    for (char i : key) {
        hash = i + (hash << 6) + (hash << 16) - hash;
    }
    return hash % sizeInAll;
}

template<class TYPE>
void HashTable<TYPE>::resizeHashTable() {
    sizeInAll *= DOUBLE;
    hash_table<TYPE> oldMap = table;
    table.clear();
    table.resize(sizeInAll);
    for (int i = static_cast<int>(sizeInAll / HALF - 1); i >= 0; --i) {
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
    sizeInAll = DEFAULT_SIZE;
    table.resize(sizeInAll);
    sizeNow = 0;
}

template<class TYPE>
bool HashTable<TYPE>::erase(const Key &k) {
    if(!contains(k)) return false;
    Hash hash = hashCalculate(k);
    if(table[hash].size() == 1) {
        table[hash].pop_back();
        return true;
    } else {
        int i = 0;
        while(table[hash][i++].first != k);
        table[hash].erase(table[hash].begin() + (--i));
        return true;
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
    return sizeNow == 0;
}

template<class TYPE>
size_t HashTable<TYPE>::size() const {
    return sizeNow;
}

template<class TYPE>
TYPE & HashTable<TYPE>::operator[](const Key &k) {
    Hash hashKey = hashCalculate(k);
    if (table[hashKey].size() > 0) {
        for (int i = 0; i < table[hashKey].size(); ++i) {
            if (table[hashKey][i].first == k)
                return table[hashKey][i].second;
        }
    }
    table[hashKey].push_back(make_pair(k,TYPE()));
    return table[hashKey].back().second;
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
HashTable<TYPE>::HashTable(const HashTable<TYPE> &b) {
    this->table = b.table;
    this->sizeNow = b.sizeNow;
}

template<class TYPE>
void HashTable<TYPE>::operator=(const HashTable<TYPE> &b) {
    this->table = b.table;
    this->sizeNow = b.sizeNow;
}



#endif //HASHTABLE_HASHTABLE_H
