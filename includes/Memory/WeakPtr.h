
#ifndef __DAHUA_MEMORY_WEAK_PTR_H__
#define __DAHUA_MEMORY_WEAK_PTR_H__

#include "Memory/SharedPtr.h"

namespace Dahua {
namespace Memory {

template < class T >
class TWeakPtr
{
	typedef TWeakPtr<T> this_type;
	typedef  T element_type;
	
#ifdef DAHUA_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
	template<class Y> friend class TWeakPtr;
	template<class Y> friend class TSharedPtr;
#endif

	T*				   m_ptr;
	Detail::weak_count m_pn;
	
public:
	
	TWeakPtr()
		: m_ptr(0), m_pn()
	{
	}
	
	TWeakPtr( TSharedPtr< T > const& rhs )
		: m_ptr( rhs.px)
		, m_pn( rhs.pn)
	{
	}
	
	TWeakPtr& operator=( TWeakPtr< T > const& other )
	{
		m_ptr = other.m_ptr;
		m_pn = other.m_pn;
		return *this;
	}
	
	template<class Y>
	TWeakPtr(TWeakPtr<Y> const & other, Detail::dynamic_cast_tag)
		: m_ptr( dynamic_cast<element_type *>(other.m_ptr) )
		, m_pn( other.m_pn )
	{
		if( m_ptr == 0 ) // need to allocate new counter -- the cast failed
		{
			m_pn = Detail::weak_count();
		}
	}
	
	template<class Y>
	TWeakPtr(TWeakPtr<Y> const & other, Detail::static_cast_tag)
		: m_ptr( static_cast<element_type *>(other.m_ptr) )
		, m_pn( other.m_pn )
	{
	}
	
	bool expired()
	{
		return m_pn.use_count() == 0;
	}

	TSharedPtr<T> lock() const
	{
		return TSharedPtr<T>( *this, Detail::sp_nothrow_tag() );
	}
	
	void reset()
	{
		this_type().swap((*this) );
	}
	
	void swap( TWeakPtr<T>&  other )
	{
		std::swap( m_ptr, other.m_ptr );
		m_pn.swap( other.m_pn );
	}
};

} // namespace Memory
} // namespace Dahua


#endif // end of __DAHUA_MEMORY_WEAK_PTR_H__

