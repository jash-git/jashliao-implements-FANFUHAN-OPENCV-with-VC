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
	Mat image = imread("../../images/l_hires.jpg", IMREAD_GRAYSCALE);//IDE 測試路徑
	//Mat image = imread("../../../images/l_hires.jpg", IMREAD_GRAYSCALE);//執行檔 測試路徑

	if (image.empty()) {
		cout << "could not load image..." << endl;
		pause();
		return -1;
	}
	else
	{
		namedWindow("input", WINDOW_AUTOSIZE);
		imshow("input", image);
		imwrite("output.jpg", image);
		waitKey(0);
	}
	
    return 0;
}

