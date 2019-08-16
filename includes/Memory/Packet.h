//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __DAHUA_MEMORY_PACKET_H__
#define __DAHUA_MEMORY_PACKET_H__

#include <stddef.h>		// for size_t
#include "Infra/Defs.h"
#include "Infra/Function.h"
#include "Defs.h"

namespace Dahua {
namespace Memory {

////////////////////////////////////////////////////////////////////////////////

struct PacketInternal;

/// \释放自定义内存的函数指针
typedef Infra::TFunction2<void, void*, size_t> FreeMemFunc;

/// \class CPacket
/// \brief 数据包缓存管理
class MEMORY_API CPacket
{
public:
  	/// 构造函数，生成一个无效的包，需要赋值才能使用。可以用于给有效包赋值，
	/// 使原包的包数据引用计数递减。
	CPacket();

	/// 构造函数
	/// \param data  数据指针
	/// \param len 	  数据长度
	/// \param func  释放函数(空表示不释放)
	CPacket(void* data, size_t len, FreeMemFunc func = FreeMemFunc());

  	/// 构造函数，生成一个可以使用的包
	/// \param dataSize 申请的包包含的有效数据缓冲的字节数。
	/// \param extraSize 扩展数据缓冲字节数
	explicit CPacket(size_t dataSize, size_t extraSize = 0);

	/// 拷贝构造函数，完成包数据引用计数递增
	CPacket(const CPacket& other);

	/// 从大包中构造小包，小包引用大包中的局部内存，如果参数不正确，构造一个无效包
	/// \param hugePacket 被引用的大包
	/// \param offset 被引用的内存在大包中的起始字节数
	/// \param size 被引用的内存字节数
	CPacket(const CPacket& hugePacket, size_t offset, size_t size, size_t extraSize);

	/// 赋值运算符重载，完成包数据引用计数递增
	CPacket& operator=(const CPacket& other);

	/// 析构函数，完成对包数据引用计数递减
	virtual ~CPacket();

	/// 重置包，恢复为无效包
	void reset();

	/// 判断是否为有效包
	bool valid() const;

	/// 从当前包缓冲的指针偏移处追加数据，同时自动更新有效数据长度。如果用此函数来
	/// 填充数据，第一次填充前应该将有效数据长度设置为0。
	/// \param buffer 追加的数据指针
	/// \param length 追加的数据长度
	/// \return 实际写入的数据，如果小于length，表示缓冲已满，剩余的数据需要调用者自行处理
	size_t putBuffer(void* buffer, size_t length);

	/// 得到包缓冲的起始位置的指针
	uint8_t* getBuffer() const;

	/// 得到包的有效数据长度, 不包含扩展数据大小
	size_t size() const;

	/// 设置包的有效数据长度，刚申请来的包的有效长度是包申请时的大小。
	/// \param size 新的长度，不会超过包的容量。
	/// \return 返回操作是否成功
	bool resize(size_t size);

	/// 得到包占用空间的大小，按内部页面对齐，可能比申请的稍大。
	size_t capacity() const;

	/// 得到扩展数据缓冲地址
	void* getExtraData() const;

	/// 得到扩展数据长度
	size_t getExtraSize() const;

	///\ brief 构造数据包
	explicit CPacket(uint32_t size, FreeMemFunc fun, void *arg, size_t extraSize = 0);
private:
	PacketInternal* m_internal;
};

////////////////////////////////////////////////////////////////////////////////

struct PacketManagerInternal;

/// \class CPacketManager
/// \brief 包管理类
/// \see CPacket
class MEMORY_API CPacketManager
{
	CPacketManager();
	CPacketManager(CPacketManager const&);
	CPacketManager& operator=(CPacketManager const&);

public:
	/// 内存分配函数类型；参数为要分配的内存大小，返回为分配的内存地址
	typedef Infra::TFunction1<void*, size_t> AllocProc;

	/// 内存释放函数类型；参数是 malloc 获得的指针
	typedef Infra::TFunction1<void, void*> FreeProc;

	/// 内存复制函数类型；第一个参数为目的地址，第二个参数为源地址，第三个参数为字节数
	typedef Infra::TFunction3<void*, void*, const void*, size_t> CopyProc;

	/// 内存管理策略
	enum Policy
	{
		policyDefault = 0,	///< 根据平台设定为系统缺省值, x86 平台为 policySystem，其他平台为 policyPool
		policySystem,		///< 每次申请空间都调用MemoryOperator.malloc，释放调用MemoryOperator.free
		policyPool,			///< 内存池模式，一次性分配好大段空间后，每次申请时分配连续内存块
		policyPoolSystem,	///< 包数据内存使用内存池，扩展数据、PacketInternal 使用系统内存；主要用于兼容组件化包管理器
		policySharePool,	///< 多进程共享内存池模式

		policyCount
	};

	/// 内存池模式的参数
	struct PoolParameter
	{
		size_t		totalSize;	///< 内存池总字节数，由于对齐的原因，实际申请的量会更大一点。缺省值为8M Bytes
		size_t		chunkSize;	///< 内存池区块字节数，必须是2^nK 字节，也是能够申请到的内存块的最小单位。缺省值为1K Bytes
		size_t		alignSize;	///< CPacket数据区可用容量对齐字节数，必须为2^n 字节。缺省值为 4 Bytes
	};

	/// 自定义内存操作函数
	struct MemoryOperator
	{
		AllocProc	malloc;		///< 内存池所管理的内存的申请函数。缺省为 ::malloc
		FreeProc	free;		///< 内存池所管理的内存的释放函数。缺省为 ::free
		CopyProc	memcpy;		///< 内存池所管理的内存之间的复制函数。缺省 ::memcpy
	};

	/// 配置包缓冲管理策略，需要在单件构造之前调用，否则使用缺省的配置。
	/// \param policy [in] 内存管理策略
	/// \param memop [in] 自定义内存操作函数，为NULL时使用缺少函数
	/// \param param [in] 内存池策略的配置参数，为NULL时使用缺省配置
	static void config(Policy policy = policyDefault, MemoryOperator* memop = NULL, PoolParameter* param = NULL);

	/// 获取内存池分配的总的内存空间的起始地址
	uint8_t*  getPoolBuffer();

	/// 创建包管理对象
	static CPacketManager* instance();

	/// 虚析构函数
	~CPacketManager();

	/// 从管理的内存中申请内存块
	void* malloc(size_t size);

	/// 释放内存块
	void free(void*);

	/// 内存复制，如果源和目标都在管理的内存范围内，使用配置时指定的内存复制函数
	void* memcpy(void* dest, const void* src, size_t size);

	/// 得到管理的内存总字节数，这个值就是缺省值或者config配置后的值。
	size_t getBufferSize();

	/// 得到管理的内存剩余字节数，是按2^n页面来进行统计的，可能会比用户调用GetPacket
	/// 时传入的bytes值累加的结果要大。
	size_t getFreeSize();

	/// 打印内存节点的状态，仅用于调试
	void dumpNodes();

private:
	PacketManagerInternal* m_internal;
};

} // namespace Memory
} // namespace Dahua

#endif	// __DAHUA_MEMORY_PACKET_H__

