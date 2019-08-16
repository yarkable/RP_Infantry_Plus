//
//  "$Id$"
//
//  Copyright (c)1992-2050, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __MEMORY_ATOMIC_REF_COUNTER__
#define __MEMORY_ATOMIC_REF_COUNTER__


#include <Infra/Defs.h>


namespace Dahua {
namespace Memory {


/// 包含强弱引用的计数器类, 用于实现强弱引用智能指针
class CRefCount
{
	/// 禁止复制构造与赋值操作
	CRefCount(CRefCount const&);
	CRefCount& operator=(CRefCount const&);

public:
	/// 构造函数, 计数值都初始为1
	CRefCount();

	/// 析构函数
	~CRefCount();

	/// 强引用计数值增1, 不影响弱引用计数值
	/// \retval 返回操作后的计数值
	int32_t incStrong();

	/// 强引用计数值减1, 不影响弱引用计数值
	/// \retval 返回操作后的计数值
	int32_t decStrong();

	/// 仅当强引用计数不为0时增1
	/// \retval 返回操作后的计数值
	int32_t tryIncStrong();

	/// 取当前强引用计数值
	int32_t getStrong();

	/// 弱引用计数值增1, 不影响强引用计数值
	/// \retval 返回操作后的计数值
	int32_t incWeak();

	/// 弱引用计数值减1, 不影响强引用计数值
	/// \retval 返回操作后的计数值
	int32_t decWeak();

	/// 取当前弱引用计数值
	/// \retval 返回操作后的计数值
	int32_t getWeak();

private:
	int32_t m_internal[8];	///< 内部成员, 32字节
};


} // namespace Memory
} // namespace Dahua

#endif // __MEMORY_ATOMIC_REF_COUNTER__


