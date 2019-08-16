#ifndef __MEMORY_DETAIL_SP_COUNTED_BASE_W32_HPP__
#define __MEMORY_DETAIL_SP_COUNTED_BASE_W32_HPP__

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <typeinfo>         // std::type_info in get_deleter

namespace Dahua {
namespace Memory {
namespace Detail {

class sp_counted_base
{
private:
	
    sp_counted_base( sp_counted_base const & );
    sp_counted_base & operator= ( sp_counted_base const & );

    long use_count_;        // #shared
    long weak_count_;       // #weak + (#shared != 0)

public:

    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }

    virtual ~sp_counted_base() // nothrow
    {
    }

    // dispose() is called when use_count_ drops to zero, to release
    // the resources managed by *this.

    virtual void dispose() = 0; // nothrow

    // destroy() is called when weak_count_ drops to zero.

    virtual void destroy() // nothrow
    {
        delete this;
    }
	
	virtual void* get_untyped_deleter() = 0;
	virtual void* get_deleter( std::type_info const& ti) = 0;

    void add_ref_copy()
    {
        InterlockedIncrement( &use_count_ );
    }


#if defined(_MSC_VER) && (_MSC_VER >= 1300)
	typedef long InterLockedType;
#else
	typedef PVOID InterLockedType;
#endif


    bool add_ref_lock() // true on success
    {
        for( ;; )
        {
            long tmp = static_cast< long const volatile& >( use_count_ );
            if( tmp == 0 ) return false;

            if( InterlockedCompareExchange( (InterLockedType*)(&use_count_), (InterLockedType)(tmp + 1),
				(InterLockedType)(tmp) ) == InterLockedType(tmp) ) 
				return true;

        }
    }

    void release() // nothrow
    {
        if( InterlockedDecrement( &use_count_ ) == 0 )
        {
            dispose();
            weak_release();
        }
    }

    void weak_add_ref() // nothrow
    {
        InterlockedIncrement( &weak_count_ );
    }

    void weak_release() // nothrow
    {
        if( InterlockedDecrement( &weak_count_ ) == 0 )
        {
            destroy();
        }
    }

    long use_count() const // nothrow
    {
        return static_cast<long const volatile &>( use_count_ );
    }
};

} // namespace Detail
} // namespace Memory
} // namespace Dahua

#endif  // #ifndef __MEMORY_DETAIL_SP_COUNTED_BASE_W32_HPP__
