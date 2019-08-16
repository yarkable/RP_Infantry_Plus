#ifndef DAHUA_DETAIL_ATOMIC_COUNT_WIN32_HPP_INCLUDED
#define DAHUA_DETAIL_ATOMIC_COUNT_WIN32_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  boost/detail/atomic_count_win32.hpp
//
//  Copyright (c) 2001-2005 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#if defined(_MSC_VER) && (_MSC_VER >= 1300) && (_MSC_VER < 1800)
	extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement( long volatile * );
	extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement( long volatile * );
#else
#define WIN32_LEAN_AND_MEAN
#	include <windows.h>
#endif

namespace Dahua {
namespace Infra {
namespace Detail {


class atomic_count
{
public:

    explicit atomic_count( long v ): value_( v )
    {
    }

    long operator++()
    {
        return InterlockedIncrement( &value_ );
    }

    long operator--()
    {
        return InterlockedDecrement( &value_ );
    }

    operator long() const
    {
        return static_cast<long const volatile &>( value_ );
    }

	long get() const
	{
		return static_cast<long const volatile &>(value_);
	}

	void set(long v)
	{
		value_ = v;
		return;
	}

private:

    atomic_count( atomic_count const & );
    atomic_count & operator=( atomic_count const & );

    long value_;
};

} // namespace Detail
} // namespace Infra
} // namespace Dahua

#endif // #ifndef DAHUA_DETAIL_ATOMIC_COUNT_WIN32_HPP_INCLUDED
