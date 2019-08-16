
#ifndef __DAHUA_INFRA_CONSTRUCT_H__
#define __DAHUA_INFRA_CONSTRUCT_H__

namespace Dahua {
namespace Infra {
namespace Datail {

template <typename T>
void construct(T* addr, T const& value)
{
	new (addr) T(value);
}

template <typename T>
void destruct(T& value)
{
	value.~T();
}

#if !defined(_MSC_VER) || (_MSC_VER > 1300)
template <typename T>
void destruct(T* value)
{
	value->~T();
}
#endif

} // end of Detail
} // end of Infra
} // end of Dahua

#endif // end of __DAHUA_INFRA_CONSTRUCT_H__
