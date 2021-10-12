#include "stdafx.h"
#include "opencv.hpp"

using namespace cv;
using namespace std;
int main() 
{
    cv::Mat I,B,temp;
    I = cv::Mat::zeros(300, 400, CV_8UC3); //创建一个黑色的画布
    B = I.clone(); //背景
    cv::Rect r1 = cv::Rect(60,60,200,100);
    cv::Rect r2 = cv::Rect(cv::Point(140, 120), cv::Size(200, 100));
    cv::rectangle(I ,r1, cv::Scalar(0, 255, 0), 2);
    cv::rectangle(I, r2, cv::Scalar(0, 0, 255), 2);
    cv::imshow("rectangle", I);
    cv::waitKey();
    //交集
    temp = I.clone();
    cv::Rect r3 = r1 & r2;
    cv::rectangle(temp, r3, cv::Scalar(255, 0, 0), 2);
    cv::imshow("Intersection", temp);
    cv::waitKey();
    //包含矩形r1和r2的最小矩形
    temp = I.clone();
    cv::Rect r4 = r1 | r2;
    cv::rectangle(temp, r4, cv::Scalar(255, 0, 0), 2);
    cv::imshow("Minimum area rectangle contain r1, r2", temp);
    cv::waitKey();
    //改变矩形大小
    temp = B.clone();
    cv::Rect rs(r1);
    rs += Size(-30, 60);
    cv::rectangle(temp, r1, cv::Scalar(0, 255, 0), 2);
    cv::rectangle(temp, rs, cv::Scalar(255, 0, 0), 2);
    cv::imshow("Enlarge", temp);
    //平移矩形
    temp = B.clone();
    cv::Rect rt(r1);
    rt += Point(30, 60); 
    cv::rectangle(temp, r1, cv::Scalar(0, 255, 0), 2);    
    cv::rectangle(temp, rt, cv::Scalar(255, 0, 0), 2);
    cv::imshow("Translate", temp);
    cv::waitKey();

    cv::Point p(80, 80);
    cv::Point q(20, 20);
    cout << "rectangle r1: " << r1 << endl;
    cout << "rectangle r2: " << r2 << endl;
    cout << "Is r1 and r2 the same rectangle: " << (r1 == r2) << endl;
    cout << "Is r1 and r2 not the same rectangle: " << (r1 != r2) << endl;
    cout << "Is r1 contains point p(80, 80): " << r1.contains(p) << endl;
    cout << "Is r1 contains point q(20, 20): " << r1.contains(q) << endl;
    system("PAUSE");
    return 0;
}
