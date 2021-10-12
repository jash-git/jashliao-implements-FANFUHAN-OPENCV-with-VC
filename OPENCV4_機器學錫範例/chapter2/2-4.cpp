#include "stdafx.h"
#include "opencv.hpp"
using namespace cv;
using namespace std;
void drawHist(string windowName, cv::Mat &srcImg)
{
    //需要计算图像的哪个通道（RGB空间需要确定计算R空间、G空间或B空间）
    const int channels[1] = { 0 };
    //直方图的bin数目
    int histSize[] = { 256 };
    //单个维度直方图数值的取值范围    
    float singleRanges[] = { 0, 256 };
    //确定每个维度的取值范围，即横坐标的总数    
    const float *ranges[] = { singleRanges };
    //输出的直方图，采用MatND类型
    MatND dstHist;
    cv::calcHist(&srcImg, 1, channels, cv::Mat(), dstHist, 1, histSize, ranges, true, false);
    //创建一个白底的图像    
    Mat drawImage(Size(256, 256), CV_8UC3, Scalar::all(255));
    //先用cv::minMaxLoc函数计算得到直方图后的像素的最大个数
    double maxValue;
    cv::minMaxLoc(dstHist, 0, &maxValue, 0, 0);
    //遍历直方图得到的数据
    for (int i = 0; i < 256; i++) //从第0个bin到第256个bin
    {
        int value = cvRound(256 * 0.9 *(dstHist.at<float>(i) / maxValue));
        //第i个bin的高度
        cv::line(drawImage, Point(i, drawImage.rows - 1), Point(i, drawImage.rows - 1 - value), Scalar(255, 0, 0)); //绘制柱状图
    }
    cv::imshow(windowName, drawImage);
    cv::waitKey(500);
}

int main()
{
    cv::Mat srcImg1, srcImg2, srcImg3, dstImg1, dstImg2, dstImg3;
    srcImg1 = cv::imread("E:/images/book/ch2/remote1_1.png", 0);
    srcImg2 = cv::imread("E:/images/book/ch2/remote1_2.png", 0);
    srcImg3 = cv::imread("E:/images/book/ch2/remote1_3.png", 0);
    //直方图均衡化
    cv::equalizeHist(srcImg1, dstImg1);
    cv::equalizeHist(srcImg2, dstImg2);
    cv::equalizeHist(srcImg3, dstImg3);
    //保存均衡化的结果
    cv::imwrite("E:/images/book/ch2/dstImg1.png", dstImg1);
    cv::imwrite("E:/images/book/ch2/dstImg2.png", dstImg2);
    cv::imwrite("E:/images/book/ch2/dstImg3.png", dstImg3);
    //计算并显示直方图
    drawHist("直方图1",srcImg1);
    drawHist("直方图2", srcImg2);
    drawHist("直方图3", srcImg3);
    drawHist("直方图均衡化1", dstImg1);
    drawHist("直方图均衡化2", dstImg2);
    drawHist("直方图均衡化3", dstImg3);    
    //显示图像
    cv::imshow("image1", srcImg1);
    cv::imshow("image2", srcImg2);
    cv::imshow("image3", srcImg3);
    cv::imshow("equalize1", dstImg1);
    cv::imshow("equalize2", dstImg2);
    cv::imshow("equalize3", dstImg3);
    cv::waitKey();
    return 0;
}
