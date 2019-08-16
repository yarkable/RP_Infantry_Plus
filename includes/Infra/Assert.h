//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

/// \file: Dahua/Assert.h
///
///	\brief 提供三个断言宏:
///			DAHUA_ASSERT(expr)
///			DAHAU_ASSERT_MSG(expr, msg)
///			DAHUA_VERIFY(expr)
///


#ifndef DAHUA_CURRENT_FUNCTION_INCLUDED
#define DAHUA_CURRENT_FUNCTION_INCLUDED

#include "Defs.h"

namespace Dahua {
namespace Infra {
namespace Detail {


/// 断言失败处理函数
INFRA_API void assertionFailed(char const * expr, char const * function, char const * file, long line);

/// 断言失败处理函数
INFRA_API void assertionFailedMsg(char const * expr, char const * msg, char const * function, char const * file, long line);


inline void current_function_helper()
{

#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600))

# define DAHUA_CURRENT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__DMC__) && (__DMC__ >= 0x810)

# define DAHUA_CURRENT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__FUNCSIG__)

# define DAHUA_CURRENT_FUNCTION __FUNCSIG__

#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))

# define DAHUA_CURRENT_FUNCTION __FUNCTION__

#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)

# define DAHUA_CURRENT_FUNCTION __FUNC__

#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)

# define DAHUA_CURRENT_FUNCTION __func__

#else

# define DAHUA_CURRENT_FUNCTION "(unknown)"

#endif

}

} // namespace Detail
} // namespace Infra
} // namespace Dahua

#endif // DAHUA_CURRENT_FUNCTION_INCLUDED

//--------------------------------------------------------------------------------------//
//                                     DAHUA_ASSERT                                     //
//--------------------------------------------------------------------------------------//

#undef DAHUA_ASSERT

#if defined(NDEBUG)

# define DAHUA_ASSERT(expr) ((void)0)

#else

#define DAHUA_ASSERT(expr) ((expr) \
  ? ((void)0) \
  : ::Dahua::Infra::Detail::assertionFailed(#expr, DAHUA_CURRENT_FUNCTION, __FILE__, __LINE__))

#endif

//--------------------------------------------------------------------------------------//
//                                   DAHUA_ASSERT_MSG                                   //
//--------------------------------------------------------------------------------------//

# undef DAHUA_ASSERT_MSG

#if defined(NDEBUG)

  #define DAHUA_ASSERT_MSG(expr, msg) ((void)0)

#else

  #define DAHUA_ASSERT_MSG(expr, msg) ((expr) \
    ? ((void)0) \
    : ::Dahua::Infra::Detail::assertionFailedMsg(#expr, msg, DAHUA_CURRENT_FUNCTION, __FILE__, __LINE__))

#endif

//--------------------------------------------------------------------------------------//
//                                     DAHUA_VERIFY                                     //
//--------------------------------------------------------------------------------------//

#undef DAHUA_VERIFY

#if defined(NDEBUG)

# define DAHUA_VERIFY(expr) ((void)(expr))

#else

# define DAHUA_VERIFY(expr) DAHUA_ASSERT(expr)

#endif

