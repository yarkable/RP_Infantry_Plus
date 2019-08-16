//
//  "$Id$"
//
//  Copyright (c)1992-2012, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//


#ifndef DAHUA_INFRA3_STATIC_ASSERT_H__
#define DAHUA_INFRA3_STATIC_ASSERT_H__

#include "Defs.h"

//
// If the compiler issues warnings about old C style casts,
// then enable this:
//
#if defined(__GNUC__) && ((__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 4)))
#  define DAHUA_STATIC_ASSERT_BOOL_CAST( x ) ((x) == 0 ? false : true)
#else
#  define DAHUA_STATIC_ASSERT_BOOL_CAST(x) (bool)(x)
#endif


namespace Dahua {
namespace Infra {

// HP aCC cannot deal with missing names for template value parameters
template <bool x> struct STATIC_ASSERTION_FAILURE;

template <> struct STATIC_ASSERTION_FAILURE<true> { enum { value = 1 }; };

// HP aCC cannot deal with missing names for template value parameters
template<int x> struct static_assert_test{};

} // namespace Infra
} // namespace Dahua

//
// Implicit instantiation requires that all member declarations be
// instantiated, but that the definitions are *not* instantiated.
//
// It's not particularly clear how this applies to enum's or typedefs;
// both are described as declarations [7.1.3] and [7.2] in the standard,
// however some compilers use "delayed evaluation" of one or more of
// these when implicitly instantiating templates.  We use typedef declarations
// by default, but try defining BOOST_USE_ENUM_STATIC_ASSERT if the enum
// version gets better results from your compiler...
//
// Implementation:
// Both of these versions rely on sizeof(incomplete_type) generating an error
// message containing the name of the incomplete type.  We use
// "STATIC_ASSERTION_FAILURE" as the type name here to generate
// an eye catching error message.  The result of the sizeof expression is either
// used as an enum initialiser, or as a template argument depending which version
// is in use...
// Note that the argument to the assert is explicitly cast to bool using old-
// style casts: too many compilers currently have problems with static_cast
// when used inside integral constant expressions.
//

#if defined(_MSC_VER) && (_MSC_VER < 1300)
// __LINE__ macro broken when -ZI is used see Q199057
// fortunately MSVC ignores duplicate typedef's.
#define DAHUA_STATIC_ASSERT( B ) \
   typedef ::Dahua::Infra::static_assert_test<\
      sizeof(::Dahua::Infra::STATIC_ASSERTION_FAILURE< (bool)( B ) >)\
      > dahua_static_assert_typedef_
#elif defined(_MSC_VER)
#define DAHUA_STATIC_ASSERT( B ) \
   typedef ::Dahua::Infra::static_assert_test<\
      sizeof(::Dahua::Infra::STATIC_ASSERTION_FAILURE< DAHUA_STATIC_ASSERT_BOOL_CAST ( B ) >)>\
         DAHUA_JOIN(dahua_static_assert_typedef_, __COUNTER__)
#else
// generic version
#define DAHUA_STATIC_ASSERT( B ) \
   typedef ::Dahua::Infra::static_assert_test<\
      sizeof(::Dahua::Infra::STATIC_ASSERTION_FAILURE< DAHUA_STATIC_ASSERT_BOOL_CAST( B ) >)>\
         DAHUA_JOIN(dahua_static_assert_typedef_, __LINE__)
#endif


#endif // DAHUA_INFRA_STATIC_ASSERT_H__
