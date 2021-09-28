// VC_FANFUHAN_OPENCV001.cpp : 定義主控台應用程式的進入點。
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
	// create image one, CV_8UC3创建三通道图像
	Mat src1 = Mat::zeros(Size(400, 400), CV_8UC3);
	Rect rect(100, 100, 100, 100);//定義一個矩形
	// Scalar() 参数为BGR三通道值，绿色和红色加起来是黄色
	src1(rect) = Scalar(0, 255, 255);//將矩形範圍填滿黃色
	imshow("input1", src1);

	// create image two
	Mat src2 = Mat::zeros(Size(400, 400), CV_8UC3);
	rect.x = 150;
	rect.y = 150;//移動矩形起始位置
	src2(rect) = Scalar(0, 0, 255);//將矩形範圍填滿紅色
	imshow("input2", src2);

	// 逻辑操作
	Mat dst1, dst2, dst3;
	bitwise_and(src1, src2, dst1);//進行AND運算
	bitwise_xor(src1, src2, dst2);//XOR運算
	bitwise_or(src1, src2, dst3);//OR運算
	imshow("and", dst1);
	imshow("xor", dst2);
	imshow("or", dst3);

	// 演示取反操作
	Mat src = imread("../../images/test1.jpg");
	Mat dst;
	if (src.empty()) {
		cout << "could not load image..." << endl;
		pause();
		return -1;
	}
	else
	{
		imshow("input", src);
		bitwise_not(src, dst);//NOT運算
		imshow("input_not", dst);
	}

	waitKey(0);
	return 0;
}

