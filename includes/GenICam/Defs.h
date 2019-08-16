#ifndef __DAHUA_GENICAM_DEFS_H__
#define __DAHUA_GENICAM_DEFS_H__
#include "Infra/Defs.h"

/// \mainpage
/// \~chinese
/// \htmlinclude mainpage_chs.html
/// \~english
/// \htmlinclude mainpage_eng.html

//#include <string.h>

// WIN32 Dynamic Link Library
#ifdef _MSC_VER
	#ifdef GENICAM_API_DLL_BUILD
		#define  GENICAM_API _declspec(dllexport)
	#elif defined GENICAM_API_DLL_USE
		#define  GENICAM_API _declspec(dllimport)
	#else
		#define GENICAM_API
	#endif
#else
	#define GENICAM_API
#endif

#define GENICAM_NAMESPACE_BEGIN namespace Dahua{ namespace GenICam {
#define GENICAM_NAMESPACE_END } }

#endif//__DAHUA_GENICAM_DEFS_H__