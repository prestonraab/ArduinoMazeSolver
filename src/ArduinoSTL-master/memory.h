/*	Copyright (C) 2004 Garrett A. Kajmowicz

	This file is part of the uClibc++ Library.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "new.h"
#include "cstddef.h"
#include "cstdlib.h"
#include "iterator_base.h"
#include "utility.h"
#include "cstdio.h"

#ifndef HEADER_STD_MEMORY
#define HEADER_STD_MEMORY 1

#pragma GCC visibility push(default)

namespace std{

template <class T> class allocator;
	// Specialize for void:

template <> class _UCXXEXPORT allocator<void> {
public:
	typedef void*       pointer;
	typedef const void* const_pointer;
	typedef void  value_type;
	template <class U> struct rebind { typedef allocator<U> other; };
};

template <class T> class _UCXXEXPORT allocator{
public:
	typedef T value_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	
	typedef T* pointer;
	typedef const T* const_pointer;

	typedef T& reference;
	typedef const T& const_reference;

	pointer address(reference r) const { return &r; }
	const_pointer address(const_reference r) const { return &r; }
	
	allocator() _UCXX_USE_NOEXCEPT{}
	template <class U> allocator(const allocator<U>& ) _UCXX_USE_NOEXCEPT;
	~allocator() _UCXX_USE_NOEXCEPT{}

	//Space for n Ts
	pointer allocate(size_type n, typename allocator<void>::const_pointer = 0){
		return static_cast<T*>(::operator new( n * sizeof(T) ));
	}
	void deallocate(pointer p, size_type){
		::operator delete(p);
	}

	//Use placement new to engage the constructor
	void construct(pointer p, const T& val) { new(static_cast<void*>(p)) T(val); }
	void destroy(pointer p){ (static_cast<T*>(p))->~T(); }	//Call destructor

	size_type max_size() const _UCXX_USE_NOEXCEPT;
	template<class U> struct rebind { typedef allocator<U> other; };

};

template <class Out, class T> class _UCXXEXPORT raw_storage_iterator
	: public iterator<output_iterator_tag, void, void, void, void>
{
		Out p;

public:
	explicit raw_storage_iterator(Out pp) : p (pp) {  }
	raw_storage_iterator & operator*() { return *this; }
	raw_storage_iterator & operator=(const T& val) {
		T* pp = &*p;
		new(pp) T(val);
		return *this;
	}

	raw_storage_iterator & operator++() { ++p; return *this; }
	raw_storage_iterator operator++(int) {
		raw_storage_iterator t = *this;
		++p;
		return t;
	}
};

template <class T> _UCXXEXPORT pair<T*, ptrdiff_t> get_temporary_buffer(ptrdiff_t n){
	pair<T*, ptrdiff_t> retval;
	retval.first = static_cast<T*>(malloc(n * sizeof(T)));
	if(retval.first == 0){
		retval.second = 0;
	}else{
		retval.second = n;
	}
	return retval;
}

template <class T> _UCXXEXPORT void return_temporary_buffer(T* p){
	free(p);
}


template <class T> class _UCXXEXPORT auto_ptr{

private:
	T * object;
	template <class Y> struct auto_ptr_ref{
		Y * p;
	};

public:

	typedef T element_type;

	explicit auto_ptr(T* p =0) _UCXX_USE_NOEXCEPT : object(p){  }
	auto_ptr(auto_ptr& p) _UCXX_USE_NOEXCEPT : object(p.release()){ }
	auto_ptr(auto_ptr_ref<T> r) _UCXX_USE_NOEXCEPT : object(r.p){
		r.p = 0;
	}
	template<class Y> auto_ptr(auto_ptr<Y>& p) _UCXX_USE_NOEXCEPT : object(p.release()){ }
	auto_ptr& operator=(auto_ptr& p) _UCXX_USE_NOEXCEPT{
		if(&p == this){
			return *this;
		}
		delete object;
		object = p.release();
		return *this;
	}
	template<class Y> auto_ptr& operator=(auto_ptr<Y>& p) _UCXX_USE_NOEXCEPT{
		if(&p == this){
			return *this;
		}
		delete object;
		object = p.release();
		return *this;
	}
	~auto_ptr(){
		delete object;
	}

	T& operator*() const _UCXX_USE_NOEXCEPT{
		return *object;
	}
	T* operator->() const _UCXX_USE_NOEXCEPT{
		return object;
	}
	T* get() const _UCXX_USE_NOEXCEPT{
		return object;
	}
	T* release() _UCXX_USE_NOEXCEPT{
		T * temp(object);
		object = 0;
		return temp;
	}
	void reset(T * p=0) _UCXX_USE_NOEXCEPT{
		if(p != object){
			delete object;
			object = p;
		}
	}
	template<class Y> operator auto_ptr_ref<Y>() _UCXX_USE_NOEXCEPT{
		auto_ptr_ref<Y> retval;
		retval.p = object;
		object = 0;
		return retval;
	}
	template<class Y> operator auto_ptr<Y>() _UCXX_USE_NOEXCEPT{
		auto_ptr<Y> retval(object);
		object = 0;
		return retval;
	}
	
};

}	//namespace std

#pragma GCC visibility pop

#endif

