#include <iostream>
#include <map>
#include <gtest/gtest.h>

#include "stack_allocator.hpp"


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

TEST(StdMap, StdAllocator)
{
	std::map<int, int> map;

	for (auto i = 0; i <= 9; i++)
	{
		map[i] = factorial(i);
	}

	print_map(map);
}

using allocator_type = stack_allocator<std::map<int, int>::value_type, 10>;

TEST(StdMap, CustomAllocator)
{
    int buffer[0x1000];

    std::map<int, int, std::less<int>, allocator_type> map{allocator_type(buffer)};

	for (auto i = 0; i <= 9; i++)
	{
		map[i] = factorial(i);
	}

	print_map(map);
}
