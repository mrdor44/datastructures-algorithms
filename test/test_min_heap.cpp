#include <vector>
#include "mock.hpp"
#include "test/common.hpp"
#include "inc/min_heap.hpp"

using testing::NotNull;

class MinHeap {
public:
    MinHeap();
    explicit MinHeap(const std::vector<int>&);
    MinHeap(const int*, const int*);
    virtual ~MinHeap();

private:
    explicit MinHeap(const t_minheap&);

public:
    void push(int);
    int pop();
    int get_min();
    std::vector<int> to_vector();
    bool is_empty();

private:
    t_minheap m_heap;
};

MinHeap::MinHeap() : MinHeap(MINHEAP_create()) {}

MinHeap::MinHeap(const std::vector<int>& v) : MinHeap(v.data(), v.data() + v.size()) {}

MinHeap::MinHeap(const int* begin, const int* end) : MinHeap(MINHEAP_create(begin, end)) {}

MinHeap::~MinHeap() {
    MINHEAP_DESTROY(m_heap);
}

MinHeap::MinHeap(const t_minheap& heap) : m_heap(heap) {
    EXPECT_THAT(m_heap, NotNull());
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

std::vector<int> MinHeap::to_vector() {
    std::vector<int> v;
    while (!is_empty()) {
        v.push_back(pop());
    }
    return v;
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
    MinHeap heap(v);

    std::vector<int> heapified = heap.to_vector();
    std::sort(v.begin(), v.end());
    EXPECT_EQ(v, heapified);
}
