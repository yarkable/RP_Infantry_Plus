#ifndef __C_INT_TYPES_H__
#define __C_INT_TYPES_H__

#if defined(__BORLANDC__)
#  define __HAS_STDINT_H
#endif

//
// If the compiler claims to be C99 conformant, then it had better
// have a <stdint.h>:
//
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#     define __HAS_STDINT_H

#elif (defined(__GNUC__) && (__GNUC__ >= 3)) || defined(__HP_aCC)
#  define __HAS_STDINT_H

//
// <stdint.h> added to glibc 2.1.1
// We can only test for 2.1 though:
//
#elif defined(__GLIBC__) && ((__GLIBC__ > 2) || ((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 1)))
   // <stdint.h> defines int64_t unconditionally, but <sys/types.h> defines
   // int64_t only if __GNUC__.  Thus, assume a fully usable <stdint.h>
   // only when using GCC.
#  if defined __GNUC__
#    define __HAS_STDINT_H
#  endif

#elif defined(__MINGW32__) && ((__MINGW32_MAJOR_VERSION > 2) || ((__MINGW32_MAJOR_VERSION == 2) && (__MINGW32_MINOR_VERSION >= 0)))
#  define __HAS_STDINT_H

#endif


//
// __int64 support:
//
#ifdef _MSC_VER

	#if (_MSC_VER >= 1200)
	#   define __HAS_MS_INT64
	#endif
	#if (_MSC_VER >= 1310) && defined(_MSC_EXTENSIONS)
	#   define __HAS_LONG_LONG
	#endif
	#if (_MSC_VER >= 1400) && !defined(_DEBUG)
	#   define __HAS_NRVO
	#endif

	#if (_MSC_VER >= 1600)
	#   define __HAS_STDINT_H
	#endif

#else
	#define __HAS_LONG_LONG

#endif


////////////////////////////////////////////////////////////////////////////////

#ifdef __HAS_STDINT_H

// The following #include is an implementation artifact; not part of interface.
# ifdef __hpux
// HP-UX has a vaguely nice <stdint.h> in a non-standard location
#   include <inttypes.h>
#   ifdef __STDC_32_MODE__
      // this is triggered with GCC, because it defines __cplusplus < 199707L
#     define __NO_INT64_T
#   endif
# elif defined(__FreeBSD__) || defined(__IBMCPP__)
#   include <inttypes.h>
# elif defined(__KERNEL__)
#   include <linux/types.h>
# elif defined(_MSC_VER)
#   include <stdint.h>
# else
#   include <stdint.h>
#  ifndef __STDC_FORMAT_MACROS
#  define __STDC_FORMAT_MACROS
#  endif
#   include <inttypes.h>

// There is a bug in Cygwin two _C macros
#   if defined(__STDC_CONSTANT_MACROS) && defined(__CYGWIN__)
#     undef INTMAX_C
#     undef UINTMAX_C
#     define INTMAX_C(c) c##LL
#     define UINTMAX_C(c) c##ULL
#   endif

# endif

#ifdef __QNX__

// QNX (Dinkumware stdlib) defines these as non-standard names.
// Reflect to the standard names.

typedef intleast8_t int_least8_t;
typedef intfast8_t int_fast8_t;
typedef uintleast8_t uint_least8_t;
typedef uintfast8_t uint_fast8_t;

typedef intleast16_t int_least16_t;
typedef intfast16_t int_fast16_t;
typedef uintleast16_t uint_least16_t;
typedef uintfast16_t uint_fast16_t;

typedef intleast32_t int_least32_t;
typedef intfast32_t int_fast32_t;
typedef uintleast32_t uint_least32_t;
typedef uintfast32_t uint_fast32_t;

# ifndef __NO_INT64_T

typedef intleast64_t int_least64_t;
typedef intfast64_t int_fast64_t;
typedef uintleast64_t uint_least64_t;
typedef uintfast64_t uint_fast64_t;

# endif

#endif

#elif defined(__FreeBSD__) && (__FreeBSD__ <= 4) || defined(__osf__)
// FreeBSD and Tru64 have an <inttypes.h> that contains much of what we need.
# include <inttypes.h>

#else  // __HAS_STDINT_H

//# include <boost/limits.hpp> // implementation artifact; not part of interface
# include <limits.h>         // needed for limits macros


//  These are fairly safe guesses for some 16-bit, and most 32-bit and 64-bit
//  platforms.  For other systems, they will have to be hand tailored.
//
//  Because the fast types are assumed to be the same as the undecorated types,
//  it may be possible to hand tailor a more efficient implementation.  Such
//  an optimization may be illusionary; on the Intel x86-family 386 on, for
//  example, byte arithmetic and load/stores are as fast as "int" sized ones.

//  8-bit types  ------------------------------------------------------------//

# if UCHAR_MAX == 0xff
	typedef signed char     int8_t;
	typedef signed char     int_least8_t;
	typedef signed char     int_fast8_t;
	typedef unsigned char   uint8_t;
	typedef unsigned char   uint_least8_t;
	typedef unsigned char   uint_fast8_t;
# else
#    error defaults not correct; you must hand modify boost/cstdint.hpp
# endif

//  16-bit types  -----------------------------------------------------------//

# if USHRT_MAX == 0xffff
#  if defined(__crayx1)
	// The Cray X1 has a 16-bit short, however it is not recommend
	// for use in performance critical code.
	typedef short           int16_t;
	typedef short           int_least16_t;
	typedef int             int_fast16_t;
	typedef unsigned short  uint16_t;
	typedef unsigned short  uint_least16_t;
	typedef unsigned int    uint_fast16_t;
#  else
	typedef short           int16_t;
	typedef short           int_least16_t;
	typedef short           int_fast16_t;
	typedef unsigned short  uint16_t;
	typedef unsigned short  uint_least16_t;
	typedef unsigned short  uint_fast16_t;
#  endif
# elif (USHRT_MAX == 0xffffffff) && defined(CRAY)
	// no 16-bit types on Cray:
	typedef short           int_least16_t;
	typedef short           int_fast16_t;
	typedef unsigned short  uint_least16_t;
	typedef unsigned short  uint_fast16_t;
# else
#    error defaults not correct; you must hand modify boost/cstdint.hpp
# endif

//  32-bit types  -----------------------------------------------------------//

# if UINT_MAX == 0xffffffff
	typedef int             int32_t;
	typedef int             int_least32_t;
	typedef int             int_fast32_t;
	typedef unsigned int    uint32_t;
	typedef unsigned int    uint_least32_t;
	typedef unsigned int    uint_fast32_t;
# elif ULONG_MAX == 0xffffffff
	typedef long            int32_t;
	typedef long            int_least32_t;
	typedef long            int_fast32_t;
	typedef unsigned long   uint32_t;
	typedef unsigned long   uint_least32_t;
	typedef unsigned long   uint_fast32_t;
# else
#    error defaults not correct; you must hand modify boost/cstdint.hpp
# endif

//  64-bit types + intmax_t and uintmax_t  ----------------------------------//

# if defined(__HAS_LONG_LONG) && \
   !defined(_MSC_VER) && !defined(__BORLANDC__) && \
   (!defined(__GLIBCPP__) || defined(_GLIBCPP_USE_LONG_LONG)) && \
   (defined(ULLONG_MAX) || defined(ULONG_LONG_MAX) || defined(ULONGLONG_MAX))
#    if defined(__hpux)
     // HP-UX's value of ULONG_LONG_MAX is unusable in preprocessor expressions
#    elif (defined(ULLONG_MAX) && ULLONG_MAX == 18446744073709551615ULL) || (defined(ULONG_LONG_MAX) && ULONG_LONG_MAX == 18446744073709551615ULL) || (defined(ULONGLONG_MAX) && ULONGLONG_MAX == 18446744073709551615ULL)
                                                                 // 2**64 - 1
#    else
#       error defaults not correct; you must hand modify boost/cstdint.hpp
#    endif

	// long long workaround ------------------------------------------//
	// On gcc (and maybe other compilers?) long long is alway supported
	// but it's use may generate either warnings (with -ansi), or errors
	// (with -pedantic -ansi) unless it's use is prefixed by __extension__
	//
	#  ifndef __GNUC__
		#ifndef __extension
			#define __extension__
		#endif
	#  endif

	__extension__ typedef  long long			intmax_t;
	__extension__ typedef  unsigned long long	uintmax_t;
	__extension__ typedef  long long			int64_t;
	__extension__ typedef  long long			int_least64_t;
	__extension__ typedef  long long			int_fast64_t;
	__extension__ typedef  unsigned long long	uint64_t;
	__extension__ typedef  unsigned long long	uint_least64_t;
	__extension__ typedef  unsigned long long	uint_fast64_t;

# elif ULONG_MAX != 0xffffffff

#   if ULONG_MAX == 18446744073709551615 // 2**64 - 1
	typedef long                 intmax_t;
	typedef unsigned long        uintmax_t;
	typedef long                 int64_t;
	typedef long                 int_least64_t;
	typedef long                 int_fast64_t;
	typedef unsigned long        uint64_t;
	typedef unsigned long        uint_least64_t;
	typedef unsigned long        uint_fast64_t;
#   else
#      error defaults not correct; you must hand modify boost/cstdint.hpp
#   endif
# elif defined(__GNUC__) && defined(__HAS_LONG_LONG)
	__extension__ typedef long long            intmax_t;
	__extension__ typedef unsigned long long   uintmax_t;
	__extension__ typedef long long            int64_t;
	__extension__ typedef long long            int_least64_t;
	__extension__ typedef long long            int_fast64_t;
	__extension__ typedef unsigned long long   uint64_t;
	__extension__ typedef unsigned long long   uint_least64_t;
	__extension__ typedef unsigned long long   uint_fast64_t;
# elif defined(__HAS_MS_INT64)
	//
	// we have Borland/Intel/Microsoft __int64:
	//
	typedef __int64             intmax_t;
	typedef unsigned __int64    uintmax_t;
	typedef __int64             int64_t;
	typedef __int64             int_least64_t;
	typedef __int64             int_fast64_t;
	typedef unsigned __int64    uint64_t;
	typedef unsigned __int64    uint_least64_t;
	typedef unsigned __int64    uint_fast64_t;
# else // assume no 64-bit integers
#  define __NO_INT64_T
	typedef int32_t              intmax_t;
	typedef uint32_t             uintmax_t;
# endif


#endif // __HAS_STDINT_H

// C99  Macros for format specifiers,
// intptr_t/uintptr_t support for Microsoft C/C++ Compiler
#ifdef _MSC_VER
	#define PRId64 "I64d"
	#define PRIi64 "I64i"
	#define PRIu64 "I64u"
	#define PRIo64 "I64o"
	#define PRIx64 "I64x"

# ifdef _WIN64
	typedef __int64 ssize_t;
# else
	typedef int ssize_t;
#endif

# if (_MSC_VER <= 1200)
	    typedef int intptr_t;
	    typedef unsigned int uintptr_t;
# endif

#endif // _MSC_VER

#endif// __C_INT_TYPES_H__

