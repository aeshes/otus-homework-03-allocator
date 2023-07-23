#pragma once

#include <cstddef>
#include <cassert>
#include <cstdio>

template<size_t N, size_t alignment = alignof(max_align_t)>
class arena
{
    alignas(alignment) char buffer[N];
    char *ptr;

public:
    arena() noexcept : ptr(buffer)
    {

    }

    arena(const arena &) = delete;
    arena& operator=(const arena &) = delete;

    template<size_t ReqAlign>
    char *allocate(size_t n);

    void deallocate(char *p, size_t n) noexcept;

    static constexpr size_t size()
    {
        return N;
    }

    size_t used() const noexcept
    {
        return static_cast<size_t>(ptr - buffer);
    }

    void reset() noexcept
    {
        ptr = buffer;
    }

    ~arena()
    {
        ptr = nullptr;
    }

private:
    static size_t align_up(size_t n) noexcept
    {
        return (n + (alignment - 1)) & ~(alignment - 1);
    }

    bool owns(char *p) noexcept
    {
        return (p >= buffer) && (p <= buffer + N);
    }
};

template<size_t N, size_t alignment>
template<size_t ReqAlign>
char *arena<N, alignment>::allocate(size_t n)
{
    //static_assert(ReqAlign <= alignment, "alignment is too small for this arena");
    assert(owns(ptr) && "short_allocator has outlived arena");

    auto const aligned_n = align_up(n);
    if (static_cast<decltype(aligned_n)>(buffer + N - ptr) >= aligned_n)
    {
        char *r = ptr;
        ptr += aligned_n;
        return r;
    }

    static_assert(alignment <= alignof(max_align_t),
                  "you've chosen an "
                  "alignment that is larger than alignof(max_align_t), and "
                  "cannot be guaranteed by normal operator new");

    return static_cast<char *>(::operator new(n));
}

template<size_t N, size_t alignment>
void arena<N, alignment>::deallocate(char *p, size_t n) noexcept
{
    assert(owns(ptr) && "short_allocator has outlived arena");

    if (!owns(p))
        ::operator delete(p);

    n = align_up(n);

    if (p + n == ptr)
        ptr = p;
}

template<class T, size_t N, size_t Align = alignof(max_align_t)>
class short_allocator
{
public:
    using value_type = T;
    static auto constexpr alignment = Align;
    static auto constexpr size = N;
    using arena_type = arena<size, alignment>;

private:
    arena_type &a;

public:
    short_allocator(const short_allocator &) = default;
    short_allocator &operator=(const short_allocator &) = delete;

    short_allocator(arena_type &a) noexcept : a(a)
    {
        static_assert(size % alignment == 0, "size N needs to be a multiple of alignment Align");
    }

    const arena_type &get_arena() const
    {
        return a;
    }

    arena_type &get_arena()
    {
        return a;
    }

    template<class U>
    short_allocator(short_allocator<U, N, alignment> &a) noexcept : a(a.get_arena())
    {

    }

    template<class U>
    struct rebind
    {
        using other = short_allocator<U, N, alignment>;
    };

    T *allocate(size_t n)
    {
        char *result = a.template allocate<alignof(T)>(n * sizeof(T));
        return reinterpret_cast<T *>(result);
    }

    void deallocate(T *p, size_t n) noexcept
    {
        a.deallocate(reinterpret_cast<char *>(p), n * sizeof(T));
    }

    template <class U, size_t M, size_t A2>
    bool equals(const short_allocator<U, M, A2> &rhs) const noexcept
    {
        return N == M && Align == A2 && &a == &rhs.get_arena();
    }
};

template <class T, size_t N, size_t A1, class U, size_t M, size_t A2>
bool operator==(const short_allocator<T, N, A1> &x,const short_allocator<U, M, A2> &y) noexcept
{
    return x.equals(y);
}

template <class T, size_t N, size_t A1, class U, size_t M, size_t A2>
bool operator!=(const short_allocator<T, N, A1> &x, const short_allocator<U, M, A2> &y) noexcept {
    return !(x == y);
}
