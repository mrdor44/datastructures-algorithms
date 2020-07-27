#include <vector>
#include "mock.hpp"
#include "inc/min_heap.hpp"

using testing::NotNull;

TEST(MinHeapTests, MinHeap) {
    t_minheap heap = MINHEAP_create();
    EXPECT_THAT(heap, NotNull());
    MINHEAP_DESTROY(heap);
}
