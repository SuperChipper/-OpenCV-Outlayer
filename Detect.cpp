//
// Created by zihan on 22-7-9.
//
#include "Detect.h"


Detect::Detect(Mat frame){

const Mat struct0= getStructuringElement(0,Size(3,3));
image=frame;
split(image,RGBchannels);
    split(image,RGBchannels);
};
Mat Detect::Get() {
    return image;
}
//Mat Detect::channels_Upd(){
//    split(Detect::Get(),RGBchannels);
//}
Mat Detect::Blue_channel(){
    //split(image,RGBchannels);
    return RGBchannels[0];
}
Mat Detect::Red_channel(){
    //split(image,RGBchannels);
    return RGBchannels[2];
}
Mat Detect::Green_channel(){
    //split(image,RGBchannels);
    return RGBchannels[1];
}
Mat Detect::Binary_Blue(){
    threshold(Blue_channel(),Binary,200,255,THRESH_BINARY);
    morphologyEx(Binary,erodeBinary,MORPH_CLOSE,struct0,Point(-1,-1),1);
    return Binary;
}
Mat Detect::Binary_Red(){
    threshold(Red_channel(),Binary,125,255,THRESH_BINARY);
    morphologyEx(Binary,erodeBinary,MORPH_CLOSE,struct0,Point(-1,-1),2);
    return erodeBinary;
}
Mat Detect::Binary_Green() {
    threshold(Green_channel(),Binary,125,255,THRESH_BINARY);
    return Binary;
}
Mat Detect::Diff(){
    threshold(0.6*Binary_Blue()+0.4*Binary_Green()-Binary_Red(),Binary,160,255,THRESH_BINARY);

    morphologyEx(Binary,erodeBinary,MORPH_CLOSE,struct0,Point(-1,-1),2);
    return erodeBinary;
};
vector<vector<Point>> Detect::CompareContour(vector<vector<Point>> contourR,vector<vector<Point>>contourB) {//预期返回一个向量包含比较后相似的轮廓
    vector<vector<Point>> contour;
    for (int n=0;n<contourR.size();n++){
        Moments mm= moments(contourR[n]);
        Mat hum;
        HuMoments(mm,hum);
        double dist;
        for (int i=0;i<contourB.size();i++){
            Moments mm2=moments(contourB[i]);
            Mat hu2;
            HuMoments(mm2,hu2);
            dist = matchShapes(hum,hu2,CONTOURS_MATCH_I1,0);
            if(dist<1){
                //drawContours(img,contourR,n,Scalar(0,0,255),3,8);
                contour.push_back(contourB[i]);//末尾添加轮廓
            }
        }
    }
    return contour;
}
void Detect::Draw_rect(RotatedRect rrect) {
    Mat img=image;
    Point2f points[4];
    rrect.points(points);
    Point2f cent=rrect.center;
    for(int i=0;i<4;i++){
        if(i==3)
        {
            line(img,points[i],points[0],Scalar(0,0,255),2,8,0);
            break;
        }
        line(img,points[i],points[i+1],Scalar(0,0,255),2,8,0);

    }
    circle(img,cent,2,Scalar(200,150,0),2,8,0);
}