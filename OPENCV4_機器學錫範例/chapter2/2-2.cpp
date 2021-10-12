#include "stdafx.h"
#include "opencv.hpp"

using namespace std;
int main()
{    
    cv::Mat img_rgb, img_gray, img_hsv, img_gray2rgb, img_hsv2rgb;
    img_rgb = cv::imread("e:/images/baboon.png", 1);
    cv::cvtColor(img_rgb, img_hsv, CV_BGR2HSV); //颜色空间转换
    cv::cvtColor(img_hsv, img_hsv2rgb, CV_HSV2BGR);
    cv::cvtColor(img_rgb, img_gray, CV_BGR2GRAY);
    cv::cvtColor(img_gray, img_gray2rgb, CV_GRAY2BGR);
    cv::imshow("RGB", img_rgb);              //显示RGB图
    cv::imshow("RGB to HSV", img_hsv);       //显示RGB图转HSV图
    cv::imshow("HSV to RGB", img_hsv2rgb);   //显示HSV图转RGB图
    cv::imshow("RGB to GRAY", img_gray);     //显示RGB图转灰度图
    cv::imshow("GRAY to RGB", img_gray2rgb);  //显示灰度图转RGB图
    cout << "RGB  image 通道数: " << img_rgb.channels() << endl;
    cout << "HSV  image 通道数: " << img_hsv.channels() << endl;
    cout << "gray image 通道数: " << img_gray.channels() << endl;
    cv::waitKey(0);
    return 0;
}
