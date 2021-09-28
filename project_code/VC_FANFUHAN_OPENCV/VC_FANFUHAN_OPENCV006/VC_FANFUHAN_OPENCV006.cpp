// VC_FANFUHAN_OPENCV006.cpp : 定義主控台應用程式的進入點。
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

void pause()
{
	printf("Press Enter key to continue...");
	fgetc(stdin);
}

// 自定义LUT ~ 灰階轉二值化
Mat &myColorMap(Mat &image);

/*
*  Look Up Table(LUT)查找表的使用
*/
int main()
{
	Mat src = imread("../../images/LinuxLogo.jpg");//IDE 測試路徑 
	//Mat image = imread("../../../images/l_hires.jpg", IMREAD_GRAYSCALE);//執行檔 測試路徑

	if (src.empty()) {
		cout << "could not load image..." << endl;
		pause();
		return -1;
	}
	else
	{
		imshow("input_LinuxLogo", src);

		// 使用LUT
		Mat dst;
		/*
		//僞色彩
		COLORMAP_AUTUMN = 0,
		COLORMAP_BONE = 1,
		COLORMAP_JET = 2,
		COLORMAP_WINTER = 3,
		COLORMAP_RAINBOW = 4,
		COLORMAP_OCEAN = 5,
		COLORMAP_SUMMER = 6,
		COLORMAP_SPRING = 7,
		COLORMAP_COOL = 8,
		COLORMAP_HSV = 9,
		COLORMAP_PINK = 10,
		COLORMAP_HOT = 11
		*/
		applyColorMap(src, dst, COLORMAP_AUTUMN);
		imshow("colorMap-COLORMAP_AUTUMN", dst);//秋天

		applyColorMap(src, dst, COLORMAP_BONE);
		imshow("colorMap-COLORMAP_BONE", dst);//骨

		applyColorMap(src, dst, COLORMAP_JET);
		imshow("colorMap-COLORMAP_JET", dst);//噴射

		applyColorMap(src, dst, COLORMAP_WINTER);
		imshow("colorMap-COLORMAP_WINTER", dst);//冬天

		applyColorMap(src, dst, COLORMAP_RAINBOW);
		imshow("colorMap-COLORMAP_RAINBOW", dst);//彩虹

		applyColorMap(src, dst, COLORMAP_OCEAN);
		imshow("colorMap-COLORMAP_OCEAN", dst);//海洋

		applyColorMap(src, dst, COLORMAP_SUMMER);
		imshow("colorMap-COLORMAP_SUMMER", dst);//夏天

		applyColorMap(src, dst, COLORMAP_SPRING);
		imshow("colorMap-COLORMAP_SPRING", dst);//春天

		applyColorMap(src, dst, COLORMAP_COOL);
		imshow("colorMap-COLORMAP_COOL", dst);//涼爽

		applyColorMap(src, dst, COLORMAP_HSV);
		imshow("colorMap-COLORMAP_HSV", dst);//HSV

		applyColorMap(src, dst, COLORMAP_PINK);
		imshow("colorMap-COLORMAP_PINK", dst);//粉色

		applyColorMap(src, dst, COLORMAP_HOT);
		imshow("colorMap-COLORMAP_HOT", dst);//熱

		// 使用自己的LUT
		Mat my_dst, gray;
		cvtColor(src, gray, COLOR_BGR2GRAY);
		my_dst = myColorMap(gray);
		imshow("my_dst", my_dst);

		waitKey(0);
	}

	return 0;
}
// 自定义LUT ~ 灰階轉二值化
Mat &myColorMap(Mat &image) {
	int lut[256];
	for (int i = 0; i < 256; ++i) {
		if (i < 127)
			lut[i] = 0;
		else
			lut[i] = 255;
	}

	for (int row = 0; row < image.rows; ++row) {
		for (int col = 0; col < image.cols; ++col) {
			int pv = image.at<uchar>(row, col);
			image.at<uchar>(row, col) = lut[pv];
		}
	}

	return image;
}
