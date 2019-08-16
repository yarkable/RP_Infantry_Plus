//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef INFRA_SHARED_COUNT_BASE_H__
#define INFRA_SHARED_COUNT_BASE_H__


#include "Infra/AtomicCount.h"


namespace Dahua {
namespace Memory {
namespace Detail {

typedef Infra::CAtomicCount sp_atomic_count;

class sp_counted_base
{
	sp_atomic_count m_use_count;

	sp_counted_base(sp_counted_base const&);
	sp_counted_base& operator=(sp_counted_base const&);

public:
	sp_counted_base() : m_use_count(1) {}

	virtual ~sp_counted_base() {} // nothrow

	// dispose() is called when use_count_ drops to zero, to release
	// the resources managed by *this.
	virtual void dispose() = 0; // nothrow

	// destroy() is called when weak_count_ drops to zero.
	virtual void destroy()	// nothrow
	{
		delete this;
	}

	virtual void* get_deleter(std::type_info const&) = 0;

	void add_ref()
	{
		++m_use_count;
	}

	void release() // nothrow
	{
		if (--m_use_count == 0)
		{
			dispose();
			destroy();
		}
	}

	long use_count() const // nothrow
	{
		return m_use_count;
	}
};

} // namespace Detail
} // namespace Memory
} // namespace Dahua

#endif // INFRA_SHARED_COUNT_BASE_H__
