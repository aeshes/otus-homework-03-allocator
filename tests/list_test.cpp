#include <cstdio>
#include <list>
#include <gtest/gtest.h>

#include "list.hpp"
#include "arena_allocator.hpp"

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

template<typename T, size_t size = 10 * alignof(T)>
using custom_list = list<T, arena_allocator<T, size, alignof(T)>>;

TEST(CustomList, StandardAllocator)
{
    list<int> l;

    for (int i = 0; i < 10; i++)
    {
        l.push_front(i);
    }

    print_list(l);
}

TEST(CustomList, CustomAllocator)
{
    custom_list<int>::allocator_type::arena_type a;
    custom_list<int> l{a};

    for (int i = 0; i < 10; i++)
    {
        l.push_front(i);
    }

    print_list(l);
}
