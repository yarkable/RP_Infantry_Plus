
#ifndef __DAHUA_INFRA_VECTOR_H__
#define __DAHUA_INFRA_VECTOR_H__

#include "Allocator.h"
#include "Detail/construct.h"

namespace Dahua {
namespace Infra {

template<typename T>
class TVector
{
public:
	
	typedef T            value_type;
	typedef value_type*  iterator;
	typedef value_type&  reference;
	typedef size_t       size_type;
	
	iterator begin() const
	{ 
		return m_start; 
	}
	
	iterator end() const
	{ 
		return m_end; 
	}
	
	size_type size() const 
	{ 
		return size_type(m_end - m_start);
	}
	
	size_type capacity() const 
	{ 
		return size_type(m_capEnd - m_start); 
	}
	
	bool empty() const 
	{ 
		return begin() == end(); 
	}
	
	reference operator[](size_type n) const
	{ 
		return *(begin() + n); 
	}
	
	TVector() 
		: m_start(0)
		, m_end(0)
		, m_capEnd(0)
	{}
	
	TVector(size_type n, const T& value) 
	{ 
		fill_initialize(n, value); 
	}
	
	explicit TVector(size_type n) 
	{ 
		fill_initialize(n, T()); 
	}
	
	TVector(TVector const& r)
	{
		m_start = (iterator)CAllocator::allocate(r.capacity() * sizeof(T));
		for (size_t i = 0; i < r.size(); ++i)
		{
			Datail::construct(&m_start[i], r.m_start[i]);
		}
		m_end = m_start + r.size();
		m_capEnd = m_start + r.capacity();
	}
	
	TVector& operator=(TVector const& r)
	{
		if (this == &r)
		{	
			return *this;
		}
		
		m_start = (iterator)CAllocator::allocate(r.capacity() * sizeof(T));
		for (size_t i = 0; i < r.size(); ++i)
		{
			Datail::construct(&m_start[i], r.m_start[i]);
		}
		m_end = m_start + r.size();
		m_capEnd = m_start + r.capacity();
		return *this;
	}
	
	~TVector() 
	{
		for (size_t i = 0; i < size(); ++i)
		{	
			Datail::destruct(m_start[i]);
		}
		
		if (m_start != 0)
		{
			CAllocator::dealocate((void *)m_start, size() * sizeof(T));
		}
		m_start = m_end = m_capEnd = 0;
	}
	
	reference front() const
	{ 
		return *m_start; 
	}
	
	reference back() const
	{ 
		return *(m_end - 1); 
	}
	
	void push_back(const T& value) 
	{
		if (m_end == m_capEnd) 
		{
			realloc();
		}
		Datail::construct(m_end, value);
		++m_end;
	}
	
	void pop_back() 
	{
		--m_end;
		Datail::destruct(m_end);
	}
	
	iterator erase(iterator pos) 
	{
		if (pos + 1 != end())
		{
			size_t copy_size = size_t(m_end - pos) - 1;
			for (size_t i = 0; i < copy_size; ++i)
				pos[i] = pos[i + 1];
		}
		--m_end;
		Datail::destruct(m_end);
		return pos;
	}
	
	void resize(size_type new_size, const T& x)
	{
		if (new_size < size())
		{
			m_end = m_start + new_size;
			for (iterator s = m_start; s != m_end; ++s)
			{
				Datail::destruct(s);
				Datail::construct(s, x);
			}
			return;
		}
		
		for ( iterator s = m_start; s != m_end; ++s )
		{
			Datail::destruct(s);
		}
		
		if (new_size > capacity())
		{
			realloc(new_size);
		}
		
		m_end = m_start + new_size;
		for ( iterator s = m_start; s != m_end; ++s )
		{
			Datail::construct(s, x);
		}
	}
	
	void resize(size_type new_size)
	{
		resize(new_size, T());
	}
	
	void clear()
	{
		for ( iterator s = m_start; s != m_end; ++s )
		{
			Datail::destruct(s);
		}
		m_end = m_start;
	}
	
private:
	
	void realloc()
	{
		size_t cap = capacity();
		if (0 == cap)
		{
			m_start = (iterator)CAllocator::allocate(sizeof(T));
			m_capEnd = m_start + 1;
			m_end = m_start;
		}
		else
		{
			size_t s = size();
			m_start = (T*)CAllocator::reallocate(m_start, cap * sizeof(T), 2 * cap * sizeof(T));
			m_capEnd = m_start + 2 * cap;
			m_end = m_start + s;
		}
	}
	
	void realloc(size_t new_size)
	{
		size_t s = size();
		size_t cap = capacity();
		if (cap == 0)
		{
			m_start = (iterator)CAllocator::allocate(sizeof(T) * new_size);
			m_capEnd = m_start + new_size;
			m_end = m_start;
			return;
		}

		size_t nbr = new_size / cap + (new_size % cap ? 1 : 0);
		m_start = (T*)CAllocator::reallocate(m_start, cap * sizeof(T), cap * nbr * sizeof(T));
		m_capEnd = m_start + cap * nbr;
		m_end = m_start + s;
	}
	
	void fill_initialize(size_type n, const T& value)
	{
		m_start = (iterator)CAllocator::allocate(n * sizeof(T));
		for (size_t i = 0; i < n; ++i)
			Datail::construct(m_start + i, value);
		
		m_end = m_start + n;
		m_capEnd = m_end;
	}
	
	iterator m_start;
	iterator m_end;
	iterator m_capEnd;
};

} // end of Infra
} // end of Dahua

#endif // end of __DAHUA_INFRA_VECTOR_H__

