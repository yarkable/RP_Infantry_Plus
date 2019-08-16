//
//  "$Id: Defs.h 129930 2013-08-02 07:51:01Z sun_xiaohui $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//


#ifndef __INFRA3_DEFS_H__
#define __INFRA3_DEFS_H__

#include "Types/Types.h"
#include "Types/IntTypes.h"

// WIN32 Dynamic Link Library
#ifdef _MSC_VER

#ifdef INFRA_DLL_BUILD
#define  INFRA_API _declspec(dllexport)
#elif defined( INFRA_DLL_USE ) || defined( UNIVERSAL_DLL_USE )
#define  INFRA_API _declspec(dllimport)
#else
#define INFRA_API
#endif

#else

#define INFRA_API

#endif


#ifndef NULL
#define NULL 0
#endif

#ifndef __GNUC__
#define __attribute__(x)
#endif

//////////////////////////////////////////////////////////////////////////
// useful definition

#define DAHUA_BITMSK(bit)		((unsigned int)1 << (bit))

#ifndef BITMSK
// 为兼容老接口保留，请勿使用
#define BITMSK(bit)				((unsigned int)1 << (bit))
#endif
//////////////////////////////////////////////////////////////////////////
// Join two variables
#define DAHUA_JOIN( X, Y ) DAHUA_DO_JOIN( X, Y )
#define DAHUA_DO_JOIN( X, Y ) DAHUA_DO_JOIN2(X,Y)
#define DAHUA_DO_JOIN2( X, Y ) X##Y

// 为兼容老接口保留，请勿使用
#define MACRO_JOIN( X, Y ) MACRO_DO_JOIN( X, Y )
#define MACRO_DO_JOIN( X, Y ) MACRO_DO_JOIN2(X,Y)
#define MACRO_DO_JOIN2( X, Y ) X##Y


//////////////////////////////////////////////////////////////////////////
// use the unified 'DEBUG' macro
#if (!defined(NDEBUG)) && !defined(DEBUG)
#	define DEBUG
#endif

//////////////////////////////////////////////////////////////////////////
// print message, controlled by messsage level
int INFRA_API logTrace(const char* fmt, ...) __attribute__((format(printf, 1, 2)));
int INFRA_API logDebug(const char* fmt, ...) __attribute__((format(printf, 1, 2)));
int INFRA_API logInfo(const char* fmt, ...) __attribute__((format(printf, 1, 2)));
int INFRA_API logWarn(const char* fmt, ...) __attribute__((format(printf, 1, 2)));
int INFRA_API logError(const char* fmt, ...) __attribute__((format(printf, 1, 2)));
int INFRA_API logFatal(const char* fmt, ...) __attribute__((format(printf, 1, 2)));

int logLibName(int nLevel, const char *, const char* fmt, ...)
	__attribute__((format(printf, 3, 4)));

#undef debugf
#undef tracef
#undef infof
#undef warnf
#undef errorf
#undef fatalf
#undef tracepoint

#ifdef __linux__ // perform complete xxxxf macro replacement
#ifdef DEBUG
#	ifdef LOG_LIB_NAME
#		define debugf(format, ...) logLibName(6, LOG_LIB_NAME, format, ## __VA_ARGS__)
#		define tracef(format, ...) logLibName(5, LOG_LIB_NAME, format, ## __VA_ARGS__)
#		define infof(format, ...) logLibName(4, LOG_LIB_NAME, format, ## __VA_ARGS__)
#		define warnf(format, ...) logLibName(3, LOG_LIB_NAME, format, ## __VA_ARGS__)
#		define errorf(format, ...) logLibName(2, LOG_LIB_NAME, format, ## __VA_ARGS__)
#		define fatalf(format, ...) logLibName(1, LOG_LIB_NAME, format, ## __VA_ARGS__)
#	else
#		define tracef(format, ...) logTrace(format, ## __VA_ARGS__)
#		define debugf(format, ...) logDebug(format, ## __VA_ARGS__)
#		define infof(format, ...) logInfo(format, ## __VA_ARGS__)
#		define warnf(format, ...) logWarn(format, ## __VA_ARGS__)
#		define errorf(format, ...) logError(format, ## __VA_ARGS__)
#		define fatalf(format, ...) logFatal(format, ## __VA_ARGS__)
#	endif
#else
#	define tracef(format, ...)
#	define debugf(format, ...)
#	ifdef LOG_LIB_NAME
#		define infof(format, ...) logLibName(4, LOG_LIB_NAME, format, ## __VA_ARGS__)
#		define warnf(format, ...) logLibName(3, LOG_LIB_NAME, format, ## __VA_ARGS__)
#		define errorf(format, ...) logLibName(2, LOG_LIB_NAME, format, ## __VA_ARGS__)
#		define fatalf(format, ...) logLibName(1, LOG_LIB_NAME, format, ## __VA_ARGS__)
#	else
#		define infof(format, ...) logInfo(format, ## __VA_ARGS__)
#		define warnf(format, ...) logWarn(format, ## __VA_ARGS__)
#		define errorf(format, ...) logError(format, ## __VA_ARGS__)
#		define fatalf(format, ...) logFatal(format, ## __VA_ARGS__)
#	endif
#endif
#else
#ifdef DEBUG
#	define tracef logTrace
#	define debugf logDebug
#	define infof logInfo
#	define warnf logWarn
#	define errorf logError
#	define fatalf logFatal
#else
#	define tracef if(0)logTrace
#	define debugf if(0)logDebug
#	define infof logInfo
#	define warnf logWarn
#	define errorf logError
#	define fatalf logFatal
#endif
#endif

#define tracepoint()  debugf("tracepoint: %s, %d.\n",__FILE__,__LINE__)

#endif //__INFRA_DEFS_H__
