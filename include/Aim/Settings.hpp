/*******************************************************************************************************************
Copyright 2017 Dajiang Innovations Technology Co., Ltd (DJI)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files(the "Software"), to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software, and
to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of
the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
*******************************************************************************************************************/

#pragma once
#include "opencv2/core/core.hpp"
#include <string>
#include "include/Aim/ArmorDetector.hpp"
#include "include/SerialPort/serialport.h"

using namespace cv;

#define ARMOR_MODE 0


class Settings {
public:

    Settings(const std::string & filename){

        FileStorage setting_fs(filename, FileStorage::READ);
        read(setting_fs);
//        FileStorage xx("/home/s305-nuc2/kevin/intergrated/param_config.yml", FileStorage::WRITE);
//        write(xx);
        setting_fs.release();
//        xx.release();
    }

    void read(const FileStorage& fs)  {
        // for debug image
        fs["show_image"] >> show_image;
        fs["save_result"] >> save_result;

        // for armor system
//      fs["min_light_gray"] >> armor.min_light_gray;
        fs["min_light_height"] >> armor.min_light_height;
//      fs["avg_contrast_threshold"] >> armor.avg_contrast_threshold;
        fs["light_slope_offset"] >> armor.light_slope_offset;
        fs["max_light_delta_h"] >> armor.max_light_delta_h;
        fs["min_light_delta_h"] >> armor.min_light_delta_h;
        fs["max_light_delta_v"] >> armor.max_light_delta_v;
        fs["max_light_delta_angle"] >> armor.max_light_delta_angle;
        fs["intrinsic_file_720"] >> intrinsic_file_720;
        fs["exposure_time"] >> exposure_time;
        fs["saturation_blue"] >> saturation_blue;
        fs["saturation_red"] >> saturation_red;
        fs["near_face_v"] >> armor.near_face_v;
        fs["max_lr_rate"] >> armor.max_lr_rate;
        fs["max_wh_ratio"] >> armor.max_wh_ratio;
        fs["min_wh_ratio"] >> armor.min_wh_ratio;
        fs["small_armor_wh_threshold"] >> armor.small_armor_wh_threshold;
        fs["binary_classfication_threshold"] >> armor.bin_cls_thres;
        fs["target_max_angle"] >> armor.target_max_angle;
    }

    void write(FileStorage& fs) const{
        // for debug image
        cvWriteComment(*fs, "\nFor Debug Image", 0);
        fs << "show_image" << show_image;
        fs << "save_result" << save_result;

        // for armor system
        cvWriteComment(*fs, "\nParameter for Armor Detection System", 0);
        fs  <<  "min_light_height" << armor.min_light_height
            << "light_slope_offset" << armor.light_slope_offset
            << "max_light_delta_h" << armor.max_light_delta_h
            << "min_light_delta_h" << armor.min_light_delta_h
            << "max_light_delta_v" << armor.max_light_delta_v
            << "max_light_delta_angle" << armor.max_light_delta_angle
            << "near_face_v" << armor.near_face_v
            << "saturation_blue" << saturation_blue
            << "saturation_red" << saturation_red;

        // for camerar
        cvWriteComment(*fs, "\nParameter for Camera", 0);
        fs << "intrinsic_file_720" << intrinsic_file_720;
        fs << "exposure_time" << exposure_time;


    }

public:
    int show_image;
    int save_result;
    ArmorParam armor;
    std::string intrinsic_file_720;
    int exposure_time;
    int saturation_blue;
    int saturation_red;

};
