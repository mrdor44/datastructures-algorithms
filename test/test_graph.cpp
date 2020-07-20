#include "inc/graph.hpp"
#include "mock.hpp"

using testing::Test;

class GraphTest : public Test {
protected:
    void SetUp() override {
        Test::SetUp();

        //     1 --> 9 --> 8 --> 7
        //     |     ^     ^     |
        //     |     |     |     |
        //     |     |    /      |
        //     |     | ---       |
        //     v     |/          |
        //     2 --> 3 --> 4 <-  |
        //     ^     |         \ |
        //     |     v          \V
        //     8 <-- 5 --> 6 --> 7
        const auto& r1 = graph.add_root(1);
        const auto& n2 = r1->add_neighbor(2);
        const auto& n3 = n2->add_neighbor(3);
        const auto& n4 = n3->add_neighbor(4);
        const auto& n9 = r1->add_neighbor(9);
        n3->add_neighbor(n9);
        const auto& top8 = n9->add_neighbor(8);
        n3->add_neighbor(top8);
        const auto& top7 = top8->add_neighbor(7);
        const auto& bottom7 = top7->add_neighbor(7);
        bottom7->add_neighbor(n4);
        const auto& n5 = n3->add_neighbor(5);
        const auto& bottom8 = n5->add_neighbor(8);
        bottom8->add_neighbor(n2);
        const auto& n6 = n5->add_neighbor(6);
        n6->add_neighbor(bottom7);
    }

    Graph<int> graph;
};

TEST_F(GraphTest, BFS) {
    EXPECT_EQ(graph.bfs().collect<List<int>>(),
              List<int>({1, 2, 9, 3, 8, 4, 5, 7, 8, 6, 7}));
}

TEST_F(GraphTest, DFS) {
    EXPECT_EQ(graph.dfs().collect<List<int>>(),
              List<int>({1, 2, 3, 4, 9, 8, 7, 7, 5, 8, 6}));
}

TEST(Graph, Circle) {
    Graph<int> graph;
    const Graph<int>::NodePtr& n1 = graph.add_root(1);
    const Graph<int>::NodePtr& n2 = n1->add_neighbor(2);
    const Graph<int>::NodePtr& n3 = n2->add_neighbor(3);
    n3->add_neighbor(n1);
    EXPECT_EQ(1, n1->value);
    EXPECT_EQ(2, n1->neighbor(0)->value);
    EXPECT_EQ(3, n1->neighbor(0)->neighbor(0)->value);
    EXPECT_EQ(1, n1->neighbor(0)->neighbor(0)->neighbor(0)->value);
}
