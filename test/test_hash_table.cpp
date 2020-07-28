#include <vector>
#include <cstdlib>
#include "mock.hpp"
#include "test/common.hpp"

extern "C" {
#include "inc/hash_table.h"
}

//@formatter:off
DECLARE_HOOKABLE(malloc);
//@formatter:on

static int g_times_to_call_original_malloc = 0;

void* __STUB__malloc(size_t __size) noexcept {
    EXPECT_GE(g_times_to_call_original_malloc, 0);
    if (0 == g_times_to_call_original_malloc) {
        return nullptr;
    }
    SCOPE_REMOVE_HOOK(malloc);
    --g_times_to_call_original_malloc;
    return malloc(__size);
}

using testing::NotNull;
using testing::IsNull;
using testing::_;
using testing::Return;

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
    operator t_hashtable(); // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)

public:
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

HashTable::operator t_hashtable() {
    return m_htable;
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
        EXPECT_EQ(RETURNCODE_HASHTABLE_REMOVE_KEY_NOT_FOUND,
                  HASHTABLE_remove(htable, i));
        EXPECT_EQ(RETURNCODE_HASHTABLE_GET_KEY_NOT_FOUND,
                  HASHTABLE_get(htable, i, nullptr));
    }
}

TEST(InvalidParameters, Create) {
    EXPECT_THAT(HASHTABLE_create(0, nullptr), IsNull());
    HASHTABLE_destroy(nullptr);
    EXPECT_EQ(RETURNCODE_HASHTABLE_INSERT_INVALID_PARAMETERS,
              HASHTABLE_insert(nullptr, 0, 0));
    EXPECT_EQ(RETURNCODE_HASHTABLE_REMOVE_INVALID_PARAMETERS,
              HASHTABLE_remove(nullptr, 0));
    EXPECT_EQ(RETURNCODE_HASHTABLE_GET_INVALID_PARAMETERS,
              HASHTABLE_get(nullptr, 0, nullptr));
}

TEST(WhiteBox, CreateStructMallocFailure) {
    auto htable = reinterpret_cast<t_hashtable>(0x1000);
    {
        g_times_to_call_original_malloc = 0;
        INSTALL_HOOK(malloc, __STUB__malloc);
        htable = HASHTABLE_create(10, HashTable::simple_hash);
    }
    EXPECT_THAT(htable, IsNull());
}

TEST(WhiteBox, CreateMallocBucketsFailure) {
    auto htable = reinterpret_cast<t_hashtable>(0x1000);
    {
        g_times_to_call_original_malloc = 1;
        INSTALL_HOOK(malloc, __STUB__malloc);
        htable = HASHTABLE_create(10, HashTable::simple_hash);
    }
    EXPECT_THAT(htable, IsNull());
}

TEST(WhiteBox, InsertMallocFailure) {
    HashTable htable(10);
    t_returncode returncode = RETURNCODE_INVALID_VALUE;
    {
        g_times_to_call_original_malloc = 0;
        INSTALL_HOOK(malloc, __STUB__malloc);
        returncode = HASHTABLE_insert(htable, 0, 0);
    }
    EXPECT_EQ(RETURNCODE_HASHTABLE_INSERT_MALLOC_FAILED, returncode);
    htable.insert(0, 0);
    EXPECT_EQ(0, htable[0]);
}
