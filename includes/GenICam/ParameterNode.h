#ifndef __DAHUA_GENICAM_GENERAL_PARAMETERS_H__
#define __DAHUA_GENICAM_GENERAL_PARAMETERS_H__

#include "Defs.h"
#include "Camera.h"
#include "Infra/CString.h"

GENICAM_NAMESPACE_BEGIN

class CIntNode;
class CDoubleNode;
class CEnumNode;
class CBoolNode;
class CCmdNode;
class CStringNode;

typedef Memory::TSharedPtr<CIntNode> CIntNodePtr;
typedef Memory::TSharedPtr<CDoubleNode> CDoubleNodePtr;
typedef Memory::TSharedPtr<CEnumNode> CEnumNodePtr;
typedef Memory::TSharedPtr<CBoolNode> CBoolNodePtr;
typedef Memory::TSharedPtr<CCmdNode> CCmdNodePtr;
typedef Memory::TSharedPtr<CStringNode> CStringNodePtr;


/// \~chinese
/// \brief 常用参数对象接口
/// \defgroup config 属性配置相关操作接口
/// \~english
/// \brief common parameter object interface
/// \defgroup config Property Operation interface
/// @{

/// \~chinese
/// \brief Class CNodeBase 属性操作基类接口 
/// \~english
/// \brief Class CNodeBase property operation base class interface
class GENICAM_API CNodeBase
{
public:
	virtual ~CNodeBase();

public:
	/// \~chinese
	/// \brief 属性是否可用
	/// \return 可用返回true，否则返回false
	/// \~english
	/// \brief check the property is available or not
	/// \return available:true, not available:false
	bool isAvailable() const;

	/// \~chinese
	/// \brief 属性是否可读
	/// \return 可读返回true，否则返回false
	/// \~english
	/// \brief check the property is readable or not
	/// \return readable:true, not readable:false
	bool isReadable() const;

	/// \~chinese
	/// \brief 属性是否可写
	/// \return 可写返回true，否则返回false
	/// \~english
	/// \brief check the property is writeable or not
	/// \return writeable:true, not writeable:false
	bool isWriteable() const;

	/// \~chinese
	/// \brief 属性是否Streamable
	/// \return 是则返回true，否则返回false
	/// \~english
	/// \brief check the property is streamable or not
	/// \return streamable:true, not streamable:false
	bool isStreamable() const;

	/// \~chinese
	/// \brief 判断属性是否有效
	/// \return 是则返回true，否则返回false
	/// \~english
	/// \brief check the property is valid or not
	/// \return valid:true, invalid:false
	bool isValid() const;

protected:
	CNodeBase(const ICameraPtr& ptrCamera, const char* pParamName);
	CNodeBase(const CNodeBase& other);
	CNodeBase& operator= (const CNodeBase& other);

protected:
	class	Impl;
	Impl*	m_pImpl;
};

/// \~chinese
/// \brief Class IIntNode 整型属性操作类
/// \~english
/// \brief Class IIntNode integer property operation class
class GENICAM_API CIntNode : public CNodeBase
{
public:
	CIntNode(const ICameraPtr& ptrCamera, const char* pParamName);
	~CIntNode();

public:
	/// \~chinese
	/// \brief 获取属性值
	/// \param [out] val 获取到的属性值
	/// \return 成功返回true，否则false
	/// \~english
	/// \brief get property's value
	/// \param [out] val the property's value
	/// \return success:true, fail:false
	bool getValue(int64_t& val) const;

	/// \~chinese
	/// \brief 设置属性值
	/// \param [in] val 待设置的属性值
	/// \return 成功则返回true，否则返回false
	/// \~english
	/// \brief set the property's value
	/// \param [in] val the value to be set for this property
	/// \return success:true, fail:false
	bool setValue(int64_t val);

	/// \~chinese
	/// \brief 获取属性可设最小值
	/// \param [out] val 获取到的属性最小值
	/// \return 成功返回true，否则false
	/// \~english
	/// \brief get the property's minimum value that can be set
	/// \param [out] val the property's minimum value
	/// \return success:true, fail:false
	bool getMinVal(int64_t& val) const;

	/// \~chinese
	/// \brief 获取属性可设最大值
	/// \param [out] val 获取到的属性最大值
	/// \return 成功返回true，否则false
	/// \~english
	/// \brief get the property's maximum value that can be set
	/// \param [out] val the property's maximum value
	/// \return success:true, fail:false
	bool getMaxVal(int64_t& val) const;

	/// \~chinese
	/// \brief 获取属性步长
	/// \param [out] val 获取到的属性步长
	/// \return 成功返回true，否则false
	/// \~english
	/// \brief get property's increment
	/// \param [out] val the property's increment
	/// \return success:true, fail:false
	bool getIncrement(int64_t& val) const;
};

/// \~chinese
/// \brief Class IDoubleNode 浮点数属性操作类
/// \~english
/// \brief Class IDoubleNode float property operation class
class GENICAM_API CDoubleNode : public CNodeBase
{
public:
	CDoubleNode(const ICameraPtr& ptrCamera, const char* pParamName);
	~CDoubleNode();

public:
	/// \~chinese
	/// \brief 获取属性值
	/// \param [out] val 获取到的属性值
	/// \return 成功返回true，否则false
	/// \~english
	/// \brief get property's value
	/// \param [out] val the property's value
	/// \return success:true, fail:false
	bool getValue(double& val) const;

	/// \~chinese
	/// \brief 设置属性值
	/// \param [in] val 待设置的属性值
	/// \return 成功则返回true，否则返回false
	/// \~english
	/// \brief set property's value
	/// \param [in] val the value to be set for this property
	/// \return success:true, fail:false
	bool setValue(double val);

	/// \~chinese
	/// \brief 获取属性可设最小值
	/// \param [out] val 获取到的属性最小值
	/// \return 成功返回true，否则false
	/// \~english
	/// \brief get the property's minimum value that can be set
	/// \param [out] val the property's minimum value
	/// \return success:true, fail:false
	bool getMinVal(double& val) const;

	/// \~chinese
	/// \brief 获取属性可设最大值
	/// \param [out] val 获取到的属性最大值
	/// \return 成功返回true，否则false
	/// \~english
	/// \brief get the property's maximum value that can be set
	/// \param [out] val the property's maximum value
	/// \return success:true, fail:false
	bool getMaxVal(double& val) const;
};

/// \~chinese
/// \brief Class IEnumNode 枚举型属性操作类
/// \~english
/// \brief  Class IEnumNode EnumNode property operation class
class GENICAM_API CEnumNode : public CNodeBase
{
public:
	CEnumNode(const ICameraPtr& ptrCamera, const char* pParamName);
	~CEnumNode();

public:
	/// \~chinese
	/// \brief 获取枚举属性symbol值
	/// \param [out] val  获取到的属性值
	/// \return 成功返回true，否则false
	/// \~english
	/// \brief get symbol value of enum property
	/// \param [out] val the property's value
	/// \return success:true, fail:false
	bool getValueSymbol(Infra::CString& val) const;

	/// \~chinese
	/// \brief 设置枚举属性symbol值
	/// \param [in] strSymbolName 待设置的属性值
	/// \return 成功则返回true，否则返回false
	/// \~english
	/// \brief set symbol value of enum property 
	/// \param [in] strSymbolName the value waiting to be set for this property
	/// \return success:true, fail:false
	bool setValueBySymbol(const Infra::CString& strSymbolName);

	/// \~chinese
	/// \brief 获取枚举属性可设置的symbol值列表
	/// \return 返回属性当前可设置symbol值列表
	/// \~english
	/// \brief Get the list of Enum property symbol value which can be set
	/// \return Return the list of Enum property symbol value which can be set now
	Infra::TVector<Infra::CString> getEnumSymbolList() const;

	/// \~chinese
	/// \brief 设置枚举属性value值
	/// \param [in] val 待设置的枚举值
	/// \return 成功则返回true，否则返回false
	/// \~english
	/// \brief set symbol value of enum property 
	/// \param [in] val the value waiting to be set for this property
	/// \return success:true, fail:false
	bool setValue(uint64_t val);

	/// \~chinese
	/// \brief 获取枚举属性value值
	/// \param [out] val 获取到的枚举值
	/// \return 成功返回true，否则false
	/// \~english
	/// \brief get symbol value of enum property
	/// \param [out] val the property's value
	/// \return success:true, fail:false
	bool getValue(uint64_t &val) const;

	/// \~chinese
	/// \brief 通过symbol获取枚举的value值
	/// \param [in]  strSymbolName 枚举字符串
	/// \param [out] val 获取到的枚举值
	/// \return 成功返回true，否则false
	/// \~english
	/// \brief get symbol value of enum property by symbol string
	/// \param [in] strSymbolName the property's string
	/// \param [out] val the property's value
	/// \return success:true, fail:false
	bool getValueBySymbol(Infra::CString strSymbolName, uint64_t &val) const;

	/// \~chinese
	/// \brief 通过value获取枚举的symbol值
	/// \param [in] val 枚举值
	/// \param [out] strSymbolName 获取到的枚举字符串
	/// \return 成功返回true，否则false
	/// \~english
	/// \brief get symbol of enum property by value
	/// \param [in]  val the property's value
	/// \param [out] strSymbolName the property's string
	/// \return success:true, fail:false
	bool getSymbolByValue(uint64_t val, Infra::CString &strSymbolName) const;
};

/// \~chinese
/// \brief Class IBoolNode 布尔型属性操作类
/// \~english
/// \brief Class IBoolNode BoolNode property operation class
class GENICAM_API CBoolNode : public CNodeBase
{
public:
	CBoolNode(const ICameraPtr& ptrCamera, const char* pParamName);
	~CBoolNode();

public:
	/// \~chinese
	/// \brief 获取属性值
	/// \param [out] val 获取到的属性值
	/// \return 成功返回true，否则false
	/// \~english
	/// \brief get property's value
	/// \param [out] val the property's value
	/// \return success:true, fail:false
	bool getValue(bool& val) const;

	/// \~chinese
	/// \brief 设置属性值
	/// \param [in] val 待设置的属性值
	/// \return 成功则返回true，否则返回false
	/// \~english
	/// \brief set property's value
	/// \param [in] val the value to be set for this property
	/// \return success:true, fail:false
	bool setValue(bool val);
};

/// \~chinese
/// \brief Class ICmdNode 命令型属性操作类
/// \~english
/// \brief Class ICmdNode CmdNode property operation class
class GENICAM_API CCmdNode : public CNodeBase
{
public:
	CCmdNode(const ICameraPtr& ptrCamera, const char* pParamName);
	~CCmdNode();

public:
	/// \~chinese
	/// \brief 执行命令类型属性
	/// \return 成功则返回true，否则返回false
	/// \~english
	/// \brief execute command property
	/// \return success:true, fail:false
	bool execute();
};

/// \~chinese
/// \brief Class IStringNode 命令型属性操作类
/// \~english
/// \brief Class IStringNode StringNode property operation class
class GENICAM_API CStringNode : public CNodeBase
{
public:
	CStringNode(const ICameraPtr& ptrCamera, const char* pParamName);
	~CStringNode();

public:
	/// \~chinese
	/// \brief 获取属性值
	/// \param [out] outStr 获取到的属性值
	/// \return 成功返回true，否则false
	/// \~english
	/// \brief get property's value
	/// \param [out] outStr the property's value
	/// \return success:true, fail:false
	bool getValue(Infra::CString &outStr);

	/// \~chinese
	/// \brief 设置属性值
	/// \param [in] inStr 待输入的属性值
	/// \return 成功则返回true，否则返回false
	/// \~english
	/// \brief set the property's value
	/// \param [in] inStr the value to be set for this property
	/// \return success:true, fail:false
	bool setValue(const Infra::CString &inStr);
};

/// @}
GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_GENERAL_PARAMETERS_H__
