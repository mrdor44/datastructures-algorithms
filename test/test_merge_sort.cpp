#include <vector>
#include <array>
#include "inc/list.hpp"
#include "inc/array_list.hpp"
#include "inc/merge_sort.hpp"
#include "mock.hpp"

using testing::Types;

template<typename Container>
class MergeSortTests : public testing::Test {
protected:
    static const Container UNSORTED;
    static const Container SORTED;
};

template<typename Container>
const Container MergeSortTests<Container>::UNSORTED({6, 7, 3, 8, 1, 5, 7, 10, 2, 8});

template<typename Container>
const Container MergeSortTests<Container>::SORTED({1, 2, 3, 5, 6, 7, 7, 8, 8, 10});

using ContainerTypes = Types<std::vector<int>, std::array<int, 11>, ArrayList<int>>;
TYPED_TEST_SUITE(MergeSortTests, ContainerTypes);

TYPED_TEST(MergeSortTests, Sort) {
    TypeParam sorted = merge_sort(this->UNSORTED);
    EXPECT_EQ(this->SORTED, sorted);
}

TEST(MergeSortTests, SortEmptyContainer) {
    std::vector<int> empty;
    merge_sort(empty);
}