#ifndef SEPARATE_H
#define SEPARATE_H

#include <opencv2/core/core.hpp>
using namespace cv;

class Separate{
public:
    void screen(Mat & src, RotatedRect &rect);
private:
    RotatedRect adjustRRect(const RotatedRect & rect){
        const Size2f & s = rect.size;
        if(s.width < s.height)
            return rect;
        return RotatedRect(rect.center, Size2f(s.height, s.width), float(double(rect.angle)+90.0));     // 两个强制转换类型只是为了消除警告
    }
    bool makeRectSafe(Rect& rect, Size size){
        // 确保圈定灯条位置在图像内
        if(rect.x < 0)
            rect.x = 0;
        if(rect.x + rect.width > size.width)
            rect.width = size.width - rect.x;
        if(rect.y < 0)
            rect.y = 0;
        if(rect.y + rect.height > size.height)
            rect.height = size.height - rect.y;
        if(rect.width <= 0 || rect.height <= 0)
            return false;
        return true;
    }
    bool save_target(Mat &dst);
    bool save_noise(Mat &dst);
    Mat roi;
    Mat noise;
    Rect roi_rect;
    Rect noise_rect;
};

#endif // SEPARATE_H
