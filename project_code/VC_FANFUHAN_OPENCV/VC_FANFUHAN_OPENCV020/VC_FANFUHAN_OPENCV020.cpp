// VC_FANFUHAN_OPENCV020.cpp : 定義主控台應用程式的進入點。
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

void showHistogram(InputArray src, cv::String StrTitle);
void backProjection_demo(Mat &mat, Mat &model);

void pause()
{
	printf("Press Enter key to continue...");
	fgetc(stdin);
}
int main()
{
	Mat src = imread("../../images/target.png");
	Mat model = imread("../../images/sample.png");
	if (src.empty() || model.empty())
	{
		cout << "could not load image.." << endl;
		pause();
		return -1;
	}
	else
	{
		imshow("input_src", src);
		namedWindow("input_model", WINDOW_NORMAL);//允許視窗可以改變大小
		imshow("input_model", model);
		showHistogram(src, "Histogram_input_src");
		showHistogram(model, "Histogram_input_model");

		backProjection_demo(src, model);

		waitKey(0);
	}

	return 0;
}

void backProjection_demo(Mat &image, Mat &model)
{
	Mat image_hsv, model_hsv;
	cvtColor(image, image_hsv, COLOR_BGR2HSV);//彩色轉HSV
	cvtColor(model, model_hsv, COLOR_BGR2HSV);

	// 定义直方图参数与属性
	int h_bins = 32, s_bins = 32;
	int histSize[] = { h_bins, s_bins };//要切分的像素強度值範圍，預設為256。每個channel皆可指定一個範圍。例如，[32,32,32] 表示RGB三個channels皆切分為32區段
	float h_ranges[] = { 0, 180 }, s_ranges[] = { 0, 256 };
	const float* ranges[] = { h_ranges, s_ranges };
	int channels[] = { 0, 1 };

	Mat roiHist;//計算ROI的直方圖
	calcHist(&model_hsv, 1, channels, Mat(), roiHist, 2, histSize, ranges);
	normalize(roiHist, roiHist, 0, 255, NORM_MINMAX, -1, Mat());

	Mat roiproj,backproj;
	calcBackProject(&image_hsv, 1, channels, roiHist, roiproj, ranges);//使用反向投影 產生ROI(前景)的mask
	bitwise_not(roiproj, backproj);//產生背景的mask
	imshow("ROIProj", roiproj);
	imshow("BackProj", backproj);
}
void showHistogram(InputArray src, cv::String StrTitle)
{
	bool blnGray = false;
	if (src.channels() == 1)
	{
		blnGray = true;
	}

	// 三通道/單通道 直方圖 紀錄陣列
	vector<Mat> bgr_plane;
	vector<Mat> gray_plane;

	// 定义参数变量
	const int channels[1] = { 0 };
	const int bins[1] = { 256 };
	float hranges[2] = { 0, 255 };
	const float *ranges[1] = { hranges };
	Mat b_hist, g_hist, r_hist, hist;
	// 计算三通道直方图
	/*
	void calcHist( const Mat* images, int nimages,const int* channels, InputArray mask,OutputArray hist, int dims, const int* histSize,const float** ranges, bool uniform=true, bool accumulate=false );
	1.輸入的圖像數組
	2.輸入數組的個數
	3.通道數
	4.掩碼
	5.直方圖
	6.直方圖維度
	7.直方圖每個維度的尺寸數組
	8.每一維數組的範圍
	9.直方圖是否是均勻
	10.配置階段不清零
	*/
	if (blnGray)
	{
		split(src, gray_plane);
		calcHist(&gray_plane[0], 1, 0, Mat(), hist, 1, bins, ranges);
	}
	else
	{
		split(src, bgr_plane);
		calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);
		calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
		calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);
	}

	/*
	* 显示直方图
	*/
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]);
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
	// 归一化直方图数据
	if (blnGray)
	{
		normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1);
	}
	else
	{
		normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1);
		normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1);
		normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1);
	}

	// 绘制直方图曲线
	for (int i = 1; i < bins[0]; ++i)
	{
		if (blnGray)
		{
			line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
				Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))), Scalar(255, 255, 255),
				2, 8, 0);
		}
		else
		{
			line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
				Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0),
				2, 8, 0);
			line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
				Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0),
				2, 8, 0);
			line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
				Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255),
				2, 8, 0);
		}


	}
	imshow(StrTitle, histImage);
}

/*
HSV （HSV顏色模型）

https://baike.baidu.hk/item/HSV/547122

HSV(Hue, Saturation, Value)是根據顏色的直觀特性由A. R. Smith在1978年創建的一種顏色空間, 也稱六角錐體模型(Hexcone Model)。

色調H : 用角度度量，取值范圍為0°～360°，從紅色開始按逆時針方向計算，紅色為0°，綠色為120°,藍色為240°。它們的補色是：黃色為60°，青色為180°,紫色為300°；

飽和度S : 表示顏色接近光譜色的程度。一種顏色，可以看成是某種光譜色與白色混合的結果。其中光譜色所占的比例愈大，顏色接近光譜色的程度就愈高，顏色的飽和度也就愈高。飽和度高，顏色則深而艷。光譜色的白光成分為0，飽和度達到最高。通常取值范圍為0%～100%，值越大，顏色越飽和。

明度V : 表示顏色明亮的程度，對於光源色，明度值與發光體的光亮度有關；對於物體色，此值和物體的透射比或反射比有關。通常取值范圍為0%（黑）到100%（白）。

RGB和CMY顏色模型都是面向硬件的，而HSV（Hue Saturation Value）顏色模型是面向用戶的。

HSV模型的三維表示從RGB立方體演化而來。設想從RGB沿立方體對角線的白色頂點向黑色頂點觀察，就可以看到立方體的六邊形外形。六邊形邊界表示色彩，水平軸表示純度，明度沿垂直軸測量。

RGB轉化到HSV的算法:
max=max(R,G,B)；
min=min(R,G,B)；
V=max(R,G,B)；
S=(max-min)/max；
if (R = max) H =(G-B)/(max-min)* 60；
if (G = max) H = 120+(B-R)/(max-min)* 60；
if (B = max) H = 240 +(R-G)/(max-min)* 60；
if (H < 0) H = H+ 360；

HSV轉化到RGB的算法:
if (s = 0)
R=G=B=V;
else
H /= 60;
i = INTEGER(H);
f = H - i;
a = V * ( 1 - s );
b = V * ( 1 - s * f );
c = V * ( 1 - s * (1 - f ) );
switch(i)
case 0: R = V; G = c; B = a;
case 1: R = b; G = v; B = a;
case 2: R = a; G = v; B = c;
case 3: R = a; G = b; B = v;
case 4: R = c; G = a; B = v;
case 5: R = v; G = a; B = b;
*/