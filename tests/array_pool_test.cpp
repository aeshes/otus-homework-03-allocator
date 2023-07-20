#include <gtest/gtest.h>

#include "array_pool.hpp"

TEST(ArrayPool, FullOnCreate)
{
    array_pool<12, 4> pool;

    ASSERT_TRUE(pool.full());
}

TEST(ArrayPool, EmptyAfterNAllocations)
{
    constexpr int nBlocks = 3;
    constexpr int blockSize = 4;

    array_pool<nBlocks, blockSize> pool;

    for (int i = 0; i < nBlocks; i++)
        pool.allocate();

    ASSERT_TRUE(pool.empty());
}

TEST(ArrayPool, Allocation)
{
    array_pool<12, 4> pool;

    ASSERT_TRUE(pool.allocate() != nullptr);
}

TEST(ArrayPool, Deallocation)
{
    array_pool<3, 4> pool;

    auto p1 = pool.allocate();
    auto p2 = pool.allocate();
    auto p3 = pool.allocate();

    ASSERT_TRUE(pool.empty());

    pool.deallocate(p3);
    pool.deallocate(p2);
    pool.deallocate(p1);

    ASSERT_TRUE(pool.full());
}
