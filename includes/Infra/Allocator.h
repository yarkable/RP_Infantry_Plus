
#ifndef __DAHUA_INFRA_ALLOCATOR_H__
#define __DAHUA_INFRA_ALLOCATOR_H__

#include <stddef.h> /// for size_t
#include "Defs.h"

namespace Dahua {
namespace Infra {

/// 内存分配器 用于自定义STL容器
class INFRA_API CAllocator
{
public:
	
	/// \brief 申请内存
	/// \param[in] size 内存大小
	/// \retval 内存指针
	static void* allocate(size_t size);
	
	/// \brief 重新申请内存
	/// \param[in] mem      原内存指针
	/// \param[in] old_size 原内存大小
	/// \param[in] new_size 新内存大小
	/// \retval 内存指针
	static void* reallocate(void* mem, size_t old_size, size_t new_size);
	
	/// \brief 释放内存
	/// \param[in] mem      原内存指针
	/// \param[in] size     内存大小
	static void dealocate(void* mem, size_t size);
};

} // end of Infra
} // end of Dahua

#endif // end of __DAHUA_INFRA_ALLOCATOR_H__
