//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

///	\file Infra/Detail/checked_delete.hpp
///	从 boost/checked_delete.hpp 移植过来带完整类型判断的 delete 操作函数
///

#ifndef INFRA_DETAIL_CHECKED_DELETE_H__
#define INFRA_DETAIL_CHECKED_DELETE_H__


#include <cassert>
#include <memory>


namespace Dahua {
namespace Memory {
namespace Detail {

// verify that types are complete for increased safety

template<class T> inline void checked_delete(T * x)
{
    // intentionally complex - simplification causes regressions
    typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
    (void) sizeof(type_must_be_complete);
    delete x;
}

template<class T> inline void checked_array_delete(T * x)
{
    typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
    (void) sizeof(type_must_be_complete);
    delete [] x;
}

template<class T> struct checked_deleter
{
    typedef void result_type;
    typedef T * argument_type;

    void operator()(T * x) const
    {
        // Dahua::Utils::Detail:: disables ADL
		Dahua::Memory::Detail::checked_delete(x);
    }
};

template<class T> struct checked_array_deleter
{
    typedef void result_type;
    typedef T * argument_type;

    void operator()(T * x) const
    {
        Dahua::Memory::Detail::checked_array_delete(x);
    }
};


} // namespace Detail
} // namespace Memory
} // namespace Dahua

#endif // INFRA_DETAIL_CHECKED_DELETE_H__
