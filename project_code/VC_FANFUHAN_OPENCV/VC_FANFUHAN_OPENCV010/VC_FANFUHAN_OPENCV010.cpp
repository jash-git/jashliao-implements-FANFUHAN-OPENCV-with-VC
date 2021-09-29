// VC_FANFUHAN_OPENCV010.cpp : 定義主控台應用程式的進入點。
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
	Mat src_gray;

	cvtColor(src_bgr, src_gray, COLOR_BGR2GRAY);

	if (src_bgr.empty() || src_gray.empty())
	{
		cout << "could not load image.." << endl;
		pause();
		return -1;
	}
	else
	{
		imshow("input_bgr", src_bgr);
		imshow("input_gray", src_gray);

		// 计算灰度图像的最大最小值
		double minVal, maxVal;
		Point minLoc, maxLoc;//座標位置
		/*
		1  minMaxLoc尋找矩陣(一維陣列當作向量,用Mat定義) 中最小值和最大值的位置.
		2  參數若不需要,則置為NULL或者0,即可.
		3  minMaxLoc針對Mat和MatND的重載中 ,第5個參數是可選的(optional),不使用不傳遞即可.
		*/
		minMaxLoc(src_gray, &minVal, &maxVal, &minLoc, &maxLoc);//搜尋灰階影像中的最大與最小值
		cout << "paramenters of src_gray:" << endl;
		printf("min:%.2f, max:%.2f \n", minVal, maxVal);
		printf("min loc: (%d, %d) \n", minLoc.x, minLoc.y);
		printf("max loc: (%d, %d) \n", maxLoc.x, maxLoc.y);
		
		Mat mean_g, stddev_g;
		/*
		計算矩陣的均值和標準偏差。
		C++: void meanStdDev(InputArray src,OutputArray mean, OutputArray stddev, InputArray mask=noArray())
		C: void cvAvgSdv(constCvArr* arr, CvScalar* mean, CvScalar* std_dev, const CvArr* mask=NULL )
		Python: cv.AvgSdv(arr,mask=None) -> (mean, stdDev)
		parameter：
		src：輸入矩陣，這個矩陣應該是1-4通道的，這可以將計算結果存在Scalar_ ‘s中
		mean：輸出引數，計算均值
		stddev：輸出引數，計算標準差
		mask：可選引數
		*/
		meanStdDev(src_gray, mean_g, stddev_g);
		printf("gray channel mean:%.2f, stddev: %.2f \n\n", mean_g.at<double>(0, 0), stddev_g.at<double>(0, 0));
		for (int row = 0; row < src_bgr.rows; ++row) {
			for (int col = 0; col < src_bgr.cols; ++col) {
				Vec3b bgr = src_gray.at<Vec3b>(row, col);
				bgr[0] = bgr[0] < mean_g.at<double>(0, 0) ? 0 : 255;
				src_gray.at<Vec3b>(row, col) = bgr;
			}
		}
		imshow("gray_binary", src_gray);

		// 普通图像转二值图像 [彩色二值化圖]
		Mat mean, stddev;
		meanStdDev(src_bgr, mean, stddev);
		cout << "paramenters of src_bgr:" << endl;
		printf("blue channel mean:%.2f, stddev: %.2f \n", mean.at<double>(0, 0), stddev.at<double>(0, 0));
		printf("green channel mean:%.2f, stddev: %.2f \n", mean.at<double>(1, 0), stddev.at<double>(1, 0));
		printf("red channel mean:%.2f, stddev: %.2f \n", mean.at<double>(2, 0), stddev.at<double>(2, 0));
		for (int row = 0; row < src_bgr.rows; ++row) {
			for (int col = 0; col < src_bgr.cols; ++col) {
				Vec3b bgr = src_bgr.at<Vec3b>(row, col);
				bgr[0] = bgr[0] < mean.at<double>(0, 0) ? 0 : 255;
				bgr[1] = bgr[1] < mean.at<double>(1, 0) ? 0 : 255;
				bgr[2] = bgr[2] < mean.at<double>(2, 0) ? 0 : 255;
				src_bgr.at<Vec3b>(row, col) = bgr;
			}
		}
		imshow("bgr_binary", src_bgr);

		waitKey(0);
	}

	return 0;
}

