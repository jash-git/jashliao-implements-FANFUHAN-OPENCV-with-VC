// VC_FANFUHAN_OPENCV014.cpp : 定義主控台應用程式的進入點。
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

		int h = src_bgr.rows;//取得圖像長寬尺寸
		int w = src_bgr.cols;
		float fx = 0.0, fy = 0.0;//建立起始點
		Mat dst = Mat::zeros(src_bgr.size(), src_bgr.type());//建立預設的空白畫布
		Size S00(w * 2, h * 2);//建立放大後尺寸
		Size S01(w * 0.5, h * 0.5);//建立縮小後尺寸

		resize(src_bgr, dst, S00, fx, fy, INTER_NEAREST);
		imshow("INTER_NEAREST", dst);

		resize(src_bgr, dst, S00, fx, fy, INTER_LINEAR);
		imshow("INTER_LINEAR", dst);

		resize(src_bgr, dst, S00, fx, fy, INTER_CUBIC);
		imshow("INTER_CUBIC", dst);

		resize(src_bgr, dst, S00, fx, fy, INTER_LANCZOS4);
		imshow("INTER_LANCZOS4", dst);

		resize(src_bgr, dst, S01, fx, fy, INTER_LINEAR);
		imshow("INTER_LINEAR01", dst);
		waitKey(0);

	}

	return 0;
}