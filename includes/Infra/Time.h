//
//  "$Id: Time.h 109610 2013-04-02 06:41:41Z qin_fenglin $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA3_TIME_WRAPPER_H__
#define __INFRA3_TIME_WRAPPER_H__

#include <string>
#include "Defs.h"
#include "String.h"
#include "Function.h"

namespace Dahua {
namespace Infra {

/// 时间结构
struct SystemTime
{
	int  year;		///< 年。
	int  month;		///< 月，January = 1, February = 2, and so on.
	int  day;		///< 日。
	int  wday;		///< 星期，Sunday = 0, Monday = 1, and so on
	int  hour;		///< 时。
	int  minute;	///< 分。
	int  second;	///< 秒。
	int  isdst;		///< 夏令时标识。
};

/// \class CTime
/// \brief 时间类，实现了本地时间存取，运算，格式控制与打印等接口
/// CTime类处理的时间都是本地时间，在GMT时间的基础上加了时区偏移。
class INFRA_API CTime : public SystemTime
{
public:
	/// 时间修改回调函数
	typedef TFunction1<bool, SystemTime> ModifyProc;

	/// 日期顺序格式
	enum DateFormat
	{
		ymd,
		mdy,
		dmy
	};

	/// 格式化模式选项
	enum FormatMask
	{
		fmGeneral = 0,		///< 只指定是否显示以及起始值
		fmSeparator = 1,	///< 指定分隔符
		fmDateFormat = 2,	///< 指定年月日顺序
		fmHourFormat = 4,	///< 指定小时制式

		fmAll = fmSeparator | fmDateFormat | fmHourFormat	///< 指定所有格式选项
	};

	/// 缺省构造函数
	CTime( );

	/// 相对时间构造函数
	CTime(uint64_t time);

	/// 普通时间构造函数
	CTime( int vyear, int vmonth, int vday, int vhour, int vmin, int vsec);

	/// 得到相对时间，相对时间指从GMT 1970-1-1 00:00:00 到某个时刻经过的秒数
	/// \return 相对时间
	uint64_t makeTime() const;

	/// 分解相对时间
	/// \param time 相对时间
	void breakTime(uint64_t time);

	/// 时间调节
	/// \param seconds 调节的秒数
	/// \return 调节后新的时间对象
	CTime operator +( int64_t seconds ) const;

	/// 时间调节
	/// \param seconds 调节的秒数
	/// \return 调节后新的时间对象
	CTime operator -( int64_t seconds ) const;

	/// 时间差运算
	/// \param time 相比较的时间
	/// \return 比较的结果，为(*this - time)得到的秒数
	int64_t operator -( const CTime& time ) const;

	/// 时间调节
	/// \param seconds 调节的秒数
	/// \return 对象本身
	CTime& operator +=( int64_t seconds );

	/// 时间调节
	/// \param seconds 调节的秒数
	/// \return 对象本身
	CTime& operator -=( int64_t seconds );

	/// 时间比较
	/// \param time 相比较的时间
	/// \return 相等返回true，否则返回false
	bool operator == (const CTime& time) const;

	/// 时间比较
	/// \param time 相比较的时间
	/// \return 不等返回true，否则返回false
	bool operator != (const CTime& time) const;

	/// 时间比较
	/// \param time 相比较的时间
	/// \return <返回true，否则返回false
	bool operator < (const CTime& time) const;

	/// 时间比较
	/// \param time 相比较的时间
	/// \return <=返回true，否则返回false
	bool operator <= (const CTime& time) const;

	/// 时间比较
	/// \param time 相比较的时间
	/// \return >返回true，否则返回false
	bool operator > (const CTime& time) const;

	/// 时间比较
	/// \param time 相比较的时间
	/// \return >=返回true，否则返回false
	bool operator >= (const CTime& time) const;

	/// 时间格式化
	/// \param buf 字符串缓冲，一定要足够大
	/// \param format 格式化字符串，如"yyyy-MM-dd HH:mm:ss tt"
	/// yy = 年，不带世纪 yyyy = 年，带世纪
	/// M = 非0起始月 MM = 0起始月 MMMM = 月名称
	/// d = 非0起始日 dd = 0起始日
	/// H = 非0起始24小时 HH = 0起始24小时 h = 非0起始12小时 hh = 0起始12小时
	/// tt = 显示上午或下午
	/// \param mask 格式选项，指定日期分隔符，年月日顺序，小时制式是否由统一的格
	/// 式决定。相应位置0，表示使用统一格式，置1，表示使用format指定的格式
	void format(char* buf, const char *format = "yyyy-MM-dd HH:mm:ss", int mask = fmGeneral) const;

	/// 时间字符串解析
	/// \param buf 输入的字符串缓冲
	/// \param format 格式化字符串，暂时只支持默认的"yyyy-MM-dd HH:mm:ss"
	/// \param mask 格式选项，指定日期分隔符，年月日顺序，小时制式是否由统一的格
	/// 式决定。相应位置0，表示使用统一格式，置1，表示使用format指定的格式
	/// \return 是否成功
	bool parse(const char* buf, const char *format = "yyyy-MM-dd HH:mm:ss", int mask = fmGeneral);

	/// 会立刻实际的去取本地当前系统时间,更精确和及时
	/// 但linux下多线程调用频繁可能会导致较高cpu，适用于时间秒跳变准确，且调用不频繁的场景
	static CTime getCurrentTime();

	/// 返回保存的当前的系统时间，内部会间隔去刷新保存的本地当前系统时间
	/// 用于多线程频繁打印，与实际时间精度控制在1s偏差范围内，但是cpu占用率低
	static CTime getCurTimeForPrint();

	/// 设置本地当前系统时间
	/// \param time 新的时间
	/// \param toleranceSeconds 容差，表示容许设置时间和当前差多少秒内不做修改
	static void setCurrentTime(const CTime& time, int toleranceSeconds = 0);

	/// 设置本地当前系统时间并返回设置成功与否
	/// \param time 新的时间
	/// \param toleranceSeconds 容差，表示容许设置时间和当前差多少秒内不做修改
	static bool setCurrentTimeEx(const CTime& time, int toleranceSeconds = 0);

	/// 得到从系统启动到现在的毫秒数
	static uint64_t getCurrentMilliSecond();

	/// 得到从系统启动到现在的微秒数
	static uint64_t getCurrentMicroSecond();

	/// 设置时间格式，会影响Format的输出的字符串格式，如"yyyy-MM-dd HH:mm:ss"
	static void setFormatString(const char* format);

	/// 获取时间格式
	static const CString getFormatString();

	/// 获取日期格式
	static DateFormat getDateFormat();

	/// 获取当前是否是12小时制
	static bool get12Hour();

	/// 获取日期分割符
	static char getSeparator();

	/// 注册修改时间回调函数，这个在上层调用了setCurrentTime后会被同步触发
	/// \param proc 时间修改回调函数
	/// \return 注册时间修改回调函数是否成功
	static bool attachModifyProc(ModifyProc proc);


	/// 设置时间格式，会影响Format的输出的字符串格式，如"yyyy-MM-dd HH:mm:ss"
	static void setFormat(const CString2& format);

	/// 获取时间格式
	static const CString2 getFormat();

	/// 获取UTC标准时间
	static uint64_t getCurrentUTCtime();

	/// 禁止时区，优化性能。CTime中不进行时区转换，也不获取时区
	static int disableTimezone();

public:
	static const CTime minTime; ///< 有效的最小时间
	static const CTime maxTime; ///< 有效的最大时间

};

} // namespace Infra
} // namespace Dahua

#endif // __INFRA_TIME_WRAPPER_H__
