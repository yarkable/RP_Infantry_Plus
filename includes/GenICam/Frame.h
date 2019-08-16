#ifndef __DAHUA_GENICAM_CFRAME_H__
#define __DAHUA_GENICAM_CFRAME_H__

#include "Defs.h"
#include "Memory/Block.h"
#include "Infra/Vector.h"
#include "Infra/String.h"
#include "PixelType.h"


GENICAM_NAMESPACE_BEGIN

/// \~chinese
/// \brief 数据帧对象接口
/// \defgroup Frame 数据帧操作接口 
/// @{
/// \~english 
/// \brief data frame object interface
/// \defgroup data Frame Buffer Operation interface
/// @{

/// \~chinese
/// \brief Class CFrame 数据帧对象接口，帧的长、宽以及数据格式可从该对象中获取
/// \~english
/// \brief Class CFrame frame object interface
class GENICAM_API CFrame : public Memory::CBlock
{
public:	

	enum EPayloadType
	{
		payloadImage = 1,	            ///< \~chinese 图片         \~english Image
		payloadRawdata,					///< \~chinese 裸数据       \~english Raw Data
		payloadFile,					///< \~chinese 文件         \~english File
		payloadChunkData,				///< \~chinese 块数据       \~english Chunk Data
		payloadExtChunkData,			///< \~chinese 扩展块数据   \~english Extension Chunk Data
		payloadJpeg,					///< \~chinese jpeg数据     \~english jpeg Data
		payloadDevSpecBase = 0x8000,    ///< \~chinese 设备特有     \~english Device specific payload type
		payloadUndefined				///< \~chinese 未定义		\~english Undefined
	};
	
	/// \~chinese
	/// brief 空构造函数
	/// \~english
	/// brief Empty Constructor function
	CFrame();
	
	/// \~chinese
	/// brief  帧对象构造函数
	/// \param [in] other 构造帧对象的原始数据块对象
	/// \~english
	/// brief  Frame object constructor function
	/// \param [in] other raw data object used to contruct frame
	explicit CFrame(Memory::CBlock const& other);
	
	/// \~chinese
	/// \brief 帧深拷贝克隆接口
	/// \return 新的一帧对象
	/// \~english
	/// \brief frame deep clone interface
	/// \return new frame object
	CFrame clone();
	
	/// \~chinese
	/// \brief 外面不使用时需要调用此接口释放Image相关内存
	/// \return none
	/// \~english
	/// \brief It is required to call this interface to release the image related memory when it is not needed externally
	/// \return none	
	void reset();
	
	/// brief 是否有效
	/// \return 返回该帧是否有效
	/// \~english
	/// brief check frame valid or not
	/// \retval < 0 frame invalid
	/// \retval 0   frame valid	
	bool valid() const;
	
	/// \~chinese
	/// \brief 获取该帧图片数据的内存首地址
	/// \return 返回该帧图片数据的内存首地址
	/// \~english
	/// \brief Get the starting address of memory of this image data
	/// \return Return the starting address of memory of this image data  	
	const void * getImage() const;
			
	/// \~chinese
	/// \brief 获取数据帧状态
	/// \return 返回数据帧状态
	/// \~english
	/// \brief Get status of data frame
	/// \return Return status of data frame
	uint32_t getFrameStatus() const;

	/// \~chinese
	/// \brief 获取图片宽度
	/// \return 返回图片宽度
	/// \~english
	/// \brief get the width of image
	/// \return the width of image, return 0 when failed	
	uint32_t getImageWidth() const;
		
	/// \~chinese
	/// \brief 获取图片高度
	/// \return 返回图片高度
	/// \~english 
	/// \brief get the height of image
	/// \return the height of image, return 0 when failed	
	uint32_t getImageHeight() const;
			
	/// \~chinese
	/// \brief 获取图片大小
	/// \return 返回图片大小
	/// \~english
	/// \brief get the size of image
	/// \return the size of image, return 0 when failed	
	uint32_t getImageSize() const;
			
	/// \~chinese
	/// \brief 获取图片像素格式
	/// \return 返回图片像素格式
	/// \~english
	/// \brief get image pixel format
	/// \return image pixel format	
	EPixelType getImagePixelFormat() const;
			 
	/// \~chinese
	/// \brief 获取图片时间戳
	/// \return 返回图片时间戳
	/// \~english
	/// \brief get timestamp of image
	/// return image time stamp, return 0 when failed	
	uint64_t getImageTimeStamp() const;
			 
	/// \~chinese
	/// \brief 获取图片对应的BlockId
	/// \return 返回图片对应的BlockId
	/// \~english
	/// \brief get the block ID of image
	/// \return the image's block ID, return 0 when failed 	
	uint64_t getBlockId() const;
			
	/// \~chinese
	/// \brief 获取当前帧数据净荷类型
	/// \param [out] payloadTypes 当前帧数据类型种类集
	/// \return 返回是否成功
	/// \~english
	/// \brief get pay load type of current frame
	/// \param [out] payloadTypes Current frame data type set
	/// \retval false failure
	/// \retval true  success	
	bool getPayLoadTypes(Infra::TVector<EPayloadType>& payloadTypes) const;
			
	/// \~chinese
	/// \brief 获取Buffer中包含的Chunk个数
	/// \return Chunk个数
	/// \~english
	/// \brief get the number of chunk in buffer
	/// \return the number of chunk	
	uint32_t getChunkCount() const;
	
	/// \~chinese
	/// \brief 获取Chunk数据
	/// \param [in] aIndex 索引ID
	/// \param [out] aID ChunkID
	/// \param [out] paramNames Chunk数据对应的属性名
	/// \return 是否成功
	/// \~english
	/// \brief get chunk data
	/// \param [in] aIndex index ID
	/// \param [out] aID ChunkID
	/// \param [out] paramNames Corresponding property name of chunk data 
	/// \return success or fail	
	bool getChunkDataByIndex(uint32_t aIndex, uint32_t &aID, Infra::TVector<Infra::CString>& paramNames) const;

    /// \~chinese
    /// \brief 获取图片paddingX
    /// \return 返回图片paddingX
    /// \~english
    /// \brief get image paddingX
    /// \return paddingX	
    uint32_t getImagePadddingX() const;

    /// \~chinese
    /// \brief 获取图片paddingY
    /// \return 返回图片paddingY
    /// \~english
    /// \brief get image paddingY
    /// \return paddingY		
    uint32_t getImagePadddingY() const;
};

/// @}

GENICAM_NAMESPACE_END

#endif //__DAHUA_GENICAM_CFRAME_H__

