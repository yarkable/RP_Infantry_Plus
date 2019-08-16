#ifndef __DAHUA_GENICAM_DIGITALIOCONTROL_H__
#define __DAHUA_GENICAM_DIGITALIOCONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class IDigitalIOControl;

typedef Memory::TSharedPtr<IDigitalIOControl> IDigitalIOControlPtr;

/// \ingroup config
/// @{

/// \~chinese
/// \brief Class IDigitalIOControl DigitalIOControl下属性操作类

/// \~english
/// \brief Class IDigitalIOControl DigitalIOControl's property operation class

class GENICAM_API IDigitalIOControl
{
public:
	/// \~chinese
	/// \brief 析构函数
	/// \~english
	/// \brief destructor
    virtual ~IDigitalIOControl() {}

public:
	/// \~chinese
	/// \brief 获取LineSelector属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get LineSelector's property operation object which can be read and written 
	/// \return property operation object
    virtual CEnumNode lineSelector() = 0;

	/// \~chinese
	/// \brief 获取LineDebouncerTimeAbs属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get LineDebouncerTimeAbs's property operation object which can be read and written 
	/// \return roperty operation object
	virtual CDoubleNode lineDebouncerTimeAbs() = 0;

	/// \~chinese
	/// \brief 获取LineSource属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get LineSource's property operation object which can be read and written  
	/// \return property operation object	
	virtual CEnumNode LineSource() = 0;

	/// \~chinese
	/// \brief 获取UserOutputSelector属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get UserOutputSelector's property operation object which can be read and written  
	/// \return property operation object	
	virtual CEnumNode userOutputSelector() = 0;

	/// \~chinese
	/// \brief 获取UserOutputValue属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get UserOutputValue's property operation object which can be read and written 
	/// \return property operation object	
	virtual CBoolNode userOutputValue() = 0;

};

/// @}

GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_DIGITALIOCONTROL_H__
