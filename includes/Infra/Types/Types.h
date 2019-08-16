//
//  "$Id: Types.h 16720 2010-12-01 09:51:53Z wang_haifeng $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//


#ifndef __DAHUA3_TYPES_H__
#define __DAHUA3_TYPES_H__

#include "IntTypes.h"
////////////////////////////////////////////////////////////////////////////////

// WIN32 Dynamic Link Library
#ifdef _MSC_VER

/// 废弃INTERFACE_API的使用，每个模块DLL应该定义自己的XXX_API，请参考INFRA_API的定义
#ifdef _DLL_BUILD
	#define  INTERFACE_API _declspec(dllexport)
#elif defined _DLL_USE
	#define  INTERFACE_API _declspec(dllimport)
#else
	#define INTERFACE_API
#endif

#else
	#define INTERFACE_API
#endif

#if (defined (WIN32) || defined(WIN64))
#   define CALLMETHOD __stdcall
#else
#	define CALLMETHOD
#endif // end #if (defined (WIN32) || defined(WIN64))

#ifdef __GNUC__
#define INFINITE            0xFFFFFFFF  // Infinite timeout
#endif

#define MAX_POLYGON_PEAK_NUM        128     ///< 最大多边形顶点个数


/// IP 地址结构
typedef union tagMvSIpAddress
{
	uint8_t		c[4];
	uint16_t	s[2];
	uint32_t	l;
}IpAddress;

//////////////////////////////////////////////////////////////////////////
/// 系统时间定义
typedef struct tagMvSSystemTime
{
	int32_t  year;		///< 年。
	int32_t  month;		///< 月，January = 1, February = 2, and so on.
	int32_t  day;		///< 日。
	int32_t  wday;		///< 星期，Sunday = 0, Monday = 1, and so on
	int32_t  hour;		///< 时。
	int32_t  minute;	///< 分。
	int32_t  second;	///< 秒。
	int32_t  isdst;		///< 夏令时标识。
}MvSSystemTime;	



/// 2D点结构体定义
typedef struct tagMvSPoint
{
	int32_t     x;
	int32_t     y;
} MvSPoint;

typedef struct tagMvSPoint2Di32
{
	int32_t		x;
	int32_t		y;
} MvSPoint2Di32;

typedef struct tagMvSPoint2Di16
{
	int16_t		x;
	int16_t		y;
} MvSPoint2Di16;

typedef struct tagMvSPoint2Df32
{
	float		x;
	float		y;
} MvSPoint2Df32;

typedef struct tagMvSPoint2Df64
{
	double		x;
	double		y;
} MvSPoint2Df64;



/// 3D点结构体定义
typedef struct tagMvSPoint3Di32
{
	int32_t		x;
	int32_t		y;
	int32_t		z;
} MvSPoint3Di32;

typedef struct tagMvSPoint3Di16
{
	int16_t		x;
	int16_t		y;
	int16_t		z;
} MvSPoint3Di16;

typedef struct tagMvSPoint3Df32
{
	float		x;
	float		y;
	float		z;
} MvSPoint3Df32;

typedef struct tagMvSPoint3Df64
{
	double		x;
	double		y;
	double		z;
} MvSPoint3Df64;



/// 矩形
typedef struct tagMvSRect
{
	int32_t left;
	int32_t top;
	int32_t right;
	int32_t bottom;
} MvSRect;

/// 尺寸
typedef struct tagMvSSize
{
	int32_t w;
	int32_t h;
} MvSSize;

/// 颜色
typedef struct tagMvSColor
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} MvSColor;

/// 直线
typedef struct tagMvSLine
{
	MvSPoint start;
	MvSPoint end;
} MvSLine;

typedef struct tagMvSLinePA
{
	MvSPoint2Df32   point;
	float           angle;
}MvSLinePA;

/// 时间段结构
typedef struct tagMvSTimeSection
{
	int enable;			///< 使能
	int startHour;		///< 开始时间:小时
	int	startMinute;	///< 开始时间:分钟
	int	startSecond;	///< 开始时间:秒钟
	int	endHour;		///< 结束时间:小时
	int	endMinute;		///< 结束时间:分钟
	int	endSecond;		///< 结束时间:秒钟
}MvSTimeSection;




/// 二维线段线段定义
//////////////////////////////////////////////////////////////////////////
typedef struct tagMvSLineSeg2Di32
{
	MvSPoint2Di32		pt1;
	MvSPoint2Di32    	pt2;
} MvSLineSeg2Di32;

typedef struct tagMvSLineSeg2Df32
{
	MvSPoint2Df32		pt1;
	MvSPoint2Df32		pt2;
} MvSLineSeg2Df32;

typedef struct tagMvSLineSegPtSlope2Df32
{
	float				angle;
	float				length;
	MvSPoint2Df32		pt;
} MvSLineSegPtSlope2Df32;

typedef union tagMvULineSeg
{
	MvSLineSeg2Df32		    twoPt;				///< 两点式
    MvSLineSegPtSlope2Df32	ptSlope;			///< 点斜式
	int32_t reserved[32];
}MvULineSeg;

typedef enum TypeLineSeg
{
    LINESEG_TOW_POINT = 0,                      ///< 两点式
    LINESEG_POINT_SLOPE,                        ///< 点斜式
}TypeLineSeg;

typedef struct tagMvSLineSeg
{
    TypeLineSeg         type;                   ///< 线段类型
    MvULineSeg          lineSeg;				///< 线段
    int32_t             reserved[31];           ///< 预留字段
} MvSLineSeg;


//尺寸定义
/////////////////////////////////////////////////////////////////////////////////
typedef struct tagMvSSizei32
{
	int32_t		width;							///< 宽
	int32_t		height;							///< 高
} MvSSizei32;

typedef struct tagMvSSizef32
{
	float		width;							///< 浮点宽高
	float		height;
} MvSSizef32;
/////////////////////////////////////////////////////////////////////////////////////

//矩形框结构体
//////////////////////////////////////////////////////////////////////////////////
typedef struct tagMvSRect2Di32
{
	MvSPoint2Di32		ul;	//左上
	MvSPoint2Di32		lr;	//右下
} MvSRect2Di32;

typedef struct tagMvSRect2Df32
{
	MvSPoint2Df32	ul;	//左上
	MvSPoint2Df32	lr;	//右下
} MvSRect2Df32;

/*矩形*/
typedef struct tagMvSRectangle 
{
    float                   cx;         ///< 中心x
    float                   cy;         ///< 中心y
    float                   lx;         ///< x方向长
    float                   ly;         ///< y方向长
    float                   ra;         ///< 旋转角度
    float                   ska;        ///< 斜切角度
}MvSRectangle;

/*圆*/
typedef struct tagMvSCircle
{
    float                   cx;         ///< 中心x
    float                   cy;         ///< 中心y
    float                   radius;     ///< 半径
} MvSCircle;

/* 圆弧 */
typedef struct tagMvSArc
{
    float                   cx;         ///< 圆弧中心X
    float                   cy;         ///< 圆弧中心Y
    float                   radius;     ///< 圆弧半径
    float                   angleStart; ///< 起始角度
    float                   angleSpan;  ///< 角度范围
}MvSArc;


/*椭圆*/
typedef struct tagMvSEllipse
{
    float                   cx;         ///< 中心x
    float                   cy;         ///< 中心y
    float                   rx;         ///< x轴系数
    float                   ry;         ///< y轴系数
    float                   ra;         ///< 旋转角度
    float                   ska;        ///< 斜切角度
}MvSEllipse;

//圆环段
typedef struct tagMvSAnnulusSection
{
    float               cx;             ///< 中心x
    float               cy;             ///< 中心y
    float               innerR;         ///< 内圆半径
    float               outerR;         ///< 外圆半径
    float               startAngle;     ///< 起始角度
    float               endAngle;       ///< 终止角度
    int32_t             reserved[26];   ///< 预留字段
} MvSAnnulusSection;

//多边形
typedef struct tagMvSPolygonf32
{
    int32_t             num;                            ///< 顶点数量
    MvSPoint2Df32       pts[MAX_POLYGON_PEAK_NUM];      ///< 顶点数据
    int32_t             reserved[31];                   ///< 预留字段
} MvSPolygonf32;

///32位程序128个字节
typedef union tagMvUGraphObj
{
	MvSRectangle		rect;						           ///< type == 0
	MvSCircle			circle;								   ///< type == 1
	MvSEllipse			ellipse;							   ///< type == 2
    MvSPolygonf32       polygon;
    MvSAnnulusSection   annulusSection;
	int32_t reserved[32];
}MvUGraphObj;

///< 任意目标
typedef struct tagMvSGraphBase
{
	int32_t				type;															///< 目标类型
	MvUGraphObj			graph;															///< 目标数据
}MvSGraphBase;

//////////////////////////////////////////////////////////////
/*图像结构体定义*/
typedef struct tagMvSImage
{
    int32_t                 type;       //图像格式，见PublicDefine.h中MvsImgType
    int32_t                 dataType;   //存储类型，见PublicDefine.h中MvsImgDataType
    int32_t                 width;      //传入图像数据宽度
    int32_t                 height;     //传入图像数据高度
    MvSRect2Di32            roi;        //有效数据区域
    uint8_t                 *imageData; //图像数据指针	
    uint8_t                 *mask;      //图像掩膜，0 (MVS_NULL)表示没有掩膜
    int32_t                 *reserved[22];  // 预留字段1
}MvSImage;


typedef struct tagMvSLineCoef
{
	float		    a;
	float		    b;
	float		    c;
}MvSLineCoef;


/*ROI*/
typedef struct tagMvSROI
{
    int32_t							num;							//ROI个数
    MvSRect2Di32					*rect;							//ROI外接矩形
    MvSImage						*img;							//ROI图像
}MvSROI;


/*coordinate struct*/
typedef struct tagMvSCoordinate
{
	float x;               // 平移x轴坐标
	float y;               // 平移y轴坐标
	float scale;           // 缩放尺度
	float ratio;           // y轴单位与x轴单位的比率
	float ra;              // 旋转角
	float ska;             // 倾斜角
	int firstProc;        //模板匹配之后的第一次执行
	int32_t *reserved[25]; // 预留字段1
}MvSCoordinate;

//图像类型定义（类型_扫描方式_图像类型_类型说明）
typedef enum tagMvSImgType
{
	//逐行扫描图像
	/* Y平面保存格式 */
	MVS_IMGTP_UITL_Y			= 0x0100,
	/* RGB平面保存格式 */
	MVS_IMGTP_UITL_RGB			= 0x0200,
	/* RGB 24平面保存格式 - R在一个平面，G在一平面，B在一个平面。*/
	MVS_IMGTP_UITL_RGBP_24		= 0x0201,
	/* HSI 平面保存格式 */
	MVS_IMGTP_UITL_HSI			= 0x0400,
	/* LAB 平面保存格式 */
	MVS_IMGTP_UITL_LAB			= 0x0500,
	/* LAB 平面保存格式 */
	MVS_IMGTP_UITL_DIF			= 0x0600,
	/* XYZ 平面保存格式 */
	MVS_IMGTP_UITL_XYZ			= 0x0700,
	/* UITL_YUV*/
	MVS_IMGTP_UITL_YUV			= 0x1000,
	/* YUV 420平面保存格式 - YUV是一个平面。*/
	MVS_IMGTP_UITL_YUV_420,
	/* YUV 420平面保存格式 - Y是一个平面，U是一个平面，V也是一个平面。*/
	MVS_IMGTP_UITL_YUVP_420,
	/* YUV 420半平面保存格式 - Y在一个平面，UV在另一平面（交错保存）。*/
	MVS_IMGTP_UITL_YUVSP_420,
	/* YUV 420半平面保存格式 - Y在一个平面，VU在另一平面（交错保存）。*/
	MVS_IMGTP_UITL_YVUSP_420,
	/* YUV 422平面保存格式 - YUV是一个平面。*/
	MVS_IMGTP_UITL_YUV_422,
	/* YUV 422平面保存格式 - Y是一个平面，V是一个平面，U也是一个平面。*/
	MVS_IMGTP_UITL_YUVP_422,
	/* YUV 422半平面保存格式 - Y是一个平面，UV是另一平面（交错保存）。*/
	MVS_IMGTP_UITL_YUVSP_422,
	/* YUV 422半平面保存格式 - Y在一个平面，VU在另一平面（交错保存）。*/
	MVS_IMGTP_UITL_YVUSP_422,

	//隔行扫描图像
	/* ITL_YUV*/
	MVS_IMGTP_ITL_YUV			= 0x3000,
	/* YUV 420平面保存格式 - Y是一个平面，U是一个平面，V也是一个平面。*/
	MVS_IMGTP_ITL_YUVP_420,
	/* YUV 420半平面保存格式 - Y在一个平面，UV在另一平面（交错保存）。*/
	MVS_IMGTP_ITL_YUVSP_420,
	/* YUV 420半平面保存格式 - Y在一个平面，VU在另一平面（交错保存）。*/
	MVS_IMGTP_ITL_YVUSP_420,
	/* YUV 422平面保存格式 - Y是一个平面，V是一个平面，U也是一个平面。*/
	MVS_IMGTP_ITL_YUVP_422,
	/* YUV 422半平面保存格式 - Y是一个平面，UV是另一平面（交错保存）。*/
	MVS_IMGTP_ITL_YUVSP_422,
	/* YUV 422半平面保存格式 - Y在一个平面，VU在另一平面（交错保存）。*/
	MVS_IMGTP_ITL_YVUSP_422,
	/* 内格式定义*/
}MvSImgType;


/*图像数据格式*/
typedef enum tagMvSImgDataType
{
	/*无符号8位*/
	MVS_IMGDTP_U8			= 0,								
	/*有符号8位*/
	MVS_IMGDTP_S8,
	/*有符号32位*/
	MVS_IMGDTP_S32,			
	/*无符号32位*/
	MVS_IMGDTP_U32,			
	/*有符号16位*/
	MVS_IMGDTP_S16,			
	/*无符号16位*/
	MVS_IMGDTP_U16,			
	/*浮点32位*/
	MVS_IMGDTP_F32,		
	/*浮点64位*/
	MVS_IMGDTP_F64,
}MvSImgDataType;

//目标类型
typedef enum tagMvSObjectType
{
	/*点*/
	MVS_OBJTP_POINT,
	/*线段*/
	MVS_OBJTP_LINE_SEG,
	/*线*/
	MVS_OBJTP_LINE,
	/*圆*/
	MVS_OBJTP_CIRCLE,
	/*椭圆*/
	MVS_OBJTP_ELLIPSE,
	/*图像*/
	MVS_OBJTP_IMG,
}MvSObjectType;

//单应性矩阵
typedef struct tagMvSHomMat2D
{
    float mat[9];
}MvSHomMat2D;

//矩阵
typedef struct tagMvSMat2Di32
{
	int32_t				rows;		//矩阵的行数
	int32_t				cols;		//矩阵的列数
	int32_t				*data;		//矩阵的数据
} MvSMat2Di32;

typedef struct tagMvSMat2Df32
{
	int32_t				rows;		//矩阵的行数
	int32_t				cols;		//矩阵的列数
	float				*data;		//矩阵的数据
}MvSMat2Df32;

typedef struct tagMvSMat2Df64
{
	int32_t				rows;		//矩阵的行数
	int32_t				cols;		//矩阵的列数
	double				*data;		//矩阵的数据
}MvSMat2Df64;

typedef struct tagMvSRotateRect
{
	float		centerX;		//中心点			
	float		centerY;
	float		hWidth;			//矩形半宽 高
	float		hHeight;
	float		angle;			//旋转角度
	int32_t     reserved[27];   // 预留字段
}MvSRotateRect;

typedef struct tagMvSRegion
{
	int32_t			imgWidth;
	int32_t			imgHeight;		//region所在图像宽高
	uint32_t		area;           // 面积
	MvSPoint2Df32	center;         // 中心
	float			circularity;	// 圆度
	float			rectangularity;	// 矩形度
	float			convexity;		// 凸度
	float			contlength;		// 周长
	MvSRotateRect	minRect;		// 最小外接矩形
	int32_t			boxTop;			//包围盒信息X1
	int32_t			boxLeft;		//包围盒信息Y1
	int32_t			boxRight;		//包围盒信息X2
	int32_t			boxDown;		//包围盒信息Y2

	int32_t			conFlag;		//1 8联通 2 四联通
	uint32_t		conSize;		//轮廓大小
	uint16_t		*conAdrX;		//轮廓地址序例，数据类型为jU16
	uint16_t		*conAdrY;		//轮廓地址序例，数据类型为jU16

	int32_t			posFlag;
	uint32_t		posSize;		//区域大小
	uint16_t		*areaAdrX;		//区域地址序例，数据类型为jU16
	uint16_t		*areaAdrY;		//区域地址序例，数据类型为jU16

	int32_t			runFlag;		// 1 8联通 2 四联通
	uint32_t		runNum;         // 行程数量
	uint16_t		*runRow;        // 行程所在行
	uint16_t		*runStart;      // 行程起始列
	uint16_t		*runEnd;        // 行程终止列
	int32_t			reserved[6];    // 预留字段
}MvSRegion;

typedef struct tagMvSMultiRegion
{
	uint32_t areaNum;       //区域个数
	MvSRegion *regions;		//区域
}MvSMultiRegion;

#endif// __DAHUA_TYPES_H__