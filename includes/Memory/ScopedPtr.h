//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

///	\file Infra/ScopedPtr.h
///	从 boost.scoped_ptr 移植过来的作用域内智能指针
///

#ifndef INFRA_SCOPED_PTR_H__
#define INFRA_SCOPED_PTR_H__

#include <cassert>
#include <memory>
#include "Detail/checked_delete.hpp"

namespace Dahua {
namespace Memory {


/// \brief scoped smart pointer.
///
///	\ingroup smart pointers
///
///	scoped_ptr mimics a built-in pointer except that it guarantees deletion
///	of the object pointed to, either on destruction of the scoped_ptr or via
///	an explicit reset(). scoped_ptr is a simple solution for simple needs;
///	use shared_ptr or std::auto_ptr if your needs are more complex.
///
template<class T> class TScopedPtr	// noncopyable
{
    T* m_ptr;

    TScopedPtr(TScopedPtr const&);
    TScopedPtr & operator=(TScopedPtr const&);

public:
    typedef TScopedPtr<T> this_type;
    typedef T element_type;

    explicit TScopedPtr(T* p = 0): m_ptr(p) // never throws
    {
    }

    explicit TScopedPtr(std::auto_ptr<T> p): m_ptr(p.release()) // never throws
    {
    }

    ~TScopedPtr() // never throws
    {
        Detail::checked_delete(m_ptr);
    }

    void reset(T* p = 0) // never throws
    {
        assert(p == 0 || p != m_ptr); // catch self-reset errors
        this_type(p).swap(*this);
    }

    T& operator*() const // never throws
    {
        assert(m_ptr != 0);
        return *m_ptr;
    }

    T* operator->() const // never throws
    {
        assert(m_ptr != 0);
        return m_ptr;
    }

    T* get() const // never throws
    {
        return m_ptr;
    }

    // implicit conversion to "bool"

    typedef T* this_type::*unspecified_bool_type;

    operator unspecified_bool_type() const // never throws
    {
        return m_ptr == 0 ? 0 : &this_type::m_ptr;
    }

    bool operator!() const // never throws
    {
        return m_ptr == 0;
    }

    void swap(TScopedPtr& b) // never throws
    {
        T* tmp = b.m_ptr;
        b.m_ptr = m_ptr;
        m_ptr = tmp;
    }
};

} // namespace Memory
} // namespace Dahua

template<class T> inline void swap(Dahua::Memory::TScopedPtr<T>& a, Dahua::Memory::TScopedPtr<T>& b) // never throws
{
    a.swap(b);
}

// get_pointer(p) is a generic way to say p.get()
template<class T> inline T * get_pointer(Dahua::Memory::TScopedPtr<T> const & p)
{
    return p.get();
}

#endif // INFRA_SCOPED_PTR_H__
