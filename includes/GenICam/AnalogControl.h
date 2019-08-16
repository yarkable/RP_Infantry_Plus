	#ifndef __DAHUA_GENICAM_ANALOGCONTROL_H__
#define __DAHUA_GENICAM_ANALOGCONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class IAnalogControl;

typedef Memory::TSharedPtr<IAnalogControl> IAnalogControlPtr;

/// \ingroup config
/// @{

/// \~chinese
/// \brief Class IAnalogControl AnalogControl下属性操作类
/// \~english
/// \brief GENICAM_AnalogControl's property operation class
class GENICAM_API IAnalogControl
{
public:
	/// \~chinese
	/// \brief 析构函数
	/// \~english
	/// \brief destruct function
	virtual ~IAnalogControl() {}

public:
	/// \~chinese
	/// \brief 获取BlackLevelSelector属性操作对象，设置操作哪个白平衡
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get BlackLevelSelector property operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode blackLevelSelector() = 0;

	/// \~chinese
	/// \brief 获取BlackLevelAuto属性操作对象，设置自动白平衡
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get BalanceWhiteAuto property operation object, set auto white balance
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode blackLevelAuto() = 0;

	/// \~chinese
	/// \brief 获取BlackLevel属性操作对象，设置白平衡值
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get BlackLevel property operation object, set black level
	/// \return success:return property operation object, fail:return NULL
	virtual CIntNode blackLevel() = 0;

	/// \~chinese
	/// \brief 获取GainAuto属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get GainAuto property operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode gainAuto() = 0;

	/// \~chinese
	/// \brief 获取GainRaw属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get GainRaw operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CDoubleNode gainRaw() = 0;

	/// \~chinese
	/// \brief 获取Gamma属性操作对象，设置Gamma值
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get Gamma operation object, set gamma
	/// \return success:return property operation object, fail:return NULL
	virtual CDoubleNode gamma() = 0;

	/// \~chinese
	/// \brief 获取BalanceRatioSelector属性操作对象，设置操作哪个白平衡
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get BalanceRatioSelector property operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode balanceRatioSelector() = 0;

	/// \~chinese
	/// \brief 获取BalanceWhiteAuto属性操作对象，设置自动白平衡
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get BalanceWhiteAuto property operation object, set auto white balance
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode balanceWhiteAuto() = 0;

	/// \~chinese
	/// \brief 获取BalanceRatio属性操作对象，设置白平衡值
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get BalanceRatioSelector property operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CDoubleNode balanceRatio() = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_ANALOGCONTROL_H__

