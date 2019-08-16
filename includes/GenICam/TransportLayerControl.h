#ifndef __DAHUA_GENICAM_TRANSPORTLAYERCONTROL_H__
#define __DAHUA_GENICAM_TRANSPORTLAYERCONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class ITransportLayerControl;

typedef Memory::TSharedPtr<ITransportLayerControl> ITransportLayerControlPtr;

/// \ingroup config
/// @{

/// \~chinese
/// \brief Class ITransportLayerControl TransportLayerControl下属性操作类
/// \~english
/// \brief Class ITransportLayerControl TransportLayerControl property's operation class 
class GENICAM_API ITransportLayerControl
{
public:
	virtual ~ITransportLayerControl() {}

public:
	/// \~chinese
	/// \brief 获取GevSCPD属性操作对象，设置包发送间隔
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get GevSCPD property operation object, set packet sending interval 
	/// \return property operation object
	virtual CIntNode gevSCPD() = 0;

	/// \~chinese
	/// \brief 获取GevCurrentIPConfigurationDHCP属性操作对象，是否启用DHCP
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get GevCurrentIPConfigurationDHCP property operation object, check whether activate DHCP or not
	/// \return property operation object
	virtual CBoolNode gevCurrentIPConfigurationDHCP() = 0;

	/// \~chinese
	/// \brief 获取GevCurrentIPConfigurationPersistentIP属性操作对象，是否启用静态IP
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get GevCurrentIPConfigurationPersistentIP property operation object, check whether activate static IP or not
	/// \return property operation object
	virtual CBoolNode gevCurrentIPConfigurationPersistentIP() = 0;

	/// \~chinese
	/// \brief 获取GevPersistentIPAddress属性操作对象，设置静态IP地址
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get GevPersistentIPAddress property operation object, set static IP
	/// \return property operation object
	virtual CStringNode gevPersistentIPAddress() = 0;

	/// \~chinese
	/// \brief 获取GevPersistentSubnetMask属性操作对象，设置静态IP子网掩码
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get GevPersistentSubnetMask property operation object, set static IP subnet mask
	/// \return property operation object
	virtual CStringNode gevPersistentSubnetMask() = 0;

	/// \~chinese
	/// \brief 获取GevPersistentDefaultGateway属性操作对象，设置静态IP网关
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get GevPersistentDefaultGateway property operation object, set static IP gateway
	/// \return property operation object
	virtual CStringNode gevPersistentDefaultGateway() = 0;

    /// \~chinese
    /// \brief 获取GevGVCPHeartbeatDisable属性操作对象，是否停用GVCP Heartbeat
    /// \return 返回属性操作对象
	/// \~english
	/// \brief get GevGVCPHeartbeatDisable property operation object, check whether disable GVCP Heartbeat or not
	/// \return property operation object
    virtual CBoolNode gevGVCPHeartbeatDisable() = 0;

	/// \~chinese
	/// \brief 获取GevGVSPExtendedIDMode属性操作对象，是否启用ChunkData
	/// \return 返回属性操作对象
	/// \~english
	/// \brief get GevGVSPExtendedIDMode property operation object, check whether disable GVCP ChunkData or not
	/// \return property operation object
	virtual CEnumNode gevGVSPExtendedIDMode() = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_TRANSPORTLAYERCONTROL_H__

