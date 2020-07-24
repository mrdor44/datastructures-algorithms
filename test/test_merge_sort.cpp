#include <vector>
#include <array>
#include "inc/list.hpp"
#include "inc/array_list.hpp"
#include "inc/merge_sort.hpp"
#include "mock.hpp"

using testing::Types;

template<typename T>
class MergeSortTests : public testing::Test {
protected:
    static const T CONTAINER;
};
TYPED_TEST_SUITE_P(MergeSortTests);

template<typename T>
const T MergeSortTests<T>::CONTAINER({2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22});

TYPED_TEST_P(MergeSortTests, Sort) {
    T sorted = merge_sort(this->CONTAINER);
    FAIL(); // check if sorted
}

REGISTER_TYPED_TEST_SUITE_P(MergeSortTests, Sort);

using ContainerTypes = Types<std::vector<int>, std::array<int, 11>, List<int>, ArrayList<int>>;
INSTANTIATE_TYPED_TEST_SUITE_P(, MergeSortTests, ContainerTypes);

TEST(MergeSortTests, SortEmptyContainer) {
    std::vector<int> empty;
    merge_sort(empty);
}