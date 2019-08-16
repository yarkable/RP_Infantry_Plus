
#ifndef __DAHUA_BLOCK_H__
#define __DAHUA_BLOCK_H__

#include "SharedPtr.h"
#include "Infra/Function.h"
#include <Infra/Defs.h>

namespace Dahua {
namespace Memory {

/// 释放内存回调函数
/// \param[in] data     需要释放的内存
typedef Infra::TFunction1<void, uint8_t*> FreeFunc; 

/// 析构附加数据函数
/// \param[in] data     附加数据内存指针 不能删除该内存
typedef Infra::TFunction1<void, uint8_t*> UnInitExDataFunc;

/// 构造附加数据函数
/// \param[in] data      附加数据内存指针 不能删除该内存
/// \param[in] data size 附加数据内存大小 
typedef Infra::TFunction2<void, uint8_t*, uint32_t> InitExDataFunc;

/// 数据管理类
/// 该类不主动申请内存 所有的内存均由外部生成，交给本类管理
/// 外部不可主动释放该内存
class INFRA_API CBlock
{
public:
	
	/// 构造函数
	CBlock();
	
	/// 复制构造函数
	CBlock(CBlock const& other);

	///  赋值函数
	CBlock& operator=(CBlock const& other);
	
	/// 带参数的构造函数
	/// \param[in] data      数据指针 该内存由CBlock类托管，外部不允许释放
	/// \param[in] size      数据大小
	/// \param[in] extraSize 附加数据大小
	/// \param[in] freeCB    内存释放函数 若为空则不释放
	CBlock(uint8_t* data, uint32_t size, uint32_t extraSize = 0, FreeFunc freeCB = FreeFunc(), UnInitExDataFunc unInitCB = UnInitExDataFunc());
	
	/// 析构函数
	virtual ~CBlock(void);
	
	/// 获取附加数据指针
	uint8_t* extraData() const;
	
	/// 获取附加数据长度
	uint32_t extraSize() const;
	
	/// 获取数据指针
	uint8_t* data() const;
	
	/// 获取数据大小
	uint32_t size() const;
	
	/// 有效性判断
	bool valid() const;
	
	/// 克隆对象 深度拷贝数据
	CBlock clone() const;

	/// 克隆对象 深度拷贝数据
	/// \param[in] constructFunc 内存构造函数
	CBlock clone( InitExDataFunc constructFunc ) const;
	
	/// 重置对象
	void reset();
	
	/// 重置对象
	/// \param[in] r 复制对象
	void reset(CBlock const& r);
	
private:
	
	struct Impl;
	Impl*  m_impl;
};

} // end of Memory
} // end of Dahua

#endif /// __DAHUA_BLOCK_H__
