#ifndef __DAHUA_GENICAM_IMAGEFORMATCONTROL_H__
#define __DAHUA_GENICAM_IMAGEFORMATCONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class IImageFormatControl;

typedef Memory::TSharedPtr<IImageFormatControl> IImageFormatControlPtr;

/// \ingroup config
/// @{

/// \~chinese
/// \brief Class IImageFormatControl ImageFormatControl下属性操作类
/// \~english
/// \brief Class ImageFormatControl's property operation class
class GENICAM_API IImageFormatControl
{
public:
	/// \~chinese
	/// \brief 析构函数
	/// \~english
	/// \brief destructor
	virtual ~IImageFormatControl() {}

public:
	/// \~chinese
	/// \brief 获取Height属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get Height property operation object
	/// \return property's object
	virtual CIntNode height() = 0;

	/// \~chinese
	/// \brief 获取Width属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get Width property operation object
	/// \return property's object	
	virtual CIntNode width() = 0;

	/// \~chinese
	/// \brief 获取OffsetX属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get offsetX property operation object
	/// \return property's object	
	virtual CIntNode offsetX() = 0;

	/// \~chinese
	/// \brief 获取OffsetY属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get OffsetY property operation object
	/// \return property's object	
	virtual CIntNode offsetY() = 0;

	/// \~chinese
	/// \brief 获取PixelFormat属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get PixelFormat property operation object
	/// \return property's object	
	virtual CEnumNode pixelFormat() = 0;

	/// \~chinese
	/// \brief 获取pixelFormat属性操作对象
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get PixelSize property operation object
	/// \return property's object	
	virtual CEnumNode PixelSize() = 0;

	/// \~chinese
	/// \brief 获取ReverseX属性操作对象，设置是否翻转图像X轴
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get ReverseX property operation object
	/// \return property's object	
	virtual CBoolNode reverseX() = 0;

	/// \~chinese
	/// \brief 获取ReverseY属性操作对象，设置是否翻转图像Y轴
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get ReverseY property operation object
	/// \return property's object		
	virtual CBoolNode reverseY() = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_IMAGEFORMATCONTROL_H__
