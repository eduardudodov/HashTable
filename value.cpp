//
// Created by Эдуард on 22.09.2018.
//

#include <iostream>
#include "value.hpp"

Value &Value::operator=(const Value &b) {
    this->weight=b.weight;
    this->age=b.age;
    this->name=b.name;
    Value temp = b;
    return *this;
}


void Value::edit(Key name, int age, int weight) {
    this->age = static_cast<unsigned int>(age);
    this->weight = static_cast<unsigned int>(weight);
    this->name = name;

}

Value::Value() {
    this->weight = 0;
    this->age = 0;
    this->name = "HEAD";
}

Key Value::getName() const {
    return this->name;
}



bool operator==(const Value &a, const Value &b) {
    return (a.weight == b.weight) && (a.age == b.age) && (a.name == b.name);
}

