// VC_FANFUHAN_OPENCV008.cpp : 定義主控台應用程式的進入點。
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
	Mat src = imread("../../images/baboon.jpg");
	if (src.empty()) {
		cout << "could not load image..." << endl;
		pause();
		return -1;
	}
	else
	{
		imshow("input", src);

		vector<Mat> mv; // mv用于存储图像分离后各通道像素
		Mat dst1, dst2, dst3;

		// 令蓝色通道为0
		split(src, mv);
		mv[0] = Scalar(0);
		merge(mv, dst1);
		imshow("blue == 0", dst1);

		// 令绿色通道为0
		split(src, mv);
		mv[1] = Scalar(0);
		merge(mv, dst2);
		imshow("green == 0", dst2);

		// 令红色通道为0
		split(src, mv);
		mv[2] = Scalar(0);
		merge(mv, dst3);
		imshow("red == 0", dst3);
		
		/*
		Mat dst4;
		subtract(src, dst3, dst4);//相減
		imshow("input - red", dst4);
		Mat dst5;
		bitwise_xor(src, dst3, dst5);//XOR運算
		imshow("input xor red", dst5);
		*/

		waitKey(0);
	}

    return 0;
}

