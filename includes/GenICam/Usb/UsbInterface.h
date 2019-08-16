#ifndef __DAHUA_GENICAM_IUSBINTERFACE_H__
#define __DAHUA_GENICAM_IUSBINTERFACE_H__

#include "GenICam/Defs.h"
#include "GenICam/Camera.h"
#include "Infra/String.h"
#include "Memory/SharedPtr.h"

GENICAM_NAMESPACE_BEGIN

class IUsbInterface;
typedef Memory::TSharedPtr<IUsbInterface> IUsbInterfacePtr;

/// \~chinese
/// \brief 相机接口类
/// \defgroup IUsbInterface  连接Usb相机的接口类
/// \~english
/// \brief camera interface class
/// \defgroup IUsbInterface API for U3V interface Only
/// @{

/// \~chinese
/// \brief Class IUsbInterface 连接Usb相机的接口类
/// \~english
/// \brief Class IUsbInterface interface class used to connect Usb Camera 
class GENICAM_API IUsbInterface
{
protected:
    virtual ~IUsbInterface(){}

public:
    /// \~chinese
    /// \brief 连接Usb相机接口对象获取函数，同一个cameraPtr对应的是同一个接口对象
    /// \param [in] cameraPtr  Usb相机智能指针对象
    /// \~english
    /// \brief Usb camera object access interface, same cameraPtr is correspond to same Usb camera object
    /// \param [in] cameraPtr Usb camera smart pointer object
    static IUsbInterfacePtr getInstance(const ICameraPtr &cameraPtr);

    /// \~chinese
    /// \brief  获取接口描述信息
    /// \return 返回接口描述信息，失败返回NULL
    /// \~english
    /// \brief get interface description information
    /// \return success:return interface description information, fail:return NULL
    virtual const char * getDescription() = 0;

    /// \~chinese
    /// \brief  获取接口的Vendor ID
    /// \return 返回接口的Vendor ID，失败返回NULL
    /// \~english
    /// \brief get interface's Vendor ID
    /// \return success:return interface's Vendor ID, fail:return NULL
    virtual const char * getVendorID() = 0;

    /// \~chinese
    /// \brief  获取接口的Device ID
    /// \return 返回接口的Device ID，失败返回NULL
    /// \~english
    /// \brief get interface's Device ID
    /// \return success:return interface's Device ID, fail:return NULL
    virtual const char * getDeviceID() = 0;

    /// \~chinese
    /// \brief 获取接口的Subsystem ID
    /// \return 返回接口的Subsystem ID，失败返回NULL
    /// \~english
    /// \brief get interface's Subsystem ID
    /// \return success:return interface's Subsystem ID, fail:return NULL
    virtual const char * getSubsystemID() = 0;

    /// \~chinese
    /// \brief  获取接口的Revision
    /// \return 返回接口的Revision，失败返回NULL
    /// \~english
    /// \brief get interface's Revision
    /// \return success:return interface's Revision, fail:return NULL
    virtual const char * getRevision() = 0;

    /// \~chinese
    /// \brief  获取接口的Speed
    /// \return 返回接口的Speed，失败返回NULL
    /// \~english
    /// \brief get interface's Speed
    /// \return success:return interface's Speed, fail:return NULL
    virtual const char * getSpeed() = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif//__DAHUA_GENICAM_IUSBINTERFACE_H__