#include <iostream>
#include <map>
#include <gtest/gtest.h>

#include "allocator.hpp"


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

TEST(Allocator, MapWithStdAllocator)
{
	std::map<int, int> map;

	for (auto i = 0; i <= 9; i++)
	{
		map[i] = factorial(i);
	}

	print_map(map);
}

TEST(Allocator, MapWithCustomAllocator)
{
	std::map<int, int, std::less<int>, allocator<int>> map;

	for (auto i = 0; i <= 9; i++)
	{
		map[i] = factorial(i);
	}

	print_map(map);
}
