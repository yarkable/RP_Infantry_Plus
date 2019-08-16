/// \mainpage
/// \~chinese
/// \htmlinclude mainpage_chs.html
/// \~english
/// \htmlinclude mainpage_eng.html

#ifndef __MV_CAMERA_H__
#define __MV_CAMERA_H__
#include "IntTypes.h"

/**
*  @brief  动态库导入导出定义
*/
#ifdef _MSC_VER
	#ifdef GENICAM_API_DLL_BUILD
		#define  GENICAM_API _declspec(dllexport)
	#elif defined GENICAM_API_DLL_USE
		#define  GENICAM_API _declspec(dllimport)
	#else
		#define GENICAM_API
	#endif
#elif defined __GNUC__
	#define GENICAM_API 
#else
	#define GENICAM_API
#endif

#if (defined (_WIN32) || defined(WIN64))
	#define CALL_METHOD __stdcall
#elif defined __GNUC__
	#define CALL_METHOD
#else
	#define CALL_METHOD
#endif // end #if (defined (_WIN32) || defined(WIN64))

#define MAX_PARAM_CNT         1000
#define MAX_STRING_LENTH      256
#define MAX_PAYLOAD_TYPE_CNT  20

#ifdef __cplusplus
extern "C" {
#endif 

/// \~chinese
/// \brief 图像格式
/// \defgroup ImageFormat 图像格式
/// @{
/// \~english
/// \brief Image Format
/// \defgroup ImageFormat Image Format
/// @{

//===================================================
// PIXEL FORMATS
//===================================================
// Indicate if pixel is monochrome or RGB

#define GVSP_PIX_MONO                           0x01000000
#define GVSP_PIX_RGB                            0x02000000 // deprecated in version 1.1
#define GVSP_PIX_COLOR                          0x02000000
#define GVSP_PIX_CUSTOM                         0x80000000
#define GVSP_PIX_COLOR_MASK                     0xFF000000

// Indicate effective number of bits occupied by the pixel (including padding).
// This can be used to compute amount of memory required to store an image.
#define GVSP_PIX_OCCUPY1BIT                     0x00010000
#define GVSP_PIX_OCCUPY2BIT                     0x00020000
#define GVSP_PIX_OCCUPY4BIT                     0x00040000
#define GVSP_PIX_OCCUPY8BIT                     0x00080000
#define GVSP_PIX_OCCUPY12BIT                    0x000C0000
#define GVSP_PIX_OCCUPY16BIT                    0x00100000
#define GVSP_PIX_OCCUPY24BIT                    0x00180000
#define GVSP_PIX_OCCUPY32BIT                    0x00200000
#define GVSP_PIX_OCCUPY36BIT                    0x00240000
#define GVSP_PIX_OCCUPY48BIT                    0x00300000
#define GVSP_PIX_EFFECTIVE_PIXEL_SIZE_MASK      0x00FF0000
#define GVSP_PIX_EFFECTIVE_PIXEL_SIZE_SHIFT     16

// Pixel ID: lower 16-bit of the pixel formats
#define GVSP_PIX_ID_MASK                        0x0000FFFF
#define GVSP_PIX_COUNT                          0x46 // next Pixel ID available

//max length of attribute name
#define MAX_ATTR_NAME_LEN 1024

enum EPixelType
{
	// Undefined pixel type
	pixelTypeUndefined = -1,

	// Mono Format
	gvspPixelMono1p = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY1BIT | 0x0037),
	gvspPixelMono2p = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY2BIT | 0x0038),
	gvspPixelMono4p = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY4BIT | 0x0039),
	gvspPixelMono8 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY8BIT | 0x0001),
	gvspPixelMono8S = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY8BIT | 0x0002),
	gvspPixelMono10 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0003),
	gvspPixelMono10Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x0004),
	gvspPixelMono12 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0005),
	gvspPixelMono12Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x0006),
	gvspPixelMono14 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0025),
	gvspPixelMono16 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0007),

	// Bayer Format
	gvspPixelBayGR8 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY8BIT | 0x0008),
	gvspPixelBayRG8 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY8BIT | 0x0009),
	gvspPixelBayGB8 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY8BIT | 0x000A),
	gvspPixelBayBG8 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY8BIT | 0x000B),
	gvspPixelBayGR10 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x000C),
	gvspPixelBayRG10 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x000D),
	gvspPixelBayGB10 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x000E),
	gvspPixelBayBG10 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x000F),
	gvspPixelBayGR12 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0010),
	gvspPixelBayRG12 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0011),
	gvspPixelBayGB12 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0012),
	gvspPixelBayBG12 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0013),
	gvspPixelBayGR10Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x0026),
	gvspPixelBayRG10Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x0027),
	gvspPixelBayGB10Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x0028),
	gvspPixelBayBG10Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x0029),
	gvspPixelBayGR12Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x002A),
	gvspPixelBayRG12Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x002B),
	gvspPixelBayGB12Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x002C),
	gvspPixelBayBG12Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x002D),
	gvspPixelBayGR16 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x002E),
	gvspPixelBayRG16 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x002F),
	gvspPixelBayGB16 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0030),
	gvspPixelBayBG16 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0031),

	// RGB Format
	gvspPixelRGB8 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x0014),
	gvspPixelBGR8 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x0015),
	gvspPixelRGBA8 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY32BIT | 0x0016),
	gvspPixelBGRA8 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY32BIT | 0x0017),
	gvspPixelRGB10 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x0018),
	gvspPixelBGR10 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x0019),
	gvspPixelRGB12 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x001A),
	gvspPixelBGR12 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x001B),
	gvspPixelRGB16 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x0033),
	gvspPixelRGB10V1Packed = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY32BIT | 0x001C),
	gvspPixelRGB10P32 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY32BIT | 0x001D),
	gvspPixelRGB12V1Packed = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY36BIT | 0X0034),
	gvspPixelRGB565P = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x0035),
	gvspPixelBGR565P = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0X0036),

	// YVR Format
	gvspPixelYUV411_8_UYYVYY = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY12BIT | 0x001E),
	gvspPixelYUV422_8_UYVY = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x001F),
	gvspPixelYUV422_8 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x0032),
	gvspPixelYUV8_UYV = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x0020),
	gvspPixelYCbCr8CbYCr = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x003A),
	gvspPixelYCbCr422_8 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x003B),
	gvspPixelYCbCr422_8_CbYCrY = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x0043),
	gvspPixelYCbCr411_8_CbYYCrYY = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY12BIT | 0x003C),
	gvspPixelYCbCr601_8_CbYCr = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x003D),
	gvspPixelYCbCr601_422_8 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x003E),
	gvspPixelYCbCr601_422_8_CbYCrY = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x0044),
	gvspPixelYCbCr601_411_8_CbYYCrYY = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY12BIT | 0x003F),
	gvspPixelYCbCr709_8_CbYCr = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x0040),
	gvspPixelYCbCr709_422_8 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x0041),
	gvspPixelYCbCr709_422_8_CbYCrY = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x0045),
	gvspPixelYCbCr709_411_8_CbYYCrYY = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY12BIT | 0x0042),

	// RGB Planar
	gvspPixelRGB8Planar = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x0021),
	gvspPixelRGB10Planar = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x0022),
	gvspPixelRGB12Planar = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x0023),
	gvspPixelRGB16Planar = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x0024),

	//BayerRG10p和BayerRG12p格式，针对特定项目临时添加,请不要使用
	//BayerRG10p and BayerRG12p, currently used for specific project, please do not use them
	gvspPixelBayRG10p = 0x010A0058,
	gvspPixelBayRG12p = 0x010c0059,

	//mono1c格式，自定义格式
	//mono1c, customized image format, used for binary output
	gvspPixelMono1c = 0x012000FF,

	//mono1e格式，自定义格式，用来显示连通域
	//mono1e, customized image format, used for displaying connected domain
	gvspPixelMono1e = 0x01080FFF
};

/// @}



typedef enum GENICAM_ECameraAccessPermission
{
	accessPermissionOpen = 0,		///< \~chinese GigE相机没有被连接        ///< \~english The GigE vision device isn't connected to any application. 
	accessPermissionExclusive, 	///< \~chinese 独占访问权限        ///< \~english Exclusive Access Permission   
	accessPermissionControl, 	///< \~chinese 非独占可读访问权限  ///< \~english Non-Exclusive Readbale Access Permission  
	accessPermissionControlWithSwitchover,  	///< \~chinese Control access with switchover enabled.        ///< \~english Control access with switchover enabled.	
	accessPermissionUnknown = 254,  	///< \~chinese 无法确定        ///< \~english Value not known; indeterminate.   	
	accessPermissionUndefined     	///< \~chinese 未定义访问权限      ///< \~english Undefined Access Permission
}GENICAM_ECameraAccessPermission;


///< \~chinese
///枚举：协议类型
///< \~english
///enumeration: protocol type
typedef	enum GENICAM_EProtocolType
{
	typeGige = 0,	///< \~chinese GigE协议        ///< \~english GigE Vision Protocol
	typeUsb3 = 1,	///< \~chinese USB3.0协议      ///< \~english USB3.0 Vision Protocol
	typeCL   = 2,	///< \~chinese CAMERALINK协议  ///< \~english Camera Link Protocol
    typePCIe = 3,   ///< \~chinese PCIe接口类型    ///< \~english PCIe Protocol
	typeAll  = 255  ///< \~chinese 忽略协议类型，设备发现传入此类型时，表示需发现所有接口下的设备   ///< \~english ALL Supported Protocol
}GENICAM_EProtocolType;

/// \~chinese
/// \brief 相机对象接口类
/// \defgroup Camera 相机共用操作接口
/// @{
/// \~english
/// \brief Camera Object Interface Class
/// \defgroup Camera Camera Object Common Interface
/// @{

/// \~chinese
/// 通用相机对象
/// 32位系统下128字节
/// \~english
/// universal camera object
/// 128 bytes in 32-bit system
typedef struct GENICAM_Camera
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// underlying private data
	void *priv;
	
	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	///  add interface reference
	/// \param [in] thiz this pointer
	int32_t	(*addRef)(struct GENICAM_Camera *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer	
	int32_t(*release)(struct GENICAM_Camera *thiz);
	
	/// \~chinese
	/// \brief  得到相机类型
	/// \param [in] thiz 本接口指针
	/// \return 成功则返回0，否则返回-1
	/// \~english
	/// \brief  get Camera Type
	/// \param [in] thiz this pointer
	/// \return Success:0, Failure:-1
	int32_t (*getType)(struct GENICAM_Camera *thiz);
	
	/// \~chinese
	/// \brief  获取相机名称
	/// \param [in] thiz 本接口指针
	/// \return 成功返回相机名称，否则返回NULL
	/// \~english
	/// \brief  get Camera Name
	/// \param [in] thiz this pointer
	/// \return Success:Camera Name, Failure:NULL
	const char* (*getName)(struct GENICAM_Camera *thiz);
	
	/// \~chinese
	/// \brief  获取相机的唯一标识.
	/// \param [in] thiz 本接口指针
	/// \return 成功返回唯一标识相机的字符串，失败返回NULL
	/// \~english
	/// \brief  get Camera Unique Key
	/// \param [in] thiz this pointer
	/// \return Success:Key, Failure:NULL
	const char* (*getKey)(struct GENICAM_Camera *thiz);
	
    /// \~chinese
	/// \brief  连接设备
	/// 与相机建立连接关系，如Gige Vision协议的相机即是获得控制权限、创建控制通道
	/// \param [in] thiz 本接口指针
	/// \param [in] accessPermission 目前只支持accessPermissionControl权限，调用该接口时传入此类权限
	/// \retval < 0 连接设备失败
	/// \retval 0   连接设备成功
	/// \~english
	/// \brief  connect to camera
	/// establish connection with camera, for example, for GigE camera, which means get the control permission of camera and create control channel
	/// \param [in] thiz this pointer
	/// \param [in] accessPermission only accessPermissionControl supported currently
	/// \retval < 0 connection failed
	/// \retval 0   connection successful
	int32_t (*connect)(struct GENICAM_Camera *thiz,GENICAM_ECameraAccessPermission accessPermission);
		
	/// \~chinese
	/// \brief 断开连接
	/// 断开与相机的连接关系，如Gige Vision协议的相机即是释放控制权限、销毁控制通道
	/// \param [in] thiz 本接口指针
	/// \retval < 0 断开设备失败
	/// \retval 0   断开设备成功
	/// \~english
	/// \brief disconnect camera
	/// disconnect the camera, for example, for GigE camera, which means release the control permission of camera and destroy the control channel
	/// \param [in] thiz this pointer
	/// \retval < 0 disconnection failed
	/// \retval 0   disconnection successful
	int32_t (*disConnect)(struct GENICAM_Camera *thiz);
		
	/// \~chinese
	/// \brief 判断相机当前是否处于已连接状态
	/// \param [in] thiz 本接口指针
	/// \retval < 0 设备处于断开状态
	/// \retval 0   设备处于连接状态
	/// \~english
	/// \brief check the camera is connected or disconnected
	/// \param [in] thiz this pointer
	/// \retval < 0 camera is disconnected
	/// \retval 0   camera is connected
	int32_t (*isConnected)(struct GENICAM_Camera *thiz);
		      								
	/// \~chinese
	/// \brief  获取相机所属的接口名
	/// \param [in] thiz 本接口指针
	/// \return 成功返回设备所属的接口名，否则返回NULL
	/// \~english
	/// \brief  get the name of interface whice is connect to camera
	/// \param [in] thiz this pointer
	/// \return Success:Interface Name, Failure:NULL
	const char* (*getInterfaceName)(struct GENICAM_Camera *thiz);

	/// \~chinese
	/// \brief  获取相机所连接的接口类型
	/// \param [in] thiz 本接口指针
	/// \return 返回相机所连接的接口类型
	/// \~english
	/// \brief  get the type of interface which is connect to camera
	/// \param [in] thiz  this pointer
	/// \return the type of interface
	int32_t (*getInterfaceType)(struct GENICAM_Camera *thiz);
	
	/// \~chinese
	/// \brief 下载相机描述XML文件
	/// 下载相机描述文件，并保存到指定路径
	/// \param [in] thiz 本接口指针
	/// \param [in] aFullFilename 文件要保存的路径
	/// \retval < 0 下载XML失败
	/// \retval 0   下载XML成功
	/// \~english
	/// \brief download XML file of camera description 
	/// download camera discription file, and save the file to specified path
	/// \param [in] thiz this pointer
	/// \param [in] aFullFilename full path name of the downloaded xml file
	/// \retval < 0 download failed
	/// \retval 0   download successful
	int32_t (*downLoadGenICamXML)(struct GENICAM_Camera *thiz,const char* aFullFilename);

	/// \~chinese
	/// \brief 获取相机制造厂商名称
	/// \param [in] thiz 本接口指针
	/// \return 返回厂商名称
	/// \~english
	/// \brief get camera's vendor 
	/// \param [in] thiz this pointer
	/// \return camera's vendor, return NULL if failed
	const char* (*getVendorName)(struct GENICAM_Camera *thiz);
	
	/// \~chinese
	/// \brief 获取相机的型号
	/// \param [in] thiz 本接口指针
	/// \return 返回相机型号
	/// \~english
	/// \brief get camera's model name
	/// \param [in] thiz this pointer
	/// \return camera's model name, return NULL if failed
	const char* (*getModelName)(struct GENICAM_Camera *thiz);

	/// \~chinese
	/// \brief 获取相机的序列号
	/// \param [in] thiz 本接口指针
	/// \return 返回相机的序列号
	/// \~english
	/// \brief get camera's serial number
	/// \param [in] thiz this pointer
	/// \return camera's serial number, return NULL if failed
	const char* (*getSerialNumber)(struct GENICAM_Camera *thiz);

	/// \~chinese
	/// \brief 获取相机固件版本号
	/// \param [in] thiz 本接口指针
	/// \return 返回相机的固件版本号
	/// \~english
	/// \brief get device version of this camera
	/// \param [in] thiz this pointer
	/// \return device version of this camera, return NULL if failed
	const char* (*getDeviceVersion)(struct GENICAM_Camera *thiz);

	/// \~chinese
	/// \brief 获取相机制造信息
	/// \param [in] thiz 本接口指针
	/// \return 返回相机的制造信息
	/// \~english
	/// \brief get manufacture info of this camera
	/// \param [in] thiz this pointer
	/// \return manufacture info of this camera, return NULL if failed
	const char* (*getManufactureInfo)(struct GENICAM_Camera *thiz);
	
	uint32_t		reserved[15];	///< \~chinese 保留  	///< \~english reserved field
}GENICAM_Camera;
/// @}

// \~chinese
/// \brief GigE设备信息
/// \~english
/// \brief GigE device info
typedef struct GigEDeviceInfo
{
    GENICAM_ECameraAccessPermission eAccessStatus;
    uint32_t nReserved[7];          ///< 保留	///< \~english reserved field

    char strMACAddr[MAX_STRING_LENTH];
    char strIPAddr[MAX_STRING_LENTH];
    char strSubnetMask[MAX_STRING_LENTH];
    char strDefaultGateWay[MAX_STRING_LENTH];
    char strProtocolVersion[MAX_STRING_LENTH];
    char strIPConfiguration[MAX_STRING_LENTH];
    char strReserved[MAX_STRING_LENTH * 10];    ///< 保留	///< \~english reserved field

}GigEDeviceInfo;

// \~chinese
/// \brief Usb设备信息
/// \~english
/// \brief Usb device info
typedef struct UsbDeviceInfo
{
    int32_t bLowSpeedSupported;     //1 支持，0 不支持，其他值 非法。
    int32_t bFullSpeedSupported;    //1 支持，0 不支持，其他值 非法。
    int32_t bHighSpeedSupported;    //1 支持，0 不支持，其他值 非法。
    int32_t bSuperSpeedSupported;   //1 支持，0 不支持，其他值 非法。
    int32_t bDriverInstalled;       //1 安装，0 未安装，其他值 非法。
    uint32_t nReserved[3];          ///< 保留	///< \~english reserved field

    char strConfigurationValid[MAX_STRING_LENTH];
    char strGenCPVersion[MAX_STRING_LENTH];
    char strU3VVersion[MAX_STRING_LENTH];
    char strDeviceGUID[MAX_STRING_LENTH];
    char strFamilyName[MAX_STRING_LENTH];
    char strU3VSerialNumber[MAX_STRING_LENTH];
    char strSpeed[MAX_STRING_LENTH];
    char strMaxPower[MAX_STRING_LENTH];
    char strReserved[MAX_STRING_LENTH * 8]; ///< 保留	///< \~english reserved field

}UsbDeviceInfo;

// \~chinese
/// \brief 设备信息
/// \~english
/// \brief device info
typedef struct DeviceInfo
{
    int32_t nType;
    uint32_t nReserved[7];      ///< 保留	///< \~english reserved field

    char strKey[MAX_STRING_LENTH];
    char strUserDefinedName[MAX_STRING_LENTH];    
    char strSerialNumber[MAX_STRING_LENTH];
    char strVendor[MAX_STRING_LENTH];
    char strModel[MAX_STRING_LENTH];
    char strManufactureInfo[MAX_STRING_LENTH];
    char strDeviceVersion[MAX_STRING_LENTH];
    char strReserved[MAX_STRING_LENTH * 9]; ///< 保留	///< \~english reserved field

    union
    {
        GigEDeviceInfo stGigEInfo;
        UsbDeviceInfo stUsbInfo;
    }DeviceSpecificInfo;

}DeviceInfo;

/// \~chinese
/// \brief 发现设备、创建常用属性对象
/// \defgroup System 设备发现、属性常用对象创建和事件订阅对象创建接口
/// @{
/// \~english
/// \brief discover camera, and create common property instance
/// \defgroup System System Management Interface
/// @{

/// \~chinese
/// \brief 全局单例系统对象,32位系统下128字节
/// \~english
/// \brief Global singleton system object, 128 bytes in 32-bit system
typedef struct GENICAM_System
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;
	
	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t	(*addRef)(struct GENICAM_System *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_System *thiz);
	
	/// \~chinese
	/// \brief 发现指定接口类型可达的设备
    /// \brief 1、该接口不能与enumDevicesInfo、createDevice接口同时使用。
    /// \brief 2、设备对象由discovery接口内部创建.
	/// \param [in] thiz 本接口指针
	/// \param [out] ppCameraList 指定接口类型所有在线设备对象列表,该内存在函数内部申请，但需外部传入一个一维指针有效地址指向该设备列表
	/// \param [out] pCameraCnt  发现的设备个数
	/// \param [in]  interfaceType  接口类型，当传入的是typeAll时，表示目前所有已支持的协议类型设备都会被发现
	/// \retval < 0 发现设备失败
	/// \retval 0   发现设备成功
	/// \~english
	/// \brief discover reachable camera which has specified interface type
    /// \brief 1、This interface can't be used with enumDevicesInfo and createDevice interface at the same time.  
    /// \brief 2、The device is created in discovery interface.
	/// \param [in] thiz this pointer
	/// \param [out] ppCameraList camera instance list of specified interface type. thie memory is allocated inside the function, but it requires externally input a pointer of valid address to the device list
	/// \param [out] pCameraCnt  the number of discovered cameras
	/// \param [in]  interfaceType  interface type.when "typeAll" is specified which means all cameras which are currently supported will be discovered
	/// \retval < 0 discovery failed
	/// \retval 0   discovery successful
	int32_t (*discovery)(struct GENICAM_System *thiz, GENICAM_Camera **ppCameraList, uint32_t *pCameraCnt, GENICAM_EProtocolType interfaceType);
	
	/// \~chinese
	/// \brief 根据相机的key获取 Camera 对象指针
	/// \param [in] thiz 本接口指针
	/// \param [in] pCameraKey 相机的key
	/// \return 返回Camera指针,若传入的pCameraKey不存在或者非法，则返回空指针
	/// \~english
	/// \brief get the pointer of camera object according to camera key
	/// \param [in] thiz this pointer
	/// \param [in] pCameraKey camera key
	/// \return Success:camera pointer, Failure:NULL
	GENICAM_Camera* (*getCamera)(struct GENICAM_System *thiz,const char * pCameraKey);

	/// \~chinese
	/// \brief 获取版本信息
	/// \param [in] thiz 本接口指针
	/// \return 版本信息，失败时返回NULL
	/// \~english
	/// \brief get version info
	/// \param [in] thiz this pointer
	/// \return Success:version info, Failure:NULL
	const char* (*getVersion)(struct GENICAM_System *thiz);
	
    /// \~chinese
    /// \brief 发现指定接口类型可达设备的设备信息
    /// \brief 1、该接口不能与discovery接口同时使用。
    /// \brief 2、该接口不会创建设备对象，只返回ppDevInfoList设备信息，用户需通过设备信息调用createDevice接口来创建设备对象。   
    /// \param [in] thiz 本接口指针
    /// \param [out] ppDevInfoList 指定接口类型所有在线设备的设备信息列表
    /// \param [out] pCameraCnt  发现的设备个数
    /// \param [in]  interfaceType  接口类型，当传入的是typeAll时，表示目前所有已支持的协议类型设备都会被发现
    /// \retval < 0 发现设备信息失败
    /// \retval 0   发现设备信息成功
    /// \~english
    /// \brief enumerate information of reachable camera which has specified interface type.  
    /// \brief 1、This interface can't be used with discovery interface at the same time.
    /// \brief 2、This interface does't create device itself. It only returns device infomation stored in param ppDevInfoList. Users can create devive using createDevice interface.
    /// \param [in] thiz this pointer
    /// \param [out] ppDevInfoList Camera information list of specified interface type.
    /// \param [out] pCameraCnt  the number of discovered cameras
    /// \param [in]  interfaceType  interface type.when "typeAll" is specified which means all cameras which are currently supported will be discovered
    /// \retval < 0 discovery failed
    /// \retval 0   discovery successful
    int32_t (*enumDevicesInfo)(struct GENICAM_System *thiz, DeviceInfo** ppDevInfoList, uint32_t *pCameraCnt, GENICAM_EProtocolType interfaceType);

    /// \~chinese
    /// \brief 创建设备对象。
    /// \brief 1、该接口不能与discovery接口同时使用。
    /// \brief 2、由该接口创建的设备对象需要调用相应的release接口来释放，以防内存泄漏。
    /// \param [in] thiz 本接口指针
    /// \param [in] pDevInfo 设备信息
    /// \param [out] ppCamera  创建的设备对象
    /// \retval < 0 创建失败
    /// \retval 0   创建成功
    /// \~english
    /// \brief create device object. 
    /// \brief 1、This interface can't be used with discovery interface at the same time.
    /// \brief 2、The device created in this interface should be released by calling corresponding release interface in case of memory leak.
    /// \param [in] thiz this pointer
    /// \param [in] pDevInfo camera information
    /// \param [out] ppCamera  the pointer of created device object
    /// \retval < 0  failed
    /// \retval 0    successful
    int32_t (*createDevice)(struct GENICAM_System *thiz, DeviceInfo *pDevInfo, GENICAM_Camera **ppCamera);

	uint32_t		reserved[24];	///< 保留	///< \~english reserved field
}GENICAM_System;

/// \~chinese
/// 创建系统对象，全局唯一
///
/// \param [out] ppSystem 输出参数，返回的是系统对象的指针
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create system object, Globally unique
///
/// \param [out] ppSystem output parameter, return pointer of the system object
/// \retval < 0 create failed
/// \retval 0   create successful
GENICAM_API int32_t  CALL_METHOD GENICAM_getSystemInstance(GENICAM_System** ppSystem);
/// @}


/// \~chinese
/// \brief 数据帧对象接口
/// \defgroup Frame 数据帧操作接口
/// @{
/// \~english 
/// \brief data frame object interface
/// \defgroup frame operation interface
/// @{
typedef enum GENICAM_EPayloadType
{
	payloadImage = 1,	            ///< \~chinese 图片         \~english Image
	payloadRawdata,					///< \~chinese 裸数据       \~english Raw Data
	payloadFile,					///< \~chinese 文件         \~english File
	payloadChunkData,				///< \~chinese 块数据       \~english Chunk Data
	payloadExtChunkData,			///< \~chinese 扩展块数据   \~english Extension Chunk Data
	payloadDevSpecBase = 0x8000,    ///< \~chinese 设备特有     \~english Device specific payload type
	payloadUndefined				///< \~chinese 未定义		\~english Undefined
}GENICAM_EPayloadType;

/// \~chinese
/// \brief 数据帧对象
/// 32位系统下128字节
/// \~english
/// \brief data frame object
/// 128 bytes in 32-bit system
typedef struct GENICAM_Frame
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 帧深拷贝克隆接口
	/// \param [in] thiz 本接口指针
	/// \return 新的一帧对象
	/// \~english
	/// \brief frame deep copy clone interface
	/// \param [in] thiz this pointer
	/// \return new frame object
	struct GENICAM_Frame* (*clone)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 外面不使用时需要调用此接口释放Image相关内存
	/// \param [in] thiz 本接口指针
	/// \return none
	/// \~english
	/// \brief Call this interface to release image related memory externally when it is not in use
	/// \param [in] thiz this pointer
	/// \return none
	void (*reset)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// brief 是否有效
	/// \param [in] thiz 本接口指针
	/// \retval < 0 该帧无效
	/// \retval 0   该帧有效
	/// \~english
	/// brief check the frame is valid or not
	/// \param [in] thiz this pointer
	/// \retval < 0 frame invalid
	/// \retval 0   frame valid
	int32_t (*valid)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取该帧图片数据的内存首地址
	/// \param [in] thiz 本接口指针
	/// \return 返回该帧图片数据的内存首地址
	/// \~english
	/// \brief Get the starting address of memory of this image data
	/// \param [in] thiz this pointer
	/// \return Return the starting address of memory of this image data  	
	const void* (*getImage)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取数据帧状态
	/// \param [in] thiz 本接口指针
	/// \return 返回数据帧状态
	/// \~english
	/// \brief Get status of data frame
	/// \param [in] thiz this pointer
	/// \return the data frame status
	uint32_t (*getFrameStatus)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取图片宽度
	/// \param [in] thiz 本接口指针
	/// \return 返回图片宽度，失败时为0
	/// \~english
	/// \brief get the width of image
	/// \param [in] thiz this pointer
	/// \return the width of image, return 0 when failed
	uint32_t (*getImageWidth)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取图片高度
	/// \param [in] thiz 本接口指针
	/// \return 返回图片高度，失败时为0
	/// \~english 
	/// \brief get the height of image
	/// \param [in] thiz this pointer
	/// \return the height of image, return 0 when failed
	uint32_t (*getImageHeight)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取图片大小
	/// \param [in] thiz 本接口指针
	/// \return 返回图片大小，失败时为0
	/// \~english
	/// \brief get the size of image
	/// \param [in] thiz this pointer
	/// \return the size of image, return 0 when failed
	uint32_t (*getImageSize)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取图片像素格式
	/// \param [in] thiz 本接口指针
	/// \return 返回图片像素格式
	/// \~english
	/// \brief get image pixel format
	/// \param [in] thiz this pointer
	/// \return image pixel format
	enum EPixelType (*getImagePixelFormat)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取图片时间戳
	/// \param [in] thiz 本接口指针
	/// \return 返回图片时间戳，失败时为0
	/// \~english
	/// \brief get timestamp of image
	/// \param [in] thiz this pointer
	/// return image time stamp, return 0 when failed
	uint64_t (*getImageTimeStamp)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取图片对应的BlockId
	/// \param [in] thiz 本接口指针
	/// \return 返回图片对应的BlockId，失败时为0
	/// \~english
	/// \brief get the image's block ID
	/// \param [in] thiz this pointer
	/// \return the image's block ID, return 0 when failed 
	uint64_t (*getBlockId)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取当前帧数据净荷类型
	/// \param [in] thiz 本接口指针
	/// \param [in/out] pPayloadTypeList 当前帧数据类型种类集，最大种类不超过MAX_PAYLOAD_TYPE_CNT，该内存外部分配
	/// \param [in/out] pTypeCnt 入参时为数组的实际长度;出参时为当前帧数据类型的实际个数，最大不超过20
	/// \return 返回当前帧数据净荷类型
	/// \~english
	/// \brief get pay load type of current frame
	/// \param [in] thiz this pointer
	/// \param [in/out] pPayloadTypeList Current frame data type set, maximum type cannot excced MAX_PAYLOAD_TYPE_CNT, and the memory is allocated externally
	/// \param [in/out] pTypeCnt the actul length of array when input;the number of the current frame's data types when output, maximum value cannot exceed 20
	/// \return pay load type of current frame
	int32_t(*getPayLoadTypes)(struct GENICAM_Frame *thiz, GENICAM_EPayloadType aPayloadTypeList[MAX_PAYLOAD_TYPE_CNT], uint32_t *pTypeCnt);

	/// \~chinese
	/// \brief 获取Buffer中包含的Chunk个数
	/// \param [in] thiz 本接口指针
	/// \return Chunk个数
	/// \~english
	/// \brief get the number of chunk in buffer
	/// \param [in] thiz this pointer
	/// \return the number of chunk
	uint32_t (*getChunkCount)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取Chunk数据
	/// \param [in] thiz 本接口指针
	/// \param [in] aIndex 索引ID
	/// \param [out] pID ChunkID
	/// \param [in/out] aRefParamList Chunk数据对应的属性名,该内存外部分配，接口约定ChunkID对应的参数列表最大不超过MAX_PARAM_CNT个，每个属性的字符长度不超过MAX_STRING_LENTH。
	/// \param [in/out] pParamCnt Chunk对应的属性个数，入参时为最大的参数个数，出参时为实际的参数个数
	/// \return 是否成功
	/// \~english
	/// \brief get chunk data
	/// \param [in] thiz this pointer
	/// \param [in] aIndex index ID
	/// \param [out] pID ChunkID
	/// \param [in/out] aRefParamList Chunk data's property name, this memory is allocated externally, Chunk ID's property list cannot exceed MAX_PARAM_CNT, each property's characters cannot exceed MAX_STRING_LENTH
	/// \param [in/out] pParamCnt the number of chunk's property, maximum parameter's number when input, real parameter's number when output
	/// \return success or fail
	int32_t (*getChunkDataByIndex)(struct GENICAM_Frame *thiz,uint32_t aIndex, uint32_t *pID,
		char aRefParamList[MAX_PARAM_CNT][MAX_STRING_LENTH], uint32_t *pParamCnt);

	/// \~chinese
	/// \brief 获取图片paddingX
	/// \param [in] thiz 本接口指针
	/// \return 返回图片paddingX，失败时为0
	/// \~english 
	/// \brief get the paddingX of image
	/// \param [in] thiz this pointer
	/// \return the paddingX of image, return 0 when failed
	uint32_t(*getImagePaddingX)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取图片paddingY
	/// \param [in] thiz 本接口指针
	/// \return 返回图片paddingY，失败时为0
	/// \~english 
	/// \brief get the paddingY of image
	/// \param [in] thiz this pointer
	/// \return the paddingY of image, return 0 when failed
	uint32_t(*getImagePaddingY)(struct GENICAM_Frame *thiz);


	uint32_t  reserved[13];	///< \~chinese 保留  	///< \~english reserved field
}GENICAM_Frame;
/// @}


/// \~chinese
/// \brief 流对象接口类
/// \defgroup stream 流对象操作接口
/// @{
/// \~english
/// \brief stream object interface class
/// \defgroup stream Stream Object Operation Interface 
/// @{
typedef enum  GENICAM_EGrabStrategy
{
	grabStrartegySequential = 0,	///< \~chinese 按到达顺序处理图片	///< \~english The images are processed in the order of their arrival
	grabStrartegyLatestImage = 1,   ///< \~chinese 获取最新的图片		///< \~english get latest image
	grabStrartegyUndefined   		///< \~chinese 未定义				///< \~english undefined
}GENICAM_EGrabStrategy;

/// \~chinese
/// \brief 设备流回调函数声明:每次回调送出一帧数据
/// pFrame 回调时主动推送的帧对象,外部用完该帧后需要释放
/// \~english
/// \brief Callback function declaration of stream: Send out one frame at each time use callback function
/// pFrame The frame which will be active pushed out during the callback, when this frame is used externally then it is required to be released
typedef void(*callbackFun)(GENICAM_Frame* pFrame);

/// \~chinese
/// \brief 设备流回调函数声明:每次回调送出一帧数据
/// pFrame 回调时主动推送的帧对象,外部用完该帧后需要释放
/// pUser  用户自定义数据
/// \~english
/// \brief Callback function declaration of stream: Send out one frame at each time use callback function
/// pFrame The frame which will be active pushed out during the callback, when this frame is used externally then it is required to be released
/// pUser  user defined data
typedef void(*callbackFunEx)(GENICAM_Frame* pFrame, void* pUser);

/// \~chinese
/// \brief GENICAM_StreamSource 流对象
/// 32位系统下128字节
/// \~english
/// \brief stream object
/// 128 bytes in 32-bit system
typedef struct GENICAM_StreamSource
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_StreamSource *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_StreamSource *thiz);

	/// \~chinese
	/// \brief 开始抓图
	/// \param [in] thiz 本接口指针
	/// \param [in] maxImagesGrabbed 允许最多的抓图数，达到指定抓图数后停止抓图，如果为0，表示忽略此参数，会连续抓图
	/// \param [in] strategy 抓图策略
	/// \return 返回抓图是否成功，0表示成功，-1表示失败
	/// \~english
	/// \brief Start grabbing
	/// \param [in] thiz this pointer
	/// \param [in] maxImagesGrabbed Maximum images allowed to grab, once it reaches the limit then stop grabbing; If it is 0, then ignore this parameter and start grabbing continuously
	/// \param [in] strategy Image grabbing strategy
	/// \return success:0, fail:-1
	int32_t (*startGrabbing)(struct GENICAM_StreamSource *thiz, uint64_t maxImagesGrabbed, GENICAM_EGrabStrategy strategy);

	/// \~chinese
	/// \brief 停止抓图
	/// \param [in] thiz 本接口指针
	/// \return 返回停止抓图是否成功，0表示成功，-1表示失败	
	/// \~english
	/// \brief Stop grabbing
	/// \param [in] thiz this pointer
	/// \return success:0, fail:-1
	int32_t (*stopGrabbing)(struct GENICAM_StreamSource *thiz);

	/// \~chinese
	/// \brief 是否正在抓图
	/// \param [in] thiz 本接口指针
	/// \return 返回是否处于拉流状态，0表示处于拉流状态，-1表示非拉流状态
	/// \~english 
	/// \brief Check whether it is grabbing or not
	/// \param [in] thiz this pointer
	/// \return grabbing or not grabbing, 0 means it is grabbing, -1 means it is not grabbing
	int32_t (*isGrabbing)(struct GENICAM_StreamSource *thiz);

	/// \~chinese
	/// \brief 获取一帧图像，该接口不支持多线程调用
	/// \param [in] thiz 本接口指针
	/// \param [out] ppFrame 一帧图像,内存由函数内部分配，用完该帧后需要显示调用GENICAM_Frame release接口显示释放
	/// \param [in]  timeoutMS 获取一帧图像的超时时长,单位MS,当值为INFINITE时表示无限等待
	/// \return 返回是否成功，0表示成功，-1表示失败
	/// \~english
	/// \brief get a frame image, and this interface does not support multi-threading
	/// \param [in] thiz this pointer
	/// \param [out] ppFrame There is one image, its memory is allocated internally in this function, it is also required to call GENICAM_Frame release interface to release memory after use up this image
	/// \param [in]  The timeout value of getting one image, unit is MS; When the value is INFINITE which means infinite wait
	/// \return success:0, fail:-1
	int32_t (*getFrame)(struct GENICAM_StreamSource *thiz, GENICAM_Frame **ppFrame, uint32_t timeoutMS);

	/// \~chinese
	/// \brief 注册数据帧回调函数。该异步获取帧机制和同步获取帧机制互斥，系统中两者只能选其一。
	/// \brief 只能处理一个回调函数
	/// \param [in] thiz 本接口指针
	/// \param [in] proc 数据帧回调函数，建议不要在该函数中处理耗时的操作，否则会阻塞后续数据帧的实时性
	/// \return 返回注册是否成功，0表示成功，-1表示失败
	/// \~english
	/// \brief Register data frame callback function; This asynchronous frame acquisition mechanism and synchronous frame acquisition mechanism are mutually exclusive, only one method can be choosed between these two in system
	/// \brief only process one callback unction 
	/// \param [in] thiz this pointer
	/// \param [in] proc Data frame callback function; It is advised to not put time-cosuming operation in this function, otherwise it will block follow-up data frames and affect real time performance
	/// \return success:0, fail:-1
	int32_t (*attachGrabbing)(struct GENICAM_StreamSource *thiz, callbackFun proc);

	/// \~chinese
	/// \brief 去注册数据帧回调函数
	/// \param [in] thiz 本接口指针
	/// \param [in] proc 去注册数据帧回调函数
	/// \return 返回去注册是否成功，0表示成功，-1表示失败
	/// \~english
	/// \brief	Unregister data frame callback function
	/// \param [in] thiz this pointer
	/// \param [in] proc Unregister data frame callback function
	/// \return success:0, fail:-1
	int32_t(*detachGrabbing)(struct GENICAM_StreamSource *thiz, callbackFun proc);

	/// \~chinese
	/// \brief 设置缓存个数,不能在拉流过程中设置
	/// \param [in] thiz 指针
	/// \param [in]  缓存数量
	/// \return 返回是否成功
	/// \~english
	/// \brief set number of buffer,it can not be set in Grabbing.
	/// \param [in] thiz this pointer
	/// \param [in] number of buffer
	/// \return success:0, fail:-1
	int32_t(*setBufferCount)(struct GENICAM_StreamSource *thiz, uint32_t nSize);

	/// \~chinese
	/// \brief 注册数据帧回调函数(包含用户自定义数据)。该异步获取帧机制和同步获取帧机制互斥，系统中两者只能选其一。
	/// \brief 只能处理一个回调函数
	/// \param [in] thiz 本接口指针
	/// \param [in] proc 数据帧回调函数，建议不要在该函数中处理耗时的操作，否则会阻塞后续数据帧的实时性
	/// \param [in] pUser 用户自定义数据
	/// \return 返回注册是否成功，0表示成功，-1表示失败
	/// \~english
	/// \brief Register data frame callback function(include user defined data); This asynchronous frame acquisition mechanism and synchronous frame acquisition mechanism are mutually exclusive, only one method can be choosed between these two in system
	/// \brief only process one callback unction 
	/// \param [in] thiz this pointer
	/// \param [in] proc Data frame callback function; It is advised to not put time-cosuming operation in this function, otherwise it will block follow-up data frames and affect real time performance
	/// \param [in] pUser user defined data
	/// \return success:0, fail:-1
	int32_t(*attachGrabbingEx)(struct GENICAM_StreamSource *thiz, callbackFunEx proc, void* pUser);

	/// \~chinese
	/// \brief 去注册数据帧回调函数(包含用户自定义数据)
	/// \param [in] thiz 本接口指针
	/// \param [in] proc 去注册数据帧回调函数
	/// \param [in] pUser 用户自定义数据(与attachGrabbingEx的pUser相同)
	/// \return 返回去注册是否成功，0表示成功，-1表示失败
	/// \~english
	/// \brief	Unregister data frame callback function(include user defined data)
	/// \param [in] thiz this pointer
	/// \param [in] proc Unregister data frame callback function(the same pUser of the attachGrabbingEx)
	/// \param [in] pUser user defined data
	/// \return success:0, fail:-1
	int32_t(*detachGrabbingEx)(struct GENICAM_StreamSource *thiz, callbackFunEx proc, void* pUser);


    /// \~chinese
    /// \brief 设置驱动包间隔时间(ms),仅对Gige设备有效
    /// \param [in] thiz 本接口指针
    /// \param [in] nTimeout 包间隔时间，单位ms
    /// \return 设置是否成功,0表示成功，-1表示失败
    /// \~english
    /// \brief	set packet timeout(ms),just for GigE devices
    /// \param [in] thiz this pointer
    /// \param [in] the value of timeout
    /// \return success:0, fail:-1
    int32_t(*setInterPacketTimeout)(struct GENICAM_StreamSource *thiz, uint32_t nTimeout);

	uint32_t  reserved[19];	///< \~chinese 保留  	///< \~english reserved field

}GENICAM_StreamSource;

/// \~chinese
/// \brief 流对象参数
/// 32位系统下128字节
/// \~english
/// \brief stream object parameter
/// 128 bytes in 32-bit system
typedef struct GENICAM_StreamSourceInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象		///< \~english camera object
	uint32_t channelId;         ///< \~chinese 通道号		///< \~english ID of channel
	uint32_t reserved[30];	    ///< \~chinese 保留			///< \~english reserved field
} GENICAM_StreamSourceInfo;

/// \~chinese
/// 创建流通道对象，该对象由外部调用该接口创建，释放时调用release接口
///
/// \param [in] pStreamSourceInfo 创建流对象的参数
/// \param [out] ppStreamSource   返回的流对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create stream channel object, this object is created by external call, and it requires to call release interface when release it
/// \param [in] pStreamSourceInfo create parameter of stream object
/// \param [out] ppStreamSource   return stream object
/// \retval < 0 create failed
/// \retval 0   create successful
GENICAM_API int32_t CALL_METHOD GENICAM_createStreamSource(const GENICAM_StreamSourceInfo* pStreamSourceInfo
										, GENICAM_StreamSource** ppStreamSource);
										
/// @}


typedef enum EVType
{
	offLine,   ///< \~chinese 设备离线通知    ///< \~english device offline notification
	onLine     ///< \~chinese 设备在线通知    ///< \~english device online notification
}EVType;

/// \~chinese
/// \brief 事件注册回调对象接口类
/// \defgroup Event 相机事件订阅注册与去注册接口
/// @{
/// \~english
/// \brief event subscribe callback interface class
/// \defgroup Event register camera event subscribe and unsubscribe interface 
/// @{

/// \~chinese
/// \brief 连接事件参数封装
/// \~english
/// \brief connection event parameters encapsulation
typedef struct GENICAM_SConnectArg
{
	EVType m_event;  		///< \~chinese 事件类型    ///< \~english event type
	uint32_t reserve[15]; 	///< \~chinese 预留字段    ///< \~english reserved field
}GENICAM_SConnectArg;

/// \~chinese
/// 参数更新事件参数封装
/// \~english
/// updating parameters event encapsulation
typedef struct GENICAM_SParamUpdataArg
{
	int32_t isPoll; 					                 ///< \~chinese 是否是定时更新,1表示是定时更新，0表示非定时更新   ///< \~english update periodically or not. 1 : update periodically, 0 : not update periodically
	uint32_t reserve[10];		                         ///< \~chinese 预留字段                 ///< \~english reserved field
	char paramNames[MAX_PARAM_CNT][MAX_STRING_LENTH];    ///< \~chinese 更新的参数名称集合,约定更新的参数不超过1000个，每个参数的字符串长度不超过256  ///< \~english array of parameter's name which need to be updated. the maximum number of parameters is 1000. and the max length of strings of each parameter is 255.
	uint32_t referenceParamCnt;                          ///< \~chinese 更新的参数个数           ///< \~english the number of parameters which need update
}GENICAM_SParamUpdataArg;

/// \~chinese
///枚举：流事件状态
/// \~english
/// enumeration:stream event status
typedef enum GENICAM_EEventStatus
{
	streamEventNormal = 1,      ///< \~chinese 正常流事件		///< \~english normal stream event
	streamEventLostFrame = 2,   ///< \~chinese 丢帧事件		    ///< \~english lost frame event
	streamEventLostPacket = 3,  ///< \~chinese 丢包事件		    ///< \~english lost packet event
	streamEventImageError = 4,       ///< \~chinese 图像错误事件		///< \~english error image event
	streamEventStreamChannelError   ///< \~chinese 取流错误事件 		///< \~english stream channel error event
}GENICAM_EEventStatus;

/// \~chinese
/// \brief 流事件参数封装
/// \~english
/// \brief stream event parameters encapsulation
typedef struct GENICAM_SStreamArg
{
	uint32_t     channel;					 ///< \~chinese 流通道号         ///< \~english channel no.
	uint64_t     blockID;					 ///< \~chinese 流数据BlockID    ///< \~english block ID of stream data
	uint64_t     timestamp;					 ///< \~chinese 时间戳           ///< \~english event timestamp
	GENICAM_EEventStatus eStreamEventStatus; ///< \~chinese 流事件状态码     ///< \~english stream event status code
	uint32_t	 status;					 ///< \~chinese 事件状态错误码   ///< \~english status error code
	uint32_t reserve[9];					 ///< \~chinese 预留字段         ///< \~english reserved field
}GENICAM_SStreamArg;

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

// \~chinese
/// \brief 流事件参数封装
/// \~english
/// \brief stream event parameters encapsulation
typedef struct GENICAM_SMsgChannelArg
{
	uint16_t  eventID;         ///< \~chinese 事件Id			///< \~english event id
	uint16_t  channelID;       ///< \~chinese 消息通道号		///< \~english channel id
	uint64_t  blockID;		   ///< \~chinese 流数据BlockID		///< \~english block ID of stream data
	uint64_t  timeStamp;       ///< \~chinese 时间戳			///< \~english event timestamp
	uint32_t   reserve[8];	   ///< \~chinese 预留字段         ///< \~english reserved field
	char paramNames[MAX_PARAM_CNT][MAX_STRING_LENTH];   ///< \~chinese 事件相关的属性名列表。约定属性名不超过1000个，每个属性名的字符串长度不超过256  ///< \~english array of parameter's name which is related. the maximum number of parameters is 1000. and the max length of strings of each parameter is 255.
	uint32_t referenceParamCnt;///< \~chinese 参数个数           ///< \~english the number of parameters which need update
}GENICAM_SMsgChannelArg;

/// \~chinese
/// \brief 设备连接状态事件回调函数声明
/// \~english
/// \brief call back function declaration of camera connection status event 
typedef void (*connectCallBack)(const GENICAM_SConnectArg* pConnectArg);

/// \~chinese
/// \brief 设备连接状态事件回调函数声明
/// \~english
/// \brief call back function declaration of camera connection status event 
typedef void(*connectCallBackEx)(const GENICAM_SConnectArg* pConnectArg, void* pUser);

/// \~chinese
/// \brief 参数更新事件回调函数声明
/// \~english
/// \brief call back function declaration of camera parameter update event 
typedef void (*paramUpdateCallBack)(const GENICAM_SParamUpdataArg* pParamUpdateArg);

/// \~chinese
/// \brief 参数更新事件回调函数声明
/// \~english
/// \brief call back function declaration of camera parameter update event 
typedef void(*paramUpdateCallBackEx)(const GENICAM_SParamUpdataArg* pParamUpdateArg, void* pUser);

/// \~chinese
/// \brief 设备流事件回调函数声明
/// \~english
/// \brief call back function declaration of stream event 
typedef void (*streamCallBack)(const GENICAM_SStreamArg* pStreamArg);

/// \~chinese
/// \brief 设备流事件回调函数声明
/// \~english
/// \brief call back function declaration of stream event 
typedef void(*streamCallBackEx)(const GENICAM_SStreamArg* pStreamArg, void *pUser);

/// \~chinese
/// \brief 消息通道事件回调函数声明
/// \~english
/// \brief call back function declaration of message channel event 
typedef void(*msgChannelCallBackEx)(const GENICAM_SMsgChannelArg* pMsgChannelArg, void *pUser);

/// \~chinese
/// \brief 事件订阅对象
/// 32位系统下128字节
/// \~english
/// \brief event subscribe object
/// 128 bytes in 32-bit system
typedef struct GENICAM_EventSubscribe
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t(*addRef)(struct GENICAM_EventSubscribe *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t(*release)(struct GENICAM_EventSubscribe *thiz);

	/// \~chinese
	/// \brief  设备连接状态事件回调注册,只支持一个回调函数有效
	/// \param [in] thiz 本接口指针
	/// \param [in] proc  设备连接状态事件回调注册函数
	/// \return 注册是否成功
	/// \~english
	/// \brief  register call back function of camera connection status event. only support one valid call back function
	/// \param [in] thiz this pointer
	/// \param [in] proc  register call back function of camera connection status event
	/// \return the result of registration
	int32_t(*subscribeConnectArgs)(struct GENICAM_EventSubscribe *thiz, const connectCallBack proc);

	/// \~chinese
	/// \brief  设备连接状态事件回调去注册
	/// \param [in] thiz 本接口指针
	/// \param [in] proc  设备连接状态事件回调去注册函数
	/// \return 去注册是否成功
	/// \~english
	/// \brief  unregister call back function of camera connection status event.
	/// \param [in] thiz this pointer
	/// \param [in] proc  unregister call back function of camera connection status event
	/// \return the result of unregistration
	int32_t(*unsubscribeConnectArgs)(struct GENICAM_EventSubscribe *thiz, const connectCallBack proc);

	/// \~chinese
	/// \brief  参数更新事件回调注册,只支持一个回调函数有效
	/// \param [in] thiz 本接口指针
	/// \param [in] proc 参数更新注册的事件回调函数
	/// \return 注册是否成功
	/// \~english
	/// \brief  register call back function of parameter update event. only support one valid call back function
	/// \param [in] thiz this pointer
	/// \param [in] proc  register call back function of parameter update event
	/// \return the result of registration
	int32_t (*subscribeParamUpdate)(struct GENICAM_EventSubscribe *thiz, const paramUpdateCallBack proc);

	/// \~chinese
	/// \brief  参数更新事件回调去注册
	/// \param [in] thiz 本接口指针
	/// \param [in] proc 参数更新事件去注册的回调函数
	/// \return 去注册是否成功
	/// \~english
	/// \brief  unregister call back function of parameter update event.
	/// \param [in] thiz this pointer
	/// \param [in] proc  unregister call back function of parameter update event
	/// \return the result of unregistration
	int32_t (*unsubscribeParamUpdate)(struct GENICAM_EventSubscribe *thiz, const paramUpdateCallBack proc);

	/// \~chinese
	/// \brief  流通道事件回调注册,只支持一个回调函数有效
	/// \param [in] thiz 本接口指针
	/// \param [in] proc 流通道事件回调注册函数
	/// \return 注册是否成功
	/// \~english
	/// \brief  register call back function of stream channel event. only support one valid call back function
	/// \param [in] thiz this pointer
	/// \param [in] proc  register call back function of stream channel event
	/// \return the result of registration
	int32_t (*subscribeStreamArg)(struct GENICAM_EventSubscribe *thiz, const streamCallBack proc);

	/// \~chinese
	/// \brief  流通道事件回调去注册
	/// \param [in] thiz 本接口指针
	/// \param [in] proc  流通道事件回调去注册函数
	/// \return 去注册是否成功
	/// \~english
	/// \brief  unregister call back function of stream channel event.
	/// \param [in] thiz this pointer
	/// \param [in] proc  unregister call back function of stream channel event
	/// \return the result of unregistration
	int32_t (*unsubscribeStreamArg)(struct GENICAM_EventSubscribe *thiz, const streamCallBack proc);

    /// \~chinese
    /// \brief  设备连接状态事件回调注册,只支持一个回调函数有效
    /// \param [in] thiz 本接口指针
    /// \param [in] proc  设备连接状态事件回调注册函数
    /// \param [in] pUser   用户自定义数据
    /// \return 注册是否成功
    /// \~english
    /// \brief  register call back function of camera connection status event. only support one valid call back function
    /// \param [in] thiz this pointer
    /// \param [in] proc  register call back function of camera connection status event
    /// \param [in] pUser user data
    /// \return the result of registration
    int32_t(*subscribeConnectArgsEx)(struct GENICAM_EventSubscribe *thiz, const connectCallBackEx proc, void* pUser);

    /// \~chinese
    /// \brief  设备连接状态事件回调去注册
    /// \param [in] thiz 本接口指针
    /// \param [in] proc  设备连接状态事件回调去注册函数
    /// \param [in] pUser   用户自定义数据
    /// \return 去注册是否成功
    /// \~english
    /// \brief  unregister call back function of camera connection status event.
    /// \param [in] thiz this pointer
    /// \param [in] proc  unregister call back function of camera connection status event
    /// \param [in] pUser user data
    /// \return the result of unregistration
    int32_t(*unsubscribeConnectArgsEx)(struct GENICAM_EventSubscribe *thiz, const connectCallBackEx proc, void *pUser);

	/// \~chinese
	/// \brief  参数更新事件回调注册,只支持一个回调函数有效
	/// \param [in] thiz 本接口指针
	/// \param [in] proc 参数更新注册的事件回调函数
    /// \param [in] pUser   用户自定义数据
	/// \return 注册是否成功
	/// \~english
	/// \brief  register call back function of parameter update event. only support one valid call back function
	/// \param [in] thiz this pointer
	/// \param [in] proc  register call back function of parameter update event
    /// \param [in] pUser user data
	/// \return the result of registration
	int32_t (*subscribeParamUpdateEx)(struct GENICAM_EventSubscribe *thiz, const paramUpdateCallBackEx proc, void* pUser);

	/// \~chinese
	/// \brief  参数更新事件回调去注册
	/// \param [in] thiz 本接口指针
	/// \param [in] proc 参数更新事件去注册的回调函数
    /// \param [in] pUser   用户自定义数据
	/// \return 去注册是否成功
	/// \~english
	/// \brief  unregister call back function of parameter update event.
	/// \param [in] thiz this pointer
	/// \param [in] proc  unregister call back function of parameter update event
    /// \param [in] pUser user data
	/// \return the result of unregistration
	int32_t (*unsubscribeParamUpdateEx)(struct GENICAM_EventSubscribe *thiz, const paramUpdateCallBackEx proc, void* pUser);

	/// \~chinese
	/// \brief  流通道事件回调注册,只支持一个回调函数有效
	/// \param [in] thiz 本接口指针
	/// \param [in] proc 流通道事件回调注册函数
    /// \param [in] pUser 用户自定义数据
	/// \return 注册是否成功
	/// \~english
	/// \brief  register call back function of stream channel event. only support one valid call back function
	/// \param [in] thiz this pointer
	/// \param [in] proc  register call back function of stream channel event
    /// \param [in] pUser user data
	/// \return the result of registration
	int32_t (*subscribeStreamArgEx)(struct GENICAM_EventSubscribe *thiz, const streamCallBackEx proc, void* pUser);

	/// \~chinese
	/// \brief  流通道事件回调去注册
	/// \param [in] thiz 本接口指针
	/// \param [in] proc  流通道事件回调去注册函数
    /// \param [in] pUser  用户自定义数据
	/// \return 去注册是否成功
	/// \~english
	/// \brief  unregister call back function of stream channel event.
	/// \param [in] thiz this pointer
	/// \param [in] proc  unregister call back function of stream channel event
    /// \param [in] pUser user data
	/// \return the result of unregistration
	int32_t (*unsubscribeStreamArgEx)(struct GENICAM_EventSubscribe *thiz, const streamCallBackEx proc, void* pUser);

	/// \~chinese
	/// \brief  消息通道事件回调注册,只支持一个回调函数有效
	/// \param [in] thiz 本接口指针
	/// \param [in] proc 消息通道事件回调注册函数
	/// \return 注册是否成功
	/// \~english
	/// \brief  register call back function of message channel event. only support one valid call back function
	/// \param [in] thiz this pointer
	/// \param [in] proc  register call back function of message channel event
	/// \return the result of registration
	int32_t(*subscribeMsgChannelEx)(struct GENICAM_EventSubscribe *thiz, const msgChannelCallBackEx proc, void* pUser);

	/// \~chinese
	/// \brief  消息通道事件回调去注册
	/// \param [in] thiz 本接口指针
	/// \param [in] proc  消息通道事件回调去注册函数
	/// \return 去注册是否成功
	/// \~english
	/// \brief  unregister call back function of message channel event.
	/// \param [in] thiz this pointer
	/// \param [in] proc  unregister call back function of message channel event
	/// \return the result of unregistration
	int32_t(*unsubscribeMsgChannelEx)(struct GENICAM_EventSubscribe *thiz, const msgChannelCallBackEx proc, void* pUser);
	
	uint32_t reserve[15];					 ///< \~chinese 预留字段    ///< \~english reserved field
}GENICAM_EventSubscribe;

/// \~chinese
/// \brief 事件订阅对象参数
/// 32位系统下128字节
/// \~english
/// \brief event subscribe info object
/// 128 bytes in 32-bit system
typedef struct GENICAM_EventSubscribeInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_EventSubscribeInfo;

/// \~chinese
/// 创建事件订阅对象
/// \param [in] pEventSubscribeInfo  创建事件订阅对象的参数
/// \param [out] ppEventSubscribe    返回的事件订阅对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create event subscribe object
/// \param [in] pEventSubscribeInfo  create event subscribe info object
/// \param [out] ppEventSubscribe    return event subscribe object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t  CALL_METHOD GENICAM_createEventSubscribe(const GENICAM_EventSubscribeInfo* pEventSubscribeInfo,
													GENICAM_EventSubscribe** ppEventSubscribe);
/// @}


/// \~chinese
/// \brief 相机对象接口类
/// \defgroup GENICAM_GigECamera  GigE相机对象操作接口
/// @{
/// \~english
/// \brief camera object interface class
/// \defgroup GENICAM_GigECamera  GigeVision Camera Object Operation Interface
/// @{
/// \~chinese													
/// \brief GiGE相机特殊接口
/// 32位系统下128字节
/// \~english
/// \brief GigE camera specific object
/// 128 bytes in 32-bit system
typedef struct GENICAM_GigECamera
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t(*addRef)(struct GENICAM_GigECamera *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t(*release)(struct GENICAM_GigECamera *thiz);

	/// \~chinese
	/// \brief 获取相机的ipAddress
	/// \param [in] thiz 本接口指针
	/// \return 返回ipAddress 相机的IP地址，失败返回NULL
	/// \~english
	/// \brief	get camera's ipAddress
	/// \param [in] thiz this pointer
	/// \return return camera's ipAddress, return NULL if failed 
	const char* (*getIpAddress)(struct GENICAM_GigECamera *thiz);

	/// \~chinese
	/// \brief 返回相机的子网掩码
	/// \param [in] thiz 本接口指针
	/// \return 返回subnetMask 相机的子网掩码，失败返回NULL
	/// \~english
	/// \brief return camera's subnetMask
	/// \param [in] thiz this pointer
	/// \return camera's subnetMask, return NULL if failed
	const char* (*getSubnetMask)(struct GENICAM_GigECamera *thiz);

	/// \~chinese
	/// \brief 返回相机的网关
	/// \param [in] thiz 本接口指针
	/// \return 返回 gateway 相机的网关，失败返回NULL
	/// \~english
	/// \brief return camera's gateway
	/// \param [in] thiz this pointer
	/// \return camera's gateway, return NULL if failed
	const char*  (*getGateway)(struct GENICAM_GigECamera *thiz);

	/// \~chinese
	/// \brief 获取相机的 macAddress
	/// \param [in] thiz 本接口指针
	/// \return 返回macAddress 相机的Mac地址，失败返回NULL
	/// \~english
	/// \brief get camera's macAddress
	/// \param [in] thiz this pointer
	/// \return camera's macAddress, return NULL if failed
	const char*  (*getMacAddress)(struct GENICAM_GigECamera *thiz);

	/// \~chinese
	/// \brief  修改设备IP	
	/// \brief 1、调用该函数时如果newSubnetMask和newGateway都设置了有效值，则以此有效值为准;
	/// \brief 2、调用该函数时如果newSubnetMask和newGateway都设置了NULL，则内部实现时用它所连接网卡的子网掩码和网关代替
	/// \brief 3、调用该函数时如果newSubnetMask和newGateway两者中其中一个为NULL，另一个非NULL，则返回失败
	/// \brief 该接口只针对通过网卡接入的设备，对于其余设备，调用此接口无意义，直接返回失败
	/// \param [in] thiz 本接口指针
	/// \param [in] newIpAddress 新的IP地址信息
	/// \param [in] newSubnetMask 新的掩码信息
	/// \param [in] newGateway 新的网关信息
	/// \retval < 0 修改IP失败
	/// \retval 0   修改IP成功
	/// \~english
	/// \brief  modify device IP	
	/// \brief 1、When callback this function, if the values of newSubnetMask and newGateway are both valid then we consider the value is correct
	/// \brief 2、When callback this function, if the values of newSubnetMask and newGateway are both NULL, then these values will be replaced by the subnetmask and gateway of NIC which this camera connect to.
	/// \brief 3、When callback this function, if there is one value of newSubnetMask or newGateway is NULL and the other one is not NULL, then return failed
	/// \brief this interface only serve the devices which is connected to NIC. As for other devices, callback this function won't work and return failed
	/// \param [in] thiz this pointer
	/// \param [in] newIpAddress new ip address 
	/// \param [in] newSubnetMask new subnetMask
	/// \param [in] newGateway new Gateway
	/// \retval < 0 modify ip failed
	/// \retval 0   modify ip success
	int32_t (*forceIpAddress)(struct GENICAM_GigECamera *thiz,const char* newIpAddress, const char* newSubnetMask, const char* newGateway);

	/// \~chinese
	/// \brief 获取相机的当前访问权限
	/// \return 如果获取成功，返回的枚举值代表相机的当前访问权限，如果失败，返回的枚举值为accessPermissionUnknown
	/// \~english
	/// \brief	get current access permission of camera
	/// \return success:return current access permission of camera, fail:return accessPermissionUnknown 
	GENICAM_ECameraAccessPermission (*getAccessPermission)(struct GENICAM_GigECamera *thiz);

	/// \~chinese
	/// \brief 获取相机的 Protocol Version
	/// \param [in] thiz 本接口指针
	/// \return 返回相机的Protocol Version，失败返回NULL
	/// \~english
	/// \brief get camera's Protocol Version
	/// \param [in] thiz this pointer
	/// \return camera's Protocol Version, return NULL if failed
	const char*  (*getProtocolVersion)(struct GENICAM_GigECamera *thiz);

	/// \~chinese
	/// \brief 获取相机的 IP Configuration
	/// \param [in] thiz 本接口指针
	/// \return 返回相机的IP Configuration，失败返回NULL
	/// \~english
	/// \brief get camera's IP Configuration
	/// \param [in] thiz this pointer
	/// \return camera's IP Configuration, return NULL if failed
	const char*  (*getIPConfiguration)(struct GENICAM_GigECamera *thiz);

	uint32_t reserve[21];					 ///< \~chinese 预留字段    ///< \~english reserved field
}GENICAM_GigECamera;

/// \~chinese
/// \brief 创建GigECamera对象参数
/// 32位系统下128字节
/// \~english
/// \brief create GigE camera object's info object
/// 128 bytes in 32-bit system
typedef struct GENICAM_GigECameraInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_GigECameraInfo;

/// \~chinese
/// 创建GiGE设备对象
/// \param [in] pGigECameraInfo 创建GiGE设备对象的参数
/// \param [out] ppGigECamera GigECamera 对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create GigE camera object
/// \param [in]  pGigECameraInfo GigE camera info object
/// \param [out] ppGigECamera    GigE camera object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createGigECamera(GENICAM_GigECameraInfo* pGigECameraInfo
													, GENICAM_GigECamera** ppGigECamera);
/// @}


/// \~chinese
/// \brief 相机接口类
/// \defgroup GigEInterface  连接GigE相机的接口
/// @{
/// \~english
/// \brief camera interface 
/// \defgroup GigEInterface Interface Of GigEVision Camera Connection
/// @{
typedef struct GENICAM_GigEInterface
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t(*addRef)(struct GENICAM_GigEInterface *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t(*release)(struct GENICAM_GigEInterface *thiz);

	/// \~chinese
	/// \param [in] thiz 本接口指针
	/// \return 返回网卡描述信息，失败返回NULL
	/// \~english
	/// \param [in] thiz this pointer
	/// \return return network card description, return NULL if failed
	const char * (*getDescription)(struct GENICAM_GigEInterface *thiz);

	/// \~chinese
	/// \param [in] thiz 本接口指针
	/// \return 返回网卡的IP地址，失败返回NULL
	/// \~english
	/// \param [in] thiz this pointer
	/// \return return NIC's IpAddress, return NULL if failed
	const char * (*getIpAddress)(struct GENICAM_GigEInterface *thiz);

	/// \~chinese
	/// \param [in] thiz 本接口指针
	/// \return 返回网卡的子网掩码，失败返回NULL
	/// \~english
	/// \param [in] thiz this pointer
	/// \return return NIC's subnetMask, return NULL if failed
	const char * (*getSubnetMask)(struct GENICAM_GigEInterface *thiz);

	/// \~chinese
	/// \brief 返回网卡的网关
	/// \param [in] thiz 本接口指针
	/// \return 返回网卡的网关，失败返回NULL
	/// \~english
	/// \brief return Gateway
	/// \param [in] thiz this pointer
	/// \return return NIC's Gateway, return NULL if failed
	const char * (*getGateway)(struct GENICAM_GigEInterface *thiz);

	/// \~chinese
	/// \param [in] thiz 本接口指针
	/// \return 返回网卡的Mac地址，失败返回NULL
	/// \~english
	/// \param [in] thiz this pointer
	/// \return return NIC's macAddress, return NULL if failed
	const char * (*getMacAddress)(struct GENICAM_GigEInterface *thiz);

	uint32_t reserve[24];					 ///< \~chinese 预留字段    ///< \~english reserved field
}GENICAM_GigEInterface;

/// \~chinese
/// \brief 创建GiGE设备接口对象参数
/// 32位系统下128字节
/// \~english
/// \brief create GigE camera interface object 
/// 128 bytes in 32-bit system
typedef struct GENICAM_GigEInterfaceInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_GigEInterfaceInfo;

/// \~chinese
/// 创建GiGE设备接口对象
/// \param [in] pGigEInterfaceInfo 创建GiGE设备对象的参数
/// \param [out] ppGigEInterface GigE Camera 所连接的接口对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create GigE camera interface object
/// \param [in] pGigEInterfaceInfo parameter used to create GigE camera object
/// \param [out] ppGigEInterface interface ojbect which connect the GigE Camera
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createGigEInterface(GENICAM_GigEInterfaceInfo*pGigEInterfaceInfo
	, GENICAM_GigEInterface** ppGigEInterface);
/// @}



/// \~chinese
/// \brief 相机对象接口类
/// \defgroup GENICAM_UsbCamera  USB相机对象操作接口
/// @{
/// \~english
/// \brief camera object interface class
/// \defgroup GENICAM_UsbCamera USB Camera Object Operation Interface
/// @{
/// \~chinese													
/// \brief USB相机特殊接口
/// 32位系统下128字节
/// \~english
/// \brief USB camera specific object
/// 128 bytes in 32-bit system
typedef struct GENICAM_UsbCamera
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t(*addRef)(struct GENICAM_UsbCamera *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t(*release)(struct GENICAM_UsbCamera *thiz);

	/// \~chinese
	/// \brief 获取相机的 Configuration Valid
	/// \param [in] thiz 本接口指针
	/// \return 返回相机的 Configuration Valid，失败返回NULL
	/// \~english
	/// \brief get camera's Configuration Valid
	/// \param [in] thiz this pointer
	/// \return camera's Configuration Valid, return NULL if failed
	const char*  (*getConfigurationValid)(struct GENICAM_UsbCamera *thiz);

	/// \~chinese
	/// \brief 获取相机的 GenCP Version
	/// \param [in] thiz 本接口指针
	/// \return 返回相机的 GenCP Version，失败返回NULL
	/// \~english
	/// \brief get camera's GenCP Version
	/// \param [in] thiz this pointer
	/// \return camera's GenCP Version, return NULL if failed
	const char*  (*getGenCPVersion)(struct GENICAM_UsbCamera *thiz);

	/// \~chinese
	/// \brief 获取相机的 U3V Version
	/// \param [in] thiz 本接口指针
	/// \return 返回相机的 U3V Version，失败返回NULL
	/// \~english
	/// \brief get camera's U3V Version
	/// \param [in] thiz this pointer
	/// \return camera's U3V Version, return NULL if failed
	const char*  (*getU3VVersion)(struct GENICAM_UsbCamera *thiz);

	/// \~chinese
	/// \brief 获取相机的 Device GUID
	/// \param [in] thiz 本接口指针
	/// \return 返回相机的 Device GUID，失败返回NULL
	/// \~english
	/// \brief get camera's Device GUID
	/// \param [in] thiz this pointer
	/// \return camera's Device GUID, return NULL if failed
	const char*  (*getDeviceGUID)(struct GENICAM_UsbCamera *thiz);

	/// \~chinese
	/// \brief 获取相机的 Family Name
	/// \param [in] thiz 本接口指针
	/// \return 返回相机的 Family Name，失败返回NULL
	/// \~english
	/// \brief get camera's Family Name
	/// \param [in] thiz this pointer
	/// \return camera's Family Name, return NULL if failed
	const char*  (*getFamilyName)(struct GENICAM_UsbCamera *thiz);

	/// \~chinese
	/// \brief 获取相机的序列号
	/// \param [in] thiz 本接口指针
	/// \return 返回相机的序列号，失败返回NULL
	/// \~english
	/// \brief get camera's serial number
	/// \param [in] thiz this pointer
	/// \return camera's serial number, return NULL if failed
	const char*  (*getU3VSerialNumber)(struct GENICAM_UsbCamera *thiz);

	/// \~chinese
	/// \brief 相机是否支持 Low Speed
	/// \param [in] thiz 本接口指针
	/// \return 0 支持, -1 不支持
	/// \~english
	/// \brief if Low Speed is supported
	/// \param [in] thiz this pointer
	/// \return 0 if supported, return -1 if not supported
	int32_t (*isLowSpeedSupported)(struct GENICAM_UsbCamera *thiz);
	
	/// \~chinese
	/// \brief 相机是否支持 Full Speed
	/// \param [in] thiz 本接口指针
	/// \return 0 支持, -1 不支持
	/// \~english
	/// \brief if Full Speed is supported
	/// \param [in] thiz this pointer
	/// \return 0 if supported, return -1 if not supported
	int32_t (*isFullSpeedSupported)(struct GENICAM_UsbCamera *thiz);

	/// \~chinese
	/// \brief 相机是否支持 High Speed
	/// \param [in] thiz 本接口指针
	/// \return 0 支持, -1 不支持
	/// \~english
	/// \brief if High Speed is supported
	/// \param [in] thiz this pointer
	/// \return 0 if supported, return -1 if not supported
	int32_t (*isHighSpeedSupported)(struct GENICAM_UsbCamera *thiz);

	/// \~chinese
	/// \brief 相机是否支持 Super Speed
	/// \param [in] thiz 本接口指针
	/// \return 0 支持, -1 不支持
	/// \~english
	/// \brief if Super Speed is supported
	/// \param [in] thiz this pointer
	/// \return 0 if supported, return -1 if not supported
	int32_t (*isSuperSpeedSupported)(struct GENICAM_UsbCamera *thiz);

	/// \~chinese
	/// \brief 获取相机的 Speed
	/// \param [in] thiz 本接口指针
	/// \return 返回相机的 Speed，失败返回NULL
	/// \~english
	/// \brief get camera's Speed
	/// \param [in] thiz this pointer
	/// \return camera's Speed, return NULL if failed
	const char*  (*getSpeed)(struct GENICAM_UsbCamera *thiz);

	/// \~chinese
	/// \brief 获取相机的 Max Power
	/// \param [in] thiz 本接口指针
	/// \return 返回相机的 Max Power，失败返回NULL
	/// \~english
	/// \brief get camera's Max Power
	/// \param [in] thiz this pointer
	/// \return camera's Max Power, return NULL if failed
	const char*  (*getMaxPower)(struct GENICAM_UsbCamera *thiz);

	/// \~chinese
	/// \brief 是否安装了USB驱动
	/// \param [in] thiz 本接口指针
	/// \return 0 安装了USB驱动，-1 没有安装USB驱动
	/// \~english
	/// \brief if USB driver is installed
	/// \param [in] thiz this pointer
	/// \return 0 if installed, return -1 if not installed
	int32_t (*isDriverInstalled)(struct GENICAM_UsbCamera *thiz);

	uint32_t reserve[16];					 ///< \~chinese 预留字段    ///< \~english reserved field
}GENICAM_UsbCamera;

/// \~chinese
/// \brief 创建UsbCamera对象参数
/// 32位系统下128字节
/// \~english
/// \brief create Usb camera object's info object
/// 128 bytes in 32-bit system
typedef struct GENICAM_UsbCameraInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_UsbCameraInfo;

/// \~chinese
/// 创建USB设备对象
/// \param [in] pUsbCameraInfo 创建USB设备对象的参数
/// \param [out] ppUsbCamera UsbCamera 对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create USB camera object
/// \param [in]  pUsbCameraInfo USB camera info object
/// \param [out] ppUsbCamera    USB camera object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createUsbCamera(GENICAM_UsbCameraInfo* pUsbCameraInfo
	, GENICAM_UsbCamera** ppUsbCamera);
/// @}



/// \~chinese
/// \brief 相机接口类
/// \defgroup UsbInterface  连接USB相机的接口
/// \~english
/// \brief camera interface 
/// \defgroup UsbInterface Interface Of USB Camera Connection
/// @{
typedef struct GENICAM_UsbInterface
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t(*addRef)(struct GENICAM_UsbInterface *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t(*release)(struct GENICAM_UsbInterface *thiz);

	/// \~chinese
	/// \param [in] thiz 本接口指针
	/// \return 返回描述信息，失败返回NULL
	/// \~english
	/// \param [in] thiz this pointer
	/// \return return description, return NULL if failed
	const char * (*getDescription)(struct GENICAM_UsbInterface *thiz);

	/// \~chinese
	/// \param [in] thiz 本接口指针
	/// \return 返回 Vendor ID，失败返回NULL
	/// \~english
	/// \param [in] thiz this pointer
	/// \return return Vendor ID, return NULL if failed
	const char * (*getVendorID)(struct GENICAM_UsbInterface *thiz);

	/// \~chinese
	/// \param [in] thiz 本接口指针
	/// \return 返回 Device ID，失败返回NULL
	/// \~english
	/// \param [in] thiz this pointer
	/// \return return Device ID, return NULL if failed
	const char * (*getDeviceID)(struct GENICAM_UsbInterface *thiz);

	/// \~chinese
	/// \param [in] thiz 本接口指针
	/// \return 返回 Subsystem ID，失败返回NULL
	/// \~english
	/// \param [in] thiz this pointer
	/// \return return Subsystem ID, return NULL if failed
	const char * (*getSubsystemID)(struct GENICAM_UsbInterface *thiz);

	/// \~chinese
	/// \param [in] thiz 本接口指针
	/// \return 返回 Revision，失败返回NULL
	/// \~english
	/// \param [in] thiz this pointer
	/// \return return Revision, return NULL if failed
	const char * (*getRevision)(struct GENICAM_UsbInterface *thiz);

	/// \~chinese
	/// \param [in] thiz 本接口指针
	/// \return 返回接口的speed，失败返回NULL
	/// \~english
	/// \param [in] thiz this pointer
	/// \return return speed of interface, return NULL if failed
	const char * (*getSpeed)(struct GENICAM_UsbInterface *thiz);

	uint32_t reserve[23];					 ///< \~chinese 预留字段    ///< \~english reserved field
}GENICAM_UsbInterface;

/// \~chinese
/// \brief 创建USB设备接口对象参数
/// 32位系统下128字节
/// \~english
/// \brief create USB camera interface object 
/// 128 bytes in 32-bit system
typedef struct GENICAM_UsbInterfaceInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_UsbInterfaceInfo;

/// \~chinese
/// 创建USB设备接口对象
/// \param [in] pUsbInterfaceInfo 创建USB设备对象的参数
/// \param [out] ppUsbInterface Usb Camera 所连接的接口对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create USB camera interface object
/// \param [in] pUsbInterfaceInfo parameter used to create Usb camera object
/// \param [out] ppUsbInterface interface ojbect which connect the Usb Camera
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createUsbInterface(GENICAM_UsbInterfaceInfo*pUsbInterfaceInfo
									, GENICAM_UsbInterface** ppUsbInterface);
/// @}


// 配置参数相关的接口

/// \~chinese
/// \brief 常用参数对象接口
/// \defgroup config 属性配置相关操作接口
/// @{
/// \~english
/// \brief common parameter object interface
/// \defgroup config Property Configure Operation Interface 
/// @{

/// \~chinese
/// \brief Class GENICAM_IntNode 整型属性操作类
/// 32位系统下128字节
/// \~english
/// \brief Integer property operation class
/// 128 bytes in 32-bit system
typedef struct GENICAM_IntNode
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_IntNode *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_IntNode *thiz);

	/// \~chinese
	/// \brief 获取属性值
	/// \param [in] thiz 本接口指针
	/// \param [out] pVal 获取到的属性值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get property's value
	/// \param [in] thiz this pointer
	/// \param [out] pVal the property value
	/// \return success:0, fail:-1
	int32_t (*getValue)(struct GENICAM_IntNode *thiz, int64_t* pVal);

	/// \~chinese
	/// \brief 设置属性值
	/// \param [in] thiz 本接口指针
	/// \param [in] val 待设置的属性值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief set the property's value
	/// \param [in] thiz this pointer
	/// \param [in] val the value to be set for this property
	/// \return success:0, fail:-1
	int32_t (*setValue)(struct GENICAM_IntNode *thiz, int64_t val);

	/// \~chinese
	/// \brief 获取属性可设最小值
	/// \param [in] thiz 本接口指针
	/// \param [out] pMinVal 获取到的属性最小值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get the property's minimum value that can be set
	/// \param [in] thiz this pointer
	/// \param [out] pMinVal the property's minimum value
	/// \return success:0, fail:-1
	int32_t (*getMinVal)(struct GENICAM_IntNode *thiz, int64_t* pMinVal);

	/// \~chinese
	/// \brief 获取属性可设最大值
	/// \param [in] thiz 本接口指针
	/// \param [out] pMaxVal 获取到的属性最大值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get the property's maximum value that can be set
	/// \param [in] thiz this pointer
	/// \param [out] pMaxVal the property's maximum value
	/// \return success:0, fail:-1
	int32_t (*getMaxVal)(struct GENICAM_IntNode *thiz, int64_t* pMaxVal);

	/// \~chinese
	/// \brief 判断属性是否有效
	/// \param [in] thiz 本接口指针
	/// \return 0表示有效，-1表示无效
	/// \~english
	/// \brief check the property is available or not
	/// \param [in] thiz this pointer
	/// \return valid:0, invalid:-1
	int32_t (*isValid)(struct GENICAM_IntNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否可用
	/// \param [in] thiz 本接口指针
	/// \return 0表示可用，-1表示不可用
	/// \~english
	/// \brief check the property is available or not
	/// \param [in] thiz this pointer
	/// \return available:0, not available:-1
	int32_t(*isAvailable)(struct GENICAM_IntNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否可读
	/// \param [in] thiz 本接口指针
	/// \return 0表示可读，-1表示不可读
	/// \~english
	/// \brief check the property is readable or not
	/// \param [in] thiz this pointer
	/// \return readable:0, not readable:-1
	int32_t(*isReadable)(struct GENICAM_IntNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否可写
	/// \param [in] thiz 本接口指针
	/// \return 0表示可写，-1表示不可写
	/// \~english
	/// \brief check the property is writeable or not
	/// \param [in] thiz this pointer
	/// \return writeable:0, not writeable:-1
	int32_t(*isWriteable)(struct GENICAM_IntNode *thiz);

	/// \~chinese
	/// \brief 获取属性步长
	/// \param [in] thiz 本接口指针
	/// \param [out] pVal 获取到的属性步长
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get property's increment
	/// \param [in] thiz this pointer
	/// \param [out] pVal the property increment
	/// \return success:0, fail:-1
	int32_t(*getIncrement)(struct GENICAM_IntNode *thiz, int64_t* pVal);

	uint32_t reserve[20];					 ///< \~chinese 预留字段    ///< \~english reserved field

}GENICAM_IntNode;


/// \~chinese
/// \brief 创建整数节点类型信息
/// 32位系统下128 + 1024 字节
/// \~english
/// \brief create int node type's info
/// 128 + 1024  bytes in 32-bit system
typedef struct GENICAM_IntNodeInfo
{
	GENICAM_Camera* pCamera;	        ///< \~chinese 相机对象    ///< \~english camera object
	char attrName[MAX_ATTR_NAME_LEN];   ///< \~chinese 属性名称    ///< \~english attribute name
	uint32_t reserved[31];	            ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_IntNodeInfo;

/// \~chinese
/// 创建整数节点类型对象
/// \param [in] pIntNodeInfo 创建整数节点类型信息
/// \param [out] ppIntNode   整数类型对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create IntNode property object class
/// \param [in]  pIntNodeInfo create IntNode info
/// \param [out] ppIntNode    IntNode type object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createIntNode(GENICAM_IntNodeInfo* pIntNodeInfo
	, GENICAM_IntNode** ppIntNode);


/// \~chinese
/// \brief Class GENICAM_DoubleNode 浮点数属性操作类
/// 32位系统下128字节
/// \~english
/// \brief Float property operation class
/// 128 bytes in 32-bit system
typedef struct GENICAM_DoubleNode
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_DoubleNode *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_DoubleNode *thiz);

	/// \~chinese
	/// \brief 获取属性值
	/// \param [in] thiz 本接口指针
	/// \param [out] pVal 获取到的属性值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get property's value
	/// \param [in] thiz this pointer
	/// \param [out] pVal the property's value
	/// \return success:0, fail:-1
	int32_t (*getValue)(struct GENICAM_DoubleNode *thiz, double* pVal);

	/// \~chinese
	/// \brief 设置属性值
	/// \param [in] thiz 本接口指针
	/// \param [in] val 待设置的属性值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief set property's value
	/// \param [in] thiz this pointer
	/// \param [in] val the value to be set for this property
	/// \return success:0, fail:-1
	int32_t (*setValue)(struct GENICAM_DoubleNode *thiz, double val);

	/// \~chinese
	/// \brief 获取属性可设最小值
	/// \param [in] thiz 本接口指针
	/// \param [out] pMinVal 获取到的属性最小值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get the property's minimum value that can be set
	/// \param [in] thiz this pointer
	/// \param [out] pMinVal the property's minimum value
	/// \return success:0, fail:-1
	int32_t (*getMinVal)(struct GENICAM_DoubleNode *thiz, double* pMinVal);

	/// \~chinese
	/// \brief 获取属性可设最大值
	/// \param [in] thiz 本接口指针
	/// \param [out] pMaxVal 获取到的属性最大值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get the property's maximum value that can be set
	/// \param [in] thiz this pointer
	/// \param [out] pMaxVal the property's maximum value
	/// \return success:0, fail:-1
	int32_t (*getMaxVal)(struct GENICAM_DoubleNode *thiz, double* pMaxVal);

	/// \~chinese
	/// \brief 判断属性是否有效
	/// \param [in] thiz 本接口指针
	/// \return 0表示有效，-1表示无效
	/// \~english
	/// \brief check the property is valid or not
	/// \param [in] thiz this pointer
	/// \return valid:0, invalid:-1
	int32_t (*isValid)(struct GENICAM_DoubleNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否可用
	/// \param [in] thiz 本接口指针
	/// \return 0表示可用，-1表示不可用
	/// \~english
	/// \brief check the property is available or not
	/// \param [in] thiz this pointer
	/// \return available:0, not available:-1
	int32_t(*isAvailable)(struct GENICAM_DoubleNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否可读
	/// \param [in] thiz 本接口指针
	/// \return 0表示可读，-1表示不可读
	/// \~english
	/// \brief check the property is readable or not
	/// \param [in] thiz this pointer
	/// \return readable:0, not readable:-1
	int32_t(*isReadable)(struct GENICAM_DoubleNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否可写
	/// \param [in] thiz 本接口指针
	/// \return 0表示可写，-1表示不可写
	/// \~english
	/// \brief check the property is writeable or not
	/// \param [in] thiz this pointer
	/// \return writeable:0, not writeable:-1
	int32_t(*isWriteable)(struct GENICAM_DoubleNode *thiz);

	uint32_t reserve[21];					 ///< \~chinese 预留字段    ///< \~english reserved field

}GENICAM_DoubleNode;


/// \~chinese
/// \brief 创建浮点数节点类型信息
/// 32位系统下128 + 1024 字节
/// \~english
/// \brief create double node info
/// 128 + 1024 bytes in 32-bit system
typedef struct GENICAM_DoubleNodeInfo
{
	GENICAM_Camera* pCamera;	        ///< \~chinese 相机对象    ///< \~english camera object
	char attrName[MAX_ATTR_NAME_LEN];   ///< \~chinese 属性名称    ///< \~english property's name
	uint32_t reserved[31];	            ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_DoubleNodeInfo;

/// \~chinese
/// 创建浮点数节点类型对象
/// \param [in]  pDoubleNodeInfo 创建浮点数节点类型信息
/// \param [out] ppDoubleNode   浮点数类型对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create double node object
/// \param [in]  pDoubleNodeInfo create double node info
/// \param [out] ppDoubleNode    double node object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createDoubleNode(GENICAM_DoubleNodeInfo* pDoubleNodeInfo
	, GENICAM_DoubleNode** ppDoubleNode);

/// \~chinese
/// \brief Class GENICAM_EnumNode 枚举型属性操作类
/// 32位系统下128字节
/// \~english
/// \brief EnumNode property operation class
/// 128 bytes in 32-bit system
typedef struct GENICAM_EnumNode
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_EnumNode *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_EnumNode *thiz);

	/// \~chinese
	/// \brief 获取枚举属性symbol值
	/// \param [in] thiz 本接口指针
	/// \param [in/out] pVal  获取到的属性值,约定字符串长度最大为256，该内存由外部分配
	/// \param [in/out] pMaxCnt 输入的字符串长度，出参时为实际的字符串长度
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get enum property symbol's value
	/// \param [in] thiz this pointer
	/// \param [in/out] pVal  the length of property's value cannot exceed 256, this memory is also allocated externally
	/// \param [in/out] pMaxCnt the length of input chars; actual length of chars when output
	/// \return success:0, fail:-1
	int32_t (*getValueSymbol)(struct GENICAM_EnumNode *thiz, char* pVal, uint32_t *pMaxCnt);

	/// \~chinese
	/// \brief 设置枚举属性symbol值
	/// \param [in] thiz 本接口指针
	/// \param [in] strSymbolName 待设置的属性值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief set enum property symbol's value
	/// \param [in] thiz this pointer
	/// \param [in] strSymbolName the value waiting to be set for this property
	/// \return success:0, fail:-1
	int32_t (*setValueBySymbol)(struct GENICAM_EnumNode *thiz,const char* strSymbolName);

	/// \~chinese
	/// \brief 获取枚举属性可设置的symbol值列表
	/// \param [in] thiz 本接口指针
	/// \param [out] symbolList  获取到的可设置的symbol值列表，字符长度最长为256.例如:char symbolList[12][256]
	/// \param [in/out] pSymbolCnt in:申请的缓冲数量,当作为输入参数时，与symbolList的一维个数一致，最多为1000; out:获取到的可设置的symbol个数.
	/// \return 返回属性当前可设置symbol值列表
	/// \~english
	/// \brief Get the list of Enum property symbol value which can be set
	/// \param [in] thiz this pointer
	/// \param [out] symbolList  get the configurable symbol's value list, maximum length of chars is 256.For example:char symbolList[12][256]
	/// \param [in/out] pSymbolCnt in:buffer count is equal to the number of one dimension in symbolList; out:get the number of configurable symbol's value list, maximum number is 1000
	/// \return Return the list of Enum property symbol value which can be set now
	int32_t(*getEnumSymbolList)(struct GENICAM_EnumNode *thiz, char symbolList[][256], uint32_t *pSymbolCnt);

	/// \~chinese
	/// \brief 判断属性是否有效
	/// \param [in] thiz 本接口指针
	/// \return 0表示有效，-1表示无效
	/// \~english
	/// \brief check the property is valid or not
	/// \param [in] thiz this pointer
	/// \return valid:0, invalid:-1
	int32_t (*isValid)(struct GENICAM_EnumNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否可用
	/// \param [in] thiz 本接口指针
	/// \return 0表示可用，-1表示不可用
	/// \~english
	/// \brief check the property is available or not
	/// \param [in] thiz this pointer
	/// \return available:0, not available:-1
	int32_t(*isAvailable)(struct GENICAM_EnumNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否可读
	/// \param [in] thiz 本接口指针
	/// \return 0表示可读，-1表示不可读
	/// \~english
	/// \brief check the property is readable or not
	/// \param [in] thiz this pointer
	/// \return readable:0, not readable:-1
	int32_t(*isReadable)(struct GENICAM_EnumNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否可写
	/// \param [in] thiz 本接口指针
	/// \return 0表示可写，-1表示不可写
	/// \~english
	/// \brief check the property is writeable or not
	/// \param [in] thiz this pointer
	/// \return writeable:0, not writeable:-1
	int32_t(*isWriteable)(struct GENICAM_EnumNode *thiz);

	/// \~chinese
	/// \brief 设置枚举属性value值
	/// \param [in] thiz 本接口指针
	/// \param [in] val 待设置的枚举值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief set symbol value of enum property
	/// \param [in] thiz this pointer
	/// \param [in] val the value waiting to be set for this property
	/// \return success:0, fail:-1
	int32_t(*setValue)(struct GENICAM_EnumNode *thiz, uint64_t val);

	/// \~chinese
	/// \brief 获取枚举属性value值
	/// \param [in] thiz 本接口指针
	/// \param [out] val 获取到的枚举值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get symbol value of enum property
	/// \param [in] thiz this pointer
	/// \param [out] val the property's value
	/// \return success:0, fail:-1
	int32_t(*getValue)(struct GENICAM_EnumNode *thiz, uint64_t *pVal);

	/// \~chinese
	/// \brief 通过symbol获取枚举的value值
	/// \param [in] thiz 本接口指针
	/// \param [in] strSymbolName 枚举字符串
	/// \param [out] val 获取到的枚举值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get symbol value of enum property by symbol string
	/// \param [in] thiz this pointer
	/// \param [in] strSymbolName the property's string
	/// \param [out] val the property's value
	/// \return success:0, fail:-1
	int32_t(*getValueBySymbol)(struct GENICAM_EnumNode *thiz, const char *strSymbolName, uint64_t *pVal);

	/// \~chinese
	/// \brief 通过value获取枚举的symbol值
	/// \param [in] thiz 本接口指针
	/// \param [in] val 枚举值
	/// \param [in/out] strSymbolName 获取到的枚举字符串,约定字符串长度最大为256，该内存由外部分配
	/// \param [in/out] pMaxCnt 输入的字符串长度，出参时为实际的字符串长度
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get symbol of enum property by value
	/// \param [in] thiz this pointer
	/// \param [in] val the property's value
	/// \param [in/out] strSymbolName the length of property's value cannot exceed 256, this memory is also allocated externally
	/// \param [in/out] pMaxCnt the length of input chars; actual length of chars when output
	/// \return success:0, fail:-1
	int32_t(*getSymbolByValue)(struct GENICAM_EnumNode *thiz, uint64_t val, char *strSymbolName, uint32_t *pMaxCnt);

	uint32_t reserve[18];					 ///< \~chinese 预留字段    ///< \~english reserved field

}GENICAM_EnumNode;


/// \~chinese
/// \brief 创建枚举节点类型信息
/// 32位系统下128 + 1024 字节
/// \~english
/// \brief create enum node info
/// 128 + 1024 bytes in 32-bit system
typedef struct GENICAM_EnumNodeInfo
{
	GENICAM_Camera* pCamera;	        ///< \~chinese 相机对象    ///< \~english camera object
	char attrName[MAX_ATTR_NAME_LEN];   ///< \~chinese 属性名称    ///< \~english attribute name
	uint32_t reserved[31];	            ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_EnumNodeInfo;

/// \~chinese
/// 创建枚举节点类型对象
/// \param [in]  pEnumNodeInfo 创建枚举节点类型信息
/// \param [out] ppEnumNode    枚举类型对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create enum node type object
/// \param [in]  pEnumNodeInfo create enum node info
/// \param [out] ppEnumNode    enum node object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createEnumNode(GENICAM_EnumNodeInfo* pEnumNodeInfo
	, GENICAM_EnumNode** ppEnumNode);


/// \~chinese
/// \brief Class GENICAM_BoolNode 布尔型属性操作类
/// 32位系统下128字节
/// \~english
/// \brief Bool property operation class
/// 128 bytes in 32-bit system
typedef struct GENICAM_BoolNode
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_BoolNode *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_BoolNode *thiz);

	/// \~chinese
	/// \brief 获取属性值
	/// \param [in] thiz 本接口指针
	/// \param [out] pVal 获取到的属性值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get property's value
	/// \param [in] thiz this pointer
	/// \param [out] pVal property's value 
	/// \return success:0, fail:-1
	int32_t (*getValue)(struct GENICAM_BoolNode *thiz,uint32_t *pVal);

	/// \~chinese
	/// \brief 设置属性值
	/// \param [in] thiz 本接口指针
	/// \param [in] val 待设置的属性值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief set the property'value 
	/// \param [in] thiz this pointer
	/// \param [in] val the value to be set for this property
	/// \return success:0, fail:-1	
	int32_t (*setValue)(struct GENICAM_BoolNode *thiz, uint32_t val);

	/// \~chinese
	/// \brief 判断属性是否有效
	/// \param [in] thiz 本接口指针
	/// \return 0表示有效，-1表示无效
	/// \~english
	/// \brief check the validity of this property
	/// \param [in] thiz this pointer
	/// \return valid:0, invalid:-1
	int32_t (*isValid)(struct GENICAM_BoolNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否可用
	/// \param [in] thiz 本接口指针
	/// \return 0表示可用，-1表示不可用
	/// \~english
	/// \brief check the property is available or not
	/// \param [in] thiz this pointer
	/// \return available:0, not available:-1
	int32_t(*isAvailable)(struct GENICAM_BoolNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否可读
	/// \param [in] thiz 本接口指针
	/// \return 0表示可读，-1表示不可读
	/// \~english
	/// \brief check the property is readable or not
	/// \param [in] thiz this pointer
	/// \return readable:0, not readable:-1
	int32_t(*isReadable)(struct GENICAM_BoolNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否可写
	/// \param [in] thiz 本接口指针
	/// \return 0表示可写，-1表示不可写
	/// \~english
	/// \brief check the property is writeable or not
	/// \param [in] thiz this pointer
	/// \return writeable:0, not writeable:-1
	int32_t(*isWriteable)(struct GENICAM_BoolNode *thiz);

	uint32_t reserve[23];					 ///< \~chinese 预留字段    ///< \~english reserved field

}GENICAM_BoolNode;


/// \~chinese
/// \brief 创建布尔节点类型信息
/// 32位系统下128 + 1024 字节
/// \~english
/// \brief create bool node info
/// 128 + 1024 bytes in 32-bit system
typedef struct GENICAM_BoolNodeInfo
{
	GENICAM_Camera* pCamera;	        ///< \~chinese 相机对象    ///< \~english camera object
	char attrName[MAX_ATTR_NAME_LEN];   ///< \~chinese 属性名称    ///< \~english attribute name
	uint32_t reserved[31];	            ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_BoolNodeInfo;

/// \~chinese
/// 创建布尔节点类型对象
/// \param [in]  pBoolNodeInfo 创建布尔节点类型信息
/// \param [out] ppBoolNode    布尔类型对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create Bool node object
/// \param [in]  pBoolNodeInfo create bool node info
/// \param [out] ppBoolNode    bool node object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createBoolNode(GENICAM_BoolNodeInfo* pBoolNodeInfo
	, GENICAM_BoolNode** ppBoolNode);


/// \~chinese
/// \brief 命令型属性操作类
/// 32位系统下128字节
/// \~english
/// \brief CmdNode property operation class
/// 128 bytes in 32-bit system
typedef struct GENICAM_CmdNode
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_CmdNode *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_CmdNode *thiz);

	/// \~chinese
	/// \brief 执行命令类型属性
	/// \param [in] thiz 本接口指针
	/// \return 成功返回0，失败返回-1
	/// \~english 
	/// \brief execute command property
	/// \param [in] thiz this pointer
	/// \return success:0, fail:-1
	int32_t (*execute)(struct GENICAM_CmdNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否有效
	/// \param [in] thiz 本接口指针
	/// \return 0表示有效，-1表示无效
	/// \~english
	/// \brief check validity of the property
	/// \param [in] thiz this pointer
	/// \return valid:0, invalid:-1
	int32_t (*isValid)(struct GENICAM_CmdNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否可用
	/// \param [in] thiz 本接口指针
	/// \return 0表示可用，-1表示不可用
	/// \~english
	/// \brief check the property is available or not
	/// \param [in] thiz this pointer
	/// \return available:0, not available:-1
	int32_t (*isAvailable)(struct GENICAM_CmdNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否可读
	/// \param [in] thiz 本接口指针
	/// \return 0表示可读，-1表示不可读
	/// \~english
	/// \brief check the property is readable or not
	/// \param [in] thiz this pointer
	/// \return readable:0, not readable:-1
	int32_t(*isReadable)(struct GENICAM_CmdNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否可写
	/// \param [in] thiz 本接口指针
	/// \return 0表示可写，-1表示不可写
	/// \~english
	/// \brief check the property is writeable or not
	/// \param [in] thiz this pointer
	/// \return writeable:0, not writeable:-1
	int32_t(*isWriteable)(struct GENICAM_CmdNode *thiz);

	uint32_t reserve[24];					 ///< \~chinese 预留字段    ///< \~english reserved field

}GENICAM_CmdNode;

/// \~chinese
/// \brief 创建命令节点类型信息
/// 32位系统下128 + 1024 字节
/// \~english
/// \brief create command node info
/// 128 + 1024 bytes in 32-bit system
typedef struct GENICAM_CmdNodeInfo
{
	GENICAM_Camera* pCamera;	        ///< \~chinese 相机对象    ///< \~english camera object
	char attrName[MAX_ATTR_NAME_LEN];   ///< \~chinese 属性名称    ///< \~english attribute name
	uint32_t reserved[31];	            ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_CmdNodeInfo;

/// \~chinese
/// 创建命令节点类型对象
/// \param [in]  pCmdNodeInfo 创建命令节点类型信息
/// \param [out] ppCmdNode    命令类型对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create command node object
/// \param [in]  pCmdNodeInfo create command node info
/// \param [out] ppCmdNode    command node object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createCmdNode(GENICAM_CmdNodeInfo* pCmdNodeInfo
	, GENICAM_CmdNode** ppCmdNode);


/// \~chinese
/// \brief GENICAM_StringNode string属性操作类
/// 32位系统下128字节
/// \~english
/// \brief string property operation class
/// 128 bytes in 32-bit system
typedef struct GENICAM_StringNode
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_StringNode *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_StringNode *thiz);

	/// \~chinese
	/// \brief 获取属性值
	/// \param [in] thiz 本接口指针
	/// \param [in/out] pOutStr 获取到的属性值，约定字符最大长度为256,该内存由外部分配
	/// \param [in/out] pMaxCnt 入参时为输入内存的长度，出参时为实际的字符长度
	/// \return 成功返回0，否则-1
	/// \~english
	/// \brief get property's value
	/// \param [in] thiz this pointer
	/// \param [in/out] pOutStr Get the property's value, and the length of char cannot exceed 256, this memory is allocated externally
	/// \param [in/out] pMaxCnt At input, it is the length of input memory; At output, it is the actual length of chars 
	/// \return success:0, fail:-1	
	int32_t (*getValue)(struct GENICAM_StringNode *thiz,char*pOutStr,uint32_t *pMaxCnt);

	/// \~chinese
	/// \brief 设置属性值
	/// \param [in] thiz 本接口指针
	/// \param [in] pInStr 待输入的属性值
	/// \return 成功则返回0，否则返回-1
	/// \~english
	/// \brief set the property
	/// \param [in] thiz this pointer
	/// \param [in] pInStr the value waiting to be input for this property
	/// \return success:0, fail:-1	
	int32_t (*setValue)(struct GENICAM_StringNode *thiz, const char *pInStr);

	/// \~chinese
	/// \brief 判断属性是否有效
	/// \param [in] thiz 本接口指针
	/// \return 0表示有效，-1表示无效
	/// \~english
	/// \brief check validity of the property
	/// \param [in] thiz this pointer
	/// \return valid:0, invalid:-1
	int32_t (*isValid)(struct GENICAM_StringNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否可用
	/// \param [in] thiz 本接口指针
	/// \return 0表示可用，-1表示不可用
	/// \~english
	/// \brief check the property is available or not
	/// \param [in] thiz this pointer
	/// \return available:0, not available:-1
	int32_t(*isAvailable)(struct GENICAM_StringNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否可读
	/// \param [in] thiz 本接口指针
	/// \return 0表示可读，-1表示不可读
	/// \~english
	/// \brief check the property is readable or not
	/// \param [in] thiz this pointer
	/// \return readable:0, not readable:-1
	int32_t(*isReadable)(struct GENICAM_StringNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否可写
	/// \param [in] thiz 本接口指针
	/// \return 0表示可写，-1表示不可写
	/// \~english
	/// \brief check the property is writeable or not
	/// \param [in] thiz this pointer
	/// \return writeable:0, not writeable:-1
	int32_t(*isWriteable)(struct GENICAM_StringNode *thiz);

	uint32_t reserve[23];					 ///< \~chinese 预留字段    ///< \~english reserved field

}GENICAM_StringNode;


/// \~chinese
/// \brief 创建字符串节点类型信息
/// 32位系统下128 + 1024 字节
/// \~english
/// \brief create string node info
/// 128 + 1024 bytes in 32-bit system
typedef struct GENICAM_StringNodeInfo
{
	GENICAM_Camera* pCamera;	        ///< \~chinese 相机对象    ///< \~english camera object
	char attrName[MAX_ATTR_NAME_LEN];   ///< \~chinese 属性名称    ///< \~english attribute name
	uint32_t reserved[31];	            ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_StringNodeInfo;

/// \~chinese
/// 创建字符串节点类型对象
/// \param [in]  pStringNodeInfo 创建字符串节点类型信息
/// \param [out] ppStringNode    字符串类型对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create string node object
/// \param [in]  pStringNodeInfo create string node info
/// \param [out] ppStringNode    string node object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createStringNode(GENICAM_StringNodeInfo* pStringNodeInfo
	, GENICAM_StringNode** ppStringNode);



/// \~chinese
/// \brief GENICAM_AcquisitionControl 下属性操作类
/// \~english
/// \brief AcquisitionControl's property operation class
typedef struct GENICAM_AcquisitionControl
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t(*addRef)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t(*release)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取AcquisitionFrameCount属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get AcquisitionFrameCount's property operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_IntNode (*acquisitionFrameCount)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取AcquisitionFrameRate属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get AcquisitionFrameRate property's operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_DoubleNode (*acquisitionFrameRate)(struct GENICAM_AcquisitionControl *thiz);


	/// \~chinese
	/// \brief 获取AcquisitionFrameRateEnable使能属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get AcquisitionFrameRateEnable property operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_BoolNode(*acquisitionFrameRateEnable)(struct GENICAM_AcquisitionControl *thiz);


	/// \~chinese
	/// \brief 获取AcquisitionFrameRate属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get AcquisitionFrameRate property operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*acquisitionMode)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取ExposureAuto属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get ExposureAuto property operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*exposureAuto)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取ExposureMode属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get ExposureMode property operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*exposureMode)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取ExposureTime属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get ExposureTime property operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_DoubleNode (*exposureTime)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取TriggerActivation属性操作对象，设置触发上升沿下降沿
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get TriggerActivation property operation object,set trigger as rising edge or falling edge
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*triggerActivation)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取TriggerDelay属性操作对象，设置软触发延时
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get TriggerDelay property operation object, set soft trigger delay
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_DoubleNode (*triggerDelay)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取TriggerMode属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get TriggerMode property operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*triggerMode)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取TriggerSelector属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get TriggerSelector property operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*triggerSelector)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取TriggerSource属性操作对象，设置内部/外部触发
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL	
	/// \~english
	/// \brief get TriggerSource property operation object, set internal/external trigger
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*triggerSource)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取TriggerSoftware属性操作对象，执行内部软触发
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get TriggerSoftware property operation object, execute internal soft trigger
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_CmdNode (*triggerSoftware)(struct GENICAM_AcquisitionControl *thiz);

	uint32_t reserve[17];					 ///< \~chinese 预留字段    ///< \~english reserved field
}GENICAM_AcquisitionControl;

/// \~chinese
/// brief 创建属性节点AcquisitionControl信息
/// 32位系统下128字节
/// \~english
/// brief create parameter node AcquisitionControl info
/// 128 bytes in 32-bit system
typedef struct GENICAM_AcquisitionControlInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	   	///< \~chinese 保留        ///< \~english reserved field
} GENICAM_AcquisitionControlInfo;

/// \~chinese
/// 创建属性节点AcquisitionControl
/// \param [in]  pAcquisitionControlInfo 创建属性节点AcquisitionControl对象的参数
/// \param [out] ppAcquisitionControl 属性节点AcquisitionControl对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create parameter node : AcquisitionControl
/// \param [in]  pAcquisitionControlInfo create AcquisitionControl info
/// \param [out] ppAcquisitionControl    AcquisitionControl object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createAcquisitionControl(GENICAM_AcquisitionControlInfo*pAcquisitionControlInfo,
																	GENICAM_AcquisitionControl** ppAcquisitionControl);

typedef enum GENICAM_EConfigSet 
{
	userSet1 = 1,			///< \~chinese 【读写】相机配置集合1    ///< \~english user set 1
	userSet2 = 2,			///< \~chinese 【读写】相机配置集合2    ///< \~english user set 2
	userSetInvalid
}GENICAM_EConfigSet;

/// \~chinese
/// \brief GENICAM_UserSetControl 下属性操作类
/// \~english
/// \brief UserSetControl property operation class
typedef struct GENICAM_UserSetControl
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_UserSetControl *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_UserSetControl *thiz);

	/// \~chinese
	/// \brief 恢复相机默认配置
	/// \param [in] thiz 本接口指针
	/// \return 成功返回0，否则返回-1
	/// \~english
	/// \brief restore default 
	/// \param [in] thiz this pointer
	/// \return success:0, fail:-1
	int32_t (*restoreDefault)(struct GENICAM_UserSetControl *thiz);

	/// \~chinese
	/// \brief 设置相机当前配置，并生效且下次以该配置启动
	/// \param [in] thiz 本接口指针
	/// \param [in] configSet 要设置的配置集合
	/// \return 成功返回0，否则返回-1
	/// \~english
	/// \brief set current camera configuration, these configurations will take effect immediately and load this userset on next time when start camera
	/// \param [in] thiz this pointer
	/// \param [in] configSet configuration set 
	/// \return success:0, fail:-1
	int32_t (*setCurrentUserSet)(struct GENICAM_UserSetControl *thiz, GENICAM_EConfigSet configSet);

	/// \~chinese
	/// \brief 保存相机当前配置到某配置集合，如userSet1
	/// \param [in] thiz 本接口指针
	/// \param [in] configSet 要保存到的配置集合
	/// \return 成功返回0，否则返回-1
	/// \~english
	/// \brief save current configuration into certain userset, for example, userSet1
	/// \param [in] thiz this pointer
	/// \param [in] configSet User set which is going to save
	/// \return success:0, fail:-1
	int32_t (*saveUserSet)(struct GENICAM_UserSetControl *thiz, GENICAM_EConfigSet configSet);

	/// \~chinese
	/// \brief 获取相机当前配置集合
	/// \param [in] thiz 本接口指针
	/// \return 返回配置集合枚举值
	/// \~english
	/// \brief get current user set
	/// \param [in] thiz this pointer
	/// \return user set enumeration value
	GENICAM_EConfigSet (*getCurrentUserSet)(struct GENICAM_UserSetControl *thiz);

	/// \~chinese
	/// \brief 获取相机当前UserSet相关是否可用
	/// \param [in] thiz 本接口指针
	/// \return 可用返回0，否则返回-1
	/// \~english
	/// \brief check validity of current user set 
	/// \param [in] thiz this pointer
	/// \return available:0, not available:-1
	int32_t (*isAvailable)(struct GENICAM_UserSetControl *thiz);

	uint32_t reserve[24];					 ///< \~chinese 预留字段    ///< \~english reserved field

}GENICAM_UserSetControl;

/// \~chinese
/// \brief 创建属性节点UserSetControl信息
/// 32位系统下128字节
/// \~english
/// \brief create UserSetControl info
/// 128 bytes in 32-bit system
typedef struct GENICAM_UserSetControlInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_UserSetControlInfo;

/// \~chinese
/// 创建属性节点UserSetControl
/// \param [in]  pUserSetControlInfo 创建属性节点UserSetControl对象的参数
/// \param [out] ppUserSetControl 属性节点UserSetControl对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create UserSetControl
/// \param [in]  pUserSetControlInfo create UserSetControl info
/// \param [out] ppUserSetControl    UserSetControl object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createUserSetControl(GENICAM_UserSetControlInfo* pUserSetControlInfo
										, GENICAM_UserSetControl** ppUserSetControl);


/// \~chinese
/// \brief GENICAM_ISPControl 下属性操作类
/// \~english
/// \brief ISPControl property operation class
typedef struct GENICAM_ISPControl
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_ISPControl *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_ISPControl *thiz);

	/// \~chinese
	/// \brief 获取Brightness属性操作对象，设置亮度
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get Brightness property operation object, set brightness
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_IntNode (*brightness)(struct GENICAM_ISPControl *thiz);

	/// \~chinese
	/// \brief 获取Sharpness属性操作对象，设置锐度
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get Sharpness property operation object, set sharpness
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_IntNode (*sharpness)(struct GENICAM_ISPControl *thiz);

	/// \~chinese
	/// \brief 获取SharpnessAuto属性操作对象，设置是否自动锐度
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get SharpnessAuto property operation object, set whether activate auto sharpness or not
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_BoolNode (*sharpnessAuto)(struct GENICAM_ISPControl *thiz);

	/// \~chinese
	/// \brief 获取SharpnessEnable属性操作对象，设置是否开启锐度
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english 
	/// \brief get SharpnessEnable property operation object, set whether enable sharpness or not
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*sharpnessEnable)(struct GENICAM_ISPControl *thiz);

	/// \~chinese
	/// \brief 获取Contrast属性操作对象，设置对比度
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get Contrast property operation object, set contrast
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_IntNode (*contrast)(struct GENICAM_ISPControl *thiz);

	/// \~chinese
	/// \brief 获取Hue属性操作对象，设置色度
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get Hue property operation object, set hue
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_IntNode (*hue)(struct GENICAM_ISPControl *thiz);

	/// \~chinese
	/// \brief 获取Saturation属性操作对象，设置饱和度
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get Saturation property operation object, set saturation
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_IntNode (*saturation)(struct GENICAM_ISPControl *thiz);

	uint32_t reserved[22];	   ///< \~chinese 保留    ///< \~english reserved field

}GENICAM_ISPControl;

/// \~chinese
/// \brief 创建属性节点信息
/// 32位系统下128字节
/// \~english
/// \brief create property node info
/// 128 bytes in 32-bit system
typedef struct GENICAM_ISPControlInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_ISPControlInfo;

/// \~chinese
/// 创建属性节点
/// \param [in]  pISPControlInfo 创建属性节点ISPControl对象的参数
/// \param [out] ppISPControl 属性节点ISPControl对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create property node
/// \param [in]  pISPControlInfo create ISPControl info
/// \param [out] ppISPControl    create ISPControl object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createISPControl(GENICAM_ISPControlInfo* pISPControlInfo
				, GENICAM_ISPControl** ppISPControl);


/// \~chinese
/// \brief AnalogControl 下属性操作类
/// 32位系统下128字节
/// \~english
/// \brief AnalogControl property operation class
/// 128 bytes in 32-bit system
typedef struct GENICAM_AnalogControl
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_AnalogControl *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_AnalogControl *thiz);

	/// \~chinese
	/// \brief 获取BlackLevelSelector属性操作对象，设置操作哪个白平衡
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get BlackLevelSelector property operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*blackLevelSelector)(struct GENICAM_AnalogControl *thiz);

	/// \~chinese
	/// \brief 获取BlackLevelAuto属性操作对象，设置自动白平衡
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get BalanceWhiteAuto property operation object, set auto white balance
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*blackLevelAuto)(struct GENICAM_AnalogControl *thiz);

	/// \~chinese
	/// \brief 获取BlackLevel属性操作对象，设置白平衡值
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get BlackLevel property operation object, set black level
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_IntNode (*blackLevel)(struct GENICAM_AnalogControl *thiz);

	/// \~chinese
	/// \brief 获取GainAuto属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get GainAuto property operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*gainAuto)(struct GENICAM_AnalogControl *thiz);

	/// \~chinese
	/// \brief 获取GainRaw属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get GainRaw operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_DoubleNode (*gainRaw)(struct GENICAM_AnalogControl *thiz);

	/// \~chinese
	/// \brief 获取Gamma属性操作对象，设置Gamma值
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get Gamma operation object, set gamma
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_DoubleNode (*gamma)(struct GENICAM_AnalogControl *thiz);
	
	/// \~chinese
	/// \brief 获取BalanceRatioSelector属性操作对象，设置操作哪个白平衡
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get BalanceRatioSelector property operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*balanceRatioSelector)(struct GENICAM_AnalogControl *thiz);
	
	/// \~chinese
	/// \brief 获取BalanceWhiteAuto属性操作对象，设置自动白平衡
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get BalanceWhiteAuto property operation object, set auto white balance
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*balanceWhiteAuto)(struct GENICAM_AnalogControl *thiz);
	
	/// \~chinese
	/// \brief 获取BalanceRatioSelector属性操作对象，设置操作哪个白平衡
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get BalanceRatioSelector property operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_DoubleNode (*balanceRatio)(struct GENICAM_AnalogControl *thiz);
	
	uint32_t reserve[20];					 ///< \~chinese 预留字段    ///< \~english reserved field
}GENICAM_AnalogControl;

/// \~chinese
/// \brief 创建属性节点信息
/// 32位系统下128字节
/// \~english
/// \brief create property node info
/// 128 bytes in 32-bit system
typedef struct GENICAM_AnalogControlInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_AnalogControlInfo;

/// \~chinese
/// 创建属性节点
/// \param [in]  pAnalogControlInfo 创建属性节点AnalogControl对象的参数
/// \param [out] ppAnalogControl    属性节点AnalogControl对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create property node
/// \param [in]  pAnalogControlInfo create AnalogControl info
/// \param [out] ppAnalogControl    AnalogControl object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t  CALL_METHOD GENICAM_createAnalogControl(GENICAM_AnalogControlInfo* pAnalogControlInfo
						, GENICAM_AnalogControl** ppAnalogControl);


/// \~chinese
/// \brief GENICAM_DeviceControl 下属性操作类
/// 32位系统下128字节
/// \~english
/// \brief DeviceControl property operation calss
/// 128 bytes in 32-bit system
typedef struct GENICAM_DeviceControl
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_DeviceControl *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_DeviceControl *thiz);

	/// \~chinese
	/// \brief 获取DeviceUserID属性操作对象，该对象可读写
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get DeviceUserID property operation object which are readable and writable
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_StringNode (*deviceUserID)(struct GENICAM_DeviceControl *thiz);

	uint32_t reserve[28];    ///< \~chinese 预留字段    ///< \~english reserved field
}GENICAM_DeviceControl;

/// \~chinese
/// \brief 创建属性节点信息
/// 32位系统下128字节
/// \~english
/// \brief create property node info
/// 128 bytes in 32-bit system
typedef struct GENICAM_DeviceControlInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_DeviceControlInfo;

/// \~chinese
/// 创建属性节点
/// \param [in]  pDeviceControlInfo 创建属性节点DeviceControl对象的参数
/// \param [out] ppDeviceControl    属性节点DeviceControl对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create property node
/// \param [in]  pDeviceControlInfo create DeviceControl info
/// \param [out] ppDeviceControl    DeviceControl object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createDeviceControl(GENICAM_DeviceControlInfo* pDeviceControlInfo
									, GENICAM_DeviceControl** ppDeviceControl);


/// \~chinese
/// \brief GENICAM_DigitalIOControl 下属性操作类
/// 32位系统下128字节
/// \~english
/// \brief DigitalIOControl property operation calss
/// 128 bytes in 32-bit system
typedef struct GENICAM_DigitalIOControl
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t(*addRef)(struct GENICAM_DigitalIOControl *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t(*release)(struct GENICAM_DigitalIOControl *thiz);

	/// \~chinese
	/// \brief 获取LineSelector属性操作对象，该对象可读写
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get LineSelector property operation object which is readable and writable
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode(*lineSelector)(struct GENICAM_DigitalIOControl *thiz);

	/// \~chinese
	/// \brief 获取LineDebouncerTimeAbs属性操作对象，该对象可读
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get LineDebouncerTimeAbs property operation object which is readable and writable 
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_DoubleNode(*lineDebouncerTimeAbs)(struct GENICAM_DigitalIOControl *thiz);

	/// \~chinese
	/// \brief 获取UserOutputSelector属性操作对象，该对象可读写
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get UserOutputSelector property operation object which is readable and writable
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode(*userOutputSelector)(struct GENICAM_DigitalIOControl *thiz);

	/// \~chinese
	/// \brief 获取UserOutputValue属性操作对象，该对象可读写
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get UserOutputValue's property operation object which is readable and writable
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_BoolNode(*userOutputValue)(struct GENICAM_DigitalIOControl *thiz);


	uint32_t reserve[25];    ///< \~chinese 预留字段    ///< \~english reserved field
}GENICAM_DigitalIOControl;

/// \~chinese
/// \brief 创建属性节点信息
/// 32位系统下128字节
/// \~english
/// \brief create property node info
/// 128 bytes in 32-bit system
typedef struct GENICAM_DigitalIOControlInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_DigitalIOControlInfo;

/// \~chinese
/// 创建属性节点
/// \param [in]  pDigitalIOControlInfo 创建属性节点DigitalIOControl对象的参数
/// \param [out] ppDigitalIOControl    属性节点DigitalIOControl对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create property node
/// \param [in]  pDigitalIOControlInfo create DigitalIOControl info
/// \param [out] ppDigitalIOControl    DigitalIOControl object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createDigitalIOControl(GENICAM_DigitalIOControlInfo* pDigitalIOControlInfo
	, GENICAM_DigitalIOControl** ppDigitalIOControl);


/// \~chinese
/// \brief GENICAM_TransportLayerControl 下属性操作类
/// 32位系统下128字节
/// \~english
/// \brief TransportLayerControl property operation class 
/// 128 bytes in 32-bit system
typedef struct GENICAM_TransportLayerControl
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_TransportLayerControl *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_TransportLayerControl *thiz);

	/// \~chinese
	/// \brief 获取GevSCPD属性操作对象，设置包发送间隔
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get GevSCPD property operation object, set packet sending interval 
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_IntNode (*gevSCPD)(struct GENICAM_TransportLayerControl *thiz);

	uint32_t reserve[28];    ///< \~chinese 预留字段    ///< \~english reserved field

}GENICAM_TransportLayerControl;

/// \~chinese
/// \brief 创建属性节点信息
/// 32位系统下128字节
/// \~english
/// \brief create property node info
/// 128 bytes in 32-bit system
typedef struct GENICAM_TransportLayerControlInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_TransportLayerControlInfo;

/// \~chinese
/// 创建属性节点
/// \param [in]  pTransportControlInfo 创建属性节点TransportLayerControl对象的参数
/// \param [out] ppTransportControl   属性节点TransportLayerControl对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create property node
/// \param [in]  pTransportControlInfo create TransportLayerControl info
/// \param [out] ppTransportControl    TransportLayerControl object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createTransportLayerControl(GENICAM_TransportLayerControlInfo* pTransportControlInfo
								, GENICAM_TransportLayerControl** ppTransportControl);


/// \~chinese
/// \brief GENICAM_ImageFormatControl 下属性操作类
/// 32位系统下128字节
/// \~english
/// \brief ImageFormatControl property operation class
/// 128 bytes in 32-bit system
typedef struct GENICAM_ImageFormatControl
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// Underlying private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// add interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_ImageFormatControl *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_ImageFormatControl *thiz);

	/// \~chinese
	/// \brief 获取Height属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get Height property operation object
	/// \param [in] thiz this pointer
	/// \return success:property's object, fail:NULL
	GENICAM_IntNode (*height)(struct GENICAM_ImageFormatControl *thiz);

	/// \~chinese
	/// \brief 获取Width属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get Width property operation object
	/// \param [in] thiz this pointer
	/// \return success:property's object, fail:NULL
	GENICAM_IntNode (*width)(struct GENICAM_ImageFormatControl *thiz);

	/// \~chinese
	/// \brief 获取OffsetX属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get OffsetX property operation object
	/// \param [in] thiz this pointer
	/// \return success:property's object, fail:NULL
	GENICAM_IntNode (*offsetX)(struct GENICAM_ImageFormatControl *thiz);

	/// \~chinese
	/// \brief 获取OffsetY属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get OffsetY property operation object
	/// \param [in] thiz this pointer
	/// \return success:property's object, fail:NULL
	GENICAM_IntNode (*offsetY)(struct GENICAM_ImageFormatControl *thiz);

	/// \~chinese
	/// \brief 获取PixelFormat属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get PixelFormat property operation object
	/// \param [in] thiz this pointer
	/// \return success:property's object, fail:NULL
	GENICAM_EnumNode (*pixelFormat)(struct GENICAM_ImageFormatControl *thiz);

	/// \~chinese
	/// \brief 获取ReverseX属性操作对象，设置是否翻转图像X轴
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get ReverseX property operation object, set whether reverse X or not
	/// \param [in] thiz this pointer
	/// \return property operation object,return NULL if failed
	GENICAM_BoolNode (*reverseX)(struct GENICAM_ImageFormatControl *thiz);

	/// \~chinese
	/// \brief 获取ReverseY属性操作对象，设置是否翻转图像Y轴
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get ReverseY property operation object, set whether reverse Y or not
	/// \param [in] thiz this pointer
	/// \return property operation object,return NULL if failed
	GENICAM_BoolNode (*reverseY)(struct GENICAM_ImageFormatControl *thiz);

	uint32_t reserve[22];					 ///< \~chinese 预留字段    ///< \~english reserved field

}GENICAM_ImageFormatControl;

/// \~chinese
/// \brief 创建属性节点信息
/// 32位系统下128字节
/// \~english
/// \brief create property node info
/// 128 bytes in 32-bit system
typedef struct GENICAM_ImageFormatControlInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_ImageFormatControlInfo;

/// \~chinese
/// 创建属性节点
/// \param [in]  pImageFormatControlInfo 创建属性节点ImageFormatControl对象的参数
/// \param [out] ppImageFormatControl    属性节点ImageFormatControl对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create property node
/// \param [in]  pImageFormatControlInfo create ImageFormatControl info
/// \param [out] ppImageFormatControl    ImageFormatControl object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t  CALL_METHOD GENICAM_createImageFormatControl(GENICAM_ImageFormatControlInfo* pImageFormatControlInfo,
												GENICAM_ImageFormatControl** ppImageFormatControl);

/// @}


#ifdef __cplusplus
}
#endif 

#endif