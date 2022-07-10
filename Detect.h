//
// Created by zihan on 22-7-9.
//

#ifndef VIDEO_TEST_CPP_DETECT_H
#define VIDEO_TEST_CPP_DETECT_H
#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;
using namespace cv;
class Detect{
private:
    Mat RGBchannels[3];
    Mat Binary;
    Mat struct0;
    Mat erodeBinary;
    Mat image;

public:
    Detect(Mat frame);
    Mat Get();
    //Mat channels_Upd();
    Mat Blue_channel();
    Mat Red_channel();
    Mat Green_channel();
    Mat Binary_Blue();
    Mat Binary_Red();
    Mat Binary_Green();
    Mat Diff();
    vector<vector<Point>> CompareContour(vector<vector<Point>>,vector<vector<Point>>);
    void Draw_rect(RotatedRect);
};

#endif //VIDEO_TEST_CPP_DETECT_H
