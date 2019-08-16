#ifndef VIDEO_H
#define VIDEO_H

#include <math.h>
#include "GenICam/System.h"
#include "Media/VideoRender.h"
#include "Media/ImageConvert.h"
#include <iostream>
#include "GenICam/Camera.h"
#include "GenICam/GigE/GigECamera.h"
#include "GenICam/GigE/GigEInterface.h"
#include "Infra/PrintLog.h"
#include "Memory/SharedPtr.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace Dahua::GenICam;
using namespace Dahua::Infra;
using namespace Dahua::Memory;
using namespace std;
using namespace cv;

static uint32_t gFormatTransferTbl[] =
    {
        // Mono Format
        gvspPixelMono1p,
        gvspPixelMono8,
        gvspPixelMono10,
        gvspPixelMono10Packed,
        gvspPixelMono12,
        gvspPixelMono12Packed,

        // Bayer Format
        gvspPixelBayRG8,
        gvspPixelBayGB8,
        gvspPixelBayBG8,
        gvspPixelBayRG10,
        gvspPixelBayGB10,
        gvspPixelBayBG10,
        gvspPixelBayRG12,
        gvspPixelBayGB12,
        gvspPixelBayBG12,
        gvspPixelBayRG10Packed,
        gvspPixelBayGB10Packed,
        gvspPixelBayBG10Packed,
        gvspPixelBayRG12Packed,
        gvspPixelBayGB12Packed,
        gvspPixelBayBG12Packed,
        gvspPixelBayRG16,
        gvspPixelBayGB16,
        gvspPixelBayBG16,
        gvspPixelBayRG10p,
        gvspPixelBayRG12p,

        gvspPixelMono1c,

        // RGB Format
        gvspPixelRGB8,
        gvspPixelBGR8,

        // YVR Format
        gvspPixelYUV411_8_UYYVYY,
        gvspPixelYUV422_8_UYVY,
        gvspPixelYUV422_8,
        gvspPixelYUV8_UYV,
};
#define gFormatTransferTblLen sizeof(gFormatTransferTbl) / sizeof(gFormatTransferTbl[0])

class Video
{
  public:
    Video() {}
    ~Video()
    {
        videoStopStream(); //断流
        videoClose();	  //析构断开与相机的链接
    }

    //枚举触发方式
    enum ETrigType
    {
        trigContinous = 0, //连续拉流
        trigSoftware = 1,  //软件触发
        trigLine = 2,	  //外部触发
    };

    bool videoCheck();										  //搜索相机
    bool videoOpen();										  //初始化相机
    void CameraChangeTrig(ETrigType trigType = trigSoftware); //设置触发模式，一般为软触发
    void ExecuteSoftTrig();									  //执行一次软触发
    bool videoStart();										  //创建流对象
    bool getFrame(Mat &img);                                  //获取一帧图片
    bool convertToRGB24(Mat &img);							  //转换为opencv可以识别的格式
    void videoStopStream();									  //断开拉流
    void videoClose();										  //断开相机

    void startGrabbing();                                   //
    void SetExposeTime(double exp);							//设置曝光
    void SetAdjustPlus(double adj);							//设置增益
    void setBufferSize(int nSize);
    void setBalanceRatio(double dRedBalanceRatio, double dGreenBalanceRatio, double dBlueBalanceRatio);
    void setResolution(int height = 720, int width = 1280); //设置分辨率
    void setROI(int64_t nX, int64_t nY, int64_t nWidth, int64_t nHeight);
    void setBinning();
    bool loadSetting(int mode);
    void setFrameRate(double rate = 210);					//设置帧率
    ICameraPtr m_pCamera;				  //相机对象
  private:
    TVector<ICameraPtr> m_vCameraPtrList; //相机列表
    IStreamSourcePtr m_pStreamSource;	 //流文件


};

class FrameBuffer
{
  private:
    uint8_t *Buffer_;

    int Width_;

    int Height_;

    int PaddingX_;

    int PaddingY_;

    int DataSize_;

    int PixelFormat_;

    uint64_t TimeStamp_;

    uint64_t BlockId_;

  public:
    FrameBuffer(Dahua::GenICam::CFrame const &frame)
    {
        if (frame.getImageSize() > 0)
        {
            if (frame.getImagePixelFormat() == Dahua::GenICam::gvspPixelMono8)
            {
                Buffer_ = new (std::nothrow) uint8_t[frame.getImageSize()];
            }
            else
            {
                Buffer_ = new (std::nothrow) uint8_t[frame.getImageWidth() * frame.getImageHeight() * 3];
            }
            if (Buffer_)
            {
                Width_ = frame.getImageWidth();
                Height_ = frame.getImageHeight();
                PaddingX_ = frame.getImagePadddingX();
                PaddingY_ = frame.getImagePadddingY();
                DataSize_ = frame.getImageSize();
                PixelFormat_ = frame.getImagePixelFormat();
                BlockId_ = frame.getBlockId();
            }
        }
    }

    ~FrameBuffer()
    {
        if (Buffer_ != NULL)
        {
            delete[] Buffer_;
            Buffer_ = NULL;
        }
    }

    bool Valid()
    {
        if (NULL != Buffer_)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int Width()
    {
        return Width_;
    }

    int Height()
    {
        return Height_;
    }

    int PaddingX()
    {
        return PaddingX_;
    }

    int PaddingY()
    {
        return PaddingY_;
    }

    int DataSize()
    {
        return DataSize_;
    }

    uint64_t PixelFormat()
    {
        return PixelFormat_;
    }

    uint64_t TimeStamp()
    {
        return TimeStamp_;
    }

    void setWidth(uint32_t iWidth)
    {
        Width_ = iWidth;
    }

    void setPaddingX(uint32_t iPaddingX)
    {
        PaddingX_ = iPaddingX;
    }

    uint64_t BlockId()
    {
        return BlockId_;
    }

    void setPaddingY(uint32_t iPaddingX)
    {
        PaddingY_ = iPaddingX;
    }

    void setHeight(uint32_t iHeight)
    {
        Height_ = iHeight;
    }

    void setDataSize(int dataSize)
    {
        DataSize_ = dataSize;
    }

    void setPixelFormat(uint32_t pixelFormat)
    {
        PixelFormat_ = pixelFormat;
    }

    void setTimeStamp(uint64_t timeStamp)
    {
        TimeStamp_ = timeStamp;
    }

    uint8_t *bufPtr()
    {
        return Buffer_;
    }
};

#endif
