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
    while (temp.next){
        addNext(temp.next);
        temp = *temp.next;
    }
    return *this;
}

void Value::addNext(Value * next) {
    Value * element = new Value;
    element->edit(next->getName(), next->age, next->weight);
    this->next = element;
}

Value *Value::getNext() {
    return this->next;
}


void Value::edit(Key name, int age, int weight) {
    this->age = static_cast<unsigned int>(age);
    this->weight = static_cast<unsigned int>(weight);
    this->name = name;
    this->next = NULL;

}

Value::Value() {
    this->weight = 0;
    this->age = 0;
    this->name = "HEAD";
    this->next = NULL;
}

Key Value::getName() {
    return this->name;
}

Value::~Value() {

}


int Value::getAge() {
    return this->age;
}

int Value::getWeight() {
    return this->weight;
}

Value::Value(Key name, unsigned int age, unsigned int weight) {
    this->name = name;
    this->age = age;
    this->weight = weight;
}


