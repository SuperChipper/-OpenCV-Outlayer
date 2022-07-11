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
    findContours(bin,contourB,hierarchy1,RETR_TREE,CHAIN_APPROX_SIMPLE);
    contour =contourB;
    vector <RotatedRect> rrect;
    for(auto &cont:contour){
        RotatedRect r=minAreaRect(cont);
        rrect.push_back(r);

        Point2f points[4];r.points(points);
        //cout<<rrect[i].center<<"\t"<<points[0]<<endl;
    }
    vector <Point2f> rec_points;
    vector <RotatedRect> criticalrect;
    for(auto &rec: rrect){
        //cout<<rec.center<<endl;

        if(((rec.angle>55)&&(rec.angle<125))||((rec.angle>235)&&(rec.angle<305))) {
            if((rec.size.width/rec.size.height>4)&&(rec.size.width/rec.size.height<15)&&(rec.size.height>2)) {
                for(auto &ptr:rec_points){
                    if((abs(ptr.x-rec.center.x)>2*rec.size.width)&&(abs(ptr.x-rec.center.x)<6*rec.size.width)&&((ptr.y-rec.center.y==0)||(abs(ptr.x-rec.center.x)/abs(ptr.y-rec.center.y)>5))){
                        line(image.Get(),ptr,rec.center,Scalar(100,200,255),2,8,0);;
                        circle(image.Get(),(rec.center+ptr)/2,2,Scalar(255,20,255),2,8,0);
                    }
                }
                criticalrect.push_back(rec);
                rec_points.push_back(rec.center);
                image.Draw_rect(rec);
            }
        }
    }
    //Detect result(img);
    //for(int i=0;i<contour.size();i++){
    //    rrect[i]=minAreaRect(contour[i]);
    //    result.Draw_rect(rrect[i]);
    //}
    imshow("con",bin);
    imshow("img",image.Get());
    //imwrite("../testpic.png",channel1);
    waitKey(0);
    destroyAllWindows();
    return 0;
}