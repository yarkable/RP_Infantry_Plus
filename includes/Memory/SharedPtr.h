//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef INFRA_SHARED_PTR_H__
#define INFRA_SHARED_PTR_H__

#include "Detail/smartptr_detail.h"
#include "Detail/shared_count.h"

#if defined(_MSC_VER) && (_MSC_VER < 1300)
#define DAHUA_NO_CV_VOID_SPECIALIZATIONS
#define DAHUA_NO_SFINAE
#define DAHUA_NO_MEMBER_TEMPLATE_FRIENDS
#endif

namespace Dahua {
namespace Memory {

////////////////////////////////////////////////////////////////////////////////

namespace Detail {

template<class T> struct shared_ptr_traits
{
	typedef T & reference;
};

template<> struct shared_ptr_traits<void>
{
	typedef void reference;
};

#ifndef DAHUA_NO_CV_VOID_SPECIALIZATIONS

template<> struct shared_ptr_traits<void const>
{
	typedef void reference;
};

template<> struct shared_ptr_traits<void volatile>
{
	typedef void reference;
};

template<> struct shared_ptr_traits<void const volatile>
{
	typedef void reference;
};

#endif

// rvalue auto_ptr support based on a technique by Dave Abrahams

#ifndef DAHUA_NO_SFINAE

template< class T, class R > struct sp_enable_if_auto_ptr
{
};

template< class T, class R > struct sp_enable_if_auto_ptr< std::auto_ptr< T >, R >
{
	typedef R type;
};

#endif

template< class Y, class T > struct sp_convertible
{
    typedef char (&yes) [1];
    typedef char (&no)  [2];

    static yes f( T* );
    static no  f( ... );

    enum _vt { value = sizeof( (f)( static_cast<Y*>(0) ) ) == sizeof(yes) };
};

template< class Y, class T > inline void sp_assert_convertible()
{
    typedef char tmp[ sp_convertible< Y, T >::value? 1: -1 ];
    (void)sizeof( tmp );
}

} // namespace Detail

////////////////////////////////////////////////////////////////////////////////

template < class T > class TWeakPtr;
template < class T > class TSharedPtr;
template < class T > class TEnableSharedFromThis;

template< class X, class Y, class T > inline void sp_enable_shared_from_this( TSharedPtr<X> const * ppx, Y const * py, TEnableSharedFromThis< T > const * pe )
{
	if( pe != 0 )
	{
		pe->_internal_accept_owner( ppx, const_cast< Y* >( py ) );
	}
}

inline void sp_enable_shared_from_this( ... )
{
}

template< class T, class Y > inline void sp_pointer_construct( TSharedPtr< T > * ppx, Y * p, Detail::shared_count & pn )
{
	Detail::shared_count( p ).swap( pn );
	sp_enable_shared_from_this( ppx, p, p );
}

template<class T> class TSharedPtr	// noncopyable
{
#ifdef DAHUA_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
	template<class Y> friend class TSharedPtr;
	template<class Y> friend class TWeakPtr;
#endif

	T* px;                                  // contained pointer
	Detail::shared_count pn;	// reference counter

public:

	typedef TSharedPtr<T> this_type;
	typedef T element_type;
	typedef T value_type;
	typedef T * pointer;
	typedef typename Detail::shared_ptr_traits<T>::reference reference;

	TSharedPtr(): px(0), pn() // never throws in 1.30+
	{
	}

	template<class Y> explicit TSharedPtr( Y * p ): px( p ), pn( ) // Y must be complete
	{
		sp_pointer_construct( this, p, pn );
	}

	//
	// Requirements: D's copy constructor must not throw
	//
	// TSharedPtr will release p by calling d(p)
	//
	template<class Y, class D> TSharedPtr(Y * p, D d): px(p), pn(p, d)
	{
	}

	// As above, but with allocator. A's copy constructor shall not throw.
	template<class Y, class D, class A> TSharedPtr( Y * p, D d, A a ): px( p ), pn( p, d, a )
	{
	}

//  generated copy constructor, assignment, destructor are fine...

//  except that Borland C++ has a bug, and g++ with -Wsynth warns
#if defined(__BORLANDC__) || defined(__GNUC__)

	TSharedPtr & operator=(TSharedPtr const & r) // never throws
	{
		px = r.px;
		pn = r.pn; // shared_count::op= doesn't throw
		return *this;
	}

#endif

	template<class Y>
	TSharedPtr(TSharedPtr<Y> const & r): px(r.px), pn(r.pn) // never throws
	{
	}

	// aliasing
	template< class Y >
	TSharedPtr( TSharedPtr<Y> const & r, T * p ): px( p ), pn( r.pn ) // never throws
	{
	}

	template<class Y>
	TSharedPtr(TSharedPtr<Y> const & r, Detail::static_cast_tag): px(static_cast<element_type *>(r.px)), pn(r.pn)
	{
	}

	template<class Y>
	TSharedPtr(TSharedPtr<Y> const & r, Detail::const_cast_tag): px(const_cast<element_type *>(r.px)), pn(r.pn)
	{
	}

	template<class Y>
	TSharedPtr(TSharedPtr<Y> const & r, Detail::dynamic_cast_tag): px(dynamic_cast<element_type *>(r.px)), pn(r.pn)
	{
		if(px == 0) // need to allocate new counter -- the cast failed
		{
			pn = Detail::shared_count();
		}
	}

	template<class Y>
	TSharedPtr(TSharedPtr<Y> const & r, Detail::polymorphic_cast_tag): px(dynamic_cast<element_type *>(r.px)), pn(r.pn)
	{
		if(px == 0)
		{
			throw std::bad_cast();
		}
	}

	template<class Y>
	explicit TSharedPtr(std::auto_ptr<Y> & r): px(r.get()), pn()
	{
		Y * tmp = r.get();
		pn = Detail::shared_count(r);
	}

#ifndef DAHUA_NO_SFINAE
	template<class Ap>
	TSharedPtr( Ap r, typename Detail::sp_enable_if_auto_ptr<Ap, int>::type = 0 ): px( r.get() ), pn()
	{
		typename Ap::element_type * tmp = r.get();
		pn = Detail::shared_count( r );
	}
#endif

	template<class Y>
	explicit TSharedPtr(TWeakPtr<Y> const & r): pn( r.m_pn ) // may throw
	{
		Detail::sp_assert_convertible< Y, T >();
		
		px = r.m_ptr;
	}
	
	template<class Y>
	explicit TSharedPtr( TWeakPtr<Y> const & r, Detail::sp_nothrow_tag ): px( 0 ), pn( r.m_pn ) // may throw
	{
		if ( !pn.empty() )
		{
			px = r.m_ptr;
		}
	}
	
	template<class Y>
	TSharedPtr & operator=(TSharedPtr<Y> const & r) // never throws
	{
		px = r.px;
		pn = r.pn; // shared_count::op= doesn't throw
		return *this;
	}

	template<class Y>
	TSharedPtr & operator=( std::auto_ptr<Y> & r )
	{
		this_type(r).swap(*this);
		return *this;
	}

#ifndef DAHUA_NO_SFINAE
	template<class Ap>
	typename Detail::sp_enable_if_auto_ptr< Ap, TSharedPtr & >::type operator=( Ap r )
	{
		this_type( r ).swap( *this );
		return *this;
	}
#endif

	void reset() // never throws in 1.30+
	{
		this_type().swap(*this);
	}

	template<class Y> void reset(Y * p) // Y must be complete
	{
		assert(p == 0 || p != px); // catch self-reset errors
		this_type(p).swap(*this);
	}

	template<class Y, class D> void reset( Y * p, D d )
	{
		this_type( p, d ).swap( *this );
	}

	template<class Y, class D, class A> void reset( Y * p, D d, A a )
	{
		this_type( p, d, a ).swap( *this );
	}

	template<class Y> void reset( TSharedPtr<Y> const & r, T * p )
	{
		this_type( r, p ).swap( *this );
	}

	reference operator* () const // never throws
	{
		assert(px != 0);
		return *px;
	}

	T * operator-> () const // never throws
	{
		assert(px != 0);
		return px;
	}

	T * get() const // never throws
	{
		return px;
	}

	// implicit conversion to "bool"
	typedef T * this_type::*unspecified_bool_type;

	operator unspecified_bool_type() const // never throws
	{
		return px == 0? 0: &this_type::px;
	}

	// operator! is redundant, but some compilers need it
	bool operator! () const // never throws
	{
		return px == 0;
	}

	bool unique() const // never throws
	{
		return pn.unique();
	}

	long use_count() const // never throws
	{
		return pn.use_count();
	}

	void swap(TSharedPtr<T> & other) // never throws
	{
		std::swap(px, other.px);
		pn.swap(other.pn);
	}

	template<class Y> bool _internal_less(TSharedPtr<Y> const & rhs) const
	{
		return pn < rhs.pn;
	}

	void * _internal_get_deleter(std::type_info const & ti) const
	{
		return pn.get_deleter(ti);
	}
};

} // namespace Memory
} // namespace Dahua

////////////////////////////////////////////////////////////////////////////////

template<class T, class U> inline bool operator==(Dahua::Memory::TSharedPtr<T> const & a, Dahua::Memory::TSharedPtr<U> const & b)
{
	return a.get() == b.get();
}

template<class T, class U> inline bool operator!=(Dahua::Memory::TSharedPtr<T> const & a, Dahua::Memory::TSharedPtr<U> const & b)
{
	return a.get() != b.get();
}

#if __GNUC__ == 2 && __GNUC_MINOR__ <= 96

// Resolve the ambiguity between our op!= and the one in rel_ops

template<class T> inline bool operator!=(Dahua::Memory::TSharedPtr<T> const & a, Dahua::Memory::TSharedPtr<T> const & b)
{
	return a.get() != b.get();
}

#endif

template<class T, class U> inline bool operator<(Dahua::Memory::TSharedPtr<T> const & a, Dahua::Memory::TSharedPtr<U> const & b)
{
	return a._internal_less(b);
}

template<class T> inline void swap(Dahua::Memory::TSharedPtr<T> & a, Dahua::Memory::TSharedPtr<T> & b)
{
	a.swap(b);
}

template<class T, class U> Dahua::Memory::TSharedPtr<T> static_pointer_cast(Dahua::Memory::TSharedPtr<U> const & r)
{
	return Dahua::Memory::TSharedPtr<T>(r, Dahua::Memory::Detail::static_cast_tag());
}

template<class T, class U> Dahua::Memory::TSharedPtr<T> const_pointer_cast(Dahua::Memory::TSharedPtr<U> const & r)
{
	return Dahua::Memory::TSharedPtr<T>(r, Dahua::Memory::Detail::const_cast_tag());
}

template<class T, class U> Dahua::Memory::TSharedPtr<T> dynamic_pointer_cast(Dahua::Memory::TSharedPtr<U> const & r)
{
	return Dahua::Memory::TSharedPtr<T>(r, Dahua::Memory::Detail::dynamic_cast_tag());
}

// get_pointer(p) is a generic way to say p.get()

template<class T> inline T * get_pointer(Dahua::Memory::TSharedPtr<T> const & p)
{
	return p.get();
}

// get_deleter
template<class D, class T> D * get_deleter(Dahua::Memory::TSharedPtr<T> const & p)
{
	return static_cast<D *>(p._internal_get_deleter(typeid(D)));
}

#endif // INFRA_SHARED_PTR_H__

