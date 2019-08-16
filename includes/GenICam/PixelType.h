#ifndef __DAHUA_PIXEL_TYPE_H__
#define __DAHUA_PIXEL_TYPE_H__
#include "Defs.h"

GENICAM_NAMESPACE_BEGIN

/// \~chinese
/// \brief 图像格式
/// \defgroup ImageFormat 图像格式
/// @{
/// \~english
/// \brief ImageFormat
/// \defgroup ImageFormat ImageFormat
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


enum EPixelType
{
	// Undefined pixel type
	pixelTypeUndefined = -1,

	// Mono Format
	gvspPixelMono1p									        = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY1BIT | 0x0037),
	gvspPixelMono2p											= (GVSP_PIX_MONO | GVSP_PIX_OCCUPY2BIT | 0x0038),
	gvspPixelMono4p											= (GVSP_PIX_MONO | GVSP_PIX_OCCUPY4BIT | 0x0039),
	gvspPixelMono8                                          = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY8BIT | 0x0001),
	gvspPixelMono8S                                         = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY8BIT | 0x0002),
	gvspPixelMono10                                         = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0003),
	gvspPixelMono10Packed									= (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x0004),
	gvspPixelMono12											= (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0005),
	gvspPixelMono12Packed									= (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x0006),
	gvspPixelMono14                                         = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0025),
	gvspPixelMono16                                         = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0007),

	// Bayer Format
	gvspPixelBayGR8											= (GVSP_PIX_MONO | GVSP_PIX_OCCUPY8BIT | 0x0008),
	gvspPixelBayRG8                                         = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY8BIT | 0x0009),
	gvspPixelBayGB8                                         = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY8BIT | 0x000A),
	gvspPixelBayBG8                                         = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY8BIT | 0x000B),
	gvspPixelBayGR10                                        = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x000C),
	gvspPixelBayRG10                                        = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x000D),
	gvspPixelBayGB10                                        = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x000E),
	gvspPixelBayBG10                                        = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x000F),
	gvspPixelBayGR12                                        = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0010),
	gvspPixelBayRG12                                        = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0011),
	gvspPixelBayGB12                                        = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0012),
	gvspPixelBayBG12                                        = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0013),
	gvspPixelBayGR10Packed	                                = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x0026),
	gvspPixelBayRG10Packed									= (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x0027),
	gvspPixelBayGB10Packed									= (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x0028),
	gvspPixelBayBG10Packed									= (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x0029),
	gvspPixelBayGR12Packed	                                = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x002A),
	gvspPixelBayRG12Packed									= (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x002B),
	gvspPixelBayGB12Packed									= (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x002C),
	gvspPixelBayBG12Packed									= (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x002D),
	gvspPixelBayGR16                                        = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x002E),
	gvspPixelBayRG16                                        = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x002F),
	gvspPixelBayGB16                                        = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0030),
	gvspPixelBayBG16                                        = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0031),
	
	//BayerRG10p和BayerRG12p格式，针对特定项目临时添加,请不要使用
	//BayerRG10p and BayerRG12p, currently used for specific project, please do not use them
    gvspPixelBayRG10p                                       = 0x010A0058,
    gvspPixelBayRG12p                                       = 0x010c0059,

    //mono1c格式，自定义格式
	//mono1c, customized image format, used for binary output
    gvspPixelMono1c                                         = 0x012000FF,

	//mono1e格式，自定义格式，用来显示连通域
	//mono1e, customized image format, used for displaying connected domain
	gvspPixelMono1e											= 0x01080FFF,

	// RGB Format
	gvspPixelRGB8											= (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x0014),
	gvspPixelBGR8                                           = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x0015),
	gvspPixelRGBA8                                          = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY32BIT | 0x0016),
	gvspPixelBGRA8                                          = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY32BIT | 0x0017),
	gvspPixelRGB10                                          = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x0018),
	gvspPixelBGR10                                          = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x0019),
	gvspPixelRGB12                                          = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x001A),
	gvspPixelBGR12                                          = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x001B),
	gvspPixelRGB16                                          = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x0033),
	gvspPixelRGB10V1Packed                                  = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY32BIT | 0x001C),
	gvspPixelRGB10P32                                       = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY32BIT | 0x001D),
	gvspPixelRGB12V1Packed									= (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY36BIT | 0X0034),
	gvspPixelRGB565P                                        = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x0035),
	gvspPixelBGR565P                                        = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0X0036),

	// YVR Format
	gvspPixelYUV411_8_UYYVYY                                = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY12BIT | 0x001E),
	gvspPixelYUV422_8_UYVY                                  = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x001F),
	gvspPixelYUV422_8                                       = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x0032),
	gvspPixelYUV8_UYV                                       = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x0020),
	gvspPixelYCbCr8CbYCr									= (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x003A),
	gvspPixelYCbCr422_8                                     = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x003B),
	gvspPixelYCbCr422_8_CbYCrY                              = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x0043),
	gvspPixelYCbCr411_8_CbYYCrYY                            = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY12BIT | 0x003C),
	gvspPixelYCbCr601_8_CbYCr                               = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x003D),
	gvspPixelYCbCr601_422_8                                 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x003E),
	gvspPixelYCbCr601_422_8_CbYCrY                          = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x0044),
	gvspPixelYCbCr601_411_8_CbYYCrYY                        = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY12BIT | 0x003F),
	gvspPixelYCbCr709_8_CbYCr                               = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x0040),
	gvspPixelYCbCr709_422_8                                 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x0041),
	gvspPixelYCbCr709_422_8_CbYCrY                          = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x0045),
	gvspPixelYCbCr709_411_8_CbYYCrYY                        = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY12BIT | 0x0042),

	// RGB Planar
	gvspPixelRGB8Planar										= (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x0021),
	gvspPixelRGB10Planar                                    = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x0022),
	gvspPixelRGB12Planar                                    = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x0023),
	gvspPixelRGB16Planar                                    = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x0024)
};

/// @}

GENICAM_NAMESPACE_END
#endif//__DAHUA_PIXEL_TYPE_H__