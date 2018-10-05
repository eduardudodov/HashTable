//
// Created by Эдуард on 19.09.2018.
//

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include <string>
#include "stdio.h"
#include "value.h"
#include "vector"
#define MAP std::vector<std::vector<std::pair<const Key, const TYPE>>>

typedef unsigned long Hash;

template<class TYPE>
class HashTable {
private:

    std::pair<unsigned int, unsigned int> tableSize; //first -- in all, second -- now
    MAP table;
public:

    Hash hashCalculate(const Key& k);
    HashTable();
    void swap(HashTable &b);
    bool insert(const Key &k, const TYPE &v);
    void resizeHashTable();

};

template<class TYPE>
HashTable<TYPE>::HashTable(){
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
    if(++tableSize.second > tableSize.first/2)
        resizeHashTable();
    return true;
}

template<class TYPE>
Hash HashTable<TYPE>::hashCalculate(const Key &key) {
    Hash hash = 137;
    for(char i : key){
        hash = i + (hash << 6) + (hash << 16) - hash;
    }
    return hash % tableSize.first;
}

template<class TYPE>
void HashTable<TYPE>::resizeHashTable() {
    tableSize.first*=2;
    MAP newTable;
    newTable.resize(tableSize.first);


}

#endif //HASHTABLE_HASHTABLE_H
