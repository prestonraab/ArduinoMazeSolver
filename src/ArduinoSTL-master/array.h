#ifndef __ARRAY__
#define __ARRAY__

#include "cstddef.h"
#include "initializer_list.h"

namespace std {

template <typename T, size_t N>
class array {
public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef pointer iterator;
	typedef const_pointer const_iterator;
	typedef size_t size_type;

private:
	value_type _data[N ? N : 1];

public:
	array() = default;
	array(std::initializer_list<T> init) {
		if (init.size() != N) {
			// error
		}
		size_t i = 0;
		for(const auto& item : init) {
			_data[i++] = item;
		}
	}
	array& operator=(const array& other) = default;

	reference operator[](size_type i) { return _data[i]; }
	const_reference operator[](size_type i) const { return _data[i]; }
	reference front() { return _data[0]; }
	const_reference front() const { return _data[0]; }
	reference back() { return _data[N - 1]; }
	const_reference back() const { return _data[N - 1]; }
	pointer data() noexcept { return _data; }
	const_pointer data() const noexcept { return _data; }
	reference at(size_type pos) { return _data[pos]; }
	const_reference at(size_type pos) const { return _data[pos]; }

	iterator begin() noexcept { return _data; }
	const_iterator begin() const noexcept { return _data; }
	const_iterator cbegin() const noexcept { return _data; }
	iterator end() noexcept { return _data + N; }
	const_iterator end() const noexcept { return _data + N; }
	const_iterator cend() const noexcept { return _data + N; }

	bool empty() const noexcept { return begin() == end(); }
	size_type size() const noexcept { return N; }
	size_type max_size() const noexcept { return N; }

	void fill(const_reference value) {
		for (auto i = 0u; i < N; ++i) {
			_data[i] = value;
		}
	}
};

}

#endif
