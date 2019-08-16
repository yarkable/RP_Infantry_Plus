////////////////////////////////////////////////////////////////////////////////
// flex_string
// Copyright (c) 2001 by Andrei Alexandrescu
// Permission to use, copy, modify, distribute and sell this software for any
//     purpose is hereby granted without fee, provided that the above copyright
//     notice appear in all copies and that both that copyright notice and this
//     permission notice appear in supporting documentation.
// The author makes no representations about the
//     suitability of this software for any purpose. It is provided "as is"
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

#ifndef DAHUA_FLEX_STRING_INC_
#define DAHUA_FLEX_STRING_INC_

// revision 754


////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && (_MSC_VER < 1300)

#include <utility>

namespace std {

template<>
struct iterator_traits<char*>
{
	typedef random_access_iterator_tag iterator_category;
	typedef char                       value_type;
	typedef ptrdiff_t                  distance_type;
	typedef char*                      pointer;
	typedef char&                      reference;
};

template<>
struct iterator_traits<const char*>
{
	typedef random_access_iterator_tag iterator_category;
	typedef char                       value_type;
	typedef ptrdiff_t                  distance_type;
	typedef const char*                pointer;
	typedef const char&                reference;
};

template<>
struct iterator_traits<wchar_t*>
{
	typedef random_access_iterator_tag iterator_category;
	typedef wchar_t                    value_type;
	typedef ptrdiff_t                  distance_type;
	typedef wchar_t*                   pointer;
	typedef wchar_t&                   reference;
};

template<>
struct iterator_traits<const wchar_t*>
{
	typedef random_access_iterator_tag iterator_category;
	typedef wchar_t                    value_type;
	typedef ptrdiff_t                  distance_type;
	typedef const wchar_t*             pointer;
	typedef const wchar_t&             reference;
};

} // namespace std

#endif

////////////////////////////////////////////////////////////////////////////////


//#define DAHUA_DEBUG_FLEX_STRING


// Ïû³ý GCC strict-aliasing ¾¯¸æ
#if defined(__GNUC__) && (__GNUC__ >= 4)
#pragma GCC system_header
#endif


#if defined(_MSC_VER)
	#pragma warning (push)
	#pragma warning (disable : 4786)
#endif


#if defined(_MSC_VER) && (_MSC_VER < 1300)

#define NO_ITERATOR_TRAITS
#define DAHUA_DEDUCED_TYPENAME

#else

#define DAHUA_DEDUCED_TYPENAME	typename

#endif

////////////////////////////////////////////////////////////////////////////////

// <THE> string
#include "flex_string_shell.h"

// Storage policies
#include "simplestringstorage.h"
#include "ministringstorage.h"
#include "allocatorstringstorage.h"
#include "vectorstringstorage.h"
#include "smallstringopt.h"
//#include "cowstringopt.h"
//#include "utf16encoding.h"



#if defined(_MSC_VER)
	#pragma warning (pop)
#endif


#undef DAHUA_DEDUCED_TYPENAME
#undef DAHUA_DEBUG_FLEX_STRING


#endif // DAHUA_FLEX_STRING_INC_
