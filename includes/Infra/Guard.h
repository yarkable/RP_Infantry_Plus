//
//  "$Id: Guard.h 55347 2012-03-22 11:26:45Z qin_fenglin $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA3_GUARD_H__
#define __INFRA3_GUARD_H__

#include "Mutex.h"
#include "RecursiveMutex.h"
#include "ReadWriteMutex.h"

namespace Dahua{
namespace Infra{


/// \class CGuard
/// \brief 守护者类。
///
/// 构造时自动调用CMutex::Enter，析构时自动调用CMutex::Leave，避免不
/// 配对的情况发生。示例如下：
/// \code
/// CMutex mutex;
/// int needProtect = 0;
/// void testAdd()
/// {
/// there:
/// 	if(needProtect % 2) // not protected
/// 	{
/// 		needProtect++;
/// 	}
/// 	else
/// 	{
/// 		return;
/// 	}
///
/// 	CGuard guard(mutex);
/// 	needProtect++;
/// 	goto there;	// will also bring ~CGuard(), thus mutex.leave()
/// }
/// void testSub()
/// {
///     needProtect--; // not protected
///
/// 	CGuard guard(mutex);
/// 	needProtect--;
/// }
/// \endcode

class CGuard
{
	CGuard(CGuard const&);
	CGuard& operator=(CGuard const&);

public:
	/// 构造函数，自动调用CMutex::enter
	/// \param mutex 互斥量引用，CGuard并不创建互斥量。
	inline CGuard(CMutex& mutex)
		:m_mutex(mutex)
	{
		m_mutex.enter();
	};

	/// 析构函数，自动调用CMutex::leave
	inline ~CGuard()
	{
		m_mutex.leave();
	};

private:
	CMutex &m_mutex;	///< 需要自动调用的互斥量引用
};

////////////////////////////////////////////////////////////////////////////////

class CRecursiveGuard
{
	CRecursiveGuard(CRecursiveGuard const&);
	CRecursiveGuard& operator=(CRecursiveGuard const&);

public:
	/// 构造函数，自动调用CMutex::enter
	/// \param mutex 互斥量引用，CGuard并不创建互斥量。
	inline CRecursiveGuard(CRecursiveMutex& mutex)
		:m_mutex(mutex)
	{
		m_mutex.enter();
	};

	/// 析构函数，自动调用CMutex::leave
	inline ~CRecursiveGuard()
	{
		m_mutex.leave();
	};

private:
	CRecursiveMutex &m_mutex;	///< 需要自动调用的互斥量引用
};

////////////////////////////////////////////////////////////////////////////////

/// 读写锁的读操作保护
class CGuardReading
{
	CGuardReading(CGuardReading const&);
	CGuardReading& operator=(CGuardReading const&);

public:
	/// 构造函数，自动调用 CRwMutex::EnterReading
	/// \param mutex 互斥量引用，CGuard并不创建互斥量。
	inline CGuardReading(CReadWriteMutex& mutex)
		: m_mutex(mutex)
	{
		m_mutex.enterReading();
	};

	/// 析构函数，自动调用 CReadWriteMutex::leave
	inline ~CGuardReading()
	{
		m_mutex.leave();
	};

private:
	CReadWriteMutex& m_mutex;	///< 需要自动调用的互斥量引用
};

////////////////////////////////////////////////////////////////////////////////

///  读写锁的写操作保护
class CGuardWriting
{
	CGuardWriting(CGuardWriting const&);
	CGuardWriting& operator=(CGuardWriting const&);

public:
	/// 构造函数，自动调用 CReadWriteMutex::EnterWriting
	/// \param mutex 互斥量引用，CGuard并不创建互斥量。
	inline CGuardWriting(CReadWriteMutex& mutex)
		: m_mutex(mutex)
	{
		m_mutex.enterWriting();
	};

	/// 析构函数，自动调用 CReadWriteMutex::leave
	inline ~CGuardWriting()
	{
		m_mutex.leave();
	};

private:
	CReadWriteMutex& m_mutex;	///< 需要自动调用的互斥量引用
};

} // namespace Infra
} // namespace Dahua

#endif //__INFRA_GUARD_H__
