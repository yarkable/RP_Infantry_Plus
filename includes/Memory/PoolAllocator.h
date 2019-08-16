//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	参考"The C++ Programming Laguage (Special Edition)", by Bjarne Stroustrup，
//  实现的内存模式内存分配器

//	Revisions:
//  2007-8-9  wang_haifeng  Modification
//

#ifndef __INFRA_POOL_ALLOCATOR_H__
#define __INFRA_POOL_ALLOCATOR_H__

#include <cassert>
#include <new>
#include "Infra/Mutex.h"
#include "Detail/singleton_pool.h"
#include "Detail/MemPool.h"

// 判断STL是否正确实现了 deallocate
#if defined(_RWSTD_VER) || defined(__SGI_STL_PORT) || defined(__BORLANDC__)
 #define DAHUA_NO_PROPER_STL_DEALLOCATE
#endif



namespace Dahua {
namespace Memory {


////////////////////////////////////////////////////////////////////////////////

namespace Pool {

struct DefaultMutex
{
	Infra::CMutex m_mutex;
	void lock() {m_mutex.enter();}
	void unlock() {m_mutex.leave();}
};

struct NullMutex
{
	void lock() {}
	void unlock() {}
};

struct PoolAllocatorTag {};

} // namespace Pool

////////////////////////////////////////////////////////////////////////////////


/// \brief 符合std:: alloctor定义的内存模式内存分配器
///
/// - 只支持list容器, 因为list容器每次只申请或释放一个一种规格的节点. 对于deque,
/// 当元素规格小于4K时, 其默认的申请策略就相当于内存池, 大于等于4K时, 会申请两
/// 种类型的规格, 一种是元素指针, 一次申请的个数采用采用番倍策略, 另一种是元素,
/// 这时才可以考虑内存池.  对vector使用池管理实在没什么意义, 其内存管理策略也
/// 已经考虑了动态增长的情况, 如果非要用内存池实现, 将付出沉重代价.
template <typename T,
	typename PoolType = Detail::CMemPool,	// 指定内存池类型
	typename Mutex = Pool::NullMutex,		// 指定锁类型, Detial::CMemPool 内部已经加锁，这里用 NullMutex
	unsigned nextSize = 64,					// 每次分配的区块数
	unsigned maxSize = 0>
class TPoolAllocator;


/// \brief TPoolAllocator的偏特化版本
template<
	typename PoolType,
	typename Mutex,
	unsigned nextSize,
	unsigned maxSize>
class TPoolAllocator<void, PoolType, Mutex, nextSize, maxSize>
{
public:
	typedef void*       pointer;
	typedef const void* const_pointer;
	typedef void        value_type;
	template <class U> struct rebind {
		typedef TPoolAllocator<U, PoolType, Mutex, nextSize, maxSize> other;
	};
};


/// \brief 符合std:: alloctor定义的内存模式内存分配器
/// 对象内存使用CMemPool管理，由于是静态变量，所以程序生命周期中申请到的系统内存一直不会释放
template <typename T,
	typename PoolType,
	typename Mutex,
	unsigned nextSize,
	unsigned maxSize>
class TPoolAllocator
{
public:
	typedef Mutex mutex_type;
	typedef PoolType pool_type;
	static const unsigned next_size = nextSize;

	typedef T value_type;
	typedef T * pointer;
	typedef const T * const_pointer;
	typedef T & reference;
	typedef const T & const_reference;
	typedef size_t size_type;
	typedef std::ptrdiff_t difference_type;

	template <typename U>
	struct rebind
	{
		typedef TPoolAllocator<U, PoolType, Mutex, nextSize, maxSize> other;
	};

	TPoolAllocator()
	{}

	template <class U>
	TPoolAllocator(TPoolAllocator<U, PoolType, Mutex, nextSize, maxSize> const&)
	{}

	~TPoolAllocator()
	{}

	pointer address(reference x) const
	{ return &x; }

	const_pointer address(const_reference x) const
	{ return x; }

	bool operator==(const TPoolAllocator &) const
	{ return true; }

	bool operator!=(const TPoolAllocator &) const
	{ return false; }

	static pointer allocate(const size_type n)
	{
		typedef Detail::singleton_pool<Pool::PoolAllocatorTag, sizeof(T), PoolType, Mutex, nextSize, maxSize> SingletonPool;
		assert(n == 1);
		const pointer ret = static_cast<pointer>(SingletonPool::malloc());
		if (ret == 0)
		{
			throw std::bad_alloc();
		}
		return ret;
	}

	static pointer allocate(const size_type n, const void * const)
	{ return allocate(n); }

	static void deallocate(const pointer ptr, const size_type n)
	{
		typedef Detail::singleton_pool<Pool::PoolAllocatorTag, sizeof(T), PoolType, Mutex, nextSize, maxSize> SingletonPool;
#ifdef DAHUA_NO_PROPER_STL_DEALLOCATE
		if (ptr == 0 || n == 0) return;
#endif
		assert(n == 1);
		SingletonPool::free(ptr);
	}

	size_type max_size() const
	{
		return static_cast<size_type>(-1) / sizeof(T);
	}

	void construct(pointer ptr, const value_type& x)
	{
		new(ptr) T(x);
	}

	void destroy(pointer ptr)
	{
		ptr->~T();
		(void) ptr; // avoid unused variable warning
	}
};

} // namespace Memory
} // namespace Dahua

#endif // __INFRA_POOL_ALLOCATOR_H__

