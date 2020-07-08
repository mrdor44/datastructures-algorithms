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

    // TODO: Convert to initializer list
    List<int> expected_items;
    expected_items.push_back(10);
    expected_items.push_back(5);
    expected_items.push_back(6);
    expected_items.push_back(7);
    expected_items.push_back(9);
    EXPECT_EQ(items, expected_items);
}
