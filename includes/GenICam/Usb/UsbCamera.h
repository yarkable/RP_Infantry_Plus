#ifndef __DAHUA_GENICAM_IUSBCAMERA_H__
#define __DAHUA_GENICAM_IUSBCAMERA_H__

#include "GenICam/Defs.h"
#include "GenICam/Camera.h"
#include "Infra/String.h"
#include "Memory/SharedPtr.h"

GENICAM_NAMESPACE_BEGIN

class IUsbCamera;
typedef Memory::TSharedPtr<IUsbCamera> IUsbCameraPtr;

/// \~chinese
/// \brief 相机对象接口类
/// \defgroup UsbCamera  Usb相机对象操作接口
/// \~english
/// \brief	camera object interface class
/// \defgroup UsbCamera API for U3V Cameras Only
/// @{

/// \~chinese
/// \brief Usb相机对象
/// \~english
/// \brief Usb camera object
class GENICAM_API IUsbCamera
{
protected:
    /// \~chinese
    /// \brief 析构函数
    /// \~english
    /// \brief destruct function 
    virtual ~IUsbCamera(){}

public:
    /// \~chinese
    /// \brief Usb相机对象获取接口，同一个cameraPtr对应的是同一个Usb相机对象
    /// \param [in] cameraPtr  Usb类型的相机智能指针对象,如果传入了其它非Usb相机类型，该接口返回空指针,表示无效
    /// \~english
    /// \brief Usb camera object access interface, same cameraPtr is correspond to same Usb camera object
    /// \brief [in] cameraPtr Smart pointer object of Usb camera, if the cameraPtr point to a camera which is not Usb camera, the interface return NULL which means it is invalid
    static  IUsbCameraPtr getInstance(const ICameraPtr &cameraPtr);

    /// \~chinese
    /// \brief 获取相机的 Configuration Valid
    /// \return 返回相机的 Configuration Valid，失败返回NULL
    /// \~english
    /// \brief	get Configuration Valid of camera
    /// \return success:return Configuration Valid of camera, fail:return NULL
    virtual const char * getConfigurationValid() = 0;

    /// \~chinese
    /// \brief 获取相机的 GenCP Version
    /// \return 返回相机的GenCP Version，失败返回NULL
    /// \~english
    /// \brief	get subnetMask of camera
    /// \return success:return camera's subnetMask, fail:return NULL
    virtual const char * getGenCPVersion() = 0;

    /// \~chinese
    /// \brief 返回相机的U3V Version
    /// \return 返回相机的U3V Version，失败返回NULL
    /// \~english
    /// \brief  get U3V Version of camera
    /// \return success:return camera's U3V Version, fail:return NULL
    virtual const char * getU3VVersion() = 0;

    /// \~chinese
    /// \brief 获取相机的 Device GUID
    /// \return 返回相机的GUID，失败返回NULL
    /// \~english
    /// \brief  get Device GUID of camera
    /// \return success:return camera's GUID, fail:return NULL
    virtual const char * getDeviceGUID() = 0;

    /// \~chinese
    /// \brief 获取相机的 Family Name
    /// \return 返回相机的Family Name，失败返回NULL
    /// \~english
    /// \brief  get Family Name of camera
    /// \return success:return camera's Family Name, fail:return NULL
    virtual const char * getFamilyName() = 0;

    /// \~chinese
    /// \brief 获取相机的序列号
    /// \return 返回相机的序列号，失败返回NULL
    /// \~english
    /// \brief	get serial number of camera
    /// \return success:return camera's serial number, fail:return NULL
    virtual const char * getU3VSerialNumber() = 0;

    /// \~chinese
    /// \brief 获取相机的 Low Speed Support
    /// \return 返回相机的 Low Speed Support
    /// \~english
    /// \brief	get Low Speed Support of camera
    /// \return success:return camera's Low Speed Support
    virtual bool isLowSpeedSupported() const = 0;

    /// \~chinese
    /// \brief 获取相机的 Full Speed Support
    /// \return 返回相机的Full Speed Support
    /// \~english
    /// \brief	get Full Speed Support of camera
    /// \return success:return camera's Full Speed Support
    virtual bool isFullSpeedSupported() const = 0;

    /// \~chinese
    /// \brief 获取相机的 High Speed Support
    /// \return 返回相机的 High Speed Support
    /// \~english
    /// \brief  get High Speed Support of camera
    /// \return success:return camera's High Speed Support
    virtual bool isHighSpeedSupported() const = 0;

    /// \~chinese
    /// \brief 获取相机的 Super Speed Support
    /// \return 返回相机的 Super Speed Support
    /// \~english
    /// \brief  get Super Speed Support of camera
    /// \return success:return camera's Super Speed Support
    virtual bool isSuperSpeedSupported() const = 0;

    /// \~chinese
    /// \brief 获取相机的 Speed
    /// \return 返回相机的 Speed，失败返回NULL
    /// \~english
    /// \brief  get Speed of camera
    /// \return success:return camera's Speed, fail:return NULL
    virtual const char * getSpeed() = 0;

    /// \~chinese
    /// \brief 获取相机的 Max Power
    /// \return 返回相机的 Max Power，失败返回NULL
    /// \~english
    /// \brief  get Max Power of camera
    /// \return success:return camera's Max Power, fail:return NULL
    virtual const char * getMaxPower() = 0;

    /// \~chinese
    /// \brief 获取相机的 Driver Installed
    /// \return 返回相机的 Driver Installed
    /// \~english
    /// \brief  get Driver Installed of camera
    /// \return success:return camera's Driver Installed
    virtual bool isDriverInstalled() const = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif//__DAHUA_GENICAM_IUSBCAMERA_H__