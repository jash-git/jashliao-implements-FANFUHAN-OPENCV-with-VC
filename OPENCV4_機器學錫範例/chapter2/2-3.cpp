#include "stdafx.h"
#include "opencv.hpp"

using namespace cv;
using namespace std;
int main()
{    
    cv::Mat image = cv::imread("e:/images/cheeseGrid4x4.jpg", 0); 
    //读取原始图像
    //1.尺度变换
    cv::Mat resize_image, resize_image_M;
    cv::resize(image, resize_image,cv::Size(0,0),0.5, 0.5, 1);
    cv::Mat warp_matrix_resize; //声明尺度变换 M 矩阵
    warp_matrix_resize = cv::Mat::zeros(2, 3, CV_32F);
    float cx = 0.75, cy = 0.5;  //设置尺度变换 M 矩阵
    warp_matrix_resize.at<float>(0, 0) = cx;
    warp_matrix_resize.at<float>(1, 1) = cy;
    cv::Size dsize = image.size();
    dsize.width *= cx;
    dsize.height *= cy;
    cout << "M resize = " << endl << warp_matrix_resize << endl << endl;
    warpAffine(image, resize_image_M, warp_matrix_resize, dsize, INTER_LINEAR,1);
    cv::imshow("original", image);      
    cv::imshow("resize", resize_image);      
    cv::imshow("M resize", resize_image_M); 

    //2.平移变换
    cv::Mat temp_image = resize_image.clone(); //使用缩小后的图像进行变换
    cv::Mat translation_image; //声明目标图像变量
    cv::Mat warp_matrix_translation;  //声明平移变换 M 矩阵
    warp_matrix_translation = cv::Mat::eye(2, 3, CV_32F);
    float tx = 40, ty = 20; //设置平移变换参数
    warp_matrix_translation.at<float>(0, 2) = tx;
    warp_matrix_translation.at<float>(1, 2) = ty;
    cout << "M translation = " << endl << warp_matrix_translation << endl << endl;
    int top = 0, bottom = ty, left = 0, right = tx; 
    cv::copyMakeBorder(temp_image, temp_image, top, bottom, left, right, BORDER_CONSTANT, cv::Scalar(200));//扩边
    cv::warpAffine(temp_image, translation_image, warp_matrix_translation, temp_image.size(),INTER_LINEAR, BORDER_TRANSPARENT);
    cv::imshow("translation", translation_image);  

    //3.旋转变换
    cv::Mat rotate_image; //声明目标图像变量
    temp_image = resize_image.clone(); 
    double angle = 45;    //设定旋转角度    
    int border = 0.207 * temp_image.cols;
    cv::copyMakeBorder(temp_image, temp_image, border, border, border, border, BORDER_CONSTANT, cv::Scalar(200));//扩边
    cv::Point2f center(temp_image.cols / 2., temp_image.rows / 2.);
    //指定旋转中心
    cv::Mat warp_rotate_matrix = cv::getRotationMatrix2D(center, angle, 1.0);
    //获取旋转变换M矩阵
    //根据旋转矩阵进行仿射变换
    cv::warpAffine(temp_image, rotate_image, warp_rotate_matrix, temp_image.size(), INTER_LINEAR, BORDER_REPLICATE);
cout << "M rotate = " << endl << warp_rotate_matrix << endl << endl;
    cv::imshow("rotate", rotate_image);  //显示图像

    //4.剪切变换
    cv::Mat shear_vertical_image, shear_horizontal_image;  
    //声明目标图像变量
    temp_image = resize_image.clone();
    cv::Mat temp_image_vertical, temp_image_horizontal; 
    border = 40;
    cv::copyMakeBorder(temp_image, temp_image_vertical, 10, 2 * border, border, 10 + border, BORDER_CONSTANT, cv::Scalar(200));
    cv::copyMakeBorder(temp_image, temp_image_horizontal, border + 10, border, 10, 2 * border, BORDER_CONSTANT, cv::Scalar(200));
    cv::Mat warp_matrix_shear_vertical, warp_matrix_shear_horizontal;
    //声明剪切变换 M 矩阵
    warp_matrix_shear_vertical = cv::Mat::eye(2, 3, CV_32F);   
    //垂直剪切变换矩阵
    warp_matrix_shear_horizontal = cv::Mat::eye(2, 3, CV_32F); 
    //水平剪切变换矩阵
    float sv = 0.3, sh = 0.3;    
    warp_matrix_shear_horizontal.at<float>(0, 1) = sh;//水平偏移矩阵
    warp_matrix_shear_vertical.at<float>(1, 0) = sv;  //垂直偏移矩阵
    cout << "M shear vertical = " << endl << warp_matrix_shear_vertical << endl << endl;
    cout << "M shear horizontal = " << endl << warp_matrix_shear_horizontal << endl << endl;
    //根据旋转矩阵进行仿射变换
    cv::warpAffine(temp_image_vertical, shear_vertical_image, warp_matrix_shear_vertical, temp_image_vertical.size(), INTER_LINEAR, BORDER_REPLICATE);
    cv::warpAffine(temp_image_horizontal, shear_horizontal_image, warp_matrix_shear_horizontal, temp_image_horizontal.size(), INTER_LINEAR, BORDER_REPLICATE);
    cv::imshow("shear vertical", shear_vertical_image);    //显示图像
    cv::imshow("shear horizontal", shear_horizontal_image);    
    cv::waitKey();
    return 0;
}
