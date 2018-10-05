#include "HashTable.h"
#include "value.h"
#include "gtest/gtest.h"

TEST(hashTableTest, insertTest){
    Value v[5];
    v[0].edit("Andrey", 12, 110);
    v[1].edit("VoVa", 23, 36);
    v[2].edit("Artem", 123, 163410);
    v[3].edit("Kostya", 53, 113460);
    v[4].edit("Lexa", 57, 11340);

    HashTable<Value> h_0;
    for(int i = 0; i < 5; ++i){
        h_0.insert(v[i].getName(), v[i]);
    }

}