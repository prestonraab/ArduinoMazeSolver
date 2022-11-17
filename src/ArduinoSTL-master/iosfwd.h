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
#include "char_traits.h"
#include "memory.h"


#ifndef __HEADER_STD_IOSFWD
#define __HEADER_STD_IOSFWD 1

#pragma GCC visibility push(default)

namespace std {
	class ios_base;
	template<> class char_traits<char>;

#ifdef __UCLIBCXX_HAS_WCHAR__
	template<> class char_traits<wchar_t>;
#endif

	template <class charT, class traits = char_traits<charT> > class basic_ios;

	template <class charT, class traits = char_traits<charT> > class basic_streambuf;
	template <class charT, class traits = char_traits<charT> > class basic_istream;
	template <class charT, class traits = char_traits<charT> > class basic_ostream;
	template <class charT, class traits = char_traits<charT> > class basic_iostream;

	template <class charT, class traits = char_traits<charT>, 
		class Allocator = allocator<charT> > class basic_stringbuf;

	template <class charT, class traits = char_traits<charT>, 
		class Allocator = allocator<charT> > class basic_istringstream;

	template <class charT, class traits = char_traits<charT>,
		class Allocator = allocator<charT> > class basic_ostringstream;

	template <class charT, class traits = char_traits<charT>,
		class Allocator = allocator<charT> > class basic_stringstream;

	template <class charT, class traits = char_traits<charT> > class basic_filebuf;

	template <class charT, class traits = char_traits<charT> > class basic_ifstream;

	template <class charT, class traits = char_traits<charT> > class basic_ofstream;

	template <class charT, class traits = char_traits<charT> > class basic_fstream;

	template <class charT, class traits = char_traits<charT> > class basic_istreambuf_iterator;

	template <class charT, class traits = char_traits<charT> > class basic_ostreambuf_iterator;

	typedef basic_ios<char>       ios;
#ifdef __UCLIBCXX_HAS_WCHAR__
	typedef basic_ios<wchar_t>    wios;
#endif

	typedef basic_streambuf<char> streambuf;
	typedef basic_istream<char>   istream;
	typedef basic_ostream<char>   ostream;
	typedef basic_iostream<char>  iostream;

	typedef basic_stringbuf<char>     stringbuf;
	typedef basic_istringstream<char> istringstream;
	typedef basic_ostringstream<char> ostringstream;
	typedef basic_stringstream<char>  stringstream;

	typedef basic_filebuf<char>  filebuf;
	typedef basic_ifstream<char> ifstream;
	typedef basic_ofstream<char> ofstream;
	typedef basic_fstream<char>  fstream;
#ifdef __UCLIBCXX_HAS_WCHAR__
	typedef basic_streambuf<wchar_t> wstreambuf;
	typedef basic_istream<wchar_t>   wistream;
	typedef basic_ostream<wchar_t>   wostream;
	typedef basic_iostream<wchar_t>  wiostream;

	typedef basic_stringbuf<wchar_t>     wstringbuf;
	typedef basic_istringstream<wchar_t> wistringstream;
	typedef basic_ostringstream<wchar_t> wostringstream;
	typedef basic_stringstream<wchar_t>  wstringstream;

	typedef basic_filebuf<wchar_t>  wfilebuf;
	typedef basic_ifstream<wchar_t> wifstream;
	typedef basic_ofstream<wchar_t> wofstream;
	typedef basic_fstream<wchar_t>  wfstream;
#endif
	
	template <class state> class fpos;
	typedef fpos<char_traits<char>::state_type> streampos;
#ifdef __UCLIBCXX_HAS_WCHAR__
	typedef fpos<char_traits<wchar_t>::state_type> wstreampos;
#endif
}

#pragma GCC visibility pop

#endif
