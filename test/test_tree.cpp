#include "inc/tree.hpp"
#include "mock.hpp"

TEST(Tree, PreOrder) {
    //     10
    //    /  \
    //   5    7
    //  / \    \
    // 9   2    1
    Tree tree(10);
    const Tree<int>::NodePtr& r10 = tree.root();
    Tree<int>::NodePtr c5 = r10->set_left(5);
    Tree<int>::NodePtr c7 = r10->set_right(7);
    c5->set_left(9);
    c5->set_right(2);
    c7->set_right(1);

    List<int> items;
    tree.do_preorder([&](const int& item) { items.push_back(item); });

    EXPECT_EQ(items, List<int>({10, 5, 9, 2, 7, 1}));
}
