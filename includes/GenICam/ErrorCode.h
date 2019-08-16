#ifndef __GENICAM_ERROR_CODE_H__
#define __GENICAM_ERROR_CODE_H__
#include "GenICam/Defs.h"

GENICAM_NAMESPACE_BEGIN

/// \~chinese
/// \brief SDK错误类型
///< 外部应用程序调用SDK接口失败后，可调用 Dahua::Infra::getLastError 获取具体的错误码
///< 可调用 Dahua::Infra::getErrMsg 获取具体的错误号对应的错误描述信息

/// \~english
/// \brief SDK error type; Once external application failed calling SDK interfaces, then users can call Dahua::Infra::getLastError to get detailed error code;Users may also call Dahua::Infra::getErrMsg to get detailed error message

#define ERROR_UNKNOW									( 0x10000000 )
#define ERROR_UNKNOW_DES								"unknow error" 

#define ERROR_MALLOC_MEMORY_FAIL						( 0x10000001 )
#define ERROR_MALLOC_MEMORY_FAIL_DES	                "malloc memory fail"

#define ERROR_CAMERA_OFFLINE							( 0x10000002 )
#define ERROR_CAMERA_OFFLINE_DES						"camera offline"

#define ERROR_CAMERA_IS_NOT_GIGE						( 0x10000003 )
#define ERROR_CAMERA_IS_NOT_GIGE_DES					"the camera is not gige"

#define ERROR_LOAD_XML_FAIL                             ( 0x10000004 )
#define ERROR_LOAD_XML_FAIL_DES                          "load xml fail" 

#define ERROR_CAMERA_HAS_BEEN_OPENED                    ( 0x10000005 )
#define ERROR_CAMERA_HAS_BEEN_OPENED_DES                 "the camera has been opened" 

#define ERROR_CAMERA_HAS_NOT_BEEN_OPENED                ( 0x10000006 )
#define ERROR_CAMERA_HAS_NOT_BEEN_OPENED_DES            "the camera has not been opened" 

#define ERROR_PARAM_IS_INVALID							( 0x10000007 )
#define ERROR_PARAM_IS_INVALID_DES						"param is invalid" 

#define ERROR_ATTRIBUTE_IS_INVALID						( 0x10000008 )
#define ERROR_ATTRIBUTE_IS_INVALID_DES					"attribute is invalid" 

#define ERROR_CAMERA_IS_GRABBING						( 0x10000009 )
#define ERROR_CAMERA_IS_GRABBING_DES					"the camera is grabbing" 

#define ERROR_CAMERA_IS_NOT_GRABBING					( 0x1000000a )
#define ERROR_CAMERA_IS_NOT_GRABBING_DES				"the camera is not grabbing" 

#define ERROR_FRAME_QUEUE_IS_EMPTY						( 0x1000000b )
#define ERROR_FRAME_QUEUE_IS_EMPTY_DES					"the frame queue is empty" 

#define ERROR_FUNCTION_HAS_BEEN_ATTACHED				( 0x1000000c )
#define ERROR_FUNCTION_HAS_BEEN_ATTACHED_DES			"the function has been attached" 

#define ERROR_FUNCTION_HAS_NOT_BEEN_ATTACHED			( 0x1000000d )
#define ERROR_FUNCTION_HAS_NOT_BEEN_ATTACHED_DES		"the function has not been attached" 

#define ERROR_CREATE_XML_FILE_FAIL						( 0x1000000e )
#define ERROR_CREATE_XML_FILE_FAIL_DES					"create xml file fail"

#define ERROR_IS_NOT_COMMON_ATTRIBUTE					( 0x1000000f )
#define ERROR_IS_NOT_COMMON_ATTRIBUTE_DES				"is not common attribute"

#define ERROR_CONFIG_FILE_IS_NOT_EXIST					( 0x10000010 )
#define ERROR_CONFIG_FILE_IS_NOT_EXIST_DES				"the config file is not exist"

#define ERROR_CONFIG_FILE_FORMAT						( 0x10000011 )
#define ERROR_CONFIG_FILE_FORMAT_DES					"the config file format is error"

#define ERROR_LOAD_ATTRIBUTE_FAIL						( 0x10000012 )
#define ERROR_LOAD_ATTRIBUTE_FAIL_DES					"load attribute fail"

GENICAM_NAMESPACE_END

#endif //__GENICAM_ERROR_CODE_H__