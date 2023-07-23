#include <iostream>
#include <map>
#include <gtest/gtest.h>

#include "short_allocator.hpp"


static unsigned int factorial(unsigned int n)
{
	if (n == 0) return 1;
	return n * factorial(n - 1);
}

template<typename Map>
static void print_map(const Map& map)
{
	for (const auto& pair : map)
	{
		std::cout << pair.first << ' ' << pair.second << std::endl;
	}
}

template<typename K, typename T, size_t size = 10 * alignof(T)>
using smap = std::map<K, T, std::less<K>, short_allocator<T, size, alignof(T)>>;

TEST(StdMap, StdAllocator)
{
	std::map<int, int> map;

	for (auto i = 0; i <= 9; i++)
	{
		map[i] = factorial(i);
	}

	print_map(map);
}

TEST(StdMap, CustomAllocator)
{
    smap<int, int>::allocator_type::arena_type a;
    smap<int, int> map;

	for (auto i = 0; i <= 9; i++)
	{
		map[i] = factorial(i);
	}

	print_map(map);
}
