#include "include/Camera/video.h"

void Video::setBufferSize(int nSize){
    bool bRet;
    m_pStreamSource = CSystem::getInstance().createStreamSource(m_pCamera);
    if (NULL == m_pStreamSource)
    {
        printf("create a SourceStream failed!\n");
        return;
    }

    m_pStreamSource->setBufferCount(nSize);
//	bRet = intNode.setValue(width);
//	if (false == bRet)
//	{
//		printf("set width fail.\n");
//		return;
//	}

//	intNode = sptrImageFormatControl
//	bRet = intNode.setValue(height);
//	if (false == bRet)
//	{
//		printf("set height fail.\n");
//		return;
//	}
}


bool Video::loadSetting(int mode)
{
    CSystem &sysobj = CSystem::getInstance();
    IUserSetControlPtr iSetPtr;
    iSetPtr = sysobj.createUserSetControl(m_pCamera);
    CEnumNode nodeUserSelect(m_pCamera, "UserSetSelector");
    if (mode == 0)
    {
        if (!nodeUserSelect.setValueBySymbol("UserSet1")){
            cout << "set UserSetSelector failed!" << endl;
        }
    }
    else if (mode == 1){
        if (!nodeUserSelect.setValueBySymbol("UserSet2")){
            cout << "set UserSetSelector failed!" << endl;
        }
    }

    CCmdNode nodeUserSetLoad(m_pCamera, "UserSetLoad");
    if (!nodeUserSetLoad.execute()){
        cout << "set UserSetLoad failed!" << endl;
    }
}

bool Video::videoCheck()
{
    CSystem &systemObj = CSystem::getInstance();

    bool bRet = systemObj.discovery(m_vCameraPtrList);
    if (false == bRet)
    {
        printf("discovery fail.\n");
        exit(-1);
        return false;
    }

    // 打印相机基本信息（key, 制造商信息, 型号, 序列号）
    for (int i = 0; i < m_vCameraPtrList.size(); i++)
    {
        ICameraPtr cameraSptr = m_vCameraPtrList[i];

        printf("Camera[%d] Info :\n", i);
        printf("    key           = [%s]\n", cameraSptr->getKey());
        printf("    vendor name   = [%s]\n", cameraSptr->getVendorName());
        printf("    model         = [%s]\n", cameraSptr->getModelName());
        printf("    serial number = [%s]\n", cameraSptr->getSerialNumber());
    }

    if (m_vCameraPtrList.size() < 1)
    {
        printf("no camera.\n");
        return false;
        //	msgBoxWarn(tr("Device Disconnected."));
    }
    else
    {
        //默认设置列表中的第一个相机为当前相机，其他操作比如打开、关闭、修改曝光都是针对这个相机。
        m_pCamera = m_vCameraPtrList[0];
    }
    return true;
}

bool Video::videoOpen()
{
    if (NULL == m_pCamera)
    {
        printf("connect camera fail. No camera.\n");
        exit(-1);
        return false;
    }

    if (true == m_pCamera->isConnected())
    {
        printf("camera is already connected.\n");
        exit(-1);
        return false;
    }

    if (false == m_pCamera->connect())
    {
        printf("connect camera fail.\n");
        exit(-1);
        return false;
    }

    return true;
}

void Video::videoClose()
{
    if (NULL == m_pCamera)
    {
        printf("disconnect camera fail. No camera.\n");
        exit(-1);
        return;
    }

    if (false == m_pCamera->isConnected())
    {
        printf("camera is already disconnected.\n");
        exit(-1);
        return;
    }

    if (false == m_pCamera->disConnect())
    {
        printf("disconnect camera fail.\n");
    }
}

bool Video::videoStart()
{
    if (m_pStreamSource != NULL)
    {
        return true;
    }

    if (NULL == m_pCamera)
    {
        printf("start camera fail. No camera.\n");
        exit(-1);
        return false;
    }

    m_pStreamSource = CSystem::getInstance().createStreamSource(m_pCamera); //创建流的对象
    if (NULL == m_pStreamSource)
    {
        printf("Create stream source failed.");
        exit(-1);
        return false;
    }


    return true;
}

void Video::startGrabbing()
{
    m_pStreamSource->setBufferCount(1);
    m_pStreamSource->startGrabbing();
}

void Video::CameraChangeTrig(ETrigType trigType)
{
    if (NULL == m_pCamera)
    {
        printf("Change Trig fail. No camera or camera is not connected.\n");
        exit(-1);
        return;
    }

    if (trigContinous == trigType)
    {
        //设置触发模式
        CEnumNode nodeTriggerMode(m_pCamera, "TriggerMode");
        if (false == nodeTriggerMode.isValid())
        {
            printf("get TriggerMode node fail.\n");
            return;
        }
        if (false == nodeTriggerMode.setValueBySymbol("Off"))
        {
            printf("set TriggerMode value = Off fail.\n");
            return;
        }
    }
    else if (trigSoftware == trigType)
    {
        //设置触发源为软触发
        CEnumNode nodeTriggerSource(m_pCamera, "TriggerSource");
        if (false == nodeTriggerSource.isValid())
        {
            printf("get TriggerSource node fail.\n");
            return;
        }
        if (false == nodeTriggerSource.setValueBySymbol("Software"))
        {
            printf("set TriggerSource value = Software fail.\n");
            return;
        }

        //设置触发器
        CEnumNode nodeTriggerSelector(m_pCamera, "TriggerSelector");
        if (false == nodeTriggerSelector.isValid())
        {
            printf("get TriggerSelector node fail.\n");
            return;
        }
        if (false == nodeTriggerSelector.setValueBySymbol("FrameStart"))
        {
            printf("set TriggerSelector value = FrameStart fail.\n");
            return;
        }

        //设置触发模式
        CEnumNode nodeTriggerMode(m_pCamera, "TriggerMode");
        if (false == nodeTriggerMode.isValid())
        {
            printf("get TriggerMode node fail.\n");
            return;
        }
        if (false == nodeTriggerMode.setValueBySymbol("On"))
        {
            printf("set TriggerMode value = On fail.\n");
            return;
        }
    }
    else if (trigLine == trigType)
    {
        //设置触发源为Line1触发
        CEnumNode nodeTriggerSource(m_pCamera, "TriggerSource");
        if (false == nodeTriggerSource.isValid())
        {
            printf("get TriggerSource node fail.\n");
            return;
        }
        if (false == nodeTriggerSource.setValueBySymbol("Line1"))
        {
            printf("set TriggerSource value = Line1 fail.\n");
            return;
        }

        //设置触发器
        CEnumNode nodeTriggerSelector(m_pCamera, "TriggerSelector");
        if (false == nodeTriggerSelector.isValid())
        {
            printf("get TriggerSelector node fail.\n");
            return;
        }
        if (false == nodeTriggerSelector.setValueBySymbol("FrameStart"))
        {
            printf("set TriggerSelector value = FrameStart fail.\n");
            return;
        }

        //设置触发模式
        CEnumNode nodeTriggerMode(m_pCamera, "TriggerMode");
        if (false == nodeTriggerMode.isValid())
        {
            printf("get TriggerMode node fail.\n");
            return;
        }
        if (false == nodeTriggerMode.setValueBySymbol("On"))
        {
            printf("set TriggerMode value = On fail.\n");
            return;
        }

        // 设置外触发为上升沿（下降沿为FallingEdge）
        CEnumNode nodeTriggerActivation(m_pCamera, "TriggerActivation");
        if (false == nodeTriggerActivation.isValid())
        {
            printf("get TriggerActivation node fail.\n");
            return;
        }
        if (false == nodeTriggerActivation.setValueBySymbol("RisingEdge"))
        {
            printf("set TriggerActivation value = RisingEdge fail.\n");
            return;
        }
    }
}

void Video::ExecuteSoftTrig()
{
    if (NULL == m_pCamera)
    {
        printf("Set GainRaw fail. No camera or camera is not connected.\n");
        return;
    }

    CCmdNode nodeTriggerSoftware(m_pCamera, "TriggerSoftware");
    if (false == nodeTriggerSoftware.isValid())
    {
        printf("get TriggerSoftware node fail.\n");
        return;
    }
    if (false == nodeTriggerSoftware.execute())
    {
        printf("set TriggerSoftware fail.\n");
        return;
    }

    // printf("ExecuteSoftTrig success.\n");
}

void Video::videoStopStream()
{
    if (m_pStreamSource == NULL)
    {
        printf("stopGrabbing succefully!\n");
        return;
    }

    if (!m_pStreamSource->stopGrabbing())
    {
        printf("stopGrabbing  fail.\n");
    }
}

bool Video::getFrame(Mat &img)
{

    CFrame frame, frameClone;
    bool isSuccess = m_pStreamSource->getFrame(frame, 300/*500*/);
    if (!isSuccess)
    {
        printf("getFrame  fail.\n");
        m_pStreamSource->stopGrabbing();
        m_pCamera->disConnect();
        exit(0);
        return false;
    }

    //判断帧的有效性
    bool isValid = frame.valid();
    if (!isValid)
    {
        printf("frame is invalid!\n");
        return false;
    }

    frameClone = frame.clone();

    TSharedPtr<FrameBuffer> PtrFrameBuffer(new FrameBuffer(frameClone));
    if (!PtrFrameBuffer)
    {
        printf("create PtrFrameBuffer failed!\n");
        return false;
    }

    uint8_t *pSrcData = new (std::nothrow) uint8_t[frameClone.getImageSize()];
    if (pSrcData)
    {
        memcpy(pSrcData, frameClone.getImage(), frameClone.getImageSize());
    }
    else
    {
        printf("new pSrcData failed!\n");
        return false;
    }

    int dstDataSize = 0;
    IMGCNV_SOpenParam openParam;
    openParam.width = PtrFrameBuffer->Width();
    openParam.height = PtrFrameBuffer->Height();
    openParam.paddingX = PtrFrameBuffer->PaddingX();
    openParam.paddingY = PtrFrameBuffer->PaddingY();
    openParam.dataSize = PtrFrameBuffer->DataSize();
    openParam.pixelForamt = PtrFrameBuffer->PixelFormat();

    IMGCNV_EErr status = IMGCNV_ConvertToBGR24(pSrcData, &openParam, PtrFrameBuffer->bufPtr(), &dstDataSize);
    if (IMGCNV_SUCCESS != status)
    {
        delete[] pSrcData;
        return false;
    }

    delete[] pSrcData;

    //将读进来的帧数据转化为opencv中的Mat格式操作
    Size size;
    size.height = PtrFrameBuffer->Height();
    size.width = PtrFrameBuffer->Width();
    img = Mat(size, CV_8UC3, PtrFrameBuffer->bufPtr()).clone();
//    PtrFrameBuffer.reset();
    frameClone.reset();
    return true;
}


void Video::setBalanceRatio(double dRedBalanceRatio, double dGreenBalanceRatio, double dBlueBalanceRatio)
{
    bool bRet;
    IAnalogControlPtr sptrAnalogControl = CSystem::getInstance().createAnalogControl(m_pCamera);
    if (NULL == sptrAnalogControl)
    {
        return ;
    }

    /* 关闭自动白平衡 */
    CEnumNode enumNode = sptrAnalogControl->balanceWhiteAuto();
    if (false == enumNode.isReadable())
    {
        printf("balanceRatio not support.\n");
        return ;
    }

    bRet = enumNode.setValueBySymbol("Off");
    if (false == bRet)
    {
        printf("set balanceWhiteAuto Off fail.\n");
        return ;
    }

    enumNode = sptrAnalogControl->balanceRatioSelector();
    bRet = enumNode.setValueBySymbol("Red");
    if (false == bRet)
    {
        printf("set red balanceRatioSelector fail.\n");
        return ;
    }

    CDoubleNode doubleNode = sptrAnalogControl->balanceRatio();
    bRet = doubleNode.setValue(dRedBalanceRatio);
    if (false == bRet)
    {
        printf("set red balanceRatio fail.\n");
        return ;
    }

    enumNode = sptrAnalogControl->balanceRatioSelector();
    bRet = enumNode.setValueBySymbol("Green");
    if (false == bRet)
    {
        printf("set green balanceRatioSelector fail.\n");
        return ;
    }

    doubleNode = sptrAnalogControl->balanceRatio();
    bRet = doubleNode.setValue(dGreenBalanceRatio);
    if (false == bRet)
    {
        printf("set green balanceRatio fail.\n");
        return ;
    }

    enumNode = sptrAnalogControl->balanceRatioSelector();
    bRet = enumNode.setValueBySymbol("Blue");
    if (false == bRet)
    {
        printf("set blue balanceRatioSelector fail.\n");
        return ;
    }

    doubleNode = sptrAnalogControl->balanceRatio();
    bRet = doubleNode.setValue(dBlueBalanceRatio);
    if (false == bRet)
    {
        printf("set blue balanceRatio fail.\n");
        return ;
    }
}


void Video::SetExposeTime(double exp)
{
    bool bRet;
    IAcquisitionControlPtr sptrAcquisitionControl = CSystem::getInstance().createAcquisitionControl(m_pCamera);
    if (NULL == sptrAcquisitionControl)
    {
        printf("create a IAcquisitionControlPtr failed!\n");
        return;
    }
    CEnumNode eNode = sptrAcquisitionControl->exposureAuto();
    uint64 getValue;
    if (!eNode.getValue(getValue))
    {
        printf("get value of type is failed!\n");
        return;
    }
    if (getValue)//如果开启了自动曝光模式，则关闭
    {
        bRet = eNode.setValueBySymbol("Off");
        if (!bRet)
        {
            printf("close autoExposure failed!\n");
            return;
        }
    }

    CDoubleNode dNode = sptrAcquisitionControl->exposureTime();
    bRet = dNode.setValue(exp);
    if (!bRet)
    {
        printf("set exposure failed!\n");
        return;
    }

}

void Video::SetAdjustPlus(double adj)
{
    if (NULL == m_pCamera)
    {
        printf("Set GainRaw fail. No camera or camera is not connected.\n");
        return;
    }

    CDoubleNode nodeGainRaw(m_pCamera, "GainRaw");

    if (false == nodeGainRaw.isValid())
    {
        printf("get GainRaw node fail.\n");
        return;
    }

    if (false == nodeGainRaw.isAvailable())
    {
        printf("GainRaw is not available.\n");
        return;
    }

    if (false == nodeGainRaw.setValue(adj))
    {
        printf("set GainRaw value = %f fail.\n", adj);
        return;
    }
}

void Video::setResolution(int height, int width)
{
    bool bRet;
    IImageFormatControlPtr sptrImageFormatControl = CSystem::getInstance().createImageFormatControl(m_pCamera);
    if (NULL == sptrImageFormatControl)
    {
        printf("create a IImageFormatControlPtr failed!\n");
        return;
    }

    CIntNode intNode = sptrImageFormatControl->height();
    bRet = intNode.setValue(width);
    if (false == bRet)
    {
        printf("set width fail.\n");
        return;
    }

    intNode = sptrImageFormatControl->height();
    bRet = intNode.setValue(height);
    if (false == bRet)
    {
        printf("set height fail.\n");
        return;
    }
}

void Video::setROI(int64_t nX, int64_t nY, int64_t nWidth, int64_t nHeight)
{
    bool bRet;
    CIntNode nodeWidth(m_pCamera, "Width");
    bRet = nodeWidth.setValue(nWidth);
    if (!bRet)
    {
        printf("set width fail.\n");
    return;
    }
    CIntNode nodeHeight(m_pCamera, "Height");
    bRet = nodeHeight.setValue(nHeight);
    if (!bRet)
    {
        printf("set Height fail.\n");
    return;
    }
    CIntNode OffsetX(m_pCamera, "OffsetX");
    bRet = OffsetX.setValue(nX);
    if (!bRet)
    {
        printf("set OffsetX fail.\n");
    return;
    }
    CIntNode OffsetY(m_pCamera, "OffsetY");
    bRet = OffsetY.setValue(nY);
    if (!bRet)
    {
        printf("set OffsetY fail.\n");
    return;
    }
//    bool bRet;
//    IImageFormatControlPtr sptrImageFormatControl = CSystem::getInstance().createImageFormatControl(m_pCamera);
//    if (NULL == sptrImageFormatControl)
//    {
//        return;
//    }

//    /* width */
//    CIntNode intNode = sptrImageFormatControl->width();
//    bRet = intNode.setValue(nWidth);
//    if (!bRet)
//    {
//        printf("set width fail.\n");
//    return;
//    }

//    /* height */
//    intNode = sptrImageFormatControl->height();
//    bRet = intNode.setValue(nHeight);
//    if (!bRet)
//    {
//        printf("set height fail.\n");
//    return;
//    }

//    /* OffsetX */
//    intNode = sptrImageFormatControl->offsetX();
//    bRet = intNode.setValue(nX);
//    if (!bRet)
//    {
//        printf("set offsetX fail.\n");
//    return;
//    }

//    /* OffsetY */
//    intNode = sptrImageFormatControl->offsetY();
//    bRet = intNode.setValue(nY);
//    if (!bRet)
//    {
//        printf("set offsetY fail.\n");
//    return;
//    }

    return;
}

void Video::setBinning()
{
    CEnumNodePtr ptrParam(new CEnumNode(m_pCamera, "Binning"));
    if (ptrParam)
    {
        if (false == ptrParam->isReadable())
        {
            printf("binning not support.\n");
            return;
        }

        if (false == ptrParam->setValueBySymbol("XY"))
        {
            printf("set Binning XY fail.\n");
            return;
        }

//        if (false == ptrParam->setValueBySymbol("Off"))
//        {
//            printf("set Binning Off fail.\n");
//            return;
//        }
    }
    return;
}

void Video::setFrameRate(double rate)
{
    bool bRet;
    IAcquisitionControlPtr sptAcquisitionControl = CSystem::getInstance().createAcquisitionControl(m_pCamera);
    if (NULL == sptAcquisitionControl)
    {
        return;
    }

    CBoolNode booleanNode = sptAcquisitionControl->acquisitionFrameRateEnable();
    bRet = booleanNode.setValue(true);
    if (false == bRet)
    {
        printf("set acquisitionFrameRateEnable fail.\n");
        return;
    }

    CDoubleNode doubleNode = sptAcquisitionControl->acquisitionFrameRate();
    bRet = doubleNode.setValue(rate);
    if (false == bRet)
    {
        printf("set acquisitionFrameRate fail.\n");
        return;
    }
}
