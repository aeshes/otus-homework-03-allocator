#pragma once

#include <cstdint>
#include <new>

template<typename T, typename Strategy>
class memory_pool
{
public:
    memory_pool()
    {
        strategy.init();
    }

    void* allocate(unsigned int size)
    {
        return strategy.allocate();
    }

    void deallocate(void* p)
    {
        strategy.deallocate(p);
    }

private:
    Strategy strategy;
};

template<typename T, unsigned int N = 10>
class linear_strategy
{
public:
    using size_type = unsigned int;

    void init()
    {
        for (size_type i = 0; i < N; i++)
        {
            state[i] = false;
        }
    }

    void* allocate()
    {
        for(size_type i = 0; i < N; i++)
        {
            if (!state[i])
            {
                state[i] = true;
                return &buffer[sizeof(T) * i];
            }
        }

        throw std::bad_alloc();
    }

    void deallocate(void* p)
    {
        for (size_type i = 0; i < N; i++)
        {
            if (&buffer[sizeof(T) * i] == p)
            {
                state[i] = false;
                return;
            }
        }
    }

private:
    uint8_t buffer[sizeof(T) * N];
    bool state[N];
};
