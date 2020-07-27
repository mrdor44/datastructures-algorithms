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

    int get_min() {
        int min = 0;
        EXPECT_SUCCESS(MINHEAP_get_min(heap, &min));
        return min;
    }

protected:
    t_minheap heap{};
};

TEST_F(MinHeapTests, MinHeap) {
    for (int i = 1; i < 30; ++i) {
        push(i);
        EXPECT_EQ(1, get_min());
    }
}
