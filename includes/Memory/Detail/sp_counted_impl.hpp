//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef INFRA_SHARED_COUNT_IMPL_H__
#define INFRA_SHARED_COUNT_IMPL_H__

#include "sp_counted_base/sp_counted_base.h"
#include "checked_delete.hpp"

namespace Dahua {
namespace Memory {
namespace Detail {

template<class X> class sp_counted_impl_p : public sp_counted_base
{
	X* m_ptr; // copy constructor must not throw

public:
	sp_counted_impl_p(X* ptr) : m_ptr(ptr)
	{
	}

	virtual void dispose() // nothrow
	{
		checked_delete(m_ptr);
	}

	virtual void* get_deleter(std::type_info const&)
	{
		return 0;
	}

	virtual void * get_untyped_deleter()
	{
		return 0;
	}
};

template<class P, class D> class sp_counted_impl_pd : public sp_counted_base
{
	P m_ptr; // copy constructor must not throw
	D m_del; // copy constructor must not throw

public:
	// pre: del(p) must not throw
	sp_counted_impl_pd(P ptr, D del) : m_ptr(ptr), m_del(del)
	{
	}

	virtual void dispose() // nothrow
	{
		m_del(m_ptr);
	}

	virtual void* get_deleter(std::type_info const& ti)
	{
		return ti == typeid(D) ? &reinterpret_cast<char&>(m_del) : 0;
	}
	
	virtual void * get_untyped_deleter()
	{
		return &reinterpret_cast<char&>(m_del);
	}
};

template<class P, class D, class A> class sp_counted_impl_pda: public sp_counted_base
{
private:

	P p_; // copy constructor must not throw
	D d_; // copy constructor must not throw
	A a_; // copy constructor must not throw

	sp_counted_impl_pda( sp_counted_impl_pda const & );
	sp_counted_impl_pda & operator= ( sp_counted_impl_pda const & );

	typedef sp_counted_impl_pda<P, D, A> this_type;

public:

	// pre: d( p ) must not throw

	sp_counted_impl_pda( P p, D d, A a ): p_( p ), d_( d ), a_( a )
	{
	}

	virtual void dispose() // nothrow
	{
		d_( p_ );
	}

	virtual void destroy() // nothrow
	{
		typedef typename A::template rebind< this_type >::other A2;

		A2 a2( a_ );

		this->~this_type();
		a2.deallocate( this, 1 );
	}

	virtual void * get_deleter( std::type_info const & ti )
	{
		return ti == typeid( D )? &reinterpret_cast<char&>( d_ ): 0;
	}

	virtual void * get_untyped_deleter()
	{
		return &reinterpret_cast<char&>(d_);
	}
};

} // namespace Detail
} // namespace Memory
} // namespace Dahua

#endif // INFRA_SHARED_COUNT_IMPL_H__
