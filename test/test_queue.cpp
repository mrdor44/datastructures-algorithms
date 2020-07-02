#include "inc/queue.hpp"
#include "mock.hpp"

TEST(Queue, EnqueueDequeue) {
    Queue<int> queue;
    queue.enqueue(1);
    EXPECT_EQ(1, queue.next());
    queue.enqueue(2);
    EXPECT_EQ(1, queue.next());
    queue.dequeue();
    EXPECT_EQ(2, queue.next());
}