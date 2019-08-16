//
//  "$Id: Mutex.h 120119 2013-06-04 11:12:32Z sun_xiaohui $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA3_MUTEX_H__
#define __INFRA3_MUTEX_H__

#include "Defs.h"
//lint -save -e1509

namespace Dahua{
namespace Infra{

struct MutexInternal;

/// \class CMutex
class INFRA_API CMutex
{
	CMutex(CMutex const&);
	CMutex& operator=(CMutex const&);

public:
	/// 构造函数，会创建系统互斥量
	CMutex();

	/// 析构函数，会销毁系统互斥量
	~CMutex();

	/// 进入临界区。
	/// \return 操作是否成功
	bool enter();
	
	/// 尝试进入临界区，已经被占用直接返回，不等待。
    /// \return进入临界区是否成功
    bool tryEnter();

	/// 离开临界区。
	/// \return 操作是否成功
	bool leave();

private:
	MutexInternal *m_internal;
};

} // namespace Infra
} // namespace Dahua
#endif //__INFRA_MUTEX_H__

//
// End of "$Id: Mutex.h 120119 2013-06-04 11:12:32Z sun_xiaohui $"
//
