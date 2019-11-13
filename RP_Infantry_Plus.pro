QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    src/Aim/AngleSolver.cpp \
    src/Aim/ArmorDetector.cpp \
    src/Camera/video.cpp \
    src/Rune/Detect.cpp \
    src/SerialPort/CRC_Check.cpp \
    src/SerialPort/serialport.cpp \
    src/ImageConsProd.cpp

INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2

LIBS += /usr/local/lib/libopencv_*
LIBS += -L./depends/	-lMVSDK
LIBS += -L/opt/DahuaTech/MVViewer/lib/	-lMVSDK
LIBS += -L./depends/	-lImageConvert
LIBS += -L./depends/	-lVideoRender
LIBS += -L/opt/DahuaTech/MVViewer/lib/GenICam/bin/Linux64_x64/ -lGCBase_gcc421_v3_0 -lGenApi_gcc421_v3_0 -lLog_gcc421_v3_0 -llog4cpp_gcc421_v3_0 -lNodeMapData_gcc421_v3_0 -lXmlParser_gcc421_v3_0 -lMathParser_gcc421_v3_0 -lrt -lpthread


INCLUDEPATH = ./includes

HEADERS += \
    include/Aim/AngleSolver.hpp \
    include/Aim/ArmorDetector.hpp \
    include/Aim/Settings.hpp \
    include/Camera/video.h \
    include/Rune/Detect.h \
    include/SerialPort/CRC_Check.h \
    include/SerialPort/serialport.h \
    include/header.h \
    include/ImageConsProd.hpp \
    includes/GenICam/CAPI/IntTypes.h \
    includes/GenICam/CAPI/SDK.h \
    includes/GenICam/GigE/GigECamera.h \
    includes/GenICam/GigE/GigEInterface.h \
    includes/GenICam/Usb/UsbCamera.h \
    includes/GenICam/Usb/UsbInterface.h \
    includes/GenICam/AcquisitionControl.h \
    includes/GenICam/AnalogControl.h \
    includes/GenICam/Camera.h \
    includes/GenICam/Defs.h \
    includes/GenICam/DeviceControl.h \
    includes/GenICam/DigitalIOControl.h \
    includes/GenICam/ErrorCode.h \
    includes/GenICam/EventSubscribe.h \
    includes/GenICam/Frame.h \
    includes/GenICam/ImageFormatControl.h \
    includes/GenICam/ISPControl.h \
    includes/GenICam/ParameterNode.h \
    includes/GenICam/PixelType.h \
    includes/GenICam/StreamSource.h \
    includes/GenICam/System.h \
    includes/GenICam/TransportLayerControl.h \
    includes/GenICam/UserSetControl.h \
    includes/Infra/Detail/allocatorstringstorage.h \
    includes/Infra/Detail/atomic_count.hpp \
    includes/Infra/Detail/atomic_count_gcc.hpp \
    includes/Infra/Detail/atomic_count_gcc_x86.hpp \
    includes/Infra/Detail/atomic_count_pthreads.hpp \
    includes/Infra/Detail/atomic_count_solaris.hpp \
    includes/Infra/Detail/atomic_count_sync.hpp \
    includes/Infra/Detail/atomic_count_win32.hpp \
    includes/Infra/Detail/atomic_count_win64.hpp \
    includes/Infra/Detail/construct.h \
    includes/Infra/Detail/cowstringopt.h \
    includes/Infra/Detail/flex_string.h \
    includes/Infra/Detail/flex_string_details.h \
    includes/Infra/Detail/flex_string_shell.h \
    includes/Infra/Detail/ministringstorage.h \
    includes/Infra/Detail/pp.hpp \
    includes/Infra/Detail/pp_gcc.hpp \
    includes/Infra/Detail/pp_msvc.hpp \
    includes/Infra/Detail/simplestringstorage.h \
    includes/Infra/Detail/smallstringopt.h \
    includes/Infra/Detail/vectorstringstorage.h \
    includes/Infra/Types/IntTypes.h \
    includes/Infra/Types/Types.h \
    includes/Infra/Allocator.h \
    includes/Infra/Assert.h \
    includes/Infra/AtomicCount.h \
    includes/Infra/CString.h \
    includes/Infra/Defs.h \
    includes/Infra/Error.h \
    includes/Infra/File.h \
    includes/Infra/Function.h \
    includes/Infra/FunctionTemplate.h \
    includes/Infra/Guard.h \
    includes/Infra/IntTypes.h \
    includes/Infra/Mutex.h \
    includes/Infra/PreProcessor.h \
    includes/Infra/PrintLog.h \
    includes/Infra/ReadWriteMutex.h \
    includes/Infra/RecursiveMutex.h \
    includes/Infra/Semaphore.h \
    includes/Infra/Signal.h \
    includes/Infra/SignalTemplate.h \
    includes/Infra/StaticAssert.h \
    includes/Infra/String.h \
    includes/Infra/System.h \
    includes/Infra/Thread.h \
    includes/Infra/ThreadSpecific.h \
    includes/Infra/Time.h \
    includes/Infra/Timer.h \
    includes/Infra/Types.h \
    includes/Infra/Vector.h \
    includes/Infra/Version.h \
    includes/Media/ImageConvert.h \
    includes/Media/VideoRender.h \
    includes/Memory/Detail/sp_counted_base/sp_counted_base.h \
    includes/Memory/Detail/sp_counted_base/sp_counted_base_gcc_ia64.hpp \
    includes/Memory/Detail/sp_counted_base/sp_counted_base_gcc_x86.hpp \
    includes/Memory/Detail/sp_counted_base/sp_counted_base_impl.hpp \
    includes/Memory/Detail/sp_counted_base/sp_counted_base_w32.hpp \
    includes/Memory/Detail/checked_delete.hpp \
    includes/Memory/Detail/MemPool.h \
    includes/Memory/Detail/shared_count.h \
    includes/Memory/Detail/singleton.h \
    includes/Memory/Detail/singleton_pool.h \
    includes/Memory/Detail/smartptr_detail.h \
    includes/Memory/Detail/sp_counted_base.hpp \
    includes/Memory/Detail/sp_counted_impl.hpp \
    includes/Memory/Block.h \
    includes/Memory/Buffer.h \
    includes/Memory/Defs.h \
    includes/Memory/EnableSharedFromThis.h \
    includes/Memory/Packet.h \
    includes/Memory/PoolAllocator.h \
    includes/Memory/RefCount.h \
    includes/Memory/ScopedPtr.h \
    includes/Memory/SharedPtr.h \
    includes/Memory/SharePacketHelper.h \
    includes/Memory/SmartObjectPtr.h \
    includes/Memory/WeakPtr.h
