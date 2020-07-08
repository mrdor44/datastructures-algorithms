#include "inc/tree.hpp"
#include "mock.hpp"

using testing::Test;

class TreeTest : public Test {
protected:
    void SetUp() override {
        Test::SetUp();
    }
};

TEST(Tree, PreOrder) {
    //     10
    //    /  \
    //   5    7
    //  / \    \
    // 9   2    1
    const Tree<int>::NodePtr& r10 = Tree<int>::create(10);
    const Tree<int>::NodePtr& c5 = r10->set_left(5);
    const Tree<int>::NodePtr& c7 = r10->set_right(7);
    c5->set_left(9);
    c5->set_right(2);
    c7->set_right(1);

    List<int> items;
    Tree<int>::do_preorder(r10, [&](const int& item) { items.push_back(item); });

    EXPECT_EQ(items, List<int>({10, 5, 9, 2, 7, 1}));
}
