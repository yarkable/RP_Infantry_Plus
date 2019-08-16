
#ifndef __DAHUA_MEMORY_ENABLESHAREDFROMTHIS_H__
#define __DAHUA_MEMORY_ENABLESHAREDFROMTHIS_H__

#include "Memory/SharedPtr.h"
#include "Memory/WeakPtr.h"

namespace Dahua {
namespace Memory {

template<class T> class TEnableSharedFromThis
{
protected:
	
	TEnableSharedFromThis() 
	{
	}

	TEnableSharedFromThis(TEnableSharedFromThis const &)
	{
	}

	TEnableSharedFromThis & operator=(TEnableSharedFromThis const &)
	{
		return *this;
	}

	~TEnableSharedFromThis()
	{
	}

public:

	TSharedPtr<T> shared_from_this()
	{
		TSharedPtr<T> p( weak_this_ );
		assert( p.get() == this );
		return p;
	}

	TSharedPtr<T const> shared_from_this() const
	{
		TSharedPtr<T const> p( weak_this_ );
		assert( p.get() == this );
		return p;
	}

public: // actually private, but avoids compiler template friendship issues

	template<class X, class Y> void _internal_accept_owner( TSharedPtr<X> const * ppx, Y * py ) const
	{
		if( weak_this_.expired() )
		{
			weak_this_ = TSharedPtr<T>( *ppx, py );
		}
	}

private:

	mutable TWeakPtr<T> weak_this_;
};

} // namespace Memory
}// namesapce Dahua

#endif // end of __DAHUA_MEMORY_ENABLESHAREDFROMTHIS_H__

