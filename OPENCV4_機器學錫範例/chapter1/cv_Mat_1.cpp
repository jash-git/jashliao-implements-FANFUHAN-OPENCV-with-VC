#include "stdafx.h"
#include "opencv.hpp"

using namespace std;
using namespace cv;
int main()    
{
    //非赋值构造
    cv::Mat a(cv::Size(4, 3), CV_8UC1,cv::Scalar(255)); //单通道
    cv::Mat b = cv::Mat(cv::Size(4, 3), CV_8UC3,cv::Scalar(0,1,2)); 
    //3通道，每个矩阵元素包含3个uchar值
    cout << "a = " << endl << a << endl << endl;
    cout << "b = " << endl << b << endl << endl;
    cv::Mat mz = cv::Mat::zeros(cv::Size(2, 2), CV_8UC1); //全0矩阵
    cv::Mat mo = cv::Mat::ones(cv::Size(2, 2), CV_8UC1);  //全1矩阵
    cv::Mat me = cv::Mat::eye(cv::Size(4, 3), CV_32FC1);  //对角线为1的矩阵
    cout << "mz = " << endl << mz << endl << endl;
    cout << "mo = " << endl << mo << endl << endl;
    cout << "me = " << endl << me << endl << endl;
    system("pause");

    //通过拷贝赋值
    cv::Mat image = cv::imread("E:/images/Lena.jpg",1);
    cv::Rect roi(cv::Point(80, 80), cv::Size(120,160));
    cv::Mat mat_roi(image, roi);
    cv::Mat mat_range(image, cv::Range(80, 80+160), cv::Range(80, 80+120));
    cv::imshow("image",image);
    cv::imshow("roi", mat_roi);
    cv::imshow("range", mat_range);
    cv::waitKey();
    return 0;
｝
