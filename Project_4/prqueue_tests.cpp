#include "prqueue.h"

#include "gtest/gtest.h"

using namespace std;

TEST(Prqueue, SizeTest) {
    prqueue<int> pq;

    pq.enqueue(10, 1);
    pq.enqueue(20, 2);
    pq.enqueue(30, 3);

    EXPECT_EQ(pq.size(),3);
}

TEST(Prqueue, ClearTest) {
    prqueue<int> pq;

    pq.enqueue(10, 1);
    pq.enqueue(20, 2);
    pq.enqueue(30, 3);

    pq.clear();

    EXPECT_EQ(0, pq.getRoot());
    EXPECT_EQ(pq.size(),0);
}

TEST(Prqueue, AsStringTest) {
    prqueue<string> names;
    names.enqueue("Gwen", 3);
    names.enqueue("Jen", 2);
    names.enqueue("Ben", 1);
    names.enqueue("Sven", 2);

    std::string expected = "1 value: Ben\n2 value: Jen\n2 value: Sven\n3 value: Gwen\n";

    EXPECT_EQ(names.as_string(), expected);
}

TEST(Prqueue, DequeueTest){
    prqueue<int> pq;

    pq.enqueue(10, 1);
    pq.enqueue(20, 2);
    pq.enqueue(30, 3);

    int expected1 = 10;
    int expected2 = 20;
    int expected3 = 30;
    
    ASSERT_EQ(pq.dequeue(), expected1);
    ASSERT_EQ(pq.dequeue(), expected2);
    ASSERT_EQ(pq.dequeue(), expected3);
    ASSERT_EQ(pq.size(), 0);
}

TEST(Prqueue, DequeueTest2){
    prqueue<string> names;
    names.enqueue("Gwen", 3);
    names.enqueue("Jen", 2);
    names.enqueue("Ben", 1);
    names.enqueue("Sven", 2);

    ASSERT_EQ(names.dequeue(), "Ben");
    ASSERT_EQ(names.dequeue(), "Jen");
    ASSERT_EQ(names.dequeue(), "Sven");
    ASSERT_EQ(names.dequeue(), "Gwen");
    ASSERT_EQ(names.size(), 0);

    prqueue<int> pq;

    pq.enqueue(10, 5);
    pq.enqueue(20, 1);
    pq.enqueue(30, 10);
    pq.enqueue(40,2);
    pq.enqueue(50, 9);
    pq.enqueue(60, 3);
    pq.enqueue(70, 8);
    pq.enqueue(80, 4);
    pq.enqueue(90, 7);

    EXPECT_EQ(pq.dequeue(), 20);
    EXPECT_EQ(pq.peek(), 40);

    EXPECT_EQ(pq.dequeue(), 40);
    EXPECT_EQ(pq.peek(), 60);

    EXPECT_EQ(pq.dequeue(), 60);
    EXPECT_EQ(pq.peek(), 80);

    EXPECT_EQ(pq.dequeue(), 80);
    EXPECT_EQ(pq.peek(), 10);
}