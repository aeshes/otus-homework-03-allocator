#pragma once

#include <array>
#include <map>

#include "array_pool.hpp"

using std::size_t;

template<typename T, size_t PreallocSize = 10>
class memory_pool
{
public:
	static memory_pool& get_instance()
	{
		if (instance == nullptr)
		{
			instance = new memory_pool();
        }

		return *instance;
	}

    using chunk_t = std::array<T, PreallocSize>;

    T* allocate(size_t size)
	{
		for (auto& chunk : pool)
		{
			auto& ar = *chunk.first;

			if (chunk.second + size <= PreallocSize)
			{
				T* ptr = &ar[0] + chunk.second;
				chunk.second += size;
				return ptr;
			}
		}

		return append_new_chunk(size);
	}

	void deallocate(T* ptr)
    {
        auto chunk = std::prev(pool.upper_bound(reinterpret_cast<chunk_t *>(ptr)));
		if (--chunk->second == 0)
		{
			delete chunk->first;
			pool.erase(chunk);
		}
	}

private:
	memory_pool()
	{

	}

	~memory_pool()
	{
		for (auto& chunk : pool)
		{
			delete chunk->first;
		}
	}

	memory_pool(const memory_pool &) = delete;
	memory_pool(memory_pool &&) = delete;
	memory_pool& operator = (const memory_pool &) = delete;
	memory_pool& operator = (memory_pool &&) = delete;

    T* append_new_chunk(size_t size)
	{
        auto c = new chunk_t();
		pool.emplace(std::make_pair(c, size));
		auto& ar = *c;
        return &ar[0];
	}

    std::map<chunk_t*, size_t> pool;

	static memory_pool* instance;
};

template<typename T, size_t PreallocSize>
memory_pool<T, PreallocSize>* memory_pool<T, PreallocSize>::instance = nullptr;


template<typename T, size_t PreallocSize = 10>
struct allocator
{
	using value_type = T;

	allocator() noexcept = default;

    template<typename U, size_t N>
    allocator(const allocator<U, N> & other) noexcept
	{

	}

    T* allocate(size_t size)
    {
        return memory_pool<T, PreallocSize>::get_instance().allocate(size);
	}

    void deallocate(T* p, size_t size)
    {
        return memory_pool<T, PreallocSize>::get_instance().deallocate(p);
	}

	template<typename U>
	struct rebind
	{
        using other = allocator<U, PreallocSize>;
	};
};

template<typename T, typename U>
constexpr bool operator == (const allocator<T>& lhs, const allocator<U>& rhs) noexcept
{
	return true;
}

template<typename T, typename U>
constexpr bool operator != (const allocator<T>& lhs, const allocator<U>& rhs) noexcept
{
	return !(lhs == rhs);
}
