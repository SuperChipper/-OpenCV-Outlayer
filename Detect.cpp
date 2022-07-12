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
    threshold(Blue_channel(),Binary,230,255,THRESH_BINARY);
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
    threshold(0.2*Binary_Blue()+0.6*Binary_Green()+0.2*Binary_Red(),Binary,230,255,THRESH_BINARY);

    //morphologyEx(Binary,erodeBinary,MORPH_CLOSE,struct0,Point(-1,-1),1);
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
void Detector(Mat img){
    namedWindow("img", WINDOW_FREERATIO);
    namedWindow("bin", WINDOW_FREERATIO);
    Detect image(img);//初始化，传入图像
    Mat bin;
    //vector<vector<Point>> contourR;
    //vector<vector<Point>> contourB;
    vector<vector<Point>> contour;
    //vector<Vec4i> hierarchy0;
    vector<Vec4i> hierarchy1;
    bin = image.Diff();
    findContours(bin, contour, hierarchy1, RETR_TREE, CHAIN_APPROX_SIMPLE);
    vector<RotatedRect> rrect;
    Rrect rec(contour);
    rec.find(image);
    imshow("bin", bin);
    imshow("img", image.Get());
}
void Detect_target(string type,string path,int waitkey){
    Mat img;
    if(type=="video"){
        VideoCapture video(path);
        while(1){
            video>>img;
            if(img.empty()){
                break;
            }
            Detector(img);
            waitKey(waitkey);
        }
    }
    else if(type=="image"){
        img=imread(path);
        if (!img.empty()) {
            Detector(img);
            waitKey(waitkey);
        }

    }
    else
        cout<<"Error, invalid type, please insert \"video\" or \"image\"";
}
Rrect::Rrect(vector<vector<Point>> contour) {
    for (auto &cont: contour) {
        RotatedRect r = minAreaRect(cont);
        rrect.push_back(r);
    }
}

void Rrect::find(Detect image) {
    for (auto &rec: rrect) {
        if (((rec.angle > 55) && (rec.angle < 125)) || ((rec.angle > 235) && (rec.angle < 305))) {
            if ((rec.size.width / rec.size.height > 4) && (rec.size.width / rec.size.height < 15)) {
                for (auto &cri: criticalrect) {
                    Point2f ptr = cri.center;
                    if ((abs(ptr.x - rec.center.x) > 2 * rec.size.width) &&
                        (abs(ptr.x - rec.center.x) < 6 * rec.size.width) &&
                        ((ptr.y - rec.center.y == 0) || (abs(ptr.x - rec.center.x) / abs(ptr.y - rec.center.y) > 4))) {
                        if((rec.size.width>0.9*cri.size.width)&&(0.9*rec.size.width<cri.size.width))
                        {
                            line(image.Get(), ptr, rec.center, Scalar(100, 200, 255), 2, 8, 0);;
                            circle(image.Get(), (rec.center + ptr) / 2, 2, Scalar(255, 20, 255), 2, 8, 0);
                        }
                    }
                }
                criticalrect.push_back(rec);
                rec_points.push_back(rec.center);
                cout<<rec.size.width<<"\t"<<rec.size.height<<endl;
                image.Draw_rect(rec);
            }
        }
    }
}