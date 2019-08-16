#ifndef __DAHUA_GENICAM_IEVENTSUBSCRIBE_H__
#define __DAHUA_GENICAM_IEVENTSUBSCRIBE_H__

#include "Defs.h"
#include "Memory/SharedPtr.h"
#include "Infra/Function.h"
#include "Infra/Vector.h"
#include "Infra/String.h"

GENICAM_NAMESPACE_BEGIN

/// \~chinese
/// \brief Struct 连接事件参数封装
/// \~english
/// \brief Struct connection event parameters encapsulation
struct SConnectArg
{
	enum EVType
	{
		offLine,   ///< \~chinese 设备离线通知    ///< \~english device offline notification
		onLine     ///< \~chinese 设备在线通知 	  ///< \~english device online notification
	};
	EVType m_event;  		///< \~chinese 事件类型    ///< \~english event type
	uint32_t reserve[15];   ///< \~chinese 预留字段    ///< \~english reserved field
};

/// \~chinese
/// \brief Struct 参数更新事件参数封装
/// \~english
/// \brief Struct updating parameters event encapsulation
struct SParamUpdataArg
{
	bool isPoll; 					   ///< \~chinese 是否是定时更新,1表示是定时更新，0表示非定时更新   ///< \~english update periodically or not. 1 : update periodically, 0 : not update periodically
	uint32_t reserve[10];		       ///< \~chinese 预留字段                 ///< \~english reserved field
	Infra::TVector<Infra::CString>  paramNames; ///< \~chinese 更新的参数名称集合,约定更新的参数不超过1000个，每个参数的字符串长度不超过256  ///< \~english array of parameter's name which need to be updated. the maximum number of parameters is 1000. and the max length of strings of each parameter is 255.
};

/// \~chinese
///枚举：流事件状态
/// \~english
/// enumeration:stream event status
enum EEventStatus
{
	streamEventNormal = 1,    ///< \~chinese 正常流事件		    ///< \~english normal stream event
	streamEventLostFrame = 2, ///< \~chinese 丢帧事件		    ///< \~english lost frame event
	streamEventLostPacket = 3,///< \~chinese 丢包事件		    ///< \~english lost packet event
	streamEventImageError = 4,    ///< \~chinese 图像错误事件		///< \~english error image event
	streamEventStreamChannelError     ///< \~chinese 取流错误事件 		///< \~english stream channel error event
};

/// \~chinese
/// \brief Struct 流事件参数封装
/// \~english
/// \brief Struct stream event parameters encapsulation
struct SStreamArg
{
	uint32_t     channel;            ///< \~chinese 流通道号         ///< \~english stream channel no.
	uint64_t     blockID;            ///< \~chinese 流数据BlockID    ///< \~english block ID of stream data
	uint64_t     timestamp;          ///< \~chinese 时间戳           ///< \~english event timestamp
	EEventStatus eStreamEventStatus; ///< \~chinese 流事件状态码     ///< \~english stream event status code
	uint32_t	 status;			 ///< \~chinese 事件状态错误码   ///< \~english status error code
	uint32_t reserve[9];			 ///< \~chinese 预留字段         ///< \~english reserved field
};

/// \~chinese
/// 消息通道事件ID列表
/// \~english
/// message channel event id list
#define MSG_EVENT_ID_EXPOSURE_END			0x9001
#define MSG_EVENT_ID_FRAME_TRIGGER			0x9002
#define MSG_EVENT_ID_FRAME_START			0x9003
#define MSG_EVENT_ID_ACQ_START				0x9004
#define MSG_EVENT_ID_ACQ_TRIGGER			0x9005
#define MSG_EVENT_ID_DATA_READ_OUT			0x9006

/// \~chinese
/// \brief Struct 消息通道事件参数封装
/// \~english
/// \brief Struct message channel event parameters encapsulation
struct SMsgChannelArg
{
	uint16_t  eventID;         ///< \~chinese 事件Id			///< \~english event id
	uint16_t  channelID;       ///< \~chinese 消息通道号		///< \~english channel id
	uint64_t  blockID;		   ///< \~chinese 流数据BlockID		///< \~english block ID of stream data
	uint64_t  timeStamp;       ///< \~chinese 时间戳			///< \~english event timestamp
	uint32_t    reserve[8];   ///< \~chinese 预留字段         ///< \~english reserved field
	Infra::TVector<Infra::CString>  paramNames;   ///< \~chinese 事件相关的属性名列表。约定属性名不超过1000个，每个属性名的字符串长度不超过256  ///< \~english array of parameter's name which is related. the maximum number of parameters is 1000. and the max length of strings of each parameter is 255.
};

/// \~chinese
/// \brief 设备连接状态事件回调函数声明
/// \~english
/// \brief call back function declaration of camera connection status event 
typedef Infra::TFunction1<void, const SConnectArg&> ConnectArgProc;

/// \~chinese
/// \brief 设备连接状态事件回调函数声明
/// \~english
/// \brief call back function declaration of camera connection status event 
typedef Infra::TFunction2<void, const SConnectArg&, void*> ConnectArgProcEx;

/// \~chinese
/// \brief 参数更新事件回调函数声明
/// \~english
/// \brief call back function declaration of camera parameter update event 
typedef Infra::TFunction1<void, const SParamUpdataArg&> ParamUpdataProc;

/// \~chinese
/// \brief 参数更新事件回调函数声明
/// \~english
/// \brief call back function declaration of camera parameter update event 
typedef Infra::TFunction2<void, const SParamUpdataArg&, void*> ParamUpdataProcEx;

/// \~chinese
/// \brief 设备流事件回调函数声明
/// \~english
/// \brief call back function declaration of stream event 
typedef Infra::TFunction1<void, const SStreamArg&> StreamArgProc;

/// \~chinese
/// \brief 设备流事件回调函数声明
/// \~english
/// \brief call back function declaration of stream event 
typedef Infra::TFunction2<void, const SStreamArg&, void*> StreamArgProcEx;

/// \brief 消息通道事件回调函数声明
/// \~english
/// \brief call back function declaration of message channel event 
typedef Infra::TFunction1<void, const SMsgChannelArg&> MsgChannelProc;

/// \brief 消息通道事件回调函数声明
/// \~english
/// \brief call back function declaration of message channel event 
typedef Infra::TFunction2<void, const SMsgChannelArg&, void*> MsgChannelProcEx;

/// \~chinese
/// \brief 事件注册回调对象接口类
/// \defgroup Event 相机事件订阅注册与去注册接口
/// @{
/// \~english
/// \brief event register callback function interface class
/// \defgroup Event Event Notification subscribe and unsubscribe interface
/// @{

/// \~chinese
/// \brief Class IEventSubscribe 事件注册回调对象接口类，其中包括设备状态事件、流通道事件及参数更新事件
/// \~english
/// \brief Class IEventSubscribe Event subscribe callback object interface class，including device status events、stream channel events and parameter update events

class GENICAM_API IEventSubscribe
{
public:
	/// \~chinese
	/// \brief 析构函数
	/// \~english
	/// \brief destructor	
	virtual ~IEventSubscribe(){}

public:
	/// \~chinese
	/// \brief  设备连接状态事件回调注册
	/// \param [in] proc  设备连接状态事件回调注册函数
	/// \return 注册是否成功
	/// \~english
	/// \brief  regist call back function of camera connection status event. only one call back function is supported.
	/// \param [in] proc  call back function of camera connection status event
	/// \return the result of registration ( Success or fail )
	virtual bool subscribeConnectArgs(ConnectArgProc const& proc) = 0;

	/// \~chinese
	/// \brief  设备连接状态事件回调去注册
	/// \param [in] proc  设备连接状态事件回调去注册函数
	/// \return 去注册是否成功
	/// \~english
	/// \brief  unregister call back function of camera connection status event.
	/// \param [in] proc  Unregister call back function of camera connection status event
	/// \return the result of unregistration ( Success or fail )	
	virtual bool unsubscribeConnectArgs(ConnectArgProc const& proc) = 0;

	/// \~chinese
	/// \brief  参数更新事件回调注册
	/// \param [in] proc 参数更新注册的事件回调函数
	/// \return 注册是否成功
	/// \~english
	/// \brief  regist call back function of parameter update event. only one call back function is supported.
	/// \param [in] proc  call back function of parameter update event
	/// \return the result of registration	( Success or fail )
	virtual bool subscribeParamUpdate(ParamUpdataProc const& proc) = 0;

	/// \~chinese
	/// \brief  参数更新事件回调去注册
	/// \param [in] proc 参数更新事件去注册的回调函数
	/// \return 去注册是否成功
	/// \~english
	/// \brief  unregister call back function of parameter update event.
	/// \param [in] proc  unregister call back function of parameter update event
	/// \return the result of unregistration ( Success or fail )	
	virtual bool unsubscribeParamUpdate(ParamUpdataProc const& proc) = 0;

	/// \~chinese
	/// \brief  流通道事件回调注册
	/// \param [in] proc 流通道事件回调注册函数
	/// \return 注册是否成功
	/// \~english
	/// \brief  register call back function of stream channel event. only one call back function is supported.
	/// \param [in] proc  register call back function of stream channel event
	/// \return the result of registration ( Success or fail )	
	virtual bool subscribeStreamArg(StreamArgProc const& proc) = 0;

	/// \~chinese
	/// \brief  流通道事件回调去注册
	/// \param [in] proc  流通道事件回调去注册函数
	/// \return 去注册是否成功
	/// \~english
	/// \brief  unregister call back function of stream channel event.
	/// \param [in] proc  unregister call back function of tream channel event
	/// \return the result of unregistration ( Success or fail )	
	virtual bool unsubscribeStreamArg(StreamArgProc const& proc) = 0;

    /// \~chinese
    /// \brief  设备连接状态事件回调注册
    /// \param [in] proc  设备连接状态事件回调注册函数
    /// \param [in] pUser  用户自定义数据
    /// \return 注册是否成功
    /// \~english
    /// \brief  regist call back function of camera connection status event. only one call back function is supported.
    /// \param [in] proc  call back function of camera connection status event
    /// \param [in] pUser  user data
    /// \return the result of registration ( Success or fail )
    virtual bool subscribeConnectArgsEx(ConnectArgProcEx const& proc, void* pUser) = 0;

    /// \~chinese
    /// \brief  设备连接状态事件回调去注册
    /// \param [in] proc  设备连接状态事件回调去注册函数
    /// \param [in] pUser  用户自定义数据
    /// \return 去注册是否成功
    /// \~english
    /// \brief  unregister call back function of camera connection status event.
    /// \param [in] proc  Unregister call back function of camera connection status event
    /// \param [in] pUser  user data
    /// \return the result of unregistration ( Success or fail )	
    virtual bool unsubscribeConnectArgsEx(ConnectArgProcEx const& proc, void* pUser) = 0;

    /// \~chinese
    /// \brief  参数更新事件回调注册
    /// \param [in] proc 参数更新注册的事件回调函数
    /// \param [in] pUser  用户自定义数据
    /// \return 注册是否成功
    /// \~english
    /// \brief  regist call back function of parameter update event. only one call back function is supported.
    /// \param [in] proc  call back function of parameter update event
    /// \param [in] pUser  user data
    /// \return the result of registration	( Success or fail )
    virtual bool subscribeParamUpdateEx(ParamUpdataProcEx const& proc, void* pUser) = 0;

    /// \~chinese
    /// \brief  参数更新事件回调去注册
    /// \param [in] proc 参数更新事件去注册的回调函数
    /// \param [in] pUser  用户自定义数据
    /// \return 去注册是否成功
    /// \~english
    /// \brief  unregister call back function of parameter update event.
    /// \param [in] proc  unregister call back function of parameter update event
    /// \param [in] pUser  user data
    /// \return the result of unregistration ( Success or fail )
    virtual bool unsubscribeParamUpdateEx(ParamUpdataProcEx const& proc, void* pUser) = 0;

    /// \~chinese
    /// \brief  流通道事件回调注册
    /// \param [in] proc 流通道事件回调注册函数
    /// \param [in] pUser  用户自定义数据
    /// \return 注册是否成功
    /// \~english
    /// \brief  register call back function of stream channel event. only one call back function is supported.
    /// \param [in] proc  register call back function of stream channel event
    /// \param [in] pUser  user data
    /// \return the result of registration ( Success or fail )	
    virtual bool subscribeStreamArgEx(StreamArgProcEx const& proc, void* pUser) = 0;

    /// \~chinese
    /// \brief  流通道事件回调去注册
    /// \param [in] proc  流通道事件回调去注册函数
    /// \param [in] pUser  用户自定义数据
    /// \return 去注册是否成功
    /// \~english
    /// \brief  unregister call back function of stream channel event.
    /// \param [in] proc  unregister call back function of tream channel event
    /// \param [in] pUser  user data
    /// \return the result of unregistration ( Success or fail )
    virtual bool unsubscribeStreamArgEx(StreamArgProcEx const& proc, void* pUser) = 0;

	/// \~chinese
	/// \brief  消息通道事件回调注册
	/// \param [in] proc 消息通道事件回调注册函数
	/// \return 注册是否成功
	/// \~english
	/// \brief  register call back function of message channel event. only one call back function is supported.
	/// \param [in] proc  register call back function of message channel event
	/// \return the result of registration ( Success or fail )	
	virtual bool subscribeMsgChannel(MsgChannelProc const& proc) = 0;

	/// \~chinese
	/// \brief  消息通道事件回调去注册
	/// \param [in] proc  消息通道事件回调去注册函数
	/// \return 去注册是否成功
	/// \~english
	/// \brief  unregister call back function of message channel event.
	/// \param [in] proc  unregister call back function of message channel event
	/// \return the result of unregistration ( Success or fail )	
	virtual bool unsubscribeMsgChannel(MsgChannelProc const& proc) = 0;

	/// \~chinese
	/// \brief  消息通道事件回调注册
	/// \param [in] proc 消息通道事件回调注册函数
	/// \param [in] pUser  用户自定义数据
	/// \return 注册是否成功
	/// \~english
	/// \brief  register call back function of message channel event. only one call back function is supported.
	/// \param [in] proc  register call back function of message channel event
	/// \param [in] pUser  user data
	/// \return the result of registration ( Success or fail )	
	virtual bool subscribeMsgChannelEx(MsgChannelProcEx const& proc, void* pUser) = 0;

	/// \~chinese
	/// \brief  消息通道事件回调去注册
	/// \param [in] proc  消息通道事件回调去注册函数
	/// \param [in] pUser  用户自定义数据
	/// \return 去注册是否成功
	/// \~english
	/// \brief  unregister call back function of message channel event.
	/// \param [in] proc  unregister call back function of message channel event
	/// \param [in] pUser  user data
	/// \return the result of unregistration ( Success or fail )	
	virtual bool unsubscribeMsgChannelEx(MsgChannelProcEx const& proc, void* pUser) = 0;
};

typedef Memory::TSharedPtr<IEventSubscribe> IEventSubscribePtr;
/// @}

GENICAM_NAMESPACE_END
#endif //__DAHUA_GENICAM_IEVENTSUBSCRIBE_H__