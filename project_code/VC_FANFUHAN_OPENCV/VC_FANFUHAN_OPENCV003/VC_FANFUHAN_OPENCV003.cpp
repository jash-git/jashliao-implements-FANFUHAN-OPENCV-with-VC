// VC_FANFUHAN_OPENCV003.cpp : 定義主控台應用程式的進入點。
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
		// 通过克隆或复制创建图像对象，m1和src指向不同内存块
		Mat m1 = src.clone();
		Mat m2;
		src.copyTo(m2);

		// 赋值法，m3和src指向同一内存块
		Mat m3 = src;
		namedWindow("input");
		imshow("input", m3);

		// 创建空白图像
		Mat m4 = Mat::zeros(src.size(), src.type());
		Mat m5 = Mat::zeros(Size(512, 512), CV_8UC3);
		Mat m6 = Mat::ones(Size(512, 512), CV_8UC3);
		Mat m7 = Mat(Size(512, 512), CV_8UC3,Scalar(255,255,255));//白色畫布
		namedWindow("m4-input(zeros)");
		imshow("m4-input(zeros)", m4);
		namedWindow("m5-Size(512, 512)[zeros]");
		imshow("m5-Size(512, 512)[zeros]", m5);
		namedWindow("m6-Size(512, 512)[ones]");
		imshow("m6-Size(512, 512)[ones]", m6);
		namedWindow("m7-Size(512, 512)[Scalar(255,255,255)]");
		imshow("m7-Size(512, 512)[Scalar(255,255,255)]", m7);

		// kernel: [0, -1, 0
		//          -1, 5, -1
		//          0, -1, 0]
		Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

		waitKey(0);
	}

	return 0;
}

