#ifndef __DAHUA_GENICAM_CSYSTEM_H__
#define __DAHUA_GENICAM_CSYSTEM_H__

#include "Defs.h"
#include "Camera.h"
#include "StreamSource.h"
#include "ParameterNode.h"
#include "AcquisitionControl.h"
#include "AnalogControl.h"
#include "ImageFormatControl.h"
#include "ISPControl.h"
#include "UserSetControl.h"
#include "DeviceControl.h"
#include "TransportLayerControl.h"
#include "DigitalIOControl.h"

#include "EventSubscribe.h"

GENICAM_NAMESPACE_BEGIN

/// \~chinese
/// \brief 发现设备、创建常用属性对象
/// \defgroup System 设备发现、属性常用对象创建和事件订阅对象创建接口
/// @{
/// \~english
/// \brief discover camera, and create common property instance
/// \defgroup System discover camera, create common property instance and create event subscribe instance interface
/// @{

/// \~chinese
/// \brief Class CSystem 枚举主机所有物理接口可达的在线相机、属性常用对象创建、事件订阅对象创建及获取SDK版本信息
/// \~english
/// \brief Class CSystem enumerate all cameras that the computer can reach, create common property object, create event subscription object, get SDK version information
class GENICAM_API CSystem
{
public:
	///< \~chinese
	///枚举：物理接口类型
	///< \~english
	///enumeration: physical interface type
	enum EInterfaceType
	{
		typeGige = 0,	///< \~chinese GigE协议        ///< \~english GigE Vision Protocol
		typeUsb3 = 1,	///< \~chinese USB3.0协议      ///< \~english USB3.0 Vision Protocol
		typeCL   = 2,	///< \~chinese CAMERALINK协议  ///< \~english Camera Link Protocol
        typePCIe = 3,	///< \~chinese PCIe协议        ///< \~english PCIe Protocol
		typeAll  = 255  ///< \~chinese 忽略协议类型，设备发现传入此类型时，表示需发现所有接口下的设备   ///< \~english ALL Supported Protocol
	};
	
	///< \~chinese
	///枚举：物理接口类型扩展，支持任意接口类型的组合，只用于新的设备发现接口中
	///< \~english
	///enumeration: physical interface type extension, support any combination of interface types, only can be used in new camera discovery interface
	enum EInterfaceTypeEx
	{
		interfaceTypeGige = 0x00000001,	   ///< \~chinese 网卡接口类型			///< \~english NIC type
		interfaceTypeUsb3 = 0x00000002,	   ///< \~chinese USB3.0接口类型		///< \~english USB3.0 interface type
		interfaceTypeCL   = 0x00000004,	   ///< \~chinese CAMERALINK接口类型	///< \~english CAMERALINK interface type
        interfaceTypePCIe = 0x00000008,    ///< \~chinese PCIe接口类型          ///< \~english PCIe interface type
		interfaceTypeAll  = 0x00000000     ///< \~chinese 忽略接口类型，设备发现传入此类型时，表示需发现所有接口下的设备	///< \~english ALL interfaces
	};
	
	/// \~chinese
    /// \brief CSystem单例获取接口
    /// \return CSystem单例对象的指针
	/// \~english
	/// \brief CSystem singleton acquisition interface
	/// \return CSystem pointer to the singleton object
	static CSystem& getInstance();

	/// \~chinese
	/// \brief 发现指定接口类型可达的设备
	/// \param [out] vCameraPtrList 指定接口类型所有在线设备对象列表,当interfaceType = typeAll 时，发现所有接口下的在线设备
	/// \param [in]  interfaceType  接口类型
	/// \return 是否成功
	/// \~english
	/// \brief discover reachable camera which has specified interface type
	/// \param [out] vCameraPtrList camera instance list of specified interface type. when interfaceType = typeAll, discover camerass in all interfaces
	/// \param [in]  interfaceType  interface type.
	/// \return success:true, fail:false
	bool discovery(Infra::TVector<ICameraPtr>& vCameraPtrList, EInterfaceType interfaceType = typeAll);
	

	/// \~chinese
	/// \brief 根据 Camera key "厂商:序列号" 获取 Camera 智能指针
	/// \param [in] pCameraKey 相机的key
	/// \return Camera 智能指针,若传入的pCameraKey不存在或者非法，则返回空智能指针对象
	/// \~english
	/// \brief get smart pointers to Camera according to Camera key "vendor:serial number"
	/// \param [in] pCameraKey Camera's key
	/// \return Camera smart pointer. if the parameter pCameraKey does not exist or is invalid, return empty smart pointer object
	ICameraPtr getCameraPtr(const char * pCameraKey) const;
	
	/// \~chinese
	/// \brief 创建流对象
	/// \param [in] cameraPtr 相机智能指针对象
	/// \param [in] channelId 流通道号，默认为0通道
	/// \return 流智能指针对象
	/// \~english
	/// \brief create stream object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \param [in] channelId stream channel id, default is 0 
	/// \return smart pointer to stream
	IStreamSourcePtr createStreamSource(const ICameraPtr &cameraPtr, uint16_t channelId = 0);

	/// \~chinese
	/// \brief 创建事件订阅对象
	/// \param [in] cameraPtr 相机智能指针对象
	/// \return 事件订阅对象
	/// \~english
	/// \brief create event subscribe object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \return event subscribe object
	IEventSubscribePtr createEventSubscribe(const ICameraPtr &cameraPtr);

	/// \~chinese
	/// \brief 创建AcquisitionControl对象
	/// \param [in] cameraPtr 相机智能指针对象
	/// \return AcquisitionControl智能指针对象
	/// \~english
	/// \brief create AcquisitionControl object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \return AcquisitionControl object
	IAcquisitionControlPtr createAcquisitionControl(const ICameraPtr &cameraPtr);

	/// \~chinese
	/// \brief 创建AnalogControl对象
	/// \param [in] cameraPtr 相机智能指针对象
	/// \return AnalogControl智能指针对象
	/// \~english
	/// \brief create AnalogControl object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \return AnalogControl object
	IAnalogControlPtr createAnalogControl(const ICameraPtr &cameraPtr);

	/// \~chinese
	/// \brief 创建ISPControl对象
	/// \param [in] cameraPtr 相机智能指针对象
	/// \return ISPControl智能指针对象
	/// \~english
	/// \brief create ISPControl object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \return ISPControl object
	IISPControlPtr createISPControl(const ICameraPtr &cameraPtr);

	/// \~chinese
	/// \brief 创建ImageFormatControl对象
	/// \param [in] cameraPtr 相机智能指针对象
	/// \return ImageFormatControl智能指针对象
	/// \~english
	/// \brief create ImageFormatControl object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \return ImageFormatControl object
	IImageFormatControlPtr createImageFormatControl(const ICameraPtr &cameraPtr);

	/// \~chinese
	/// \brief 创建UserSetControl对象
	/// \param [in] cameraPtr 相机智能指针对象
	/// \return UserSetControl智能指针对象
	/// \~english
	/// \brief create UserSetControl object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \return UserSetControl object
	IUserSetControlPtr createUserSetControl(const ICameraPtr &cameraPtr);

	/// \~chinese
	/// \brief 创建DeviceControl对象
	/// \param [in] cameraPtr 相机智能指针对象
	/// \return DeviceControl智能指针对象
	/// \~english
	/// \brief create DeviceControl object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \return DeviceControl object
	IDeviceControlPtr createDeviceControl(const ICameraPtr &cameraPtr);
	 
	/// \~chinese
	/// \brief 创建TransportLayerControl对象
	/// \param [in] cameraPtr 相机智能指针对象
	/// \return TransportLayerControl智能指针对象
	/// \~english
	/// \brief create TransportLayerControl object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \return TransportLayerControl object
	ITransportLayerControlPtr createTransportLayerControl(const ICameraPtr &cameraPtr);

    /// \~chinese
    /// \brief 创建DigitalIOControl对象
    /// \param [in] cameraPtr 相机智能指针对象
    /// \return DigitalIOControl智能指针对象
	/// \~english
	/// \brief create DigitalIOControl object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \return DigitalIOControl object
    IDigitalIOControlPtr createDigitalIOControl(const ICameraPtr &cameraPtr);

	/// \~chinese
	/// \brief 获取版本信息
	/// \return 版本信息
	/// \~english
	/// \brief get version information
	/// \return version information
	const char* getVersion() const;

private:
	/// \~chinese
	/// \brief 构造函数
	/// \~english
	/// \brief constructor function
	CSystem();
	
	/// \~chinese
	/// \brief 拷贝构造函数
	/// \~english
	/// \brief copy constructor function
	CSystem(const CSystem&); 
	
	/// \~chinese
	/// \brief 赋值函数
	/// \~english
	/// \brief assignment function
	CSystem& operator = (const CSystem&);

	/// \~chinese
	/// \brief 析构函数
	/// \~english
	/// \brief destructor function
	~CSystem();
	
	class Impl;
	Impl *m_pImpl;
};

/// @}

GENICAM_NAMESPACE_END

#endif//__DAHUA_GENICAM_CSYSTEM_H__
