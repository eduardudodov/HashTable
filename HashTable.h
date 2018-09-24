//
// Created by Эдуард on 19.09.2018.
//

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include <string>
#include <queue>        // подключаем заголовочный файл очереди
#include <string>
#include "value.h"



class HashTable {
private:
    int tableSize;
    Value * table;
    int fullness;


public:
    int getTableSize(){
        return tableSize;
    }
    Value * getTable();
    unsigned int hashCalculation(const Key& k);
    void resize();

    HashTable();
    ~HashTable();

    HashTable(const HashTable& b);
    // Обменивает значения двух хэш-таблиц.
    // Подумайте, зачем нужен этот метод, при наличии стандартной функции
    // std::swap.
    void swap(HashTable& b);
    HashTable& operator=(const HashTable& b);
    // Очищает контейнер.
    void clear();
    // Удаляет элемент по заданному ключу.
    bool erase(const Key& k);
    // Вставка в контейнер. Возвращаемое значение - успешность вставки.
    bool insert(const Key& k, Value& v);
    // Проверка наличия значения по заданному ключу.
    bool contains(const Key& k) const;
    // Возвращает значение по ключу. Небезопасный метод.
    // В случае отсутствия ключа в контейнере, следует вставить в контейнер
    // значение, созданное конструктором по умолчанию и вернуть ссылку на него.
    Value& operator[](const Key& k);
    // Возвращает значение по ключу. Бросает исключение при неудаче.
    Value& at(const Key& k);
    const Value& at(const Key& k) const;
    size_t size() const;
    bool empty() const;
    friend bool operator==(const HashTable & a, const HashTable & b);
    friend bool operator!=(const HashTable & a, const HashTable & b);

};


#endif //HASHTABLE_HASHTABLE_H
