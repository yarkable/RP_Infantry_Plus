//
//  "$Id: Timer.h 130874 2013-08-09 00:50:14Z qin_fenglin $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef _INFRA3_TIMER_H_
#define _INFRA3_TIMER_H_

#include "Defs.h"
#include "Function.h"

namespace Dahua{
namespace Infra{

struct TimerInternal;

/// \class CTimer
/// \brief 多平台定时器，支持延时、周期、异步等多种过程执行方式
///
/// 每次调用都是从线程池中取一个线程执行，所以多个的定时器的执行不会有直接影响，
/// 但是同一个定时器的上次调用还没有执行完毕，则下次调用会失败。
/// \see CTimerManager
class INFRA_API CTimer
{
	CTimer(CTimer const&);
	CTimer& operator=(CTimer const&);

public:
	typedef TFunction1<void, unsigned long> Proc;

	/// 构造函数
	/// \param name 定时器名称
	CTimer(const char * name);

	/// 析构函数
	virtual ~CTimer();

	/// 启动定时器
	/// \param fun 定时器回调函数
	/// \param delay 指定启动后延时多少时间调用，单位为毫秒，如果为0表示立即开始调用
	/// \param period 定时器的周期，指定距上次调用多少时间后再次调用，单位为毫秒，
	///		   如果为0表示是非周期定时器，第一次调用完毕后会自动停止。
	/// \param param 回调函数参数，在回调被触发是会传给回调函数。
	/// \param timeout 回调函数执行的超时时间，这个时间会被设置给回调时的定时器线程,
	///        毫秒为单位。0表示永不超时，默认值为1分钟。
	/// \return 在非延时的定时器的上次调用还没有完成的情况下返回false，其他情况返回true
	/// \note 把延时参数和周期参数都设置为0，即可实现异步调用。
	bool start(Proc fun, uint32_t delay, uint32_t period, unsigned long param = 0, uint32_t timeout = 60000);

	/// 关闭定时器
	/// \param callNow 定时器停止时同时再调用一下回调函数，只对带延时的非周期定时器有效。
	/// \return 定时器没有开启的情况下调用停止会返回false
	bool stop(bool callNow = false);

	/// 得到定时器名称
	const char* getName();

	/// 设置定时器名称
	/// \name 新的定时器名称
	void setName(const char* name);

	/// 判断定时器是否开启
	/// \note 非周期定时器在调用过后会自动将状态关闭
	bool isStarted();

	/// 判断非周期定时器是否已经调用过
	bool isCalled();

	/// 判断回调函数是否正在执行
	bool isRunning();

	/// 关闭定时器并等待，直到回调函数结束才返回。
	/// \note 一般在用户类析构的时候调用，调用要特别小心，防止死锁。
	bool stopAndWait();

	///\brief 重新设置定时器执行周期
	///\param [in] pertime 需要重新设置的执行周期
	void setPeriodTime(unsigned int pertime);

	///\brief 开启统计
	void enableStat(bool bStat=true);
private:
	TimerInternal* m_internal;
};


////////////////////////////////////////////////////////////////////////////////

struct TimerManagerInternal;

/// \class CTimerManager
/// \brief 定时器管理类，使用高精度系统定时其来驱动应用定时器工作
///
/// 高精度定时器每次被触发时，检查所有应用定时器的状态，决定是否调用其回调函数。
/// 这个定时器的周期也决定了应用定时器的精度。
/// - Win32使用多媒体定时器，周期为1ms
/// - pSOS使用tmdlTimer组件，周期为1ms
/// - ucLinux2.4 使用系统信号，周期为10ms
/// \see CTimer
class INFRA_API CTimerManager
{
	CTimerManager();
	CTimerManager(CTimerManager const&);
	CTimerManager& operator=(CTimerManager const&);

public:
	/// 创建定时器管理对象
	static CTimerManager* instance();

	/// 析构函数
	~CTimerManager();

	/// 打印所有线程信息
	void dumpTimers();

	/// 限制线程池空闲线程数
	bool limitIdlePooled(int count);

private:
	TimerManagerInternal* m_internal;
};

} // namespace Infra
} // namespace Dahua

#endif
