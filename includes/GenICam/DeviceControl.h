#ifndef __DAHUA_GENICAM_DEVICECONTROL_H__
#define __DAHUA_GENICAM_DEVICECONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class IDeviceControl;

typedef Memory::TSharedPtr<IDeviceControl> IDeviceControlPtr;

/// \ingroup config
/// @{

/// \~chinese
/// \brief Class IDeviceControl DeviceControl下属性操作类
/// \~english
/// \brief Class IDeviceControl DeviceControl operation class
class GENICAM_API IDeviceControl
{
public:
	/// \~chinese
	/// \brief 析构函数
	/// \~english
	/// \brief  destruct function 
	virtual ~IDeviceControl() {}

public:

	/// \~chinese
	/// \brief 获取DeviceUserID属性操作对象，该对象可读写
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get DeviceUserID property operation object, it can be written and read.
	/// \return  property operation object
	virtual CStringNode deviceUserID() = 0;

	/// \~chinese
	/// \brief 获取DeviceVersion属性操作对象，该对象为只读
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get DeviceVersion property operation object, it always can be read.
	/// \return  property operation object
	virtual CStringNode DeviceVersion() = 0;
};

/// @}
GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_DEVICECONTROL_H__
