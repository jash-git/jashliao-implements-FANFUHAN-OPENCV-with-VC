// VC_FANFUHAN_OPENCV016.cpp : 定義主控台應用程式的進入點。
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
	Mat src = imread("../../images/test.png");
	/*
	* 提取图像前景和背景
	*/
	Mat src2 = imread("../../images/boy.jpg");
	if (src.empty() && src2.empty())
	{
		cout << "could not load image.." << endl;
		pause();
		return -1;
	}
	else
	{
		imshow("input", src);
		int h = src.rows;
		int w = src.cols;
		
		int cy = h / 2;
		int cx = w / 2;
		Rect rect(cx - 100, cy - 100, 200, 200);
		// 注意：roi 与 src指向同一块内存区域，改变roi,src也会改变
		Mat roi = src(rect);// 感興趣區域 (Region of Interest)
		imshow("roi", roi);

		//---------------------//
		/*
		//VC_FANFUHAN_OPENCV009內容
		Mat hsv;
		imshow("input boy", src2);
		cvtColor(src2, hsv, COLOR_BGR2HSV);


		Mat mask, mask_not;// 感興趣區域 (Region of Interest)

		// 从HSV表中查到绿色的最低值和最高值，建立掩模
		inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);//符合規定為白色(255)，不符合範圍為黑色(0)		
		bitwise_not(mask, mask_not);
		imshow("mask", mask);//背景遮罩
		imshow("mask_not", mask_not);//前景遮罩

		Mat fg, bg;
		bitwise_and(src2, src2, bg, mask);// 提取背景		
		bitwise_and(src2, src2, fg, mask_not);// 提取前景
		imshow("background", bg);
		imshow("foreground", fg);
		*/

		//*
		// 人物背景图，换背景

		// load image
		Mat image = imread("../../images/boy.jpg");
		imshow("input_image", image);

		// generate mask
		Mat hsv, mask, mask_not;
		cvtColor(image, hsv, COLOR_BGR2HSV);

		inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);//取出綠色背景
		imshow("mask", mask);

		bitwise_not(mask, mask_not);
		imshow("mask_not", mask_not);//取出非綠色前景

		// extract person
		Mat person;
		bitwise_and(image, image, person, mask_not);
		imshow("person", person);

		// gengerate background
		Mat background = Mat::zeros(image.size(), image.type());//建立黑色畫布
		background.setTo(Scalar(255, 0, 0));//把黑色改成紅色
		imshow("background", background);

		// combine background + person
		Mat dst;
		bitwise_or(background, background, dst, mask);//新背景
		imshow("dst", dst);

		add(dst, person, dst);
		imshow("ouput", dst);
		//*/

		waitKey(0);
	}

	return 0;
}