#include "HashTable.h"
#include "value.h"
#include "gtest/gtest.h"
#include <cstdlib>
#define N 100

Key randomString(size_t length) {
    auto randchar = []() -> char {
        const char charset[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
        const size_t maxIndex = (sizeof(charset) - 1);
        return charset[rand() % maxIndex];
    };
    Key str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

HashTable<Value> createRandHashTable(){
    srand(static_cast<unsigned int>(time(NULL)));
    Value v[N];
    for(int i = 0; i < N; ++i )
        v[i].edit(randomString(10), rand()%3, rand()%5);

    HashTable<Value> h_0;
    for(int i = 0; i < N; ++i){
        h_0.insert(v[i].getName(), v[i]);
    }
    return h_0;
}

TEST(hashTableTest, insertTest){
    HashTable<Value> h_0 = createRandHashTable();
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < h_0.getTable()[i].size(); ++j ) {
            EXPECT_EQ(i, h_0.hashCalculate(h_0.getTable()[i][j].first));
        }
    }
}

TEST(hashTableTest, clearTest){
    HashTable<Value> h_0 = createRandHashTable();
    h_0.clear();
    int cnt = 0;
    for(int i = 0; i < h_0.getTable().size(); ++i){
        for(int j = 0; j < h_0.getTable()[i].size(); ++i) {
            ++cnt;
        }
    }
    EXPECT_EQ(cnt, 0);
}

TEST(hashTableTest, eraseTest){
    std::vector<Key> keys;
    HashTable<Value> h_0 = createRandHashTable();
    for(int i = 0; i < h_0.getTable().size(); ++i){
        for(int j = 0; j < h_0.getTable()[i].size(); ++i) {
            keys.push_back(h_0.getTable()[i][j].first);
        }
    }
    while (keys.size() > 0) {
        EXPECT_TRUE(h_0.erase(keys.back()));
        keys.pop_back();
    }
}

TEST(hashTableTest, containTest) {
    std::vector<Key> keys;
    HashTable<Value> h_0 = createRandHashTable();
    for (int i = 0; i < h_0.getTable().size(); ++i) {
        for (int j = 0; j < h_0.getTable()[i].size(); ++i) {
            keys.push_back(h_0.getTable()[i][j].first);
        }
    }
    while (keys.size() > 0) {
        EXPECT_TRUE(h_0.contains(keys.back()));
        keys.pop_back();
    }
}


