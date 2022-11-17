/*	Copyright (C) 2006 Garrett A. Kajmowicz

	This file is part of the uClibc++ Library.
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation version 2.1

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <wchar.h>
#include "basic_definitions.h"

#ifndef __HEADER_CWCHAR
#define __HEADER_CWCHAR 1


namespace std{
	using ::mbstate_t;
	using ::wint_t;

	using ::btowc;
	using ::fgetwc;
	using ::fgetws;
	using ::fputwc;
	using ::fputws;
	using ::fwide;
	using ::fwprintf;
	using ::fwscanf;
	using ::getwc;
	using ::getwchar;
	using ::mbrlen;
	using ::mbrtowc;
	using ::mbsinit;
	using ::mbsrtowcs;
	using ::putwc;
	using ::putwchar;
	using ::swprintf;
	using ::swscanf;
	using ::ungetwc;
	using ::vfwprintf;
	using ::vswprintf;
	using ::vwprintf;
	using ::wcrtomb;
	using ::wcscat;
	using ::wcschr;
	using ::wcscmp;
	using ::wcscoll;
	using ::wcscpy;
	using ::wcscspn;
	using ::wcsftime;
	using ::wcslen;
	using ::wcsncat;
	using ::wcsncmp;
	using ::wcsncpy;
	using ::wcspbrk;
	using ::wcsrchr;
	using ::wcsrtombs;
	using ::wcsspn;
	using ::wcsstr;
	using ::wcstod;
	using ::wcstok;
	using ::wcstol;
	using ::wcstoul;
	using ::wcsxfrm;
	using ::wctob;
	using ::wmemchr;
	using ::wmemcmp;
	using ::wmemcpy;
	using ::wmemmove;
	using ::wmemset;
	using ::wprintf;
	using ::wscanf;
}



#endif

