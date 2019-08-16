//
//  "$Id$"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA3_PRINT_LOG_H__
#define __INFRA3_PRINT_LOG_H__

#include <stdio.h>
#include "Defs.h"
#include "Function.h"
#include "Thread.h"

//// log格式"[Time]|Category|[Version]|Level|File|[Function]|Line|[Tid]|Content"

/// \defgroup PrintLog PrintLog
/// 打印信息记录等等。
/// 打印信息分trace, debug, info, warn, error, fatal共6个级别，记录的形式可以是
/// 直接打印到标准输出，也可以记录到文件或者发送到远程日志服务器，目前只支持
/// 第一种方式。每行打印信息前自动加上了时间和打印类型的字符串，比如"12:54:12|info"
/// @{
namespace Dahua{
namespace Infra{

///日志等级, 通过setPrintLogLevel进行设置
enum LogLevel
{
	logLevelUnknown= 0, ///< 未知打印等级类型
	logLevelFatal,	///< fatal等级，当设置为此等级时，有一种打印输出（fatal）都有输出
	logLevelError,	///< error等级，当设置为此等级时，有两种打印输出（fatal，error）都有输出
	logLevelWarn,	///< warn等级，当设置为此等级时，有三种打印输出（fatal，error，warn）都有输出
	logLevelInfo,	///< info等级，当设置为此等级时，有四种打印输出（fatal，error，warn，info）都有输出
	logLevelTrace,	///< Trace等级，当设置为此等级时，有五种打印输出（fatal，error，warn，info，trace）都有输出
	logLevelDebug,	///< Debug等级，当设置为此等级时，以上六种打印（fatal，error，warn，info，trace，debug）都有输出
};

//打印选项
struct PrintOptions
{
	char time; 		//是否打印时间，0打印，1不打印，默认打印
	char color; 	//是否打印颜色，0打印，1不打印，默认打印
	char libName; 	//是否打印库名，0打印，1不打印，默认打印
	char level; 	//是否打印等级，0打印，1不打印，默认打印
	char resv[28]; 	//保留
};

/// 打印输出回调函数类型
/// 参数为要打印的字符串
typedef TFunction1<void, char const*> LogPrinterProc;

/// 定义打印回调函数类型
typedef TFunction1<bool, char const*> PrintProc;

/// 设置打印的输出回调函数
/// \param [in] printer 输出回调函数, 为空时设置打印输出到标准输出设备
/// \return 成功返回0, 失败返回-1
int INFRA_API setLogPrinter(LogPrinterProc printer);

/// 设置打印的级别，高于该级别的打印不能输出
///\param [in] level-日志等级，参见 LogLevel 定义
void INFRA_API setPrintLogLevel(int level);

/// 打印调用库名，记录调试信息，级别nLevel，不直接调用
/// \return 返回打印的字节数
int INFRA_API logLibName(int nLevel, const char* libName, const char* fmt, ...)
	__attribute__((format(printf, 3, 4)));

/// 记录调试信息，级别6，不直接调用，用于实现debgf宏
/// \return 返回打印的字节数
int INFRA_API logDebug(const char* fmt, ...) __attribute__((format(printf, 1, 2)));

/// 记录跟踪信息，级别5，不直接调用，用于实现tracef宏
/// \return 返回打印的字节数
int INFRA_API logTrace(const char* fmt, ...) __attribute__((format(printf, 1, 2)));

/// 记录调试信息，级别4，不直接调用，用于实现infof宏
/// \return 返回打印的字节数
int INFRA_API logInfo(const char* fmt, ...) __attribute__((format(printf, 1, 2)));

/// 记录警告信息，级别3，不直接调用，用于实现warnf宏
/// \return 返回打印的字节数
int INFRA_API logWarn(const char* fmt, ...) __attribute__((format(printf, 1, 2)));

/// 记录错误信息，级别2，不直接调用，用于实现errorf宏
/// \return 返回打印的字节数
int INFRA_API logError(const char* fmt, ...) __attribute__((format(printf, 1, 2)));

/// 记录致命错误信息，级别1，不直接调用，用于实现fatalf宏
/// \return 返回打印的字节数
int INFRA_API logFatal(const char* fmt, ...) __attribute__((format(printf, 1, 2)));

/// 以16进制和字符对应的方式打印内存数据
/// \param pdat 数据缓冲指针
/// \param length 数据缓冲长度
void INFRA_API dumpHex(uint8_t* pdat, size_t length = 512);

/// 注册打印处理函数
bool INFRA_API attachPrint(PrintProc proc);

/// 注销打印处理函数
bool INFRA_API detachPrint(PrintProc proc);

/// 设置打印选项
/// \printOptions 打印选项，参见PrintOptions结构体
void INFRA_API setPrintOptions(PrintOptions printOptions);

///设置日志动态过滤条件(-h命令查看帮助)，
///参数说明：logfilter command usage:
///logfilter -loglevel [levelnum](0-no printlevel, 1-fatal, 2-error, 3-warn, 4-info, 5-trace, 6-debug): set log level;
///logfilter -logmodule [modulename] [on/off] #turn module's log on/off
///logfilter -logmoduleLevel[modulename][levelnum] #set module's loglevel
///logfilter -logtime [on/off] #turn log's time on/off
///logfilter -logthread [on/off] #turn log's thread on/off
///logfilter -logversion [on/off] #turn module svn version on/off
///logfilter -logpath [logpath/""] #logger module's log to logpath or cancel logger(by set path to "")
///logfiter -logsize [logsize] #log file max size limited to logsize Kbytes;
///\ param [in] argc --arg参数的个数
///\ param [in] argv---arg参数内容
void INFRA_API	setLogFilter(int argc, char * argv[]);

struct ModulePrintLevel{
	char module[256];
	Infra::LogLevel level;
};

///获取所有模块的日志级别
///\ param [in/out] moduleLlist --日志列表指针
///\ param [out] len --日志列表有效长度
void INFRA_API	getLogModules(ModulePrintLevel moduleLlist[256], int &len);

/// 日志过滤处理函数
///\ param [in] level--日志等级
///\ param [in] module--该日志产生的模块名
///\ param [in] file--该日志产生的文件名
///\ param [in] func--该日志产生的函数名
///\ param [in] line--该日志产生的行号
///\ param [in] svnversion ---该模块的版本号
///\ param [in] fmt---日志格式控制符，后面跟用户的日志信息
int INFRA_API logFilter(int level, 
						const char* module, 
						const char *file,
						const char *func,
						int line,
						const char *svnversion, 
						const char *fmt, ...)__attribute__((format(printf, 7, 8)));

/// 日志模块清理接口，用于清理日志模块所打开的资源，
/// 应该最后模块卸载或者程序退出才使用。
void INFRA_API logCleanup();


} // namespace Infra
} // namespace Dahua

#define __FUNCTION_NO_NS__ (strrchr(__FUNCTION__, ':') != NULL ? strrchr(__FUNCTION__, ':') + 1 : __FUNCTION__)

//////////////////////////////////////////////////////////////////////////
// print message, controlled by messsage level

#undef debugf
#undef tracef
#undef infof
#undef warnf
#undef errorf
#undef fatalf
#undef tracepoint

#ifndef LOG_LIB_NAME
#define LOG_LIB_NAME "Unknown"
#endif

#ifndef LOG_LIB_VERSION
#define LOG_LIB_VERSION "Unknown"
#endif

#if !defined(_MSC_VER) || (_MSC_VER > 1310)

#define debugf(format, ...) \
	logFilter(Dahua::Infra::logLevelDebug, LOG_LIB_NAME,__FILE__, __FUNCTION_NO_NS__, __LINE__,  LOG_LIB_VERSION, format , ## __VA_ARGS__)
#define tracef(format, ...)\
	logFilter(Dahua::Infra::logLevelTrace, LOG_LIB_NAME,__FILE__, __FUNCTION_NO_NS__, __LINE__,  LOG_LIB_VERSION, format , ## __VA_ARGS__)
#define infof(format, ...) \
	logFilter(Dahua::Infra::logLevelInfo, LOG_LIB_NAME,__FILE__, __FUNCTION_NO_NS__, __LINE__,  LOG_LIB_VERSION, format , ## __VA_ARGS__)
#define warnf(format, ...) \
	logFilter(Dahua::Infra::logLevelWarn, LOG_LIB_NAME,__FILE__, __FUNCTION_NO_NS__, __LINE__,  LOG_LIB_VERSION, format , ## __VA_ARGS__)
#define errorf(format, ...) \
	logFilter(Dahua::Infra::logLevelError, LOG_LIB_NAME,__FILE__, __FUNCTION_NO_NS__, __LINE__,  LOG_LIB_VERSION, format , ## __VA_ARGS__)
#define fatalf(format, ...) \
	logFilter(Dahua::Infra::logLevelFatal, LOG_LIB_NAME,__FILE__, __FUNCTION_NO_NS__, __LINE__,  LOG_LIB_VERSION, format , ## __VA_ARGS__)


#define tracepoint()  debugf("tracepoint:\n")


/// 打印宏(带当前线程号和this指针地址)
#define debugf_log_this(format, ...)	debugf("[%s:%d] this:%p tid:%d, " format, __FILE__, __LINE__, this,Dahua::Infra::CThread::getCurrentThreadID(), ## __VA_ARGS__)
#define tracef_log_this(format, ...)	tracef("[%s:%d] this:%p tid:%d, " format, __FILE__, __LINE__, this, Dahua::Infra::CThread::getCurrentThreadID(), ## __VA_ARGS__)
#define infof_log_this(format, ...)		infof("[%s:%d] this:%p tid:%d, " format, __FILE__, __LINE__, this,Dahua::Infra::CThread::getCurrentThreadID(), ## __VA_ARGS__)
#define warnf_log_this(format, ...)		warnf("[%s:%d] this:%p tid:%d, " format, __FILE__, __LINE__, this, Dahua::Infra::CThread::getCurrentThreadID(), ## __VA_ARGS__)
#define errorf_log_this(format, ...)	errorf("[%s:%d] this:%p tid:%d, " format, __FILE__, __LINE__, this, Dahua::Infra::CThread::getCurrentThreadID(), ## __VA_ARGS__)
#define fatalf_log_this(format, ...)	fatalf("[%s:%d] this:%p tid:%d, " format, __FILE__, __LINE__, this, Dahua::Infra::CThread::getCurrentThreadID(), ## __VA_ARGS__)

/// 打印宏(带当前线程号)
#define debugf_log(format, ...) 		debugf("[%s:%d] tid:%d, " format,  __FILE__, __LINE__, Dahua::Infra::CThread::getCurrentThreadID(),  ## __VA_ARGS__)
#define tracef_log(format, ...)			tracef("[%s:%d] tid:%d, " format,  __FILE__, __LINE__, Dahua::Infra::CThread::getCurrentThreadID(),  ## __VA_ARGS__)
#define infof_log(format, ...)          infof("[%s:%d] tid:%d, " format,  __FILE__, __LINE__, Dahua::Infra::CThread::getCurrentThreadID(),  ## __VA_ARGS__)
#define warnf_log(format, ...)          warnf("[%s:%d] tid:%d, " format,  __FILE__, __LINE__, Dahua::Infra::CThread::getCurrentThreadID(),  ## __VA_ARGS__)
#define errorf_log(format, ...)         errorf("[%s:%d] tid:%d, " format,  __FILE__, __LINE__, Dahua::Infra::CThread::getCurrentThreadID(),  ## __VA_ARGS__)
#define fatalf_log(format, ...)         fatalf("[%s:%d] tid:%d, " format,  __FILE__, __LINE__, Dahua::Infra::CThread::getCurrentThreadID(),  ## __VA_ARGS__)

#else 

////// 对于windows平台vc6(_MSC_VER <1300)日志打印宏
#define debugf		logDebug
#define tracef		logTrace
#define infof		logInfo
#define warnf		logWarn
#define errorf		logError
#define fatalf		logFatal
#define tracepoint	logDebug

/// 打印宏(带当前线程号和this指针地址)
#define debugf_log_this		debugf
#define tracef_log_this		tracef
#define infof_log_this		infof
#define warnf_log_this		warnf
#define errorf_log_this		errorf
#define fatalf_log_this		fatalf

/// 打印宏(带当前线程号)
#define debugf_log			debugf
#define tracef_log			tracef
#define infof_log			infof
#define warnf_log			warnf
#define errorf_log			errorf
#define fatalf_log			fatalf
#endif

#endif //__INFRA_PRINT_LOG_H__

