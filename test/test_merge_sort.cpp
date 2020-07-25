#include <vector>
#include "mock.hpp"

extern "C" {
#include "inc/merge_sort.h"
}

static std::vector<int> UNSORTED({6, 7, 3, 8, 1, 5, 7, 10, 2, 8, 11});

static std::vector<int> SORTED({1, 2, 3, 5, 6, 7, 7, 8, 8, 10, 11});

TEST(MergeSortTests, Sort) {
    int* raw_sorted = merge_sort(UNSORTED.data(), UNSORTED.size());
    std::vector<int> sorted(raw_sorted, raw_sorted + UNSORTED.size());
    EXPECT_EQ(SORTED, sorted);
    FREE(raw_sorted);
}

TEST(MergeSortTests, SortEmptyContainer) {
    std::vector<int> empty;
    merge_sort(empty.data(), empty.size());
}