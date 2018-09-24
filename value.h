//
// Created by Эдуард on 22.09.2018.
//

#ifndef HASHTABLE_VALUE_H
#define HASHTABLE_VALUE_H

#include <string>

typedef std::string Key;

class Value {
private:
    Key name;
    unsigned age;
    unsigned weight;
public:
    void edit(Key name, int age, int weight);
    Value();
    Value& operator=(const Value& b);
    void addNext(Value * next);
    Value * getNext();
    Key getName();
    int getAge();
    int getWeight();


    Value * next;
};

#endif //HASHTABLE_VALUE_H
