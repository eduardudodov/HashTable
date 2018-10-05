//
// Created by Эдуард on 19.09.2018.
//

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include <string>
#include <queue>        // подключаем заголовочный файл очереди
#include <string>
#include "stdio.h"
#include "value.h"
#define MAP std::vector<std::vector<TYPE> > // вектор очередей ТИПА

typedef unsigned long Hash;

template<class TYPE>
class HashTable {
private:
    unsigned long tableSize;
    std::vector<TYPE> tableValues;
    std::vector<Key> tableKeys;
    MAP table;
public:
    Value * getTable();
    Hash hashCalculate(const Key& k);
    HashTable();
    void swap(HashTable &b);
    bool insert(const Key &k, const TYPE &v);


};

template<class TYPE>
HashTable<TYPE>::HashTable(){
    tableSize = 10;
    table.resize(tableSize);
}

template<class TYPE>
Value *HashTable<TYPE>::getTable() {
    return nullptr;
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
    this->table[hashV].push_back(v);
    return false;
}

template<class TYPE>
Hash HashTable<TYPE>::hashCalculate(const Key &key) {
    Hash hash = 137;
    for(char i : key){
        hash = i + (hash << 6) + (hash << 16) - hash;
    }
    return hash % tableSize;
}
#endif //HASHTABLE_HASHTABLE_H
