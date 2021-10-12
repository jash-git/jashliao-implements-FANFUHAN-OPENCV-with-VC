#include "stdafx.h"
#include "opencv.hpp"

using namespace std;
using namespace cv;
int main()
{ 
    cv::Mat I;
    I = cv::Mat(300, 400, CV_8UC3,cv::Scalar(255,255,255)); //创建一个白色画布
    cv::Point2f center(200, 150);
    cv::Size2f size(180, 120); //size(width, height)
    float angle = 30.0;
    cv::RotatedRect rRect(center, size, angle);
    cout << "the center of rRect is: " << rRect.center << endl;
    cout << "the size of rRect is: " << rRect.size << endl;
    cout << "the angle of rRect is: " << rRect.angle << endl;
    cv::Point2f vertices[4];
    rRect.points(vertices); //获取4个角点
    for (int i = 0; i < 4; i++) //逐条边绘制旋转矩形
        line(I, vertices[i], vertices[(i + 1) % 4], Scalar(255, 0, 0),2);
    cv::circle(I,center,2,cv::Scalar(0,0,0),2); //中点center
    cv::Rect boundingRect = rRect.boundingRect(); //外接矩形
    cv::rectangle(I, boundingRect, Scalar(0, 0, 255),1);
    cv::imshow("rotated rectangle", I);
    waitKey(0);
    return 0;
}
