template<typename T>
struct allocator
{
	using value_type = T;

	allocator() noexcept = default;

	template<typename U>
	allocator(const allocator<U> &) noexcept
	{

	}

	T* allocate(std::size_t size)
	{
		return static_cast<T*>(::operator new(size * sizeof(T)));
	}

	void deallocate(T* p, std::size_t size)
	{
		::operator delete(p);
	}
};

template<typename T, typename U>
constexpr bool operator==(const allocator<T>& a, const allocator<U>& b) noexcept
{
	return true;
}

template<typename T, typename U>
constexpr bool operator!=(const allocator<T>& a, const allocator<U>& b) noexcept
{
	return false;
}
