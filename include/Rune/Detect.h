#ifndef DETECT_H
#define DETECT_H
#include "header.h"

#define NO_TARGET -1
#define MAX_NUM 921600

//#define GET_ROI

class Detect{
    enum binaryMode{
        BGR = 1,
        HSV = 2,
        BGR_useG = 3,
        OTSU = 4,
        GRAY = 5,
        YCrCb = 6,
        LUV = 7,
    };

    enum predictMode{
        FIT_CIRCLE = 1,
        PUSH_CIRCLE = 2,
        TANGENT = 3
    };

    struct armorData{
        Point2f armorCenter;
        Point2f R_center;
        float angle;
        int quadrant;
        bool isFind;
        armorData(){
            armorCenter = Point2f(0,0);
            R_center = Point2f(0,0);
            angle = 0;
            quadrant = 0;
            isFind = 0;// 0: 未识别，1: 全部识别到
        }
    };

    struct switchParam{
        bool debug;
        bool use_yolo;
        bool use_lenet;
        switchParam(){
            debug = 1;
            use_yolo = 0;
            use_lenet = 0;
        }
    };

    struct DectParam{
        int bMode;
        int pMode;
        Mat element;
        int radius;
        float noise_point_area;
        int flabellum_area_min;
        float flabellum_whrio_min;
        float flabellum_whrio_max;
        float armor_whrio_min;
        float armor_whrio_max;
        float armor_rev_thres;
        int armor_area_min;
        int cutLimitedTime;
        float preAngle;
        DectParam(){
            // radius
            radius = 148;
            // mode
            bMode = GRAY;
            pMode = TANGENT;
            // getArmorCenter
            element = getStructuringElement(MORPH_RECT,Size(7,7));
            noise_point_area = 200;
            flabellum_area_min = 2000;// standard:7000
            flabellum_whrio_min = 1.5;
            flabellum_whrio_max = 2.7;//standard:2
            armor_whrio_min = 1.5;
            armor_whrio_max = 2.7;// standard:2
            armor_rev_thres = 0.3;// standard: 0.0x
            armor_area_min = 300;
            // cutLimit
            cutLimitedTime = 40;// 400ms
            // predict
            preAngle = CV_PI/7.8;
        }
    };
private:
    // param
    DectParam param;
    switchParam sParam;

    // init
    int mode;
    Mat debug_src;
    armorData lastData;
    armorData lostData;
    uint frame_cnt = 0;
    bool dirFlag;

    // deep learning
    dnn::Net yolo_lite;
    dnn::Net lenet;

private:
    float distance(const Point2f pt1,const Point2f pt2){
        return sqrt((pt1.x - pt2.x)*(pt1.x - pt2.x)+(pt1.y - pt2.y)*(pt1.y - pt2.y));
    }
    bool makeRectSafe(const Rect rect,const Size size);
    bool circleLeastFit(const vector<Point2f> &points,Point2f &R_center);
    bool change_angle(const int quadrant,const float angle,float &tran_angle);
public:
    Detect();
    void clear();
    bool forward(const Mat src,Mat &dect_src,Point2f &offset);
    bool setImage(const Mat src,Mat &dect_src,Point2f &offset);
    bool setBinary(const Mat src,Mat &binary,int bMode);
    bool getArmorCenter(const Mat src,const int bMode,armorData &data,Point2f offset = Point2f (0,0));
    bool getDirection();
    void isCut(const armorData new_data,int &status);
    bool predict(const armorData data,Point2f& preCenter,int pMode);
    void detect(const Mat frame,int Mode,Point2f& pt,int& status);
};
#endif // DETECT_H