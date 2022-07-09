//
// Created by zihan on 22-7-9.
//

#ifndef VIDEO_TEST_CPP_DETECT_H
#define VIDEO_TEST_CPP_DETECT_H
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
class Detect{
private:Mat RGBchannels[3];

public:
    Detect(Mat frame);
    Mat Blue_channel();

};

#endif //VIDEO_TEST_CPP_DETECT_H
