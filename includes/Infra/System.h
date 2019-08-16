//
//  "$Id: Support.h 20211 2011-02-24 02:50:44Z wang_haifeng $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA3_SYSTEM_H__
#define __INFRA3_SYSTEM_H__

#include "Defs.h"

namespace Dahua {
namespace Infra {

/// \defgroup System System
/// 一些系统相关辅助函数。
/// @{

/// 系统调用接口,以字符串的形式调用系统命令
int INFRA_API systemCall(const char* command);


///	\ 获取当前进程id
uint64_t INFRA_API getCurrectProcessID();


/// @} end of group

} // namespace Infra
} // namespace Dahua

#endif //__INFRA_SUPPORT_H__


