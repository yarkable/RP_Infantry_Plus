//
//  "$Id$"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//


#ifndef DAHUA_MEMORY_DETAIL_POOL_H__
#define DAHUA_MEMORY_DETAIL_POOL_H__


// std::less, std::less_equal, std::greater
#include <functional>
// std::size_t, std::ptrdiff_t
#include <cstddef>
// std::max
#include <algorithm>

#include "singleton.h"


#ifndef DAHUA_PREVENT_MACRO_SUBSTITUTION
#define DAHUA_PREVENT_MACRO_SUBSTITUTION
#endif


namespace Dahua {
namespace Memory {
namespace Detail {

////////////////////////////////////////////////////////////////////////////////

/// 线程安全的单件内存池
template <typename Tag, unsigned requestedSize,
	typename Pool,
	typename Mutex,
	unsigned nextSize,
	unsigned maxSize>
struct singleton_pool
{
public:
	typedef Tag tag;
	typedef Pool pool_type;
	typedef Mutex mutex_type;
	typedef size_t size_type;
	typedef std::ptrdiff_t difference_type;

	static const unsigned requested_size = requestedSize;
	static const unsigned next_size = nextSize;

private:
	struct mem_pool : Mutex
	{
		pool_type p;
		mem_pool() : p(requestedSize, nextSize) {}
	};

	struct guard
	{
		Mutex& m;
		guard(Mutex& mutex) : m(mutex) {m.lock();}
		~guard() {m.unlock();}
	};

	typedef singleton_default<mem_pool> singleton;

	singleton_pool();

public:
	static void * malloc DAHUA_PREVENT_MACRO_SUBSTITUTION()
	{
		mem_pool & p = singleton::instance();
		guard g(p);
		return (p.p.malloc)();
	}
	static void free DAHUA_PREVENT_MACRO_SUBSTITUTION(void * const ptr)
	{
		mem_pool & p = singleton::instance();
		guard g(p);
		(p.p.free)(ptr);
	}
};


} // namespace Detail
} // namespace Memory
} // namespace Dahua

#endif // DAHUA_MEMORY_DETAIL_POOL_H__
