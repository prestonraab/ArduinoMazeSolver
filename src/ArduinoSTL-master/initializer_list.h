/*	Copyright (C) 2016 Michael Matera

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


#ifndef __STD_HEADER_INITIALIZER_LIST
#define __STD_HEADER_INITIALIZER_LIST

#pragma GCC visibility push(default)

namespace std { 

template<class T> 
class initializer_list {
  
private:
  const T* array; 
  size_t len; 

  // Initialize from a { ... } construct
  initializer_list(const T *a, size_t l): array(a), len(l) { }

public:
  
  // default constructor
  initializer_list() : array(NULL), len(0) {}

  size_t size() const {
    return len;
  }

  const T *begin() {
    return array; 
  }

  const T *end() {
    return array + len;
  }

};

}

#endif
