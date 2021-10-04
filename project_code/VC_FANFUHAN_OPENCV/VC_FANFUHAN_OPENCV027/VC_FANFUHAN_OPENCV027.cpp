// VC_FANFUHAN_OPENCV027.cpp : 定義主控台應用程式的進入點。
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
		imshow("input_src", src);
		showHistogram(src, "Histogram_input_src");

		Mat dst01, dst02;;

		/*

		void bilateralFilter(src, dst, d, sigmaColor, sigmaSpace, BORDER_DEFAULT)
		. InputArray src: 輸入影象，可以是Mat型別，影象必須是8位或浮點型單通道、三通道的影象。
		. OutputArray dst: 輸出影象，和原影象有相同的尺寸和型別。
		. int d: （直徑範圍）表示在過濾過程中每個畫素鄰域的直徑範圍。如果這個值是非正數，則函式會從第五個引數sigmaSpace計算該值。
		. double sigmaColor:（sigma顏色） 顏色空間過濾器的sigma值，這個引數的值月大，表明該畫素鄰域內有月寬廣的顏色會被混合到一起，產生較大的半相等顏色區域。
		. double sigmaSpace:（sigma空間） 座標空間中濾波器的sigma值，如果該值較大，則意味著顏色相近的較遠的畫素將相互影響，從而使更大的區域中足夠相似的顏色獲取相同的顏色。當d>0時，d指定了鄰域大小且與sigmaSpace五官，否則d正比於sigmaSpace.
		. int borderType=BORDER_DEFAULT: 用於推斷影象外部畫素的某種邊界模式，有預設值BORDER_DEFAULT.
		*/
		bilateralFilter(src, dst01, 10, 10, 10);
		imshow("bilateral_blur", dst01);

		/*
		meanShfit均值漂移演算法是一種通用的聚類演算法，它的基本原理是：對於給定的一定數量樣本，任選其中一個樣本，以該樣本為中心點劃定一個圓形區域，求取該圓形區域內樣本的質心，即密度最大處的點，再以該點為中心繼續執行上述迭代過程，直至最終收斂。可以利用均值偏移演算法的這個特性，實現彩色影像分割.

		pyrMeanShiftFiltering(src, dst, double sp, double sr, int maxLevel=1, TermCriteria termcrit=TermCriteria)

		引數如下:

		src，輸入影像，8位，三通道的彩色影像；
		dst，輸出影像，跟輸入src有同樣的大小和資料格式；
		sp，定義的漂移物理空間半徑大小；
		sr，定義的漂移色彩空間半徑大小；
		maxLevel，定義金字塔的最大層數；
		termcrit，定義的漂移迭代終止條件，可以設定為迭代次數滿足終止，迭代目標與中心點偏差滿足終止，或者兩者的結合；
		*/
		pyrMeanShiftFiltering(src, dst02, 15, 30);
		imshow("mean_shift_blur", dst02);

		waitKey(0);
		return 0;

	}

	return 0;
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