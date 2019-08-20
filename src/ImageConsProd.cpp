#include "include/ImageConsProd.hpp"
#include "include/Aim/AngleSolver.hpp"
#include "include/SerialPort/serialport.h"
#include "include/header.h"
#include "include/SerialPort/CRC_Check.h"
#include "include/Rune/Detect.h"
#include "iostream"
#include "GenICam/System.h"
#include "GenICam/Camera.h"
#include "GenICam/GigE/GigECamera.h"
#include "GenICam/GigE/GigEInterface.h"
#include "Infra/PrintLog.h"
#include "Memory/SharedPtr.h"
#include "include/Camera/video.h"

using namespace std;
// 工业相机SDK
using namespace Dahua::GenICam;
using namespace Dahua::Infra;

//#define SHOW_IMAGE
//#define USE_VIDEO
#define COUT
#define CAP_VIDEO
#define RUNE_CAP_VIDEO
//#define SERIAL_DEBUG

#define VIDEO_WIDTH  1280
#define VIDEO_HEIGHT 720
#define V_OFFSET 304
#define EXPOSURE (3000 + 2000)// 5000
#define SATURATION_BLUE 60
#define SATURATION_RED 100

#define EXPOSURE_RUNE 2000
#define RUNE_WIDTH  888
#define RUNE_HEIGHT 1000

#define BUFFER_SIZE 1

volatile unsigned int prdIdx;
volatile unsigned int csmIdx;
#ifdef SERIAL_DEBUG
volatile unsigned int mode = 7;
volatile unsigned int sentry_mode = 1;
volatile unsigned int base_mode = 0;
#else
volatile unsigned int mode;
volatile unsigned int sentry_mode;
volatile unsigned int base_mode;
#endif

struct ImageData {
    Mat img;
    unsigned int frame;
};
ImageData data[BUFFER_SIZE];


void ImageConsProd::ImageProducer(){

#ifdef USE_VIDEO
    settings->save_result = 0;
    string video_name = "/home/ubuntu/projects/RMVision/build-RMVision-Desktop-Release/webcam.avi";
    //string video_name = "/home/ubuntu/projects/RMVision/RMVision/20160823165244.mp4";
    VideoCapture cap(video_name); // open the default camera
    if (!cap.isOpened())  // check if we succeeded
        return;
#endif

    //////////////////////// setting camera ///////////////////////////

    // 创建工业相机的实例
    Video v;

    // 切换大小符和自瞄的变量
    bool aim_settled = false, rune_settled = false;

    if (!v.videoCheck())
    {
        printf("videoCheck failed!\n");
        return ;
    }
    if (!v.videoOpen())
    {
        printf("videoOpen failed!\n");
        return ;
    }

//    v.setBufferSize(1);
    v.SetExposeTime(EXPOSURE);                                   //设置曝光
    v.setBalanceRatio(1,1,1);
//    v.SetAdjustPlus(3);                                      //设置增益
    Video::ETrigType type = Video::ETrigType::trigContinous; //改为连续拉流
    v.CameraChangeTrig(type);                                //默认为软触发
    if (!v.videoStart())
    {
        printf("videoStart failed!\n");
        return ;
    }



    //////////////////////// Setting Camera End //////////////////////
    Mat img;
    while(1){

        // 录制素材
#ifdef RUNE_CAP_VIDEO
        VideoWriter Rune_write;
        // 基于当前系统的当前日期/时间
        time_t now = time(0);
        tm *ltm = localtime(&now);
        // 输出 tm 结构的各个组成部分
        string year = to_string(1900 + ltm->tm_year);
        string month = to_string(ltm->tm_mon + 1);
        string day = to_string(ltm->tm_mday);
        string hour = to_string(ltm->tm_hour);
        string minute = to_string(ltm->tm_min);
        string second = to_string(ltm->tm_sec);
        string ex = to_string(EXPOSURE);
        string name = "5----RUNE" + ex + "exp-"+ year + "-" + month + "-" + day + "-" + hour + "-" + minute  + "-" + second + ".avi";
        if (mode == 0){
        }else if(mode == 3 || mode == 4 || mode == 5 || mode == 6 || mode == 7 || mode == 8){
            Rune_write.open(name, CV_FOURCC('M', 'J', 'P', 'G'), 120, Size(888, 1000));
        }
        int cnt = 2000;
        while(cnt--){
#endif
            while(prdIdx - csmIdx >= BUFFER_SIZE);
            int mode_temp;
            int sentry_mode_temp;
            int base_mode_temp;
#ifndef SERIAL_DEBUG
            // 检测不到串口就退出程序
            if (_port.get_Mode(mode_temp, sentry_mode_temp, base_mode_temp) == false)
                exit(-1);
            mode = mode_temp;
            sentry_mode = sentry_mode_temp;
            base_mode = base_mode_temp;
#endif
            
            // 开始读取图片
            if(mode == 0x01 || mode == 0x02){
                rune_settled = false;
                if (aim_settled){}
                else{
                    v.videoStopStream();
                    v.loadSetting(0);
                    v.SetExposeTime(EXPOSURE);
                    v.startGrabbing();
                }

                aim_settled = true;

                if (v.getFrame(img)){
                }
                else
                {
                    printf("getFrame failed!\n");
                    continue ;
                }
                data[prdIdx % BUFFER_SIZE].img = img;
                data[prdIdx % BUFFER_SIZE].frame++;
                ++prdIdx;
            }else if(mode == 0x03 || mode == 0x06 || mode == 0x04 || mode == 0x05 || mode == 0x07 || mode == 0x08){
                aim_settled = false;
                if (rune_settled){}
                else{
                    v.videoStopStream();
                    v.loadSetting(1);
                    v.SetExposeTime(EXPOSURE_RUNE);
                    v.startGrabbing();
                }

                rune_settled = true;
                if (v.getFrame(img)){
                }
                else{
                    printf("getFrame failed!\n");
                    continue ;
                }
                data[prdIdx % BUFFER_SIZE].img = img;
                data[prdIdx % BUFFER_SIZE].frame++;
                ++prdIdx;
#ifdef RUNE_CAP_VIDEO
                if(mode == 0){}
                else if(mode == 3 || mode == 4 || mode == 5 || mode == 6 || mode == 7 || mode == 8){
                    Rune_write <<  img;
                }
            }
#endif
        }
    }
}

void ImageConsProd::ImageConsumer(){
    Settings & setting = *settings;

    // load calibration parameter
    FileStorage fs1(setting.intrinsic_file_720, FileStorage::READ);
    if (!fs1.isOpened())	{
        cout << "Could not open the configuration file: \"" << setting.intrinsic_file_720 << "\"" << endl;
        return ;
    }
    Mat cam_matrix_720, distortion_coeff_720;
    fs1["Camera_Matrix"] >> cam_matrix_720;
    fs1["Distortion_Coefficients"] >> distortion_coeff_720;

    //======================== 结算角度 ===============================

    // 最后不是根据这个的
    AngleSolver solver_720(cam_matrix_720, distortion_coeff_720, 22.5, 5.5);
    Point2f image_center_720 = Point2f(cam_matrix_720.at<double>(0,2), cam_matrix_720.at<double>(1,2));

    // 大小装甲板的角度解法
    AngleSolverFactory angle_slover;
    angle_slover.setTargetSize(22.5, 5.5, AngleSolverFactory::TARGET_ARMOR);
    angle_slover.setTargetSize(13, 5.5, AngleSolverFactory::TARGET_SAMLL_ATMOR);

    ArmorDetector armor_detector(setting.armor);
    armor_detector.setPnPSlover(&solver_720);

    // vars for debug use
    Mat src_csm;
    Mat src;
    int t1 = 0, t2 = 0;
    int frame_num = 0;
    int near_face = 0;
    int miss_detection_cnt = 0;
    int find_cnt = 0;
    float last_x = 0, last_y = 0, last_dist;


    // dafu param
    Detect Find;
    VisionData Vision;
    bool Rune_flag = false;


    // =================== 大循环 =======================

    while(1){

    // 录制素材（用mp24格式会比mjpg快四五毫秒）
#ifdef CAP_VIDEO
        VideoWriter write;
        // 基于当前系统的当前日期/时间
        time_t now = time(0);
        tm *ltm = localtime(&now);
        // 输出 tm 结构的各个组成部分
        string year = to_string(1900 + ltm->tm_year);
        string month = to_string(ltm->tm_mon + 1);
        string day = to_string(ltm->tm_mday);
        string hour = to_string(ltm->tm_hour);
        string minute = to_string(ltm->tm_min);
        string second = to_string(ltm->tm_sec);
        string ex = to_string(EXPOSURE);
        string name = ex + "exp-"+ year + "-" + month + "-" + day + "-" + hour + "-" + minute  + "-" + second + ".avi";
        if (mode != 1 && mode != 2){
        }else{
            write.open(name, CV_FOURCC('M', 'J', 'P', 'G'), 120, Size(1280, 720));
        }
        int cnt = 2000;
        while(cnt--)
{

#endif
        // 接收敌方颜色信息
        if (mode == 1 || mode == 2){
            if (mode == 1)
                armor_detector.enemy_color = RED;
            else if (mode == 2)
                armor_detector.enemy_color = BLUE;
            while(prdIdx - csmIdx == 0);
            t1 = cv::getTickCount();
            data[csmIdx % BUFFER_SIZE].img.copyTo(src);
#ifdef CAP_VIDEO
            // 没有命令时就不处理
            if (mode == 0){}
            else{
                double tt1 = getTickCount();
                write << src;
                double tt2 = getTickCount();
                cout << "time::::::::::::::::::::" << (tt2 - tt1) * 1000 / getTickFrequency() << endl;
            }
#endif
            frame_num = data[csmIdx % BUFFER_SIZE].frame;
            ++csmIdx;
            if(src.empty()){
                continue;
            }

            if(setting.show_image || setting.save_result){
                t1 = cv::getTickCount();
                src.copyTo(src_csm);
            }

            if (src.channels() != 3)
                continue;

            RotatedRect rect;
            double angle_x = 0.0, angle_y = 0.0, dist = 0;
            double distance = 0;
            Point2f center = cv::Point2f();
            VisionData vdata;


            ArmorParam armor_para_720 = setting.armor;
            armor_detector.setPara(armor_para_720);
            angle_slover.setSolver(&solver_720);

            // 直接调用函数找到读进来的图中是否有目标
            rect = armor_detector.getTargetAera(src, sentry_mode, base_mode);

            center= rect.center;
            int len = MIN(rect.size.height, rect.size.width);
            // 用灯条的高度来判断目标是否贴脸（已弃用）
            if (len > armor_detector.get_near_face()){
                near_face = 1;
            }else{
                near_face = 0;
            }


            // 根据长宽比判断目标是大装甲还是小装甲
            // 哨兵模式下强制为大装甲
            AngleSolverFactory::TargetType type = armor_detector.isSamllArmor() ? AngleSolverFactory::TARGET_SAMLL_ATMOR : AngleSolverFactory::TARGET_ARMOR;
            if (sentry_mode) type = AngleSolverFactory::TARGET_ARMOR;

            // 解算出的角度，为false则说明没有识别到目标
            if (angle_slover.getAngle(rect, type, angle_x, angle_y, dist) == true){
                miss_detection_cnt = 0;
                /**
                 * 这是当初为了做移动预测加的条件，已弃用
                 */
                int bias_w_l = rect.size.width * (0.5 + 0.8);
                int bias_w_r = rect.size.width * (0.5 + 0.8);
                int bias_h_u = rect.size.height * (0.5 + 0.5);
                int bias_h_b = rect.size.height * (0.5 + 0.2);
                int actual_center_x = 765;
                int actual_center_y = 291;
                if(rect.center.x > actual_center_x - bias_w_l
                    && rect.center.x < actual_center_x + bias_w_r
                    && rect.center.y > actual_center_y - bias_h_u
                    && rect.center.y < actual_center_y + bias_h_b)
                ++find_cnt;

                else{
                    find_cnt = 0;
                }

            }
            else {
                ++miss_detection_cnt;
                find_cnt = 0;
            }
            if (angle_x != 0 && angle_y != 0){
                // 这是用excel拟合出来的灯条高度与实际距离的函数关系（我用单目pnp解出的距离不行）
                distance = 10941 * pow(len, -1.066);

                // do the angle compensation here
                /////////////////////////////////
                /**
                 * 可以在这里做子弹下坠补偿，通过pnp解出的角度在5米之内几乎都能打中装甲板
                 * 在5米之外就要通过一些补偿才能击中，不过5米之外一般不会开枪了。。
                 */
                if (sentry_mode)
                    angle_y += 1;

                // 基地模式发送特殊的识别flag
                if (base_mode){
                    vdata = {center.x, center.y, distance, 1, 8, 0, near_face};
                }
                else{
                    if(find_cnt >= 2)
                        vdata = {angle_x, angle_y, distance, 1, 1, 0, near_face};
                    else
                        vdata = {angle_x, angle_y, distance, 0, 1, 0, near_face};

                    last_x = angle_x;
                    last_y = angle_y;
                    last_dist = distance;
                }


                _port.TransformData(vdata);
                _port.send();
            }
            else{
                
                if (base_mode){
                    vdata = {center.x, center.y, distance, 1, 0, 0, near_face};
                }
                else{
                    /**
                     * 对哨兵模式进行了特殊处理
                     * 在掉帧超过一定帧数时才会发送未识别
                     * 否则就发送之前的角度乘以一个系数
                     * 这是为了防止打灭灯条后云台会停一下的问题
                     */
                    if (sentry_mode){
                        if (miss_detection_cnt > 10)
                            vdata = {angle_x, angle_y, distance, 0, 0, 0, near_face};
                        else
                            vdata = {last_x / 3, last_y / 3, last_dist, 0, 1, 0, near_face};
                    }
                    else{
                        if (miss_detection_cnt > 5)
                            vdata = {angle_x, angle_y, distance, 0, 0, 0, near_face};
                        else
                            vdata = {last_x / 3, last_y / 3, last_dist, 0, 1, 0, near_face};
                    }
                }

                _port.TransformData(vdata);
                _port.send();
            }


            // draw result
            if(setting.show_image > 0 || setting.save_result > 0){
#ifdef SHOW_IMAGE
                cv::Point2f & image_center = image_center_720;
                circle(src_csm, image_center, 3, CV_RGB(0, 255, 0), 2);

                Point2f vertices[4];
                rect.points(vertices);
                for (int i = 0; i < 4; i++){
                    line(src_csm, vertices[i], vertices[(i + 1) % 4], CV_RGB(0, 255, 0), 3);
                }
                circle(src_csm, rect.center, 4, Scalar(0, 0, 255), 4);

                // debug可视化参数
                char str[50], str1[50];
                Scalar color = armor_detector.enemy_color == RED ? Scalar(0, 66, 255) : Scalar(255, 200, 0);
                sprintf(str, "%.2f, %.2f, %.2f, %.f, %.f",
                        vdata.yaw_angle.f, vdata.pitch_angle.f, distance, center.x, center.y);
                putText(src_csm, str, Point(10, 40), CV_FONT_HERSHEY_COMPLEX_SMALL, 1.3, color, 1);
                const char * size = type == AngleSolverFactory::TARGET_SAMLL_ATMOR ? "small" : "big";
                if (center.x == 0) size = "NoTarget";
                sprintf(str1, "%d, %d, %d, %s",
                        sentry_mode, vdata.isFindTarget, vdata.nearFace, size);
                putText(src_csm, str1, Point(666, 40), CV_FONT_HERSHEY_COMPLEX_SMALL, 1.3, color, 1);
#endif


                t2 = cv::getTickCount();
#ifdef COUT
            cout << "Consumer-Time: " << (t2 - t1) * 1000.0 / cv::getTickFrequency() << "ms   frame No.:" << frame_num << endl << endl;
#endif
            }



            if (setting.show_image > 0){
                Mat src_show = src_csm;
#ifdef SHOW_IMAGE
                imshow("result", src_show);
                char key = waitKey(1);
                if (key == 'q' || key == 'Q'){
                    exit(0);
                }
#endif
            }
            if(Rune_flag == true){
                Rune_flag = false;
            }
        }
        else if (mode == 3 || mode == 4 || mode == 5 || mode == 6 || mode ==7 || mode == 8){
            while(prdIdx - csmIdx == 0);
            QTime time;
            time.start();
            if(Rune_flag == false){
                Find.clear();
            }
            Mat frame;
            data[csmIdx % BUFFER_SIZE].img.copyTo(frame);
            int frame_num = data[csmIdx % BUFFER_SIZE].frame;
            ++csmIdx;
            if(frame.empty()){
                continue;
            }
            Point2f Pt = Point2f(0,0);
            int status = 0;
            Find.detect(frame,mode,Pt,status);
            if(status == 0){
                memset(&Vision,0,sizeof(VisionData));
            }else if(status == 1){
                Vision = {Pt.x,Pt.y,0,0,0,1,0};
            }else if(status == 2){
                Vision = {Pt.x,Pt.y,0,0,0,2,0};
            }
            _port.TransformData(Vision);
            _port.send();
            Rune_flag = true;
//            imshow("frame",frame);
            waitKey(1);
//            cout << "time:" << time.elapsed() << endl;
        }
    }

#ifdef CAP_VIDEO
}
#endif

}
