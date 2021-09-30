// VC_FANFUHAN_OPENCV017.cpp : 定義主控台應用程式的進入點。
//
/*
// Debug | x32
通用屬性
| C/C++
|	| 一般
|		| 其他 Include 目錄 -> C:\opencv\build\include
|
| 連結器
| 	|一一般
|		|  其他程式庫目錄 -> C:\opencv\build\x64\vc15\lib
|
| 	|一輸入
|		| 其他相依性 -> opencv_world411d.lib;%(AdditionalDependencies)

// Releas | x64
組態屬性
| C/C++
|	| 一般
|		| 其他 Include 目錄 -> C:\opencv\build\include
|
| 連結器
| 	|一般
|		| 其他程式庫目錄 -> C:\opencv\build\x64\vc15\lib
|
| 	|一輸入
|		| 其他相依性 -> opencv_world411.lib;%(AdditionalDependencies)

*/
#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void showHistogram(InputArray src, cv::String StrTitle);

void pause()
{
	printf("Press Enter key to continue...");
	fgetc(stdin);
}
int main()
{
	Mat src = imread("../../images/test.png");
	if (src.empty())
	{
		cout << "could not load image.." << endl;
		pause();
		return -1;
	}
	else
	{
		imshow("input", src);
		showHistogram(src,"Histogram");

		Mat src_gray;
		cvtColor(src, src_gray, COLOR_BGR2GRAY);
		imshow("input_gray", src_gray);
		showHistogram(src_gray,"Histogram_gray");

		waitKey(0);
	}

	return 0;
}
void showHistogram(InputArray src, cv::String StrTitle)
{
	bool blnGray = false;
	if (src.channels() == 1)
	{
		blnGray = true;
	}

	// 三通道/單通道 直方圖 紀錄陣列
	vector<Mat> bgr_plane;
	vector<Mat> gray_plane;

	// 定义参数变量
	const int channels[1] = { 0 };
	const int bins[1] = { 256 };
	float hranges[2] = { 0, 255 };
	const float *ranges[1] = { hranges };
	Mat b_hist, g_hist, r_hist,hist;
	// 计算三通道直方图
	if (blnGray)
	{
		split(src, gray_plane);
		calcHist(&gray_plane[0], 1, 0, Mat(), hist, 1, bins, ranges);
	}
	else
	{
		split(src, bgr_plane);
		calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);
		calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
		calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);
	}

	/*
	* 显示直方图
	*/
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]);
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
	// 归一化直方图数据
	if (blnGray)
	{
		normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1);
	}
	else
	{
		normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1);
		normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1);
		normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1);
	}

	// 绘制直方图曲线
	for (int i = 1; i < bins[0]; ++i)
	{
		if (blnGray)
		{
			line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
				Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))), Scalar(255, 255, 255),
				2, 8, 0);
		}
		else
		{
			line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
				Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0),
				2, 8, 0);
			line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
				Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0),
				2, 8, 0);
			line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
				Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255),
				2, 8, 0);
		}


	}
	imshow(StrTitle, histImage);
}
