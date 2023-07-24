#include <memory_resource>
#include <vector>
#include <array>
#include <iostream>
#include <gtest/gtest.h>

static unsigned int factorial(unsigned int n)
{
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

template<typename T>
using vector = std::vector<T, std::pmr::polymorphic_allocator<T>>;

TEST(StdVector, PolymorphicAllocator)
{
    std::array<int, 10> buffer;
    std::pmr::memory_resource* resource = std::pmr::new_delete_resource();
    std::pmr::monotonic_buffer_resource pool { buffer.data(), buffer.size(), resource };

    vector<int> v { &pool };

    for (int i = 0; i < 10; i++)
    {
        v.push_back(factorial(i));
    }

    for (auto i : v)
    {
        std::cout << i << std::endl;
    }
}
