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
    Value(Key name, unsigned int age, unsigned int weight);
    void edit(Key name, int age, int weight);
    Value();
    //Value(Key name, int age, int weight);
    Value& operator=(const Value& b);
    void addNext(Value * next);
    Value * getNext();
    Key getName();
    int getAge();
    int getWeight();

    virtual ~Value();


    Value * next;
};

#endif //HASHTABLE_VALUE_H
