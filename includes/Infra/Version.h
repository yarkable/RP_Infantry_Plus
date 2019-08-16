//
//  "$Id: Version.h 55347 2012-03-22 11:26:45Z qin_fenglin $"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA3_VERSION_H__
#define __INFRA3_VERSION_H__

#include "Infra/Defs.h"
#include "Infra/Time.h"

namespace Dahua {
namespace Infra {

/// \brief 版本类
///
/// 版本管理采用统一的类CVersion，每个组件都应该定义各自的版本结构对象，并提供
/// 访问接口。组件集成的时候得到所有组件的版本信息并打印出来，与组件配套表对应，
/// 避免版本不匹配的组件被一起使用。每个组件也应该根据修改提供正确的版本信息。
/// 版本对象最简单的使用方法，就是在组件集成时，打印出所有组件的版本信息：
/// \code
/// int main(int argc, char * argv[])
/// {
///		CVersion appVersion("Application", 1, 0, 0, "$Rev: 23572 $", __DATE__);
///		appVersion.dump();
/// 	......
/// }
/// \endcode
class INFRA_API CVersion
{
public:
	char	name[32];	///< 组件名称
	int		major;		///< 主版本号，架构变动时增加
	int		minor;		///< 次版本号，接口变化或严重缺陷修正时增加
	int		revision;	///< 修订版本号，缺陷修正时增加
	int		svn;		///< svn版本号，记录上述3版本号变更时对应的svn版本号
	SystemTime date;	///< 编译日期，使用__DATE__宏

	static	SystemTime appDate;	///< 应用程序编译日期

	/// 构造函数，版本对象一般作为全局对象构造
	CVersion(const char* name, int major, int minor, int revision, const char* svnString, const char* dateString);

	/// 版本信息打印
	void print() const;

	/// 设置应用程序编译日期，应在Main函数体中设置，设置后才可获取
	static void setAppDate(const char* dateString);

};

} // namespace Infra
} // namespace Dahua

#endif //__INFRA_VERSION_H__


