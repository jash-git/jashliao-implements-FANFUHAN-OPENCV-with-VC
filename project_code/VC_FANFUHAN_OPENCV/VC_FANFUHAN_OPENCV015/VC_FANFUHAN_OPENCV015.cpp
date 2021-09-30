// VC_FANFUHAN_OPENCV015.cpp : 定義主控台應用程式的進入點。
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

		Mat image = Mat::zeros(Size(512, 512), CV_8UC3);//建立彩色黑底畫布
		Rect rect(100, 100, 200, 200);//建立一個矩形
		// 绘制
		rectangle(image, rect, Scalar(255, 0, 0), 2, LINE_8, 0);//繪製未填滿顏色的藍色邊框矩形
		circle(image, Point(256, 256), 50, Scalar(0, 255, 0), 2, LINE_8, 0);//繪製未填滿顏色的綠色邊框圓形
		ellipse(image, Point(256, 256), Size(150, 50), 360, 0, 360, Scalar(0, 0, 255), 2, LINE_8, 0);//繪製未填滿顏色的紅色色邊框橢圓形
		imshow("image_draw", image);
		// 填充  thickness=-1 or FILLED
		rectangle(image, rect, Scalar(255, 0, 0), FILLED, LINE_8, 0);
		ellipse(image, Point(256, 256), Size(150, 50), 360, 0, 360, Scalar(0, 0, 255), FILLED, LINE_8, 0);
		circle(image, Point(256, 256), 50, Scalar(0, 255, 0), -1, LINE_8, 0);
		imshow("image_fill", image);

		// 随机数/亂數
		RNG rng(0xFFFFFF);
		image.setTo(Scalar(0, 0, 0));
		Mat image_copy = image.clone();
		for (int i = 0; i < 100000; ++i) {
			int x1 = rng.uniform(0, 512);
			int y1 = rng.uniform(0, 512);
			int x2 = rng.uniform(0, 512);
			int y2 = rng.uniform(0, 512);

			int b = rng.uniform(0, 256);
			int g = rng.uniform(0, 256);
			int r = rng.uniform(0, 256);

			rect.x = x1;
			rect.y = y1;
			rect.width = x2 - x1;
			rect.height = y2 - y1;
			// LINE_AA 反锯齿
			line(image, Point(x1, y1), Point(x2, y2), Scalar(b, g, r), 1, LINE_AA, 0);//畫彩色線段
			rectangle(image_copy, rect, Scalar(b, g, r), 1, LINE_AA, 0);
			imshow("image_line", image);
			imshow("image_rect", image_copy);
			char c = waitKey(20);
			if (c == 27)// ESC
			{
				break;
			}
		}

		waitKey(0);
	}

	return 0;
}