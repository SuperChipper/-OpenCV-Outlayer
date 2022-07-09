#include <iostream>
#include <opencv2/opencv.hpp>
#include "Detect.h"
using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
    Mat img=imread("../1920.png");
    namedWindow("img",WINDOW_FREERATIO);
    namedWindow("CHAN",WINDOW_FREERATIO);
    if(img.empty())
    {
        cout << "failed to open the image" << endl;
        return -1;
    }
    Detect image(img);
    Mat channels[3];
    split(img,channels);
    Mat channel1=image.Blue_channel();
    Mat edge;
    Mat bin;
    Canny(channel1,edge,80,180);
    threshold(channel1,bin,125,255,THRESH_BINARY);
    imshow("CHAN",edge);
    imshow("img",bin);
    imwrite("../testpic.png",channel1);
    waitKey(0);
    destroyAllWindows();
 return 0;
}