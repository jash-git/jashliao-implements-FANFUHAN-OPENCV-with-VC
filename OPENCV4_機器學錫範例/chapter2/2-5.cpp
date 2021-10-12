#include "stdafx.h"
#include "opencv.hpp"

using namespace cv;
int main()
{
    cv::Mat srcImg, dstImg;
    srcImg = cv::imread("E:/images/book/ch2/remote2.png", 1);
    
    //1st plane: rectangle
    int x = 90, y = 175, width = 90, height = 95;
    cv::Rect rect1(x, y, width, height);
    cv::rectangle(srcImg, rect1, cv::Scalar(0, 255, 0), 2);
    cv::putText(srcImg, "plane1", cv::Point(x,y-10), CV_FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 255, 255), 2, 3);
    
    //2nd plane: rectangle
    cv::Rect rect2 = rect1;
    rect2.x += 110;
    cv::rectangle(srcImg, rect2, cv::Scalar(0, 255, 0), 2);
    cv::putText(srcImg, "plane2", cv::Point(x+110, y - 10), CV_FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 255, 255), 2, 3);
    
    //3rd plane: rotate rectangle
    cv::Point2f center(420, 300);    
    cv::Size2f size(90, 95);    
    float angle = 6;
    cv::RotatedRect rRect(center, size, angle);
    Point2f vertices[4];
    rRect.points(vertices);
    for (int i = 0; i < 4; i++)
    line(srcImg, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2, CV_AA);
    cv::putText(srcImg, "plane3", cv::Point(360, 240), CV_FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 255, 255), 2, 3);
    cv::imshow("airport", srcImg);
    cv::waitKey();
    
    return 0;
}
