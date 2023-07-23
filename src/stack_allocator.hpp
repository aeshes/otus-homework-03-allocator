#include <memory>

template<typename T, size_t N, typename Alloc = std::allocator<T>>
class stack_allocator
{
public:
    using value_type = typename std::allocator_traits<Alloc>::value_type;
    using pointer = typename std::allocator_traits<Alloc>::pointer;
    using const_pointer = typename std::allocator_traits<Alloc>::const_pointer;
    using const_void_pointer = typename std::allocator_traits<Alloc>::const_void_pointer;
    using allocator_type = Alloc;
    using size_type = size_t;

    explicit stack_allocator(const allocator_type& alloc = allocator_type())
        : alloc(alloc), begin(nullptr), end(nullptr), stack_pointer(nullptr)
    {

    }

    explicit stack_allocator(pointer buffer, const allocator_type& alloc = allocator_type())
        : alloc(alloc), begin(buffer), end(buffer + N), stack_pointer(buffer)
    {

    }

    template<typename U>
    stack_allocator(const stack_allocator<U, N, Alloc>& other)
        : alloc(other.alloc), begin(other.begin), end(other.end), stack_pointer(other.stack_pointer)
    {

    }

    pointer allocate(size_type n, const_void_pointer hint = const_void_pointer())
    {
        if (n <= size_type(std::distance(stack_pointer, end)))
        {
            pointer result = stack_pointer;
            stack_pointer += n;
            return result;
        }

        return alloc.allocate(n, hint);
    }

    void deallocate(pointer p, size_type n)
    {
        if (owns(p))
        {
            stack_pointer -= n;
        }
        else alloc.deallocate(p, n);
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
        using other = stack_allocator<U, N, allocator_type>;
    };

private:
    allocator_type alloc;
    pointer begin;
    pointer end;
    pointer stack_pointer;
};

template <typename T1, std::size_t N, typename Allocator, typename T2>
bool operator == (const stack_allocator<T1, N, Allocator>& lhs, const stack_allocator<T2, N, Allocator>& rhs) noexcept
{
    return lhs.buffer() == rhs.buffer();
}

template <typename T1, std::size_t N, typename Allocator, typename T2>
bool operator != (const stack_allocator<T1, N, Allocator>& lhs,  const stack_allocator<T2, N, Allocator>& rhs) noexcept
{
    return !(lhs == rhs);
}
