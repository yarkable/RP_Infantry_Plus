#ifndef DAHUA_DETAIL_ATOMIC_COUNT_GCC_HPP_INCLUDED
#define DAHUA_DETAIL_ATOMIC_COUNT_GCC_HPP_INCLUDED

//
//  boost/detail/atomic_count_gcc.hpp
//
//  atomic_count for GNU libstdc++ v3
//
//  http://gcc.gnu.org/onlinedocs/porting/Thread-safety.html
//
//  Copyright (c) 2001, 2002 Peter Dimov and Multi Media Ltd.
//  Copyright (c) 2002 Lars Gullik Bjønnes <larsbj@lyx.org>
//  Copyright 2003-2005 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include <bits/atomicity.h>

namespace Dahua {
namespace Infra {
namespace Detail {


#if defined(__GLIBCXX__) // g++ 3.4+

using __gnu_cxx::__atomic_add;
using __gnu_cxx::__exchange_and_add;

#endif

class atomic_count
{
public:

    explicit atomic_count(long v) : value_(v) {}

    long operator++()
    {
        return __exchange_and_add(&value_, 1) + 1;
    }

    long operator--()
    {
        return __exchange_and_add(&value_, -1) - 1;
    }

    operator long() const
    {
        return __exchange_and_add(&value_, 0);
    }

    long get() const
    {
        return __exchange_and_add(&value_, 0);
    }

    void set(long v)
    {
        long tmp = get();
        __exchange_and_add(&value_, v - tmp);
        return;
    }

private:

    atomic_count(atomic_count const &);
    atomic_count & operator=(atomic_count const &);

    mutable _Atomic_word value_;
};

} // namespace Detail
} // namespace Infra
} // namespace Dahua

#endif // #ifndef DAHUA_DETAIL_ATOMIC_COUNT_GCC_HPP_INCLUDED
