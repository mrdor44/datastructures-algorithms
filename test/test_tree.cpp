#include "inc/tree.hpp"
#include "mock.hpp"

TEST(Tree, PreOrder) {
    //    10
    //   / | \
    //  5  6  7
    //  |
    //  9
    Tree tree(10);
    const Tree<int>::NodePtr& r10 = tree.root();
    Tree<int>::NodePtr c5 = r10->add_child(5);
    Tree<int>::NodePtr c6 = r10->add_child(6);
    c5->add_child(9);
    r10->add_child(7);

    List<int> items;
    tree.do_preorder([&](const int& item) { items.push_back(item); });

    EXPECT_EQ(items, List<int>({10, 5, 6, 7, 9}));
}
