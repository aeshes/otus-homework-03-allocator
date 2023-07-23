#include <vector>
#include <gtest/gtest.h>

#include "stack_allocator.hpp"

static unsigned int factorial(unsigned int n)
{
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

using allocator_type = stack_allocator<int, 10>;

TEST(StdVector, CustomAllocator)
{
    int buffer[0x1000];

    std::vector<int, allocator_type> v{allocator_type(buffer)};

    for (int i = 0; i < 10; i++)
    {
        v.push_back(factorial(i));
    }
}
