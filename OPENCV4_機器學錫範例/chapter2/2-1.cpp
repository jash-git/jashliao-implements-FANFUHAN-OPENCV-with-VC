#include "stdafx.h"
#include "opencv.hpp" //OpenCV头文件

using namespace cv;
using namespace std;
int main()
{    
    cv::Mat img, imgGaussian;
    cout << "size of initail Mat: " << img.size() << endl;  //输出图像初始尺寸
    img = cv::imread("E:/images/cameraman.jpg", 1);    //读取图像    
    int width = img.cols;
    int height = img.rows;
    cout << "size of loaded image: " << img.size() << endl;  //输出图像尺寸
    cout << "width of loaded image: " << width << endl;    //输出图像宽
    cout << "height of loaded image: " << height << endl;   //输出图像高
    if (img.empty()) 
             return -1;
    cv::GaussianBlur(img, imgGaussian, cv::Size(5, 5), 0, 0); //高斯滤波    
    cv::imshow("Original", img); //显示图像
    cv::imshow("Gaussian", imgGaussian);
    cv::waitKey(0);//等待按键
    cv::imwrite("gaussian_filter.jpg", imgGaussian);
    return 0;
}
