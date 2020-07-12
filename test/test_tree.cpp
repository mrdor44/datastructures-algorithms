#include "inc/tree.hpp"
#include "mock.hpp"

using testing::Test;

class TreeTest : public Test {
protected:
    void SetUp() override {
        Test::SetUp();

        //     10
        //    /  \
        //   5    7
        //  / \    \
        // 9   2    1
        tree = Tree<int>::create(10);
        const Tree<int>::NodePtr& c5 = tree->set_left(5);
        const Tree<int>::NodePtr& c7 = tree->set_right(7);
        c5->set_left(9);
        c5->set_right(2);
        c7->set_right(1);
    }

    Tree<int>::NodePtr tree;
};

TEST_F(TreeTest, PreOrder) {
    auto items = Tree<int>::preorder(tree).collect<List<int>>();
    EXPECT_EQ(items, List<int>({10, 5, 9, 2, 7, 1}));
}

TEST_F(TreeTest, PostOrder) {
    auto items = Tree<int>::postorder(tree).collect<List<int>>();
    EXPECT_EQ(items, List<int>({9, 2, 5, 1, 7, 10}));
}

TEST_F(TreeTest, InOrder) {
    auto items = Tree<int>::inorder(tree).collect<List<int>>();
    EXPECT_EQ(items, List<int>({9, 5, 2, 10, 7, 1}));
}

TEST_F(TreeTest, BFS) {
    auto items = Tree<int>::bfs(tree).collect<List<int>>();
    EXPECT_EQ(items, List<int>({10, 5, 7, 9, 2, 1}));
}
