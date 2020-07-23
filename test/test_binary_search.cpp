#include <vector>
#include "inc/binary_search.hpp"
#include "mock.hpp"

using testing::ValuesIn;

// TODO: Use Lists, std::array, classic array, strings
template<typename T>
class BinarySearchTests : public testing::Test {
protected:
    static const T CONTAINER;
};
TYPED_TEST_SUITE_P(BinarySearchTests);

template<typename T>
const T BinarySearchTests<T>::CONTAINER({2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22});

TYPED_TEST_P(BinarySearchTests, SearchExistingValues) {
    for (int value : this->CONTAINER) {
        const auto& it = dsa::binary_search(this->CONTAINER.cbegin(),
                                            this->CONTAINER.cend(),
                                            value);
        EXPECT_EQ(*it, value);
    }
}

TYPED_TEST_P(BinarySearchTests, SearchNonExistingElement) {
    for (int value : this->CONTAINER) {
        const auto& it = dsa::binary_search(this->CONTAINER.cbegin(),
                                            this->CONTAINER.cend(),
                                            value + 1);
        EXPECT_NE(*it, value);
    }
}

REGISTER_TYPED_TEST_SUITE_P(BinarySearchTests, SearchExistingValues, SearchNonExistingElement);

using ContainerTypes = testing::Types<std::vector<int>>;
INSTANTIATE_TYPED_TEST_SUITE_P(, BinarySearchTests, ContainerTypes);

TEST(BinarySearchTests, SearchInEmptyContainer) {
    std::vector<int> empty;
    const auto& it = dsa::binary_search(empty.cbegin(), empty.cend(), 1);
    EXPECT_EQ(it, empty.cend());
}