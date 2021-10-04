// VC_FANFUHAN_OPENCV030.cpp : 定義主控台應用程式的進入點。
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

void blur_demo(Mat &image, Mat &sum);
void edge_demo(Mat &image, Mat &sum);
int getblockSum(Mat &sum, int x1, int y1, int x2, int y2, int i);

void showHistogram(InputArray src, cv::String StrTitle);
void backProjection_demo(Mat &mat, Mat &model);
void blur3x3(Mat &src, Mat *det);

void add_salt_pepper_noise(Mat &image);
void add_gaussian_noise(Mat &image);

void pause()
{
	printf("Press Enter key to continue...");
	fgetc(stdin);
}
int main()
{
	Mat src = imread("../../images/test.png");

	if (src.empty())
	{
		cout << "could not load image.." << endl;
		pause();
		return -1;
	}
	else
	{
		Mat src_gray;
		cvtColor(src, src_gray, COLOR_BGR2GRAY);

		imshow("input_src", src);
		showHistogram(src, "Histogram_input_src");

		imshow("input_src_gray", src_gray);
		showHistogram(src_gray, "Histogram_input_src_gray");

		Mat dst1, dst2, dst3;

		// 均值模糊
		Mat kernel1 = Mat::ones(5, 5, CV_32F) / (float)(25);
		/*
		void filter2D(InputArray src, OutputArray dst, int ddepth, InputArray kernel, Point anchor=Point(-1,-1), double delta=0, int borderType=BORDER_DEFAULT )
		引數意義說明：
		src:源矩陣或影象
		dst:輸出矩陣或影象
		ddepth:輸出影象的深度。如果這個值是負者，那麼輸出影象的深度和源影象一致。可以是如下的組合：
		src.depth() = CV_8U, ddepth = -1/CV_16S/CV_32F/CV_64F
		src.depth() = CV_16U/CV_16S, ddepth = -1/CV_32F/CV_64F
		src.depth() = CV_32F, ddepth = -1/CV_32F/CV_64F
		src.depth() = CV_64F, ddepth = -1/CV_64F
		kernel:核算子，即我上面說的視窗矩陣。它的型別是單通道的浮點矩陣。如果你想處理多通道的影象矩陣，則可以一個通道一個通道的處理。
		anchor：錨點。視窗遍歷運算結果替換的位置。預設值為(-1,-1)，代表錨點是視窗的中心點。
		delta：結果偏移值。
		*/
		filter2D(src, dst1, -1, kernel1);

		// 锐化
		Mat kernel2 = (Mat_<char>(3, 3) << 0, -1, 0,
			-1, 5, -1,
			0, -1, 0);
		filter2D(src, dst2, -1, kernel2);

		// 梯度
		Mat kernel3 = (Mat_<int>(2, 2) << 1, 0, 0, -1);
		filter2D(src, dst3, CV_32F, kernel3);
		convertScaleAbs(dst3, dst3);  // 转换为字节类型，非常重要

		imshow("blur=5x5", dst1);
		imshow("shape=3x3", dst2);
		imshow("gradient=2x2", dst3);

		Mat dst4, dst5, dst6;
		// 均值模糊
		Mat kernel4 = Mat::ones(5, 5, CV_32F) / (float)(25);
		filter2D(src_gray, dst4, -1, kernel4);

		// 锐化
		Mat kernel5 = (Mat_<char>(3, 3) << 0, -1, 0,
			-1, 5, -1,
			0, -1, 0);
		filter2D(src_gray, dst5, -1, kernel5);

		// 梯度
		Mat kernel6 = (Mat_<int>(2, 2) << 1, 0, 0, -1);
		filter2D(src_gray, dst6, CV_32F, kernel6);
		/*
		想將圖片轉化成為8點陣圖形進行顯示
		Opencv中有一個函式convertScaleAbs可以實現這種功能
		C++: void convertScaleAbs(InputArray src, OutputArray dst, double alpha=1, double beta=0)
		Parameters:
		src: input array
		dst: output array
		alpha: optional scale factor
		beta: optional delta added to the scaled values
		the governmental definition for the function is :
		On each element of the input array, the function covertScaleAbs performs three operations sequentially: scaling, taking an absolute value, conversion to an unsigned 8-bit type:
		*/
		convertScaleAbs(dst6, dst6);  // 转换为字节类型，非常重要

		imshow("blur_gray=5x5", dst4);
		imshow("shape_gray=3x3", dst5);
		imshow("gradient_gray=2x2", dst6);

		/*
		//Sobel operator
		//Gx=[-1 0 1; -2 0 2; -1 0 1]
		//Gy=[-1 -2 -1; 0 0 0; 1 2 1]

		Mat kernel7 = (Mat_<char>(3, 3) << -1, 0, 1,
			-2, 0, 2,
			-1, 0, 1);
		Mat kernel8 = (Mat_<char>(3, 3) << -1, -2, -1,
			0, 0, 0,
			1, 2, 1);
		Mat dst7, dst8, dst9, dstX;
		filter2D(src_gray, dst7, -1, kernel7);
		filter2D(src_gray, dst8, -1, kernel8);
		filter2D(src, dst9, -1, kernel7);
		filter2D(src, dstX, -1, kernel8);
		imshow("SobelX_gray", dst7);
		imshow("SobelY_gray", dst8);
		imshow("SobelX", dst9);
		imshow("SobelY", dstX);
		*/
		waitKey(0);
		return 0;

	}

	return 0;
}

void blur_demo(Mat &image, Mat &sum) {
	int w = image.cols;
	int h = image.rows;
	Mat result = Mat::zeros(image.size(), image.type());
	int x2 = 0, y2 = 0;
	int x1 = 0, y1 = 0;
	int ksize = 5;
	int radius = ksize / 2;
	int ch = image.channels();
	int cx = 0, cy = 0;
	for (int row = 0; row < h + radius; row++) {
		y2 = (row + 1)>h ? h : (row + 1);
		y1 = (row - ksize) < 0 ? 0 : (row - ksize);
		for (int col = 0; col < w + radius; col++) {
			x2 = (col + 1)>w ? w : (col + 1);
			x1 = (col - ksize) < 0 ? 0 : (col - ksize);
			cx = (col - radius) < 0 ? 0 : col - radius;
			cy = (row - radius) < 0 ? 0 : row - radius;
			int num = (x2 - x1)*(y2 - y1);
			for (int i = 0; i < ch; i++) {
				// 积分图查找和表，计算卷积
				int s = getblockSum(sum, x1, y1, x2, y2, i);
				result.at<Vec3b>(cy, cx)[i] = saturate_cast<uchar>(s / num);
			}
		}
	}
	imshow("blur_demo", result);
}

/**
* 3x3 sobel 垂直边缘检测演示
*/
void edge_demo(Mat &image, Mat &sum) {
	int w = image.cols;
	int h = image.rows;
	Mat result = Mat::zeros(image.size(), CV_32SC3);
	int x2 = 0, y2 = 0;
	int x1 = 0, y1 = 0;
	int ksize = 3; // 算子大小，可以修改，越大边缘效应越明显
	int radius = ksize / 2;
	int ch = image.channels();
	int cx = 0, cy = 0;
	for (int row = 0; row < h + radius; row++) {
		y2 = (row + 1)>h ? h : (row + 1);
		y1 = (row - ksize) < 0 ? 0 : (row - ksize);
		for (int col = 0; col < w + radius; col++) {
			x2 = (col + 1)>w ? w : (col + 1);
			x1 = (col - ksize) < 0 ? 0 : (col - ksize);
			cx = (col - radius) < 0 ? 0 : col - radius;
			cy = (row - radius) < 0 ? 0 : row - radius;
			int num = (x2 - x1)*(y2 - y1);
			for (int i = 0; i < ch; i++) {
				// 积分图查找和表，计算卷积
				int s1 = getblockSum(sum, x1, y1, cx, y2, i);
				int s2 = getblockSum(sum, cx, y1, x2, y2, i);
				result.at<Vec3i>(cy, cx)[i] = saturate_cast<int>(s2 - s1);
			}
		}
	}
	Mat dst, gray;
	convertScaleAbs(result, dst);
	normalize(dst, dst, 0, 255, NORM_MINMAX);
	cvtColor(dst, gray, COLOR_BGR2GRAY);
	imshow("edge_demo", gray);
}

int getblockSum(Mat &sum, int x1, int y1, int x2, int y2, int i) {
	int tl = sum.at<Vec3i>(y1, x1)[i];
	int tr = sum.at<Vec3i>(y2, x1)[i];
	int bl = sum.at<Vec3i>(y1, x2)[i];
	int br = sum.at<Vec3i>(y2, x2)[i];
	int s = (br - bl - tr + tl);
	return s;
}
void add_gaussian_noise(Mat &image) {
	Mat noise = Mat::zeros(image.size(), image.type());
	// 产生高斯噪声
	randn(noise, (15, 15, 15), (30, 30, 30));
	Mat dst;
	add(image, noise, dst);
	image = dst.clone();//dst.copyTo(image);//圖像複製
						//imshow("gaussian_noise", dst);
}

void add_salt_pepper_noise(Mat &image) {
	// 随机数产生器
	RNG rng(12345);
	for (int i = 0; i < 1000; ++i) {
		int x = rng.uniform(0, image.rows);
		int y = rng.uniform(0, image.cols);
		if (i % 2 == 1) {
			image.at<Vec3b>(y, x) = Vec3b(255, 255, 255);
		}
		else {
			image.at<Vec3b>(y, x) = Vec3b(0, 0, 0);
		}
	}
	//imshow("saltp_epper", image);
}

void blur3x3(Mat &src, Mat *det)
{
	// 3x3 均值模糊，自定义版本实现
	for (int row = 1; row < src.rows - 1; row++) {
		for (int col = 1; col < src.cols - 1; col++) {
			Vec3b p1 = src.at<Vec3b>(row - 1, col - 1);
			Vec3b p2 = src.at<Vec3b>(row - 1, col);
			Vec3b p3 = src.at<Vec3b>(row - 1, col + 1);
			Vec3b p4 = src.at<Vec3b>(row, col - 1);
			Vec3b p5 = src.at<Vec3b>(row, col);
			Vec3b p6 = src.at<Vec3b>(row, col + 1);
			Vec3b p7 = src.at<Vec3b>(row + 1, col - 1);
			Vec3b p8 = src.at<Vec3b>(row + 1, col);
			Vec3b p9 = src.at<Vec3b>(row + 1, col + 1);

			int b = p1[0] + p2[0] + p3[0] + p4[0] + p5[0] + p6[0] + p7[0] + p8[0] + p9[0];
			int g = p1[1] + p2[1] + p3[1] + p4[1] + p5[1] + p6[1] + p7[1] + p8[1] + p9[1];
			int r = p1[2] + p2[2] + p3[2] + p4[2] + p5[2] + p6[2] + p7[2] + p8[2] + p9[2];

			det->at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b / 9);
			det->at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g / 9);
			det->at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r / 9);
		}
	}
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

	Mat roiproj, backproj;
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