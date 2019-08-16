//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __DAHUA_MEMORY_BUFFER_H__
#define __DAHUA_MEMORY_BUFFER_H__

#include <stddef.h>		// for size_t
#include "Infra/Defs.h"
#include "Defs.h"

namespace Dahua {
namespace Memory {

/// 可动态增长的数据缓存类
class MEMORY_API CBuffer
{
	/// 禁止复制构造和赋值操作
	CBuffer(CBuffer const&);
	CBuffer& operator=(CBuffer const&);

public:
	/// 构造函数
	CBuffer();

	/// 析构函数
	~CBuffer();

	/// 追加数据, 如果原缓存容量不够, 会造成内存重新分配以及内存复制操作
	/// \param buffer 追加的数据指针
	/// \param length 追加的数据长度
	/// \return 实际写入的数据
	size_t putBuffer(uint8_t* buffer, size_t length);

	/// 取数据地址
	uint8_t* getBuffer() const;

	/// 取有效数据长度
	size_t size() const;

	/// 设置有效数据长度, 如果原缓存容量不够, 会造成内存重新分配以及内存复制操作
	/// \param size 新的有效数据长度
	void resize(size_t size);

	/// 取缓存容量
	size_t capacity() const;

	/// 预分配缓存容量, 如果原缓存容量不够, 会造成内存重新分配以及内存复制操作
	/// \param capacity 新的缓存容量
	void reserve(size_t capacity);

	/// 释放缓存,重置为构造时的初始状态
	void reset();

	/// 设置每次动态增长的大小
	void setIncreasedSize(size_t increase);

private:
	struct BufferInternal;
	BufferInternal* m_internal;
};

} // namespace Memory
} // namespace Dahua

#endif	// __DAHUA_MEMORY_BUFFER_H__

