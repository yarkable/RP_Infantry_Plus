//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA3_RECURSIVE_MUTEX_H__
#define __INFRA3_RECURSIVE_MUTEX_H__

#include "Defs.h"


namespace Dahua {
namespace Infra {

struct RecursiveMutexInternal;

/// \class CRecursiveMutex 递归锁
class INFRA_API CRecursiveMutex
{
	CRecursiveMutex(CRecursiveMutex const&);
	CRecursiveMutex& operator=(CRecursiveMutex const&);

public:
	/// 构造函数，会创建系统互斥量
	CRecursiveMutex();

	/// 析构函数，会销毁系统互斥量
	~CRecursiveMutex();

	/// 进入临界区。
	/// \return 操作是否成功
	bool enter();

	/// 离开临界区。
	/// \return 操作是否成功
	bool leave();

private:
	RecursiveMutexInternal *m_internal;
};

} // namespace Infra
} // namespace Dahua

#endif //__INFRA_RECURSIVE_MUTEX_H__

//
// End of "$Id$"
//
