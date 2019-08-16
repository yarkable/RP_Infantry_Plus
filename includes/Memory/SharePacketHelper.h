
#ifndef __DAHUA_MEMORY_SHAREPACKETHELPER_H__
#define __DAHUA_MEMORY_SHAREPACKETHELPER_H__

#include "Memory/Packet.h"
#include <string>

namespace Dahua{
namespace Memory{

/// 参数基类
struct BaseArg
{
	BaseArg(uint32_t argType) : type(argType) {}

	uint32_t type;
};

/// 内存池参数
struct SharePacketArg : public BaseArg
{
	enum
	{
		MAP_POOL,    ///< 映射共享内存(应用进程使用)
		INIT_POOL     ///< 初始化共享内存(守护进程使用)
	};

	SharePacketArg(int type = MAP_POOL) : BaseArg(type) {}

	uint32_t     poolSize;    ///< 内存池大小
	std::string  poolType;   ///< "ShareMemory" or "AvMemory"
	uint32_t     pageSize;  ///< 页大小(buddy算法有关, 一次能申请的最小内存)
	uint32_t     orderNum; ///< order数量(buddy算法有关，一次能申请的最大内存=(2^(order - 1))*pageSize)
	uint32_t     debugMode;  ///< 调试模式 0：正常版本  1:检测右边越界  2:检测左边越界
};

class MEMORY_API CSharePacketHelper
{
public:

	/// 获取实例
	static CSharePacketHelper* instance();

	/// \由原始数据包构造一个用于发送的描述信息包
	/// \param pkt [in] 原始数据包
	/// \return 描述信息CPacket
	/// \note 是否成功由CPacket的valid接口校验
	CPacket toDescribePacket(const CPacket& pkt);

	/// \由描述信息包还原出原始数据包
	/// \param pkt [in] 描述信息包
	/// \return 原始数据包
	/// \note 是否成功由CPacket的valid接口校验
	CPacket toOriginalPacket(const CPacket& pkt);

	/// \初始化共享内存
	/// \param [in] arg 初始化内存的参数
	/// \retval true 成功 false 失败
	bool initSharePacket(BaseArg * arg);

};


} // namespace Memory
} // namespace Dahua


#endif // end of __DAHUA_MEMORY_SHAREPACKETHELPER_H__

