// VC_FANFUHAN_OPENCV002.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
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
	Mat src = imread("../../images/l_hires.jpg");//IDE 測試路徑
	//Mat src = imread("../../../images/l_hires.jpg");//執行檔 測試路徑

	if (src.empty()) {
		cout << "could not load image..." << endl;
		pause();
		return -1;
	}
	else
	{
		namedWindow("input");
		imshow("input", src);

		Mat gray,hsv;
		/*
		COLOR_BGR2GRAY = 6 彩色轉灰階
		COLOR_GRAY2BGR = 8 灰度轉彩色彩色
		COLOR_BGR2HSV = 40 RGB轉HSV
		COLOR_HSV2BGR = 54 HSV轉RGB
		*/
		cvtColor(src, gray, COLOR_BGR2GRAY);
		cvtColor(src, hsv, COLOR_BGR2HSV);
		
		namedWindow("output gray");
		imshow("output gray", gray);
		
		namedWindow("output hsv");
		imshow("output hsv", hsv);

		imwrite("gray.jpg", gray);
		imwrite("hsv.jpg", hsv);

		waitKey(0);
	}

    return 0;
}

