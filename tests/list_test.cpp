#include <cstdio>
#include <memory_resource>
#include <gtest/gtest.h>

#include "list.hpp"

static unsigned int factorial(unsigned int n)
{
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

template<class List>
void print_list(const List &l)
{
    for (auto it : l)
    {
        printf("%d ", it);
    }
    printf("\n");
}

TEST(CustomList, DefaultAllocator)
{
    list<int> l;

    for (int i = 0; i < 10; i++)
    {
        l.push_front(i);
    }

    print_list(l);
}

template<typename T>
using custom_list = list<T, std::pmr::polymorphic_allocator<T>>;

TEST(CustomList, CustomAllocator)
{
    std::array<int, 10> buffer;
    std::pmr::monotonic_buffer_resource pool { buffer.data(), buffer.size() };

    custom_list<int> l{ &pool };

    for (int i = 0; i < 10; i++)
    {
        l.push_front(i);
    }

    print_list(l);
}
