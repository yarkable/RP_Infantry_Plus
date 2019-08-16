/**
* @file   ImageConvert.h
* @brief  图像格式转换.
* @author 
* @par    Copyright (c):
*         All Rights Reserved
* @version 1.0.0.1
*/

#ifndef __IMAGE_CONVERT_H_
#define __IMAGE_CONVERT_H_

#ifdef  __cplusplus
extern "C"{
#endif  // end #ifdef  __cplusplus

#ifdef WIN64
#undef WIN32
#endif

	/** 编译选项 */
#ifdef WIN32  // win64位下，会报和def重复定义的警告 In Win 64bit, it will report warning for duplicate definition
#  ifdef _USRDLL // 动态库导出 Export DLL
#    ifdef IMAGECONVERT_EXPORTS
#		define IMGCNV_API __declspec(dllexport)
#	 else
#		define IMGCNV_API __declspec(dllimport)
#	 endif
#  else
#    define IMGCNV_API
#  endif // end of ifdef _USRDLL
#else
#	define IMGCNV_API
#endif //end #ifdef WIN32

#if (defined (WIN32) || defined(WIN64))
#   define CALLMETHOD __stdcall
#else
#	define CALLMETHOD
#endif // end #if (defined (WIN32) || defined(WIN64))

	typedef void* IMGCNV_HANDLE;        ///< 转码API使用的句柄 Handle for using conversion API

	/**
	* @enum IMGCNV_EErr
	* @brief 接口返回值 Return value
	* @attention 无 No
	*/
	typedef enum tagIMGCNV_EErr
	{
		IMGCNV_SUCCESS,
		IMGCNV_ILLEGAL_PARAM,			 ///< 非法参数 Illegal parameter
		IMGCNV_ERR_ORDER,                ///< 调用接口顺序错误 Sequence error for calling interfaces
		IMGCNV_NO_MEMORY,				 ///< 内存不足 No memory
		IMGCNV_NOT_SUPPORT,              ///< 不支持   Not support
	}IMGCNV_EErr;

	typedef struct tagIMGCNV_SOpenParam
	{
		int width;							///< 图像宽 Image width
		int height;							///< 图像高 Image Height
		int paddingX;						///< 图像宽填充 Padding X
		int paddingY;						///< 图像高填充 Padding Y
		int dataSize;						///< 图像大小   Image size
		unsigned int pixelForamt;			///< 源图像的图像格式 Image format of source image
	}IMGCNV_SOpenParam;

	typedef enum tagIMGCNV_EBayerDemosaic
	{
		IMGCNV_DEMOSAIC_NEAREST_NEIGHBOR,		 ///< 最近邻 Nearest neighbor
		IMGCNV_DEMOSAIC_BILINEAR,				 ///< 双线性 Bilinear
		IMGCNV_DEMOSAIC_EDGE_SENSING,			 ///< 边缘检测 Edge sensing
		IMGCNV_DEMOSAIC_NOT_SUPPORT = 255,       ///< 不支持 Not support
	}IMGCNV_EBayerDemosaic;

	/**
    *  ~chinese  
	*  @brief  转换为BGR24的转换函数
	*  @param[in] pSrcData		：源数据
	*  @param[in] pOpenParam	：IMGCNV_SOpenParam结构体,格式转换所需要的参数
	*  @param[out]pDstData		：转换后的数据	
	*  @param[out]pDstDataSize	：转换后数据的长度	
	*  @Return:   IMGCNV_ERR_E  : 图像格式转换接口返回值
	*  - IMGCNV_SUCCESS 表示执行成功
	*  - 其他值见IMGCNV_ERR_E枚举
	*  特别说明
	*  像素格式为YUV411Packed的时，图像宽须能被4整除
	*  像素格式为YUV422Packed的时，图像宽须能被2整除
	*  像素格式为YUYVPacked的时，图像宽须能被2整除
	*  转换后的图像:数据存储是从最上面第一行开始的，这个是相机数据的默认存储方向
	*  ~english  
	*  @brief  convert to BGR24
	*  @param[in] pSrcData		：source data
	*  @param[in] pOpenParam	：conversion required paraneters
	*  @param[out]pDstData		：converted data
	*  @param[out]pDstDataSize	：length of converted data 
	*  @Return:   IMGCNV_ERR_E	:return value
	*  - IMGCNV_SUCCESS return ok
	*  - Other values refers to enumeration of IMGCNV_ERR_E 
	*  Special note
	*  pixelFormat:YUV411Packed,the image width is divisible by 4
	*  pixelFormat:YUV422Packed,the image width is divisible by 2
	*  pixelFormat:YUYVPacked，the image width is divisible by 2
	*  converted image：The first row of the image is located at the start of the image buffer.This is the default for image taken by a camera.
	*/
	IMGCNV_API IMGCNV_EErr CALLMETHOD IMGCNV_ConvertToBGR24(unsigned char* pSrcData, IMGCNV_SOpenParam* pOpenParam, unsigned char* pDstData, int* pDstDataSize);

	/**
    *  ~chinese  
	*  @brief  转换为RGB24的转换函数
	*  @param[in] pSrcData		：源数据
	*  @param[in] pOpenParam	：IMGCNV_SOpenParam结构体,格式转换所需要的参数
	*  @param[out]pDstData		：转换后的数据	
	*  @param[out]pDstDataSize	：转换后数据的长度	
	*  @Return:   IMGCNV_ERR_E  : 图像格式转换接口返回值
	*  - IMGCNV_SUCCESS 表示执行成功
	*  - 其他值见IMGCNV_ERR_E枚举
	*  特别说明
	*  像素格式为YUV411Packed的时，图像宽须能被4整除
	*  像素格式为YUV422Packed的时，图像宽须能被2整除
	*  像素格式为YUYVPacked的时，图像宽须能被2整除
	*  转换后的图像:数据存储是从最上面第一行开始的，这个是相机数据的默认存储方向
	*  ~english  
	*  @brief  convert to RGB24
	*  @param[in] pSrcData		：source data
	*  @param[in] pOpenParam	：conversion required paraneters
	*  @param[out]pDstData		：converted data
	*  @param[out]pDstDataSize	：length of converted data 
	*  @Return:   IMGCNV_ERR_E	:return value
	*  - IMGCNV_SUCCESS return ok
	*  - Other values refers to enumeration of IMGCNV_ERR_E 
	*  Special note
	*  pixelFormat:YUV411Packed,the image width is divisible by 4
	*  pixelFormat:YUV422Packed,the image width is divisible by 2
	*  pixelFormat:YUYVPacked，the image width is divisible by 2
	*  converted image：The first row of the image is located at the start of the image buffer.This is the default for image taken by a camera.
	*/
	IMGCNV_API IMGCNV_EErr CALLMETHOD IMGCNV_ConvertToRGB24(unsigned char* pSrcData, IMGCNV_SOpenParam* pOpenParam, unsigned char* pDstData, int* pDstDataSize);

	/**
	*  ~chinese
	*  @brief  转换为Mono8的转换函数
	*  @param[in] pSrcData		：源数据
	*  @param[in] pOpenParam	：IMGCNV_SOpenParam结构体,格式转换所需要的参数
	*  @param[out]pDstData		：转换后的数据
	*  @param[out]pDstDataSize	：转换后数据的长度
	*  @Return:   IMGCNV_ERR_E  : 图像格式转换接口返回值
	*  - IMGCNV_SUCCESS 表示执行成功
	*  - 其他值见IMGCNV_ERR_E枚举
	*  特别说明
	*  像素格式为YUV411Packed的时，图像宽须能被4整除
	*  像素格式为YUV422Packed的时，图像宽须能被2整除
	*  像素格式为YUYVPacked的时，图像宽须能被2整除
	*  转换后的图像:数据存储是从最上面第一行开始的，这个是相机数据的默认存储方向
	*  ~english
	*  @brief  convert to Mono8
	*  @param[in] pSrcData		：source data
	*  @param[in] pOpenParam	：conversion required paraneters
	*  @param[out]pDstData		：converted data
	*  @param[out]pDstDataSize	：length of converted data
	*  @Return:   IMGCNV_ERR_E	:return value
	*  - IMGCNV_SUCCESS return ok
	*  - Other values refers to enumeration of IMGCNV_ERR_E
	*  Special note
	*  pixelFormat:YUV411Packed,the image width is divisible by 4
	*  pixelFormat:YUV422Packed,the image width is divisible by 2
	*  pixelFormat:YUYVPacked，the image width is divisible by 2
	*  converted image：The first row of the image is located at the start of the image buffer.This is the default for image taken by a camera.
	*/
	IMGCNV_API IMGCNV_EErr CALLMETHOD IMGCNV_ConvertToMono8(unsigned char* pSrcData, IMGCNV_SOpenParam* pOpenParam, unsigned char* pDstData, int* pDstDataSize);

	/**
	*  ~chinese
	*  @brief  转换为BGR24的转换函数
	*  @param[in] pSrcData		：源数据
	*  @param[in] pOpenParam	：IMGCNV_SOpenParam结构体,格式转换所需要的参数
	*  @param[out]pDstData		：转换后的数据
	*  @param[out]pDstDataSize	：转换后数据的长度
	*  @param[in]eBayerDemosaic ：选择转换Bayer格式所用的算法
	*  @Return:   IMGCNV_ERR_E  : 图像格式转换接口返回值
	*  - IMGCNV_SUCCESS 表示执行成功
	*  - 其他值见IMGCNV_ERR_E枚举
	*  特别说明
	*  像素格式为YUV411Packed的时，图像宽须能被4整除
	*  像素格式为YUV422Packed的时，图像宽须能被2整除
	*  像素格式为YUYVPacked的时，图像宽须能被2整除
	*  转换后的图像:数据存储是从最上面第一行开始的，这个是相机数据的默认存储方向
	*  ~english
	*  @brief  convert to BGR24
	*  @param[in] pSrcData		：source data
	*  @param[in] pOpenParam	：conversion required paraneters
	*  @param[out]pDstData		：converted data
	*  @param[out]pDstDataSize	：length of converted data
	*  @param[in]eBayerDemosaic ：alorithm used for Bayer demosaic
	*  @Return:   IMGCNV_ERR_E	:return value
	*  - IMGCNV_SUCCESS return ok
	*  - Other values refers to enumeration of IMGCNV_ERR_E
	*  Special note
	*  pixelFormat:YUV411Packed,the image width is divisible by 4
	*  pixelFormat:YUV422Packed,the image width is divisible by 2
	*  pixelFormat:YUYVPacked，the image width is divisible by 2
	*  converted image：The first row of the image is located at the start of the image buffer.This is the default for image taken by a camera.
	*/
	IMGCNV_API IMGCNV_EErr CALLMETHOD IMGCNV_ConvertToBGR24_Ex(unsigned char* pSrcData, IMGCNV_SOpenParam* pOpenParam, unsigned char* pDstData, int* pDstDataSize, IMGCNV_EBayerDemosaic eBayerDemosaic);

	/**
	*  ~chinese
	*  @brief  转换为RGB24的转换函数
	*  @param[in] pSrcData		：源数据
	*  @param[in] pOpenParam	：IMGCNV_SOpenParam结构体,格式转换所需要的参数
	*  @param[out]pDstData		：转换后的数据
	*  @param[out]pDstDataSize	：转换后数据的长度
	*  @param[in]eBayerDemosaic ：选择转换Bayer格式所用的算法
	*  @Return:   IMGCNV_ERR_E  : 图像格式转换接口返回值
	*  - IMGCNV_SUCCESS 表示执行成功
	*  - 其他值见IMGCNV_ERR_E枚举
	*  特别说明
	*  像素格式为YUV411Packed的时，图像宽须能被4整除
	*  像素格式为YUV422Packed的时，图像宽须能被2整除
	*  像素格式为YUYVPacked的时，图像宽须能被2整除
	*  转换后的图像:数据存储是从最上面第一行开始的，这个是相机数据的默认存储方向
	*  ~english
	*  @brief  convert to RGB24
	*  @param[in] pSrcData		：source data
	*  @param[in] pOpenParam	：conversion required paraneters
	*  @param[out]pDstData		：converted data
	*  @param[out]pDstDataSize	：length of converted data
	*  @param[in]eBayerDemosaic ：alorithm used for Bayer demosaic
	*  @Return:   IMGCNV_ERR_E	:return value
	*  - IMGCNV_SUCCESS return ok
	*  - Other values refers to enumeration of IMGCNV_ERR_E
	*  Special note
	*  pixelFormat:YUV411Packed,the image width is divisible by 4
	*  pixelFormat:YUV422Packed,the image width is divisible by 2
	*  pixelFormat:YUYVPacked，the image width is divisible by 2
	*  converted image：The first row of the image is located at the start of the image buffer.This is the default for image taken by a camera.
	*/
	IMGCNV_API IMGCNV_EErr CALLMETHOD IMGCNV_ConvertToRGB24_Ex(unsigned char* pSrcData, IMGCNV_SOpenParam* pOpenParam, unsigned char* pDstData, int* pDstDataSize, IMGCNV_EBayerDemosaic eBayerDemosaic);

	/**
	*  ~chinese
	*  @brief  转换为Mono8的转换函数
	*  @param[in] pSrcData		：源数据
	*  @param[in] pOpenParam	：IMGCNV_SOpenParam结构体,格式转换所需要的参数
	*  @param[out]pDstData		：转换后的数据
	*  @param[out]pDstDataSize	：转换后数据的长度
	*  @param[in]eBayerDemosaic ：选择转换Bayer格式所用的算法
	*  @Return:   IMGCNV_ERR_E  : 图像格式转换接口返回值
	*  - IMGCNV_SUCCESS 表示执行成功
	*  - 其他值见IMGCNV_ERR_E枚举
	*  特别说明
	*  像素格式为YUV411Packed的时，图像宽须能被4整除
	*  像素格式为YUV422Packed的时，图像宽须能被2整除
	*  像素格式为YUYVPacked的时，图像宽须能被2整除
	*  转换后的图像:数据存储是从最上面第一行开始的，这个是相机数据的默认存储方向
	*  ~english
	*  @brief  convert to Mono8
	*  @param[in] pSrcData		：source data
	*  @param[in] pOpenParam	：conversion required paraneters
	*  @param[out]pDstData		：converted data
	*  @param[out]pDstDataSize	：length of converted data
	*  @param[in]eBayerDemosaic ：alorithm used for Bayer demosaic
	*  @Return:   IMGCNV_ERR_E	:return value
	*  - IMGCNV_SUCCESS return ok
	*  - Other values refers to enumeration of IMGCNV_ERR_E
	*  Special note
	*  pixelFormat:YUV411Packed,the image width is divisible by 4
	*  pixelFormat:YUV422Packed,the image width is divisible by 2
	*  pixelFormat:YUYVPacked，the image width is divisible by 2
	*  converted image：The first row of the image is located at the start of the image buffer.This is the default for image taken by a camera.
	*/
	IMGCNV_API IMGCNV_EErr CALLMETHOD IMGCNV_ConvertToMono8_Ex(unsigned char* pSrcData, IMGCNV_SOpenParam* pOpenParam, unsigned char* pDstData, int* pDstDataSize, IMGCNV_EBayerDemosaic eBayerDemosaic);


    /**
    *  ~chinese
    *  @brief  转换为BGRA32的转换函数
    *  @param[in] pSrcData		：源数据
    *  @param[in] pOpenParam	：IMGCNV_SOpenParam结构体,格式转换所需要的参数
    *  @param[out]pDstData		：转换后的数据
    *  @param[out]pDstDataSize	：转换后数据的长度
    *  @param[in]eBayerDemosaic ：选择转换Bayer格式所用的算法
    *  @Return:   IMGCNV_ERR_E  : 图像格式转换接口返回值
    *  - IMGCNV_SUCCESS 表示执行成功
    *  - 其他值见IMGCNV_ERR_E枚举
    *  特别说明
    *  像素格式为YUV411Packed的时，图像宽须能被4整除
    *  像素格式为YUV422Packed的时，图像宽须能被2整除
    *  像素格式为YUYVPacked的时，图像宽须能被2整除
    *  转换后的图像:数据存储是从最上面第一行开始的，这个是相机数据的默认存储方向
    *  ~english
    *  @brief  convert to BGRA32
    *  @param[in] pSrcData		：source data
    *  @param[in] pOpenParam	：conversion required paraneters
    *  @param[out]pDstData		：converted data
    *  @param[out]pDstDataSize	：length of converted data
    *  @param[in]eBayerDemosaic ：alorithm used for Bayer demosaic
    *  @Return:   IMGCNV_ERR_E	:return value
    *  - IMGCNV_SUCCESS return ok
    *  - Other values refers to enumeration of IMGCNV_ERR_E
    *  Special note
    *  pixelFormat:YUV411Packed,the image width is divisible by 4
    *  pixelFormat:YUV422Packed,the image width is divisible by 2
    *  pixelFormat:YUYVPacked，the image width is divisible by 2
    *  converted image：The first row of the image is located at the start of the image buffer.This is the default for image taken by a camera.
    */
    IMGCNV_API IMGCNV_EErr CALLMETHOD IMGCNV_ConvertToBGRA32_Ex(unsigned char* pSrcData, IMGCNV_SOpenParam* pOpenParam, unsigned char* pDstData, int* pDstDataSize, IMGCNV_EBayerDemosaic eBayerDemosaic);

#ifdef  __cplusplus
}
#endif // end #ifdef  __cplusplus

#endif // end of #ifndef __IMAGE_CONVERT_H_