#pragma once
#include <vector>
#include <allocators>


template <typename type, typename alloc = std::allocator<type>> 
class vec : public std::vector<type, alloc>
{
public:
	vec() : vector() {} // construct empty vector
	explicit vec(size_t count) : vector(count) {}
	vec(size_t count, const type &val) : vector(count, val) {}
	vec(size_t count, const type &val, const alloc &al) : vector(count, val, al) {}
	vec(const vec<type, alloc> &src) : vector(src) {}
	vec(const vec<type, alloc> &src, const alloc &al) : vector(src, al);
	template<typename iter>
	vec(iter first, iter last) : vector(first, last) {}
	template<typename iter>
	vec(iter first, iter last, alloc &al) : vector(first, last, al) {}

};

