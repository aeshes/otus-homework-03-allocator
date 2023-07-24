#include <iostream>
#include <map>
#include <memory_resource>
#include <gtest/gtest.h>


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

TEST(StdMap, DefaultAllocator)
{
	std::map<int, int> map;

	for (auto i = 0; i <= 9; i++)
	{
		map[i] = factorial(i);
	}

	print_map(map);
}

template<typename K, typename T>
using smap = std::map<K, T, std::less<K>, std::pmr::polymorphic_allocator<T>>;

TEST(StdMap, CustomAllocator)
{
    std::array<int, 10> buffer;
    std::pmr::memory_resource* resource = std::pmr::new_delete_resource();
    std::pmr::monotonic_buffer_resource pool { buffer.data(), buffer.size(), resource };

    smap<int, int> map{ &pool };

	for (auto i = 0; i <= 9; i++)
	{
		map[i] = factorial(i);
	}

	print_map(map);
}
