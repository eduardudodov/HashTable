#include "HashTable.hpp"
#include "value.hpp"
#include "gtest/gtest.h"
#include <cstdlib>
#define N 1000

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
    for (int i = 0; i < h_0.getTable().size(); ++i) {
        for (int j = 0; j < h_0.getTable()[i].size(); ++i) {
            keys.push_back(h_0.getTable()[i][j].first);
        }
    }
    int i = N;
    while (--i) {
        EXPECT_FALSE(h_0.erase(randomString(11)));
    }
    while (keys.size() != 0){
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

TEST(hashTableTest, emptyTest) {
    HashTable<Value> h_0 = createRandHashTable();
    HashTable<Value> h_1;
    EXPECT_FALSE(h_0.empty());
    EXPECT_TRUE(h_1.empty());
}

TEST(hashTableTest, sizeTest) {
    HashTable<Value> h_0 = createRandHashTable();
    EXPECT_EQ(h_0.size(),N);
}

TEST(hashTableTest, constructorTest){
    HashTable<Value> h_0 = createRandHashTable();
    HashTable<Value> h_1 = h_0;
    EXPECT_TRUE(h_1 == h_0);
}

TEST(hashTableTest, operatorParenthesesTest){
    std::vector<Key> keys;
    HashTable<Value> h_0 = createRandHashTable();
    for (int i = 0; i < h_0.getTable().size(); ++i) {
        for (int j = 0; j < h_0.getTable()[i].size(); ++i) {
            keys.push_back(h_0.getTable()[i][j].first);
        }
    }

    while (keys.size() > 0) {
        EXPECT_EQ(h_0[keys.back()].getName(), keys.back());
        keys.pop_back();
    }
    for(int i = 0; i < 1000; ++i) {
        Key randStr = randomString(10);
        EXPECT_EQ(h_0[randStr].getName(), "HEAD");
    }

}

TEST(hashTableTest, atTest){
    std::vector<Key> keys;
    HashTable<Value> h_0 = createRandHashTable();
    for (int i = 0; i < h_0.getTable().size(); ++i) {
        for (int j = 0; j < h_0.getTable()[i].size(); ++i) {
            keys.push_back(h_0.getTable()[i][j].first);
        }
    }

    while (keys.size() > 0) {
        EXPECT_EQ(h_0.at(keys.back()).getName(), keys.back());
        keys.pop_back();
    }
    for(int i = 0; i < 1000; ++i) {
        Key randStr = randomString(10);
        EXPECT_THROW(h_0.at(randStr).getName(), std::invalid_argument);
    }

}

TEST(hashTableTest, swapTest) {
    std::vector<Key> keys_0, keys_1;
    HashTable<Value> h_0 = createRandHashTable();
    HashTable<Value> h_1 = createRandHashTable();
    for (int i = 0; i < h_0.getTable().size(); ++i) {
        for (int j = 0; j < h_0.getTable()[i].size(); ++i) {
            keys_0.push_back(h_0.getTable()[i][j].first);
        }
    }
    for (int i = 0; i < h_1.getTable().size(); ++i) {
        for (int j = 0; j < h_1.getTable()[i].size(); ++i) {
            keys_1.push_back(h_1.getTable()[i][j].first);
        }
    }
    h_0.swap(h_1);
    while (!keys_0.empty()){
        EXPECT_TRUE(h_1.contains(keys_0.back()));
        keys_0.pop_back();
    }

    while (!keys_1.empty()){
        EXPECT_TRUE(h_0.contains(keys_1.back()));
        keys_1.pop_back();
    }
}

TEST(hashTableTest, assignmentTest){
    std::vector<Key> keys_0, keys_1;
    HashTable<Value> h_0 = createRandHashTable();
    HashTable<Value> h_1;
    for (int i = 0; i < h_0.getTable().size(); ++i) {
        for (int j = 0; j < h_0.getTable()[i].size(); ++i) {
            keys_0.push_back(h_0.getTable()[i][j].first);
        }
    }
    h_1 = h_0;
    while (!keys_0.empty()) {
        EXPECT_TRUE(h_1.contains(keys_0.back()));
        keys_0.pop_back();
    }

}

TEST(hashTableTest, constAtTest){

    const HashTable<Value> h_0 = createRandHashTable();
    std::vector<Key> keys;
    for (int i = 0; i < h_0.getTable().size(); ++i) {
        for (int j = 0; j < h_0.getTable()[i].size(); ++i) {
            keys.push_back(h_0.getTable()[i][j].first);
        }
    }

    while (keys.size() > 0) {
        EXPECT_EQ(h_0.at(keys.back()).getName(), keys.back());
        keys.pop_back();
    }
    for(int i = 0; i < 1000; ++i) {
        Key randStr = randomString(11);
        EXPECT_THROW(h_0.at(randStr).getName(), std::invalid_argument);
    }
}

TEST(hashTableTest, eqTest){
    HashTable<Value> h_0 = createRandHashTable();
    HashTable<Value> h_1;
    HashTable<Value> h_2;
    h_1 = h_0;
    h_2 = h_0;
    Value a;
    h_2.insert("TEST", a);
    EXPECT_TRUE(h_0 != h_2);
    EXPECT_TRUE(h_0 == h_1);

}