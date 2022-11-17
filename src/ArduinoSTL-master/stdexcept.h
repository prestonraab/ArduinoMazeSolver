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

#include "basic_definitions.h"
#include "exception.h"
#include "string.h"

#ifndef HEADER_STD_EXCEPTIONS
#define HEADER_STD_EXCEPTIONS 1

//Don't include support if not needed
#ifdef __UCLIBCXX_EXCEPTION_SUPPORT__

#pragma GCC visibility push(default)

namespace std{

//typedef basic_string<char> string;

class _UCXXEXPORT logic_error : public exception {
protected:
	string mstring;
public:
	logic_error() _UCXX_USE_NOEXCEPT;
	logic_error(const string& what_arg);

	virtual ~logic_error() _UCXX_USE_NOEXCEPT {}
	virtual const char * what() const _UCXX_USE_NOEXCEPT;

};	

class _UCXXEXPORT domain_error : public logic_error {
public:
	domain_error() : logic_error() {}
	domain_error(const string& what_arg) : logic_error(what_arg) {}
	virtual ~domain_error() _UCXX_USE_NOEXCEPT {}
};

class _UCXXEXPORT invalid_argument : public logic_error {
public:
	invalid_argument() : logic_error(){}
	invalid_argument(const string& what_arg) : logic_error(what_arg){}
	virtual ~invalid_argument() _UCXX_USE_NOEXCEPT {}
};

class _UCXXEXPORT length_error : public logic_error {
public:
	length_error() : logic_error(){}
	length_error(const string& what_arg) : logic_error(what_arg){}
	virtual ~length_error() _UCXX_USE_NOEXCEPT {}
};

class _UCXXEXPORT out_of_range : public logic_error{
public:
	out_of_range();
	out_of_range(const string & what_arg);
	virtual ~out_of_range() _UCXX_USE_NOEXCEPT {}

};

class _UCXXEXPORT runtime_error : public exception{
protected:
	string mstring;
public:
	runtime_error();
	runtime_error(const string& what_arg);

	virtual ~runtime_error() _UCXX_USE_NOEXCEPT {}
	virtual const char * what() const _UCXX_USE_NOEXCEPT;
};

class _UCXXEXPORT range_error : public runtime_error{
public:
	range_error() : runtime_error(){}
	range_error(const string& what_arg) : runtime_error(what_arg) {}
	virtual ~range_error() _UCXX_USE_NOEXCEPT{ }
};


class _UCXXEXPORT overflow_error : public runtime_error{
public:
	overflow_error() : runtime_error(){}
	overflow_error(const string& what_arg) : runtime_error(what_arg) {}
	virtual ~overflow_error() _UCXX_USE_NOEXCEPT{}
};

class _UCXXEXPORT underflow_error : public runtime_error{
public:
	underflow_error() : runtime_error(){}
	underflow_error(const string& what_arg) : runtime_error(what_arg) {}
	virtual ~underflow_error() _UCXX_USE_NOEXCEPT{}
};



}

#pragma GCC visibility pop

#endif
#endif
