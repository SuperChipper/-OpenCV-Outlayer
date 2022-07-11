#include <iostream>
#include <opencv2/opencv.hpp>
#include "Detect.h"
#include <vector>
using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
    Mat img=imread("../1920.png");
    namedWindow("img",WINDOW_FREERATIO);
    namedWindow("con",WINDOW_FREERATIO);
    if(img.empty())
    {
        cout << "failed to open the image" << endl;
        return -1;
    }
    Detect image(img);//初始化，传入图像
    Mat channel1=image.Blue_channel();  Mat bin;
    vector<vector<Point>> contourR;vector<vector<Point>> contourB;vector<vector<Point>> contour;
    vector<Vec4i> hierarchy0;vector<Vec4i> hierarchy1;
    findContours(image.Binary_Blue(),contourB,hierarchy0,RETR_TREE,CHAIN_APPROX_SIMPLE);
    //Canny(channel1,edge,80,180);
    bin=image.Binary_Blue();
    //img=image.Diff();
    findContours(bin,contourR,hierarchy1,RETR_TREE,CHAIN_APPROX_SIMPLE);
    contour =contourR;
    vector <RotatedRect> rrect;
    for(auto &cont:contour){
        RotatedRect r=minAreaRect(cont);
        rrect.push_back(r);
        image.Draw_rect(r);
        Point2f points[4];r.points(points);
        //cout<<rrect[i].center<<"\t"<<points[0]<<endl;
    }
    for(auto &rec: rrect){
        cout<<rec.center<<endl;
    }
    //image.channels_Upd();
    //threshold(image.Red_channel(),bin,251,255,THRESH_BINARY);
    //findContours(bin,contourR,hierarchy1,RETR_TREE,CHAIN_APPROX_SIMPLE);
    //contour =image.CompareContour(contourB,contourR);
    //Detect result(img);
    //for(int i=0;i<contour.size();i++){
    //    rrect[i]=minAreaRect(contour[i]);
    //    result.Draw_rect(rrect[i]);
    //}

    //drawContours(img,contour,-1,Scalar(0,50,250),3);
    //for (auto i = hierarchy1.begin(); i != hierarchy1.end(); i++) {
    //    std::cout << *i << ' ';
    //}
    //for (auto i = contour.begin(); i != contour.end(); i++) {
    //    std::cout << *i << ' ';
    //}
    imshow("con",image.Red_channel());
    imshow("img",image.Get());
    //imwrite("../testpic.png",channel1);
    waitKey(0);
    destroyAllWindows();
    return 0;
}