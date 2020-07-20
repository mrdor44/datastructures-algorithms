#include <vector>
#include "inc/binary_search.hpp"
#include "mock.hpp"

// TODO: Use Lists, std::array, classic array, strings
class BinarySearchTests : public testing::Test {
protected:
    void SetUp() override {
        Test::SetUp();
        container = std::vector<int>({2, 4, 6, 8, 10, 12, 14, 16, 18, 20});
    }

    std::vector<int> container;
};

TEST_F(BinarySearchTests, SearchExistingElement) {
    // TODO: Search for all values
    const auto& it = dsa::binary_search(container.cbegin(), container.cend(), 8);
    EXPECT_EQ(*it, 8);
}

TEST_F(BinarySearchTests, SearchFirstElement) {
    FAIL();
}

TEST_F(BinarySearchTests, SearchLastElement) {
    FAIL();
}

TEST_F(BinarySearchTests, SearchNonExistingElement) {
    FAIL();
}

TEST_F(BinarySearchTests, SearchInEmptyContainer) {
    FAIL();
}