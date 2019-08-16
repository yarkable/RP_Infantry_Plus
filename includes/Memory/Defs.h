//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//


#ifndef __DAHUA_MEMORY_DEFS_H__
#define __DAHUA_MEMORY_DEFS_H__


// WIN32 Dynamic Link Library
#ifdef _MSC_VER

#ifdef MEMORY_DLL_BUILD
#define  MEMORY_API _declspec(dllexport)
#elif defined( MEMORY_DLL_USE ) || defined( UNIVERSAL_DLL_USE )
#define  MEMORY_API _declspec(dllimport)
#else
#define MEMORY_API
#endif

#else

#define MEMORY_API

#endif


//////////////////////////////////////////////////////////////////////////
// use the unified 'DEBUG' macro
#if (!defined(NDEBUG)) && !defined(DEBUG)
#	define DEBUG
#endif

#endif //__DAHUA_MEMORY_DEFS_H__
