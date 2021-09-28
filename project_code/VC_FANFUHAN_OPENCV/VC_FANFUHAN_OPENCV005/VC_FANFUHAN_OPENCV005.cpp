// VC_FANFUHAN_OPENCV005.cpp : 定義主控台應用程式的進入點。
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
	Mat src1 = imread("../../images/LinuxLogo.jpg");
	Mat src2 = imread("../../images/WindowsLogo.jpg");
	//Mat image = imread("../../../images/l_hires.jpg", IMREAD_GRAYSCALE);//執行檔 測試路徑

	if (src1.empty() || src2.empty()) {
		cout << "could not load image..." << endl;
		pause();
		return -1;
	}
	else
	{
		imshow("input1", src1);
		imshow("input2", src2);

		// 加法
		Mat add_result = Mat::zeros(src1.size(), src1.type());
		add(src1, src2, add_result);
		imshow("add_result", add_result);

		// 带权重的加法，一般推荐使用这个 浮水印 透明感
		Mat add_weight_result = Mat::zeros(src1.size(), src1.type());
		addWeighted(src1, 0.5, src2, (1.0 - 0.5), 0.0, add_weight_result);
		imshow("add_weight_result", add_weight_result);

		// 减法
		Mat sub_result = Mat::zeros(src1.size(), src1.type());
		subtract(src1, src2, sub_result);
		imshow("sub_result", sub_result);

		// 乘法
		Mat mul_result = Mat::zeros(src1.size(), src1.type());
		multiply(src1, src2, mul_result);
		imshow("mul_result", mul_result);

		// 除法
		Mat div_result = Mat::zeros(src1.size(), src1.type());
		divide(src1, src2, div_result);
		imshow("div_result", div_result);

		// 自己实现加法操作
		int b1 = 0, g1 = 0, r1 = 0;
		int b2 = 0, g2 = 0, r2 = 0;

		Mat my_add_result = Mat::zeros(src1.size(), src1.type());
		for (int row = 0; row < src1.rows; ++row) {
			for (int col = 0; col < src1.cols; ++col) {
				b1 = src1.at<Vec3b>(row, col)[0];
				g1 = src1.at<Vec3b>(row, col)[1];
				r1 = src1.at<Vec3b>(row, col)[2];

				b2 = src2.at<Vec3b>(row, col)[0];
				g2 = src2.at<Vec3b>(row, col)[1];
				r2 = src2.at<Vec3b>(row, col)[2];

				// b1:0~255,b2:0~255, b1+b2可能大于255，所以需要转换，通过saturate_cast<uchar>()
				my_add_result.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b1 + b2);
				my_add_result.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g1 + g2);
				my_add_result.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r1 + r2);
			}
		}

		imshow("my_add_result", my_add_result);

		imwrite("add_result.jpg", add_result);
		imwrite("add_weight_result.jpg", add_weight_result);
		imwrite("sub_result.jpg", sub_result);
		imwrite("div_result.jpg", div_result);

		waitKey(0);
	}

	return 0;
}

