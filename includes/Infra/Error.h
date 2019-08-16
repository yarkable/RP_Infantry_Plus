//
//  "$Id: Error.h 106479 2013-03-18 05:55:07Z wang_haifeng $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//


#ifndef __INFRA3_ERROR_H__
#define __INFRA3_ERROR_H__

#include "String.h"
#include "Defs.h"

namespace Dahua {

/////////////////////////////////////////////////////////////////////////
// Error Number Define For
enum InfraError
{
	// 与 linux 兼容的错误号
	errorPERM		= 1,	///< Operation not permitted
	errorNOFILE		= 2,	///< No such file or directory
	errorNOENT		= 2,
	errorSRCH		= 3,	///< No such process
	errorINTR		= 4,	///< Interrupted function call
	errorIO			= 5,	///< Input/output error
	errorNXIO		= 6,	///< No such device or address
	error2BIG		= 7,	///< Arg list too long
	errorNOEXEC		= 8,	///< Exec format error
	errorBADF		= 9,	///< Bad file descriptor
	errorCHILD		= 10,	///< No child processes
	errorAGAIN		= 11,	///< Resource temporarily unavailable
	errorNOMEM		= 12,	///< Not enough space
	errorACCES		= 13,	///< Permission denied
	errorFAULT		= 14,	///< Bad address
	errorBUSY		= 16,	///< strerror reports "Resource device"
	errorEXIST		= 17,	///< File exists
	errorXDEV		= 18,	///< Improper link (cross-device link?)
	errorNODEV		= 19,	///< No such device
	errorNOTDIR		= 20,	///< Not a directory
	errorISDIR		= 21,	///< Is a directory
	errorINVAL		= 22,	///< Invalid argument
	errorNFILE		= 23,	///< Too many open files in system
	errorMFILE		= 24,	///< Too many open files
	errorNOTTY		= 25,	///< Inappropriate I/O control operation
	errorFBIG		= 27,	///< File too large
	errorNOSPC		= 28,	///< No space left on device
	errorSPIPE		= 29,	///< Invalid seek (seek on a pipe?)
	errorROFS		= 30,	///< Read-only file system
	errorMLINK		= 31,	///< Too many links
	errorPIPE		= 32,	///< Broken pipe
	errorDOM		= 33,	///< Domain error (math functions)
	errorRANGE		= 34,	///< Result too large (possibly too small)
	errorDEADLOCK	= 36,	///< Resource deadlock avoided (non-Cyg)
	errorDEADLK		= 36,
	errorNAMETOOLONG= 38,	///< Filename too long (91 in Cyg?)
	errorNOLCK		= 39,	///< No locks available (46 in Cyg?)
	errorNOSYS		= 40,	///< Function not implemented (88 in Cyg?)
	errorNOTEMPTY	= 41,	///< Directory not empty (90 in Cyg?)
	errorILSEQ		= 42,	///< Illegal byte sequence


	// Infra 组件错误号
	infraErrorNoFound				= 0x10000000,	///< 没有找到指定的对象
	infraErrorExist					= 0x10000001,	///< 对象已经存在
	infraErrorFull					= 0x10000002,	///< 容器达到个数上限
	infraErrorEmptyProc				= 0x10000003,	///< 对象包含的函数指针为空，没有意义
	infraErrorNotInTimeSection		= 0x10000004,	///< 不在时间段内
	infraErrorPalInterfaceEmpty		= 0x10000005,	///< PAL 接口未实现
	infraErrorPalCallFailed			= 0x10000006,	///< PAL 接口调用失败
	infraErrorThreadIsRunning		= 0x10000007,	///< 线程正在运行
	infraErrorThreadNotExist		= 0x10000008,	///< 线程不存在
	infraErrorThreadNotManaged		= 0x10000009,	///< 线程未被管理
	infraErrorTlsOutOfIndexes		= 0x1000000a,	///< TLS 索引不正确
	infraErrorTimerNotStarted		= 0x1000000b,	///< 定时器未开启
	infraErrorTimerIsRunning		= 0x1000000c,	///< 定时器正在运行
	infraErrorPacketNoFree			= 0x1000000d,	///< Packet 内存空间不足
	infraErrorModifySysTimeFailed	= 0x1000000e,	///< 直接修改系统时间失败
	infraErrorSyncRtcTimeFailed		= 0x1000000f,	///< 修改时间时RTC时钟同步失败或者回调函数(一般用于同步rtc时钟)失败
};

namespace Infra {

	/// 调用系统函数出错时，设置调用线程最后一个错误。
	/// 各组件内部逻辑出错时，应该掉用此接口根据不同原因设置错误号。如果是调用
	/// 系统函数或者其他非组件库出错时，也应该将(errno)的值设置为当前错误。
	INFRA_API void setLastError(int eno);

	/// 获取调用线程最后一个错误，使用linux兼容错误码。
	INFRA_API int getLastError();

	/// 设置错误码对应的错误字符串
	INFRA_API void setErrMsg(int eno, const char* message);

	/// 根据错误码获取错误字符串。
	INFRA_API const char* getErrMsg(int eno);

	/// 设置错误码对应的错误字符串
	INFRA_API void setErrorMessage(int eno, CString2 const& message);

	/// 根据错误码获取错误字符串。
	INFRA_API CString2 getErrorMessage(int eno);

} // namespace Infra
} // namespace Dahua

#endif //__INFRA_ERROR_H__
