#include <iostream>
#include <map>

#include "allocator.hpp"
#include "list.hpp"

static unsigned int factorial(unsigned int n)
{
    if (n == 0)
        return 1;

    return n * factorial(n - 1);
}

template<typename Map>
static void print_map(const Map& map)
{
    std::cout << "Printing map values" << std::endl;

    for (const auto& pair : map)
    {
        std::cout << pair.first << ' ' << pair.second << std::endl;
    }
}

template<typename List>
static void print_list(const List& l)
{
    std::cout << "Printing list values" << std::endl;

    for (auto it = l.begin(); it != l.end(); ++it)
    {
        std::cout << *it << ' ' << std::endl;
    }
}

void fillMapWithStdAllocator()
{
    std::map<int, int> map;

    for (auto i = 0; i <= 9; i++)
    {
        map[i] = factorial(i);
    }

    print_map(map);
}

void fillMapWithCustomAllocator()
{
    std::map<int, int, std::less<int>, allocator<int>> map;

    for (auto i = 0; i <= 9; ++i)
    {
        map[i] = factorial(i);
    }

    print_map(map);
}

void fillListWithStdAllocator()
{
    list<int> l;

    for (auto i = 0; i <= 9; i++)
    {
        l.push_front(i);
    }

    print_list(l);
}

void fillListWithCustomAllocator()
{
    list<int, allocator<int>> l;

    for (auto i = 0; i <= 9; i++)
    {
        l.push_front(i);
    }

    print_list(l);
}

int main(int argc, char** argv)
{
    try
    {
        fillMapWithStdAllocator();
        fillMapWithCustomAllocator();
        fillListWithStdAllocator();
        fillListWithCustomAllocator();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}
