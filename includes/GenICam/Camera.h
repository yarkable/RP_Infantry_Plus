#ifndef __DAHUA_GENICAM_ICAMERA_H__
#define __DAHUA_GENICAM_ICAMERA_H__

#include "Defs.h"
#include "Frame.h"
#include "Memory/SharedPtr.h"
#include "StreamSource.h"

GENICAM_NAMESPACE_BEGIN

/// \~chinese
/// \brief 相机对象接口类
/// \defgroup Camera 相机共用操作接口
/// @{
/// \~english
/// \brief Camera Object Interface Class
/// \defgroup Camera Camera's Common Operation Interface
/// @{

/// \~chinese
/// \brief Class ICamera 相机对象接口类，表示一台相机，所有协议类型都可共用的接口。该实例对象可通过CSystem获取
/// \~english
/// \brief Class ICamera Camera Object Interface Class, it means a common interface for all protocol type; This instance object can be got by CSystem 
class GENICAM_API ICamera
{
protected:
	/// \~chinese
	/// \brief 析构函数
	/// \~english
	/// \brief destruct function
	virtual ~ICamera(){}
	
public:

	enum ECameraAccessPermission
	{
		accessPermissionOpen = 0,		///< \~chinese GigE相机没有被连接        ///< \~english The GigE vision device isn't connected to any application. 
		accessPermissionExclusive, 	///< \~chinese 独占访问权限        ///< \~english Exclusive Access Permission   
		accessPermissionControl, 	///< \~chinese 非独占可读访问权限  ///< \~english Non-Exclusive Readbale Access Permission  
		accessPermissionControlWithSwitchover,  	///< \~chinese Control access with switchover enabled.        ///< \~english Control access with switchover enabled.	
		accessPermissionUnknown = 254,  	///< \~chinese 无法确定        ///< \~english Value not known; indeterminate.   	
		accessPermissionUndefined     	///< \~chinese 未定义访问权限      ///< \~english Undefined Access Permission
	};

	enum ECameraType
	{
		typeGige = 0,	    ///< \~chinese GIGE相机       ///< \~english GigE Vision Camera
		typeU3v = 1,	    ///< \~chinese USB3.0相机     ///< \~english USB3.0 Vision Camera
        typeCL = 2,		    ///< \~chinese CAMERALINK 相机///< \~english Cameralink camera
        typePCIe = 3,       ///< \~chinese PCIe相机       ///< \~english PCIe Camera
		typeUndefined = 255	///< \~chinese 未知类型       ///< \~english Undefined Camera
	};
	
	/// \~chinese
	/// \brief  得到相机类型
	/// \return 返回相机类型
	/// \~english
	/// \brief  get Camera Type
	/// \return Success: Camera Type, Failure:typeUndefined
	virtual int32_t getType() const = 0;
	
	/// \~chinese
	/// \brief  获取相机名称
	/// \return 返回相机名称
	/// \~english
	/// \brief  get Camera Name
	/// \return Success:Camera Name, Failure:NULL
	virtual const char * getName() = 0;
	
	/// \~chinese
	/// \brief  获取相机的唯一标识.
	/// \return 唯一标识相机的字符串.
	/// \~english
	/// \brief  get Camera Unique Indentification
	/// \return Success:Identification (Key), Failure:NULL
	virtual const char * getKey()  = 0;
	
    /// \~chinese
	/// \brief  连接设备
	/// 与相机建立连接关系，如Gige Vision协议的相机即是获得控制权限、创建控制通道
	/// \param [in] accessPermission 打开相机控制通道时默认为control access 权限
	/// \return 是否连接成功
	/// \~english
	/// \brief  connect to camera
	/// get the control permission of camera, and create the control channel
	/// \param [in] accessPermission Control access permission is default when open the control channel of the camera
	/// \retval false connection failed
	/// \retval true  connection successful
	virtual bool connect(ECameraAccessPermission accessPermission = accessPermissionControl) = 0;
		
	/// \~chinese
	/// \brief 断开连接
	/// 断开与相机的连接关系，如Gige Vision协议的相机即是释放控制权限、销毁控制通道
	/// \return 是否断开成功 
	/// \~english
	/// \brief disconnect camera
	/// release the control permission of camera, and withdraw the control channel
	/// \retval false disconnection failed
	/// \retval true  disconnection successful
	virtual bool disConnect() = 0;
		
	/// \~chinese
	/// \brief 判断相机当前是否处于已连接状态
	/// \return 是否已连接
	/// \~english
	/// \brief check the camera is connected or disconnected
	/// \retval false camera is disconnected
	/// \retval true  camera is connected
	virtual bool isConnected() = 0;
		      								
	/// \~chinese
	/// \brief  获取相机所属的接口名
	/// \return 设备所属的接口名
	/// \~english
	/// \brief  get the name of interface which is used for connecting the camera
	/// \return Success:Interface Name, Failure:NULL
	virtual const char * getInterfaceName()  = 0;

	/// \~chinese
	/// \brief  获取相机所连接的接口类型
	/// \return 相机所连接的接口类型
	/// \~english
	/// \brief  get the type of interface which is used for connecting the camera
	/// \return the type of interface
	virtual int32_t getInterfaceType() const = 0;
	
	/// \~chinese
	/// \brief 下载相机描述XML文件
	/// 下载相机描述文件，并保存到指定路径
	/// \param [in] aFullFilename 文件要保存的路径
	/// \return 是否下载成功
	/// \~english
	/// \brief download camera description XML file
	/// download camera description files, and save the files to specified path
	/// \param [in] aFullFilename The full paths where the downloaded XMl files would be saved to
	/// \retval false download failed
	/// \retval true  download successful
	virtual bool downLoadGenICamXML(const char* aFullFilename) = 0;

	/// \~chinese
	/// \brief 读用户自定义数据。相机内部保留32768字节用于用户存储自定义数据（此功能针对本品牌相机，其它品牌相机无此功能）。
	/// \param [out] pBuffer 数据缓冲的指针。
	/// \param [in] dwCount 期望读出的字节数
	/// \return 返回用户实际读取到的字节数
	/// \~english read user-defined data; Inside the camera, there are 32768 bytes reserved for user to store private data (Only our own camera has this function)
	/// \param [out] pBuffer pointer of the data buffer
	/// \param [in]  dwCount byte count expected
	/// \return return byte count read in fact
	virtual size_t readUserPrivateData(void* pBuffer, size_t dwCount) = 0;
	
	/// \~chinese
	/// \brief 写用户自定义数据。和readUserPrivateData对应
	/// \param [in] pBuffer 数据缓冲的指针。
	/// \param [in] dwCount 期望写入的字节数
	/// \return 返回用户实际写入的字节数
	/// \~english write user-defined data; Inside the camera, there are 32768 bytes reserved for user to store private data (Only our own camera has this function)
	/// \param [out] pBuffer pointer of the data buffer
	/// \param [in]  dwCount byte count expected
	/// \return return byte count written in fact
	virtual size_t writeUserPrivateData(const void *pBuffer, size_t dwCount) = 0;
	
	/// \~chinese
	/// \brief 获取相机制造厂商名称
	/// \return 返回相机制造厂商名称
	/// \~english
	/// \brief get the vendor name of this camera
	/// \return camera's vendor, return NULL if failed
	virtual const char * getVendorName() = 0;
	
	/// \~chinese
	/// \brief 获取相机型号
	/// \return 返回相机型号
	/// \~english
	/// \brief get the model name of this camera 
	/// \return camera's model name, return NULL if failed
	virtual const char * getModelName() = 0;

	/// \~chinese
	/// \brief 获取相机序列号
	/// \return 返回相机序列号
	/// \~english
	/// \brief get serial number of this camera
	/// \return camera's serial number, return NULL if failed
	virtual const char * getSerialNumber() = 0;

	/// \~chinese
	/// \brief 获取相机固件版本号
	/// \return 返回相机固件版本号
	/// \~english
	/// \brief get device version of this camera
	/// \return camera's device version, return NULL if failed
	virtual const char * getDeviceVersion() = 0;

	/// \~chinese
	/// \brief 往相机串口寄存器写数据，每次写会清除掉上次的数据（此功能只支持包含串口功能的本品牌相机 ）
	/// \param [in] pBuffer 数据缓冲的指针。
	/// \param [in] dwCount 期望写入的字节数
	/// \return 返回用户实际写入的字节数
	/// \~english write serial data to camera serial register, will erase the data writen before (Only our own camera with Serial Port has this function)
	/// \param [in] pBuffer pointer of the data buffer
	/// \param [in]  dwCount byte count expected
	/// \return return byte count written in fact
	virtual size_t writeUARTData(const void* pBuffer, size_t dwCount) = 0;

	/// \~chinese
	/// \brief 从相机串口寄存器读取串口数据（此功能只支持包含串口功能的本品牌相机 ）
	/// \param [out] pBuffer 数据缓冲的指针。
	/// \param [in] dwCount 期望读出的字节数
	/// \return 返回用户实际读取到的字节数
	/// \~english read serial data from camera serial register (Only our own camera with Serial Port has this function)
	/// \param [out] pBuffer pointer of the data buffer
	/// \param [in]  dwCount byte count expected
	/// \return return byte count read in fact
	virtual size_t readUARTData(void* pBuffer, size_t dwCount) = 0;

    /// \~chinese
    /// \brief 获取相机制造信息
    /// \return 返回相机制造信息，失败：返回NULL
    /// \~english
    /// \brief get manufacture info of this camera
    /// \return camera's manufacture info, return NULL if failed
    virtual const char * getManufactureInfo() = 0;
};

typedef Memory::TSharedPtr<ICamera> ICameraPtr;
/// @}

GENICAM_NAMESPACE_END

#endif//__DAHUA_GENICAM_ICAMERA_H__
