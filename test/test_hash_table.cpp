#include <vector>
#include "mock.hpp"
#include "test/common.hpp"

extern "C" {
#include "inc/hash_table.h"
}

using testing::NotNull;

class HashTable {
public:
    explicit HashTable(int num_buckets);
    virtual ~HashTable();

private:
    explicit HashTable(const t_hashtable&);

public:
    void insert(int key, int value);
    void remove(int key);
    int operator[](int key);

private:
    static unsigned int simple_hash(int);

private:
    t_hashtable m_htable;
};

HashTable::HashTable(int num_buckets) :
        HashTable(HASHTABLE_create(num_buckets, simple_hash)) {}

HashTable::~HashTable() {
    HASHTABLE_DESTROY(m_htable);
}

HashTable::HashTable(const t_hashtable& htable) : m_htable(htable) {
    EXPECT_THAT(m_htable, NotNull());
}

void HashTable::insert(int key, int value) {
    EXPECT_SUCCESS(HASHTABLE_insert(m_htable, key, value));
}

void HashTable::remove(int key) {
    EXPECT_SUCCESS(HASHTABLE_remove(m_htable, key));
}

int HashTable::operator[](int key) {
    int value = 0;
    EXPECT_SUCCESS(HASHTABLE_get(m_htable, key, &value));
    return value;
}

unsigned int HashTable::simple_hash(int n) {
    return abs(n);
}

class HashTableTests : public testing::TestWithParam<int> {
};

INSTANTIATE_TEST_SUITE_P(, HashTableTests, testing::Range(1, 10000, 10));

TEST_P(HashTableTests, InsertGetRemove) {
    static const int NUM_ELEMENTS = 10000;

    HashTable htable(GetParam());

    for (int i = 1; i < NUM_ELEMENTS + 1; ++i) {
        htable.insert(i, i + 1);
        EXPECT_EQ(i + 1, htable[i]);
    }

    for (int i = 1; i < NUM_ELEMENTS / 2; ++i) {
        htable.remove(i);
    }
}
