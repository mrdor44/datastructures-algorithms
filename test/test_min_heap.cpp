#include <vector>
#include "mock.hpp"
#include "test/common.hpp"
#include "inc/min_heap.hpp"

using testing::NotNull;

class MinHeapTests : public testing::Test {
protected:
    void SetUp() override {
        Test::SetUp();
        heap = MINHEAP_create();
        EXPECT_THAT(heap, NotNull());
    }

    void TearDown() override {
        MINHEAP_DESTROY(heap);
        Test::TearDown();
    }

    void push(int value) {
        EXPECT_SUCCESS(MINHEAP_push(heap, value));
    }

    int pop() {
        int min = 0;
        EXPECT_SUCCESS(MINHEAP_pop_min(heap, &min));
        return min;
    }

    int get_min() {
        int min = 0;
        EXPECT_SUCCESS(MINHEAP_get_min(heap, &min));
        return min;
    }

protected:
    t_minheap heap{};
};

TEST_F(MinHeapTests, MinHeap) {
    static const int NUM_ELEMENTS = 30;

    for (int i = 1; i < NUM_ELEMENTS + 1; ++i) {
        push(i);
        EXPECT_EQ(1, get_min());
    }

    for (int i = 1; i < NUM_ELEMENTS + 1; ++i) {
        EXPECT_EQ(i, pop());
    }
}
