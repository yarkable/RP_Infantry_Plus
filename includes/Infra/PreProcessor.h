//
//  "$Id: Guard.h 55347 2012-03-22 11:26:45Z qin_fenglin $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA3_PREPROCESSOR_H__
#define __INFRA3_PREPROCESSOR_H__


#if defined(__GNUC__)
#include "Detail/pp_gcc.hpp"
#elif defined(_MSC_VER) && (_MSC_VER >= 1300)
#include "Detail/pp_msvc.hpp"
#else
//#error unknown platform!!! 
#endif

#endif // __INFRA3_PREPROCESSOR_H__
