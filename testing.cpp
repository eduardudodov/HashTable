
#include <gtest/gtest.h>
#include "HashTable.h"

class testHashTable : public ::testing::Test {
protected:
    virtual void SetUp() {
    }
    HashTable h0_;
};

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

class testValue : public ::testing::Test {
protected:
    virtual void SetUp() {
    }
    Value v[100];
};



TEST_F(testHashTable, resizeTest){
    int i = 5; int size = 10;
    while(i--) {
        h0_.resize();
        size*=2;
        EXPECT_EQ(size, h0_.getTableSize());
    }

}

//test value filling
TEST_F(testValue, addToValueTest) {
    for (int i = 0; i < 100; ++i) {
        v[i].edit(randomString(10), rand()%2, rand()%8);
    }

    for (int i = 0; i < 100; ++i) {
        v[i].addNext(&v[i + 1]);
    }
    for (int i = 0; i < 100; ++i) {
        std::string aStr = v[i].getNext()->getName();
        std::string bStr = v[i+1].getName();
        EXPECT_EQ(aStr, bStr);
    }
}

//test value operator =
TEST_F(testValue, operatorEqTest){
    for (int i = 0; i < 100000; i+=2) {
        v[i].edit(randomString(1000), rand()%2, rand()%8);
        v[i+1] = v[i];
        EXPECT_EQ(v[i + 1].getName(), v[i].getName());
    }
}

//test HashTable_insert

::testing::AssertionResult valueEq(Value a, Value b){
    if(a.getName() == b.getName()) return ::testing::AssertionSuccess();
    while(a.getNext() != NULL){
        a = *a.getNext();
        if(a.getName() == b.getName()) return ::testing::AssertionSuccess();
    }
    return ::testing::AssertionFailure();

}

TEST_F(testHashTable, insertTestLessThanHalf){
    srand(static_cast<unsigned int>(time(NULL)));
    int valueSize = 2000;
    Value * v = new Value[valueSize];
    for (int i = 0; i < valueSize; ++i) {
        v[i].edit(randomString(10), rand()%2, rand()%8);
        std::cout<< std::endl << i << ") #" << h0_.hashCalculation(v[i].getName()) << " " << v[i].getName();
    }
    for (int i = 0; i < valueSize; ++i) {
        EXPECT_TRUE(h0_.insert(v[i].getName(), v[i]));
    }
    for (int i = 0; i < valueSize; ++i) {
        Value  a = v[i];
        Value * b = h0_.getTable()[h0_.hashCalculation(v[i].getName())].getNext();
        EXPECT_TRUE(valueEq(*b,a));
    }
}

