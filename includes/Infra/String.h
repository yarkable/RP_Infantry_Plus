//
//  "$Id$"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __DAHUA_INFRA_STRING_H__
#define __DAHUA_INFRA_STRING_H__

#include "Defs.h"
#include "CString.h"
#include "Detail/flex_string.h"

////////////////////////////////////////////////////////////////////////////////
// 与 std::basic_string 接口完全兼容的字符串处理类

namespace Dahua {
namespace Infra {

// 兼容CStirng和std::string的字符串，新函数应该直接使用CString来定义
#ifdef _WIN32
typedef CString CString2;
#else
typedef std::string CString2;
#endif // WIN32

typedef flex_string<
	wchar_t,
	std::char_traits<wchar_t>,
	std::allocator<wchar_t>,
	SmallStringOpt<AllocatorStringStorage<wchar_t, std::allocator<wchar_t> >, 31>
> CWString;

/// 最小字符串类，sizeof(CMiniString)固定为sizeof(void *)
typedef flex_string<
	char,
	std::char_traits<char>,
	std::allocator<char>,
	MiniStringStorage<char, std::allocator<char> >
> CMiniString;

} // namespace Infra
} // namespace Dahua


#endif// __DAHUA_INFRA_STRING_H__


