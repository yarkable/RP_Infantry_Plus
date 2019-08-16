//
//  "$Id$"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//


#ifndef DAHUA_MINI_STRING_STORAGE_INC_
#define DAHUA_MINI_STRING_STORAGE_INC_


/* This is the template for a storage policy
////////////////////////////////////////////////////////////////////////////////
template <typename E, class A = @>
class StoragePolicy
{
    typedef E value_type;
    typedef @ iterator;
    typedef @ const_iterator;
    typedef A allocator_type;
    typedef @ size_type;

    StoragePolicy(const StoragePolicy& s);
    StoragePolicy(const A&);
    StoragePolicy(const E* s, size_type len, const A&);
    StoragePolicy(size_type len, E c, const A&);
    ~StoragePolicy();

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    size_type size() const;
    size_type max_size() const;
    size_type capacity() const;

    void reserve(size_type res_arg);

    template <class ForwardIterator>
    void append(ForwardIterator b, ForwardIterator e);

    void resize(size_type newSize, E fill);

    void swap(StoragePolicy& rhs);

    const E* c_str() const;
    const E* data() const;

    A get_allocator() const;
};
////////////////////////////////////////////////////////////////////////////////
*/

#include <memory>
#include <algorithm>
#include <functional>
#include <cassert>
#include <limits>
#include <stdexcept>


namespace Dahua {
namespace Infra {

////////////////////////////////////////////////////////////////////////////////
// class template MiniStringStorage
// Allocates memory with malloc
////////////////////////////////////////////////////////////////////////////////

template <typename E, class A = std::allocator<E> >
class MiniStringStorage
{
    // The "public" below exists because MSVC can't do template typedefs
public:
    struct Data
    {
        Data() : pEnd_(buffer_), pEndOfMem_(buffer_) { buffer_[0] = E(0); }

        E* pEnd_;
        E* pEndOfMem_;
        E buffer_[1];
    };

    typedef typename A::size_type size_type;

private:
    Data* pData_;

    void Init(size_type size, size_type capacity)
    {
        assert(size <= capacity);
        if (capacity == 0)
        {
			pData_ = NULL;
        }
        else
        {
            // 11-17-2000: comment added:
            //     No need to allocate (capacity + 1) to
            //     accommodate the terminating 0, because Data already
            //     has one one character in there
            pData_ = static_cast<Data*>(
                malloc(sizeof(Data) + capacity * sizeof(E)));
            if (!pData_) assert(0);
            pData_->pEnd_ = pData_->buffer_ + size;
            pData_->pEndOfMem_ = pData_->buffer_ + capacity;
        }
    }

private:
    // Warning - this doesn't initialize pData_. Used in reserve()
    MiniStringStorage() : pData_(NULL)
    { }

public:
    typedef E value_type;
    typedef E* iterator;
    typedef const E* const_iterator;
    typedef A allocator_type;
    typedef typename A::reference reference;


    MiniStringStorage(const MiniStringStorage& rhs)
    {
        const size_type sz = rhs.size();
        Init(sz, sz);
        if (sz) flex_string_details::pod_copy(rhs.begin(), rhs.end(), begin());
    }

    MiniStringStorage(const MiniStringStorage& s,
        flex_string_details::Shallow)
        : pData_(s.pData_)
    {
    }

    MiniStringStorage(const A&)
    { pData_ = NULL; }

    MiniStringStorage(const E* s, size_type len, const A&)
    {
        Init(len, len);
        flex_string_details::pod_copy(s, s + len, begin());
    }

    MiniStringStorage(size_type len, E c, const A&)
    {
        Init(len, len);
        flex_string_details::pod_fill(begin(), end(), c);
    }

    MiniStringStorage& operator=(const MiniStringStorage& rhs)
    {
        const size_type sz = rhs.size();
        reserve(sz);
        flex_string_details::pod_copy(&*rhs.begin(), &*rhs.end(), begin());
        pData_->pEnd_ = &*begin() + sz;
        return *this;
    }

    ~MiniStringStorage()
    {
        assert(begin() <= end());
        free(pData_);
    }

    iterator begin()
    { return pData_ ? pData_->buffer_ : NULL; }

    const_iterator begin() const
    { return pData_ ? pData_->buffer_ : NULL; }

    iterator end()
    { return pData_ ? pData_->pEnd_ : NULL; }

    const_iterator end() const
    { return pData_ ? pData_->pEnd_ : NULL; }

    size_type size() const
    { return pData_ ? pData_->pEnd_ - pData_->buffer_ : 0; }

    size_type max_size() const
    { return size_t(-1) / sizeof(E) - sizeof(Data) - 1; }

    size_type capacity() const
    { return pData_ ? pData_->pEndOfMem_ - pData_->buffer_ : 0; }

    void reserve(size_type res_arg)
    {
        if (pData_ != NULL && res_arg <= capacity())
        {
            // @@@ insert shrinkage here if you wish
            return;
        }

        if (pData_ == NULL)
        {
            Init(0, res_arg);
        }
        else
        {
            const size_type sz = size();

            void* p = realloc(pData_,
                sizeof(Data) + res_arg * sizeof(E));
            if (!p) assert(0);

            if (p != pData_)
            {
                pData_ = static_cast<Data*>(p);
                pData_->pEnd_ = pData_->buffer_ + sz;
            }
            pData_->pEndOfMem_ = pData_->buffer_ + res_arg;
        }
    }

    template <class InputIterator>
    void append(InputIterator b, InputIterator e)
    {
        const size_type
            sz = std::distance(b, e),
            neededCapacity = size() + sz;
        if (capacity() < neededCapacity)
        {
            static std::less_equal<const E*> le;
            (void) le;
            assert(!(le(begin(), &*b) && le(&*b, end()))); // no aliasing
            reserve(neededCapacity);
        }
        std::copy(b, e, end());
        pData_->pEnd_ += sz;
    }

    void resize(size_type newSize, E fill)
    {
        const int delta = int(newSize - size());
        if (delta == 0) return;

        if (delta > 0)
        {
            if (newSize > capacity())
            {
                reserve(newSize);
            }
            E* e = &*end();
            flex_string_details::pod_fill(e, e + delta, fill);
        }
        pData_->pEnd_ = pData_->buffer_ + newSize;
    }

    void swap(MiniStringStorage& rhs)
    {
        std::swap(pData_, rhs.pData_);
    }

    const E* c_str() const
    {
		if (pData_ == NULL)
		{
			return "";
		}

        *pData_->pEnd_ = E();
        return pData_->buffer_;
    }

    const E* data() const
    { return pData_ ? pData_->buffer_ : ""; }

    A get_allocator() const
    { return A(); }
};


} // namespace Infra
} // namespace Dahua

#endif // DAHUA_MINI_STRING_STORAGE_INC_
