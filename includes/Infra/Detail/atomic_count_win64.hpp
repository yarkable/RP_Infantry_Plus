#ifndef DAHUA_DETAIL_ATOMIC_COUNT_WIN64_HPP_INCLUDED
#define DAHUA_DETAIL_ATOMIC_COUNT_WIN64_HPP_INCLUDED

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

//#if defined(_MSC_VER) && (_MSC_VER >= 1300)
//extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement( long volatile * );
//extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement( long volatile * );
//#else
//#	include <windows.h>
//#endif
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Dahua {
	namespace Infra {
		namespace Detail {


			class atomic_count
			{
			public:

				explicit atomic_count( LONG64 v ): value_( v )
				{
				}

				LONG64 operator++()
				{
					return InterlockedIncrement64( &value_ );
				}

				LONG64 operator--()
				{
					return InterlockedDecrement64( &value_ );
				}

				operator LONG64() const
				{
					return static_cast<LONG64 const volatile &>( value_ );
				}

				LONG64 get() const
				{
					return static_cast<LONG64 const volatile &>(value_);
				}

				void set(LONG64 v)
				{
					value_ = v;
					return;
				}

			private:

				atomic_count( atomic_count const & );
				atomic_count & operator=( atomic_count const & );

				LONG64 value_;
			};

		} // namespace Detail
	} // namespace Infra
} // namespace Dahua

#endif // #ifndef DAHUA_DETAIL_ATOMIC_COUNT_WIN64_HPP_INCLUDED
