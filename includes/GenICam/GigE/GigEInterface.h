#ifndef __DAHUA_GENICAM_IGIGEINTERFACE_H__
#define __DAHUA_GENICAM_IGIGEINTERFACE_H__

#include "GenICam/Defs.h"
#include "GenICam/Camera.h"
#include "Infra/String.h"
#include "Memory/SharedPtr.h"

GENICAM_NAMESPACE_BEGIN

class IGigEInterface;
typedef Memory::TSharedPtr<IGigEInterface> IGigEInterfacePtr;

/// \~chinese
/// \brief 相机接口类
/// \defgroup IGigEInterface  连接GigE相机的接口类
/// \~english
/// \brief camera interface class
/// \defgroup IGigEInterface API for GigEVision interface Only
/// @{

/// \~chinese
/// \brief Class IGigEInterface 连接GigE相机的接口类
/// \~english
/// \brief Class IGigEInterface interface class used to connect GigE Camera 
class GENICAM_API IGigEInterface
{
protected:
	virtual ~IGigEInterface(){}

public:
	/// \~chinese
	/// \brief 连接GigE相机接口对象获取函数，同一个cameraPtr对应的是同一个接口对象
	/// \param [in] cameraPtr  GigE相机智能指针对象
	/// \~english
	/// \brief GigE camera object access interface, same cameraPtr is correspond to same GigE camera object
	/// \param [in] cameraPtr GigE camera smart pointer object
	static IGigEInterfacePtr getInstance(const ICameraPtr &cameraPtr);
    
	/// \~chinese
	/// \brief  获取网卡描述信息
	/// \return 返回网卡描述信息
	/// \~english
	/// \brief get NIC description information
	/// \return success:return NIC description information, fail:return empty string
	virtual Infra::CString getDescription() const = 0;
	
	/// \~chinese
	/// \brief  获取网卡的IP地址
	/// \return 返回网卡的IP地址
	/// \~english
	/// \brief get NIC's IP Address
	/// \return success:return NIC's IP Address, fail:return empty string
	virtual Infra::CString getIpAddress() const = 0;
	
	/// \~chinese
	/// \brief  获取网卡的子网掩码
	/// \return 返回网卡的子网掩码
	/// \~english
	/// \brief get NIC's subnetMask
	/// \return success:return NIC's subnetMask, fail:return empty string
	virtual Infra::CString getSubnetMask() const = 0;
	
	/// \~chinese
	/// \brief 获取网卡的网关
	/// \return 返回网卡的网关
	/// \~english
	/// \brief get NIC's gateway
	/// \return success:return NIC's gateway, fail:return empty string
	virtual Infra::CString getGateway() const = 0;
	
	/// \~chinese
	/// \brief  获取网卡的Mac地址
	/// \return 返回网卡的Mac地址
	/// \~english
	/// \brief get NIC's MacAddress
	/// \return success:return NIC's MacAddress, fail:return empty string
	virtual Infra::CString getMacAddress() const = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif//__DAHUA_GENICAM_IGIGEINTERFACE_H__