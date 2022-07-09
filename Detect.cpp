//
// Created by zihan on 22-7-9.
//
#include "Detect.h"


Detect::Detect(Mat frame){
split(frame,RGBchannels);
};
Mat Detect::Blue_channel(){
return RGBchannels[0];
}