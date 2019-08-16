//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef DAHUA3_THREAD_SPECIFIC_H__
#define DAHUA3_THREAD_SPECIFIC_H__

#include "Defs.h"


namespace Dahua {
namespace Infra {


struct ThreadSpecificInternal;

/// 线程专有存储(又称线程本地存储); TSS(Thread-Specific Storage), TLS(Thread Local Storage)
class INFRA_API CThreadSpecific
{
public:
	/// 构造函数; 分配 TSS 索引
	CThreadSpecific();

	/// 析构函数; 释放 TSS 索引
	~CThreadSpecific();

	/// TSS 索引是否可用
	bool valid();

	/// 设置存储值
	bool setValue(void const* value);

	/// 取得存储值
	bool getValue(void** pvalue);

private:
	ThreadSpecificInternal* m_internal;
};


} // namespace Infra
} // namespace Dahua

#endif // DAHUA_THREAD_SPECIFIC_H__
