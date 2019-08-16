#ifndef __DAHUA_GENICAM_ACQUISITIONCONTROL_H__
#define __DAHUA_GENICAM_ACQUISITIONCONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class IAcquisitionControl;

typedef Memory::TSharedPtr<IAcquisitionControl> IAcquisitionControlPtr;

/// \ingroup config
/// @{

/// \~chinese
/// \brief Class IAcquisitionControl AcquisitionControl下属性操作类
/// \~english
/// \brief GENICAM_AcquisitionControl's property operation class
class GENICAM_API IAcquisitionControl
{
public:
	/// \~chinese
	/// \brief 析构函数
	/// \~english
	/// \brief destructor function
	virtual ~IAcquisitionControl() {}

public:
	/// \~chinese
	/// \brief 获取AcquisitionFrameCount属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get AcquisitionFrameCount property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CIntNode acquisitionFrameCount() = 0;

	/// \~chinese
	/// \brief 获取AcquisitionFrameRate属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get AcquisitionFrameRate property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CDoubleNode acquisitionFrameRate() = 0;

	/// \~chinese
	/// \brief 获取AcquisitionFrameRate属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get AcquisitionFrameRate property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode acquisitionMode() = 0;

	/// \~chinese
	/// \brief 获取ExposureAuto属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get ExposureAuto property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode exposureAuto() = 0;

	/// \~chinese
	/// \brief 获取ExposureMode属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get ExposureMode property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode exposureMode() = 0;

	/// \~chinese
	/// \brief 获取ExposureTime属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get ExposureTime property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CDoubleNode exposureTime() = 0;

	/// \~chinese
	/// \brief 获取TriggerActivation属性操作对象，设置触发上升沿下降沿
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get TriggerActivation property's operation object,set TriggerActivation in RisingEdge or FallingEdge
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode triggerActivation() = 0;

	/// \~chinese
	/// \brief 获取TriggerDelay属性操作对象，设置软触发延时
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get TriggerDelay property's operation object, set software trigger delay
	/// \return success:return property operation object, fail:return NULL
	virtual CDoubleNode triggerDelay() = 0;

	/// \~chinese
	/// \brief 获取TriggerMode属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get TriggerMode property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode triggerMode() = 0;

	/// \~chinese
	/// \brief 获取TriggerSelector属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get TriggerSelector property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode triggerSelector() = 0;

	/// \~chinese
	/// \brief 获取TriggerSource属性操作对象，设置内部/外部触发
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get TriggerSource property's operation object, set internal/external trigger
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode triggerSource() = 0;

	/// \~chinese
	/// \brief 获取TriggerSoftware属性操作对象，执行内部软触发
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get TriggerSoftware property's operation object, execute internal software trigger
	/// \return success:return property operation object, fail:return NULL
	virtual CCmdNode triggerSoftware() = 0;

	/// \~chinese
	/// \brief 获取AcquisitionFrameRateEnable使能属性操作对象
	/// \return 返回属性操作对象
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get AcquisitionFrameRateEnable property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CBoolNode acquisitionFrameRateEnable() = 0;

	/// \~chinese
	/// \brief 获取acquisitionLineRate属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get acquisitionLineRate property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CDoubleNode acquisitionLineRate() = 0;

	/// \~chinese
	/// \brief 获取acquisitionLineRateEnable使能属性操作对象
	/// \return 返回属性操作对象
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get acquisitionLineRateEnable property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CBoolNode acquisitionLineRateEnable() = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_ACQUISITIONCONTROL_H__
