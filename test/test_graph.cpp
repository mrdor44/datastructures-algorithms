#include "inc/graph.hpp"
#include "mock.hpp"

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