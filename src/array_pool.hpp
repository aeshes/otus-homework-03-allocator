#pragma once

#include <array>

using std::size_t;
using byte = unsigned char;

// N - число блоков
// S - размер блока
template<unsigned int n, unsigned int s>
class array_pool
{
public:
	array_pool() : top(-1)
	{
        byte* block = bytes;
        for (int i = 0; i < n; ++i, block += s)
			stack[i] = block;
        top = n - 1;

	}

	void* allocate()
	{
		return reinterpret_cast<void *>(stack[top--]);
	}

	void deallocate(void* back)
	{
		stack[++top] = reinterpret_cast<byte *>(back);
	}

	bool empty() const
	{
		return top < 0;
	}

	bool full() const
	{
		return top == (n - 1);
	}

private:
    unsigned char bytes[n * s];
    unsigned char* stack[n];
	int top;

    std::array<unsigned char, n * s> buffer;
    std::array<unsigned char*, n> st;
};


