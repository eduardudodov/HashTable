//
// Created by Эдуард on 19.09.2018.
//

#include <iostream>
#include "HashTable.h"


unsigned int HashTable::hashCalculation(const Key &k) {
    unsigned int hash = 137;
    for(char i : k){
        hash = i + (hash << 6) + (hash << 16) - hash;
    }
    return hash % tableSize;
}

HashTable::HashTable() {
    tableSize = 10;
    fullness = 0;
    this->table = new Value[tableSize];
}

HashTable::~HashTable() {
    delete [] this->table;
}

HashTable::HashTable(const HashTable &b) {

}

void HashTable::swap(HashTable &b) {

}

HashTable &HashTable::operator=(const HashTable &b) {
  //  return <#initializer#>;
}

void HashTable::clear() {

}

bool HashTable::erase(const Key &k) {

    return false;
}

bool HashTable::insert(const Key &k,  Value &v) {
    int hash = hashCalculation(k);
    std::cout<< std::endl << hash << " " << k;

    Value * a = &table[hash];
    while(a->next != NULL){
        a = a->next;
    }
    a->next = new Value;
    a->next = &v;

    fullness++;
    if(this->fullness > (this->tableSize/2))
        resize();
    return true;
}

void HashTable::resize(){
    this->tableSize*=2;
    Value * newTable = new Value[tableSize];
    Value *item;
    for(int i = 0; i < this->tableSize/2; ++i){
        if(this->table[i].next == NULL) continue;
        item = this->table[i].next;
            int itemNewHash = this->hashCalculation(item->getName());
            Value * newTableItem = &newTable[itemNewHash];
            while(newTableItem->next != NULL) {
                newTableItem = newTableItem->next;
            }
            newTableItem->next = item;
        Value * tmp = this->table;

        //delete tmp;
        }
    this->table = newTable;
    }


bool HashTable::contains(const Key &k) const {
    return false;
}

Value &HashTable::operator[](const Key &k) {
 //   return <#initializer#>;
}

Value &HashTable::at(const Key &k) {
 //   return <#initializer#>;
}

const Value &HashTable::at(const Key &k) const {
//    return <#initializer#>;
}

size_t HashTable::size() const {
    return 0;
}

bool HashTable::empty() const {
    return false;
}

bool operator==(const HashTable &a, const HashTable &b) {
    return false;
}

bool operator!=(const HashTable &a, const HashTable &b) {
    return false;
}

Value *HashTable::getTable() {
    return this->table;
}


