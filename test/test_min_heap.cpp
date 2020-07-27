#include <vector>
#include "mock.hpp"
#include "test/common.hpp"
#include "inc/min_heap.hpp"

using testing::NotNull;

class MinHeap {
public:
    MinHeap();
    MinHeap(int*, int*);
    virtual ~MinHeap();
    void push(int);
    int pop();
    int get_min();

    bool is_empty();
private:
    t_minheap m_heap;
};

MinHeap::MinHeap() : m_heap(MINHEAP_create()) {
    EXPECT_THAT(m_heap, NotNull());
}

MinHeap::MinHeap(int* begin, int* end) :
        m_heap(MINHEAP_create(begin, end)) {
    EXPECT_THAT(m_heap, NotNull());
}

MinHeap::~MinHeap() {
    MINHEAP_DESTROY(m_heap);
}

void MinHeap::push(int value) {
    EXPECT_SUCCESS(MINHEAP_push(m_heap, value));
}

int MinHeap::pop() {
    int min = 0;
    EXPECT_SUCCESS(MINHEAP_pop_min(m_heap, &min));
    return min;
}

int MinHeap::get_min() {
    int min = 0;
    EXPECT_SUCCESS(MINHEAP_get_min(m_heap, &min));
    return min;
}

bool MinHeap::is_empty() {
    return MINHEAP_is_empty(m_heap);
}

TEST(MinHeapTests, PushGetMinPop) {
    static const int NUM_ELEMENTS = 30;

    MinHeap heap;

    for (int i = 1; i < NUM_ELEMENTS + 1; ++i) {
        heap.push(i);
        EXPECT_EQ(1, heap.get_min());
    }

    for (int i = 1; i < NUM_ELEMENTS + 1; ++i) {
        EXPECT_EQ(i, heap.pop());
    }
}

TEST(MinHeapTests, Heapify) {
    std::vector<int> v({8, 2, 9, 3, 5, 7, 1});
    MinHeap heap(v.data(), v.data() + v.size());

    std::vector<int> heapified;
    while (!heap.is_empty()) {
        heapified.push_back(heap.pop());
    }
    std::sort(v.begin(), v.end());
    EXPECT_EQ(v, heapified);
}
