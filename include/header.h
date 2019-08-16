#ifndef HEADER_H
#define HEADER_H
#include <opencv2/core/core.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/video/tracking.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <string.h>
#include <QTime>
#include <QDebug>

using namespace std;
using namespace cv;

enum detectMode{
    RED_ANCLOCK = 3,
    BLUE_ANCLOCK = 4,
    RED_CLOCK = 5,
    BLUE_CLOCK = 6,
    RED_STATIC = 7,
    BLUE_STATIC = 8
};


const string camera_yaml = "/home/nuc/kevin/RP_Infantry_Plus/extraFile/Rune/xml/Mono_out.xml";
const string yolo_model_file = "/home/nuc/kevin/RP_Infantry_Plus/extraFile/Rune/yolo/单通道/tiny-yolov2-trial3-noBatch_80000.weights";
const string yolo_txt_file = "/home/nuc/kevin/RP_Infantry_Plus/extraFile/Rune/yolo/单通道/tiny-yolov2-trial3-noBatch.cfg";
const string lenet_model_file = "/home/nuc/kevin/RP_Infantry_Plus/extraFile/Rune/lenet/lenet_iter_80000加了负样本.caffemodel";
const string lenet_txt_file = "/home/nuc/kevin/RP_Infantry_Plus/extraFile/Rune/lenet/deploy.prototxt";
#endif // HEADER_H
