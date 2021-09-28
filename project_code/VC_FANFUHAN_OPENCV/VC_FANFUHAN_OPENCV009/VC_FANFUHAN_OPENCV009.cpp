// VC_FANFUHAN_OPENCV009.cpp : 定義主控台應用程式的進入點。
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
int main()
{
	Mat src = imread("../../images/test.png");
	/*
	* 提取图像前景和背景
	*/
	Mat src2 = imread("../../images/boy.jpg");
	if (src.empty() && src2.empty())
	{
		cout << "could not load image.." << endl;
		pause();
		return -1;
	}
	else
	{
		imshow("input", src);

		// RGB ==> HSV  YUV  YCrCb
		Mat hsv, yuv, ycrcb;
		cvtColor(src, hsv, COLOR_BGR2HSV);
		cvtColor(src, yuv, COLOR_BGR2YUV);
		cvtColor(src, ycrcb, COLOR_BGR2YCrCb);
		imshow("hsv", hsv);
		imshow("yuv", yuv);
		imshow("ycrcb", ycrcb);

		//---------------------//
		imshow("input boy", src2);
		cvtColor(src2, hsv, COLOR_BGR2HSV);

		
		Mat mask, mask_not;
		// 从HSV表中查到绿色的最低值和最高值，建立掩模
		inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);//符合規定為白色(255)，不符合範圍為黑色(0)		
		bitwise_not(mask, mask_not);
		imshow("mask", mask);//背景遮罩
		imshow("mask_not", mask_not);//前景遮罩

		Mat fg, bg;
		bitwise_and(src2, src2, bg, mask);// 提取背景		
		bitwise_and(src2, src2, fg, mask_not);// 提取前景
		imshow("background", bg);
		imshow("foreground", fg);

		waitKey(0);
	}

    return 0;
}

