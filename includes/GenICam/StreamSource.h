#ifndef __DAHUA_GENICAM_ISTREAMSOURCE_H__
#define __DAHUA_GENICAM_ISTREAMSOURCE_H__

#include "Defs.h"
#include "Frame.h"
#include "Infra/Signal.h"

GENICAM_NAMESPACE_BEGIN

/// \~chinese
/// \brief 流对象接口类
/// \defgroup stream 流对象操作接口
/// @{
/// \~english
/// \brief stream object interface class
/// \defgroup stream Stream Operation Interface
/// @{

/// \~chinese
/// \brief Class IStreamSource 流对象接口
/// \~english
/// \brief Class IStreamSource stream object interface
class GENICAM_API IStreamSource
{
protected:
	/// \~chinese
	/// \brief 析构函数
	/// \~english
	/// \brief destructor
	virtual ~IStreamSource(){}
	
public:	

	enum EGrabStrategy
	{
		grabStrartegySequential  = 0,	///< \~chinese 按到达顺序处理图片	///< \~english The images are processed in the order of their arrival
		grabStrartegyLatestImage = 1,   ///< \~chinese 获取最新的图片		///< \~english get the latest image
		grabStrartegyUndefined   		///< \~chinese 未定义				///< \~english undefined
	};

	/// \~chinese	
	/// \brief 设备流回调函数声明:每次回调送出一帧数据
	/// CFrame 回调时主动推送的帧对象
	/// \~english
	/// \brief Callback function declaration of stream: Send out one frame at each time use callback function
	/// CFrame The frame which will be active pushed out during the callback
	typedef Infra::TSignal1<const CFrame&> Signal;
	typedef Signal::Proc Proc;

    /// \~chinese	
    /// \brief 设备流回调函数声明:每次回调送出一帧数据和用户数据
    /// CFrame 回调时主动推送的帧对象
    /// void*  回调时推送的用户数据
    /// \~english
    /// \brief Callback function declaration of stream: Send out one frame and user data at each time use callback function
    /// CFrame The frame which will be active pushed out during the callback
    /// void* The user data which will be active pushed out during the callback
    typedef Infra::TSignal2<const CFrame&, const void*> SignalEx;
    typedef SignalEx::Proc ProcEx;

	/// \~chinese
	/// \brief 开始抓图
	/// \param [in] maxImagesGrabbed 允许最多的抓图数，达到指定抓图数后停止抓图，如果为0，表示忽略此参数连续抓图
	/// \param [in] strategy 抓图策略,默认按缓存队列中的顺序抓图
	/// \return 返回抓图是否成功
	/// \~english
	/// \brief Start grabbing
	/// \param [in] maxImagesGrabbed Maximum images allowed to grab, once it reaches the limit then stop grabbing; If it is 0, then ignore this parameter and start grabbing continuously
	/// \param [in] strategy Image grabbing strategy; Image grabbing according to the order in buffer queue is default
	/// \return success:true, fail:false
	virtual bool startGrabbing(uint64_t maxImagesGrabbed = 0,EGrabStrategy strategy = grabStrartegySequential) = 0;
					
	/// \~chinese
	/// \brief 停止抓图
	/// \return 返回停止抓图是否成功
	/// \~english
	/// \brief Stop grabbing
	/// \return success:true, fail:false
	virtual bool stopGrabbing() = 0;
							
	/// \~chinese
	/// \brief 是否正在抓图
	/// \return 返回是否成功
	/// \~english 
	/// \brief Check whether it is grabbing or not
	/// \return grabbing or not grabbing, true means it is grabbing, false means it is not grabbing
	virtual bool isGrabbing() = 0;
				
	/// \~chinese
	/// \brief 获取一帧图像，该接口不支持多线程调用
	/// \param [out] frame 一帧图像
	/// \param [in]  timeoutMS 获取一帧图像的超时时长,单位MS,当值为INFINITE时表示无限等待
	/// \return 返回是否成功
	/// \~english
	/// \brief get a frame image, and this interface does not support multi-threading
	/// \param [out] frame one frame
	/// \param [in]  timeoutMS The timeout value of getting one image, unit is MS; When the value is INFINITE which means infinite wait
	/// \return success:true, fail:false
	virtual bool getFrame(CFrame &frame,uint32_t timeoutMS = INFINITE) const = 0;

	/// \~chinese
	/// \brief 注册数据帧回调函数。该异步获取帧机制和同步获取帧机制互斥，系统中两者只能选其一。
	/// \param [in] proc 数据帧回调函数，建议不要在该函数中处理耗时的操作，否则会阻塞后续数据帧的实时性
	/// \return 返回注册是否成功
	/// \~english
	/// \brief Register data frame callback function; This asynchronous frame acquisition mechanism and synchronous frame acquisition mechanism are mutually exclusive, only one method can be choosed between these two in system
	/// \brief only callback one function 
	/// \param [in] proc Data frame callback function; It is advised to not put time-cosuming operation in this function, otherwise it will block follow-up data frames and affect real time performance
	/// \return success:true, fail:false
	virtual bool attachGrabbing(Proc proc) = 0;

	/// \~chinese
	/// \brief 去注册数据帧回调函数
	/// \param [in] proc 去注册数据帧回调函数
	/// \return 返回去注册是否成功
	/// \~english
	/// \brief Unregister data frame callback function
	/// \param [in] proc Unregister data frame callback function
	/// \return success:true, fail:false
	virtual bool detachGrabbing(Proc proc) = 0;
	
	/// \~chinese
    /// \brief 设置缓存个数,不能在拉流过程中设置
    /// \param [in]  nSize 缓存数量，最大为200
    /// \return 返回是否成功
	/// \~english
	/// \brief Set buffer count, this cannot be set during frame grabbing
	/// \param [in]  nSize the buffer count， max size is 200.
	/// \return success:true, fail:false
    virtual bool setBufferCount(uint32_t nSize) = 0;

    /// \~chinese
    /// \brief 注册数据帧回调函数(包含用户自定义数据)。
    /// \param [in] proc 数据帧回调函数，建议不要在该函数中处理耗时的操作，否则会阻塞后续数据帧的实时性
    /// \param [in] pUser 用户自定义数据
    /// \return 返回注册是否成功
    /// \~english
    /// \brief Register data frame callback function(include user defined data); 
    /// \param [in] proc Data frame callback function; It is advised to not put time-cosuming operation in this function, otherwise it will block follow-up data frames and affect real time performance
    /// \param [in] pUser user defined data
    /// \return success:true, fail:false
    virtual bool attachGrabbingEx(ProcEx proc, void* pUser) = 0;

    /// \~chinese
    /// \brief 去注册数据帧回调函数(包含用户自定义数据)
    /// \param [in] proc 去注册数据帧回调函数
    /// \param [in] pUser 用户自定义数据(与attachGrabbingEx的pUser相同)
    /// \return 返回去注册是否成功
    /// \~english
    /// \brief	Unregister data frame callback function(include user defined data)
    /// \param [in] proc Unregister data frame callback function(the same pUser of the attachGrabbingEx)
    /// \param [in] pUser user defined data
    /// \return success:true, fail:false
    virtual bool detachGrabbingEx(ProcEx proc, void* pUser) = 0;

    /// \~chinese
    /// \brief 设置驱动包间隔时间(ms),仅对Gige设备有效
    /// \param [in] nTimeout 包间隔时间，单位ms
    /// \return 设置是否成功,true表示成功，false表示失败
    /// \~english
    /// \brief	set packet timeout(ms), just for GigE devices
    /// \param [in] the value of timeout
    /// \return success:true, fail:false
    virtual bool setInterPacketTimeout(uint32_t nTimeout) = 0;
};

typedef Memory::TSharedPtr<IStreamSource> IStreamSourcePtr;
/// @}

GENICAM_NAMESPACE_END

#endif //__DAHUA_GENICAM_ISTREAMSOURCE_H__