#include <vector>
#include "inc/binary_search.hpp"
#include "mock.hpp"

using testing::ValuesIn;

// TODO: Use Lists, std::array, classic array, strings
class BinarySearchTests : public testing::TestWithParam<int> {
public:
    static const std::vector<int> CONTAINER;
};

const std::vector<int> BinarySearchTests::CONTAINER({2, 4, 6, 8, 10, 12, 14, 16, 18, 20});

INSTANTIATE_TEST_SUITE_P(ExistingValues,
                         BinarySearchTests,
                         ValuesIn(BinarySearchTests::CONTAINER),
                         testing::PrintToStringParamName());

TEST_P(BinarySearchTests, SearchExistingValue) {
    const auto& it = dsa::binary_search(CONTAINER.cbegin(),
                                        CONTAINER.cend(),
                                        GetParam());
    EXPECT_EQ(*it, GetParam());
}

TEST_F(BinarySearchTests, SearchNonExistingElement) {
    FAIL();
}

TEST_F(BinarySearchTests, SearchInEmptyContainer) {
    FAIL();
}