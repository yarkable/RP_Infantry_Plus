#include "include/ImageConsProd.hpp"
#include "include/Aim/Settings.hpp"
#include "include/Camera/v4l2.h"
#include <thread>

using namespace cv;
using namespace std;

#define MULTI

int main()
{
    
    string config_file_name = "/home/nuc/kevin/RP_Infantry_Plus/extraFile/AimXMl/param_config.yml";
    Settings setting(config_file_name);
    // communicate with car
    SerialPort port("/dev/ttyUSB"); // 利用udev给TTL-USB串口模块重新命名(解决/dev/ttyUSB0突变成/dev/ttyUSB1的问题)
    port.initSerialPort();

    // start threads
    ImageConsProd image_cons_prod(&setting, port);    
#ifdef MULTI
    // 利用多线程加快速度
    std::thread t1(&ImageConsProd::ImageProducer, std::ref(image_cons_prod)); // pass by reference
    std::thread t2(&ImageConsProd::ImageConsumer, std::ref(image_cons_prod));

    t1.join();
    t2.join();

#else

    std::thread t3(&ImageConsProd::test, image_cons_prod);
    t3.join();

#endif

port.closePort();
}
