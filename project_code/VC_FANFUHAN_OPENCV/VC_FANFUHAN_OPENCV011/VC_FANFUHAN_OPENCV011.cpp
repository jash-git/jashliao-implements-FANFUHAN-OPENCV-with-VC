// VC_FANFUHAN_OPENCV011.cpp : 定義主控台應用程式的進入點。
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

		Mat gray;
		cvtColor(src_bgr, gray, COLOR_BGR2GRAY);
		imshow("input_gray", gray);	

		// 计算灰度图像的最大最小值
		double minVal00, maxVal00;
		Point minLoc00, maxLoc00;//座標位置
		/*
		1  minMaxLoc尋找矩陣(一維陣列當作向量,用Mat定義) 中最小值和最大值的位置.
		2  參數若不需要,則置為NULL或者0,即可.
		3  minMaxLoc針對Mat和MatND的重載中 ,第5個參數是可選的(optional),不使用不傳遞即可.
		*/
		minMaxLoc(gray, &minVal00, &maxVal00, &minLoc00, &maxLoc00);//搜尋灰階影像中的最大與最小值
		cout << "paramenters of gray:" << endl;
		printf("min:%.2f, max:%.2f \n", minVal00, maxVal00);
		printf("min loc: (%d, %d) \n", minLoc00.x, minLoc00.y);
		printf("max loc: (%d, %d) \n\n", maxLoc00.x, maxLoc00.y);


		/*
		歸一化 normalize()

		NORM_MINMAX : 陣列的數值被平移或縮放到一個指定的範圍，線性歸一化，一般較常用。
		NORM_INF :  此型別的定義沒有查到，根據opencv 1的對應項，可能是歸一化陣列的C-範數(絕對值的最大值)
		NORM_L1 :  歸一化陣列的L1-範數(絕對值的和)
		NORM_L2 :  歸一化陣列的(歐幾里德)L2-範數
		PS.最常用的就是NORM_MINMAX归一化方法.

		歸一化就是要把需要處理的資料經過處理後（通過某種演算法）限制在你需要的一定範圍內。

		首先歸一化是為了後面資料處理的方便，其次是保證程式運行時收斂加快。

		歸一化的具體作用是歸納統一樣本的統計分佈性。歸一化在0-1之間是統計的概率分佈，歸一化在某個區間上是統計的座標分佈。

		歸一化有同一、統一和合一的意思。

		歸一化的目的，是使得沒有可比性的資料變得具有可比性，同時又保持相比較的兩個資料之間的相對關係，如大小關係；或是為了作圖，原來很難在一張圖上作出來，歸一化後就可以很方便的給出圖上的相對位置等。

		*/
		// 显示图像用uchar类型，计算时转为float类型
		gray.convertTo(gray, CV_32F);

		// NORM_MINMAX
		Mat dst = Mat::zeros(gray.size(), CV_32FC1);
		normalize(gray, dst, 1.0, 0, NORM_MINMAX);
		Mat res = dst * 255;
		res.convertTo(dst, CV_8UC1); // 显示图像用uchar类型
		imshow("NORM_MINMAX", dst);

		// 计算灰度图像的最大最小值
		double minVal01, maxVal01;
		Point minLoc01, maxLoc01;//座標位置
		/*
		1  minMaxLoc尋找矩陣(一維陣列當作向量,用Mat定義) 中最小值和最大值的位置.
		2  參數若不需要,則置為NULL或者0,即可.
		3  minMaxLoc針對Mat和MatND的重載中 ,第5個參數是可選的(optional),不使用不傳遞即可.
		*/
		minMaxLoc(dst, &minVal01, &maxVal01, &minLoc01, &maxLoc01);//搜尋灰階影像中的最大與最小值
		cout << "NORM_MINMAX:" << endl;
		printf("min:%.2f, max:%.2f \n", minVal01, maxVal01);
		printf("min loc: (%d, %d) \n", minLoc01.x, minLoc01.y);
		printf("max loc: (%d, %d) \n\n", maxLoc01.x, maxLoc01.y);

		// scale and shift by NORM_INF
		normalize(gray, dst, 1.0, 0, NORM_INF);
		res = dst * 255;
		res.convertTo(dst, CV_8UC1);
		imshow("NORM_INF", dst);

		// scale and shift by NORM_L1
		normalize(gray, dst, 1.0, 0, NORM_L1);
		res = dst * 10000000;
		res.convertTo(dst, CV_8UC1);
		imshow("NORM_L1", dst);

		// scale and shift by NORM_L2
		normalize(gray, dst, 1.0, 0, NORM_L2);
		res = dst * 10000;
		res.convertTo(dst, CV_8UC1);
		imshow("NORM_L2", dst);

		waitKey(0);
	}

	return 0;
}

