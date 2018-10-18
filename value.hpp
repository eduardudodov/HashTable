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
    Value();
    void edit(Key name, int age, int weight);
    Value& operator=(const Value& b);
    Key getName() const;
    friend bool operator==(const Value & a, const Value & b);
};

#endif //HASHTABLE_VALUE_H
