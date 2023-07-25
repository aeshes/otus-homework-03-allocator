#include <memory>
#include <iostream>

template<typename T, size_t N = 10, typename Alloc = std::allocator<T>>
class stack_allocator
{
public:
    using value_type = typename std::allocator_traits<Alloc>::value_type;
    using pointer = typename std::allocator_traits<Alloc>::pointer;
    using const_pointer = typename std::allocator_traits<Alloc>::const_pointer;
    using const_void_pointer = typename std::allocator_traits<Alloc>::const_void_pointer;
    using size_type = size_t;

    explicit stack_allocator()
        : begin(nullptr), end(nullptr), stack_pointer(nullptr)
    {
        std::cout << "default ctor" << std::endl;
    }

    explicit stack_allocator(pointer buffer)
        : begin(buffer), end(buffer + N), stack_pointer(buffer)
    {
        std::cout << "pointer: " << std::hex << buffer << std::endl;
        std::cout << "begin: " << std::hex << begin << std::endl;
        std::cout << "end: " << std::hex << end << std::endl;
        std::cout << "stack_pointer: " << std::hex << stack_pointer << std::endl;
    }

    stack_allocator(const stack_allocator& other)
        : allocator(other.allocator), begin(other.begin), end(other.end), stack_pointer(other.stack_pointer)
    {

    }

    template<typename U>
    stack_allocator(const stack_allocator<U, N>& other)
        : allocator(other.allocator), begin(other.begin), end(other.end), stack_pointer(other.stack_pointer)
    {

    }

    pointer allocate(size_type n, const_void_pointer hint = const_void_pointer())
    {
        std::cout << "distance: " << size_type(std::distance(stack_pointer, end)) << std::endl;
        std::cout << "begin: " << std::hex << begin << std::endl;
        std::cout << "end: " << std::hex << end << std::endl;
        std::cout << "stack_pointer: " << std::hex << stack_pointer << std::endl;

        if (n <= size_type(std::distance(stack_pointer, end)))
        {
            pointer result = stack_pointer;
            stack_pointer += n;
            return result;
        }

        return allocator.allocate(n, hint);
    }

    void deallocate(pointer p, size_type n)
    {
        if (owns(p))
        {
            stack_pointer -= n;
        }
    }

    bool owns(const_pointer p)
    {
        return (!(std::less<const_pointer>()(p, begin)) && (std::less<const_pointer>()(p, end)));
    }

    pointer buffer() const noexcept
    {
        return begin;
    }

    template <class U>
    struct rebind
    {
        using other = stack_allocator<U, N>;
    };

private:
    pointer begin;
    pointer end;
    pointer stack_pointer;
    Alloc allocator;
};

template <typename T1, std::size_t N, typename T2>
bool operator == (const stack_allocator<T1, N>& lhs, const stack_allocator<T2, N>& rhs) noexcept
{
    return lhs.buffer() == rhs.buffer();
}

template <typename T1, std::size_t N, typename T2>
bool operator != (const stack_allocator<T1, N>& lhs,  const stack_allocator<T2, N>& rhs) noexcept
{
    return !(lhs == rhs);
}

