// VC_FANFUHAN_OPENCV013.cpp : 定義主控台應用程式的進入點。
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
	Mat src_bgr = imread("../../images/test.png");

	if (src_bgr.empty())
	{
		cout << "could not load image.." << endl;
		pause();
		return -1;
	}
	else
	{
		imshow("input_bgr", src_bgr);
		Mat dst;
		/*
		flipCode	Anno
		1			水平翻转
		0			垂直翻转
		-1			水平垂直翻转
		*/
		// X轴 倒影
		flip(src_bgr, dst, 0);
		imshow("x_flip", dst);

		// Y轴 镜像
		flip(src_bgr, dst, 1);
		imshow("y_flip", dst);

		// XY轴 对角
		flip(src_bgr, dst, -1);
		imshow("xy_flip", dst);

		waitKey(0);
	}

	return 0;
}