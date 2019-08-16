#ifndef __DAHUA_GENICAM_IGIGECAMERA_H__
#define __DAHUA_GENICAM_IGIGECAMERA_H__

#include "GenICam/Defs.h"
#include "GenICam/Camera.h"
#include "Infra/String.h"
#include "Memory/SharedPtr.h"

GENICAM_NAMESPACE_BEGIN

class IGigECamera;
typedef Memory::TSharedPtr<IGigECamera> IGigECameraPtr;

/// \~chinese
/// \brief 相机对象接口类
/// \defgroup GigECamera  GigE相机对象操作接口
/// \~english
/// \brief	camera object interface class
/// \defgroup GigECamera API for GigEVision Cameras Only
/// @{

/// \~chinese
/// \brief GigE相机对象
/// \~english
/// \brief GigE camera object
class GENICAM_API IGigECamera
{
public:

	enum ECameraAccessPermission
	{
		accessPermissionOpen = 0,		///< \~chinese GigE相机没有被连接        ///< \~english The GigE vision device isn't connected to any application. 
		accessPermissionExclusive, 	///< \~chinese 独占访问权限        ///< \~english Exclusive Access Permission   
		accessPermissionControl, 	///< \~chinese 非独占可读访问权限  ///< \~english Non-Exclusive Readbale Access Permission  
		accessPermissionControlWithSwitchover,  	///< \~chinese Control access with switchover enabled.        ///< \~english Control access with switchover enabled.	
		accessPermissionUnknown = 254,  	///< \~chinese 无法确定        ///< \~english Value not known; indeterminate.   	
		accessPermissionUndefined     	///< \~chinese 未定义访问权限      ///< \~english Undefined Access Permission
	};

protected:
	/// \~chinese
	/// \brief 析构函数
	/// \~english
	/// \brief destruct function 
	virtual ~IGigECamera(){}

public: 
	/// \~chinese
	/// \brief GigE相机对象获取接口，同一个cameraPtr对应的是同一个GigE相机对象
	/// \param [in] cameraPtr  GigE类型的相机智能指针对象,如果传入了其它非GigE相机类型，该接口返回空指针,表示无效
	/// \~english
	/// \brief GigE GigE camera object access interface, same cameraPtr is correspond to same GigE camera object
	/// \brief [in] cameraPtr Smart pointer object of GigE camera, if the cameraPtr point to a camera which is not GigE camera, the interface return NULL which means it is invalid
	static  IGigECameraPtr getInstance(const ICameraPtr &cameraPtr);
	
	/// \~chinese
	/// \brief 获取相机的ipAddress
	/// \return 返回ipAddress 相机的IP地址
	/// \~english
	/// \brief	get ipAddress of camera
	/// \return success:return ipAddress of camera, fail:return empty string 
	virtual Infra::CString getIpAddress() const = 0;

	/// \~chinese
	/// \brief 返回相机的子网掩码
	/// \return 返回subnetMask 相机的子网掩码
	/// \~english
	/// \brief	get subnetMask of camera
	/// \return success:return camera's subnetMask, fail:return empty string 
	virtual Infra::CString getSubnetMask() const = 0;

	/// \~chinese
	/// \brief 返回相机的网关
	/// \return 返回 gateway 相机的网关
	/// \~english
	/// \brief	get gateway of camera
	/// \return success:return camera's gateway, fail:return empty string 
	virtual Infra::CString getGateway() const = 0;

	/// \~chinese
	/// \brief 获取相机的 macAddress
	/// \return 返回macAddress 相机的Mac地址
	/// \~english
	/// \brief	get macAddress of camera
	/// \return success:return camera's macAddress, fail:return empty string 
	virtual Infra::CString getMacAddress() const = 0;
	
    /// \~chinese
	/// \brief  修改设备IP
	///1、调用该函数时如果newSubnetMask和newGateway都设置了有效值，则以此有效值为准;
	///2、调用该函数时如果newSubnetMask和newGateway都设置了NULL，则内部实现时用它所连接网卡的子网掩码和网关代替
	///3、调用该函数时如果newSubnetMask和newGateway两者中其中一个为NULL，另一个非NULL，则返回失败
	/// 该接口只针对通过网卡接入的设备，对于其余设备，调用此接口无意义
	/// \param [in] newIpAddress 新的IP地址信息
	/// \param [in] newSubnetMask 新的掩码信息
	/// \param [in] newGateway 新的网关信息
	/// \return 是否成功
	/// \~english
	/// \brief  modify device IP	
	/// \brief 1、When callback this function, if the values of newSubnetMask and newGateway are both valid then we consider the value is correct
	/// \brief 2、When callback this function, if the values of newSubnetMask and newGateway are both NULL, then these values will be replaced by the subnetmask and gateway of NIC which this camera connect to.
	/// \brief 3、When callback this function, if there is one value of newSubnetMask or newGateway is NULL and the other one is not NULL, then return failed
	/// \brief this interface only serve the devices which is connected to NIC. As for other devices, callback this function won't work and return failed
	/// \param [in] newIpAddress  new IP address 
	/// \param [in] newSubnetMask new SubnetMask
	/// \param [in] newGateway    new Gateway
	/// \retval true  modify IP failed
	/// \retval false modify IP success
	virtual bool forceIpAddress (const char* newIpAddress, const char* newSubnetMask = NULL, const char* newGateway = NULL) = 0;
	
	/// \~chinese
	/// \brief 获取相机的当前访问权限
	/// \return 如果获取成功，返回的枚举值代表相机的当前访问权限，如果失败，返回的枚举值为accessPermissionUnknown
	/// \~english
	/// \brief	get current access permission of camera
	/// \return success:return current access permission of camera, fail:return accessPermissionUnknown 
	virtual ECameraAccessPermission getAccessPermission() const = 0;

    /// \~chinese
    /// \brief 获取相机的 Protocol Version
    /// \return 返回相机的 Protocol Version，失败：返回空字符串
    /// \~english
    /// \brief	get Protocol Version of camera
    /// \return success:return camera's Protocol Version, fail:return empty string 
    virtual Infra::CString getProtocolVersion() const = 0;

    /// \~chinese
    /// \brief 获取相机的 IP Configuration
    /// \return 返回相机的 IP Configuration，失败：返回空字符串
    /// \~english
    /// \brief	get IP Configuration of camera
    /// \return success:return camera's IP Configuration, fail:return empty string 
    virtual Infra::CString getIPConfiguration() const = 0;

	/// \~chinese
	/// \brief 设置相机对sdk命令的响应超时时间
	/// \param [in] timeout 超时时间，单位ms
	/// \return 是否设置成功
	/// \~english
	/// \brief Set the response timeout interval of camera sends command to SDK
	/// \param [in] Timeout interval, unit：ms
	/// \retval false Configuration fail
	/// \retval true  Configuration success
	virtual bool setAnswerTimeout(uint16_t timeout) = 0;

	/// \~chinese
	/// \brief 获取相机的 IP Configuration options
	/// \return 返回相机的 IP Configuration options，失败：返回0
	/// \return value:4 相机只支持LLA
	/// \return value:5 相机支持LLA和Persistent IP
	/// \return value:6 相机支持LLA和DHCP
	/// \return value:7 相机支持LLA、DHCP和Persistent IP
	/// \return value:0 失败
	/// \~english
	/// \brief	get IP Configuration options of camera
	/// \return success:return camera's IP Configuration options, fail:return 0 
	/// \return value:4 camera supports LLA 
	/// \return value:5 camera supports LLA and Persistent IP
	/// \return value:6 camera supports LLA and DHCP
	/// \return value:7 camera supports LLA, DHCP and Persistent IP
	/// \return value:0 fail
	virtual uint32_t getIpConfigOptions() const = 0;

	/// \~chinese
	/// \brief 获取相机当前的 IP Configuration options
	/// \return 返回相机当前的 IP Configuration options，失败：返回0
	/// \return value:4 LLA使能
	/// \return value:5 LLA和Persistent IP使能
	/// \return value:6 LLA和DHCP使能
	/// \return value:7 LLA、DHCP和Persistent IP使能
	/// \return value:0 失败
	/// \~english
	/// \brief	get current IP Configuration options of camera
	/// \return success:return camera's current IP Configuration options, fail:return 0 
	/// \return value:4 LLA is active
	/// \return value:5 LLA and Persistent IP are active
	/// \return value:6 LLA and DHCP are active
	/// \return value:7 LLA, DHCP and Persistent IP are active
	/// \return value:0 fail
	virtual uint32_t getIpConfigCurrent() const = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif//__DAHUA_GENICAM_IGIGECAMERA_H__