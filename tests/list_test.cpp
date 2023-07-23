#include <cstdio>
#include <list>
#include <gtest/gtest.h>

#include "list.hpp"
#include "stack_allocator.hpp"

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

template<typename T, size_t size = 10>
using custom_list = list<T, stack_allocator<T, size>>;

TEST(CustomList, StandardAllocator)
{
    list<int> l;

    for (int i = 0; i < 10; i++)
    {
        l.push_front(i);
    }

    print_list(l);
}

using allocator_type = stack_allocator<int, 10>;

TEST(CustomList, CustomAllocator)
{
    int buffer[0x1000];

    custom_list<int> l{allocator_type(buffer)};

    for (int i = 0; i < 10; i++)
    {
        l.push_front(i);
    }

    print_list(l);
}
