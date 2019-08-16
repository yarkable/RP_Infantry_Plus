
#ifndef __DAHUA_MEMORY_DETAIL_SP_COUNTED_BASE_HPP__
#define __DAHUA_MEMORY_DETAIL_SP_COUNTED_BASE_HPP__

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#if defined( __GNUC__ ) && ( defined( __i386__ ) || defined( __x86_64__ ) ) && !defined(__PATHSCALE__)
# include "sp_counted_base_gcc_x86.hpp"

#elif defined( __GNUC__ ) && defined( __ia64__ ) && !defined( __INTEL_COMPILER ) && !defined(__PATHSCALE__)
# include "sp_counted_base_gcc_ia64.hpp"

#elif defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined(__CYGWIN__)
# include "sp_counted_base_w32.hpp"

#elif defined( __GNUC__ ) && ( __GNUC__ * 100 + __GNUC_MINOR__ >= 401 )
# include "sp_counted_base_impl.hpp"

#else

#error Unrecognized threading platform

#endif

#endif  // #ifndef __DAHUA_MEMORY_DETAIL_SP_COUNTED_BASE_HPP__

