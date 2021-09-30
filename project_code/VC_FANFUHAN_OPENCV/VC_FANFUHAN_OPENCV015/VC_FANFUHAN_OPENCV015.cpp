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
/*
OpenCV 畫線
	void line(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
	img：輸入圖，線會畫在上面。
	pt1：線的起點。
	pt2：線的終點。
	color：線的顏色。
	thickness：線的厚度。
	lineType：通道型態，可輸入8、4、CV_AA： 8->8通道連結。 4->4通道連結。 CV_AA->消除鋸齒(antialiased line)，消除顯示器畫面線邊緣的凹凸鋸齒。


OpenCV 畫矩形
	void rectangle(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
	img：輸入圖，矩形會畫在上面。
	pt1：矩形頂點。
	pt2：矩形頂點，pt1的對角邊
	color：矩形的顏色。
	thickness：矩形的邊線寬度，輸入負值或CV_FILLED代表填滿矩形。
	lineType：通道型態，可輸入8、4、CV_AA： 8->8通道連結。 4->4通道連結。 CV_AA->消除鋸齒(antialiased line)，消除顯示器畫面線邊緣的凹凸鋸齒。


OpenCV 畫圓
void circle(Mat& img, Point center, int radius, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
	img：輸入圖，圓會畫在上面。
	center：圓心。
	radius：圓半徑。
	color：圓形的顏色。
	thickness：圓形的邊線寬度，輸入負值或CV_FILLED代表填滿圓形。
	lineType：通道型態，可輸入8、4、CV_AA： 8->8通道連結。 4->4通道連結。 CV_AA->消除鋸齒(antialiased line)，消除顯示器畫面線邊緣的凹凸鋸齒。


OpenCV 畫橢圓
void ellipse(Mat& img, Point center, Size axes, double angle, double startAngle, double endAngle, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
	img：輸入圖，橢圓會畫在上面。
	center：圓心。
	axes：橢圓軸的尺寸。
	angle：旋轉角度，單位角度。
	startAngle：橢圓弧度起始角度，單位角度。
	endAngle：橢圓弧度結束角度，單位角度。
	color：橢圓的顏色。
	thickness：橢圓的邊線寬度，輸入負值或CV_FILLED代表填滿橢圓形 。
	lineType：通道型態，可輸入8、4、CV_AA： 8->8通道連結。 4->4通道連結。 CV_AA->消除鋸齒(antialiased line)，消除顯示器畫面線邊緣的凹凸鋸齒。


OpenCV 畫多角形
void polylines(Mat& img, const Point** pts, const int* npts, int ncontours, bool isClosed, const Scalar& color, int thickness=1, intlineType=8, int shift=0)
	img：輸入圖，多角形會畫在上面。
	pts：包含多角形各個曲線點的陣列。
	npts：包含多角形各曲線頂點數目的陣列。
	ncontours：曲線數。
	isClosed：是否為封閉的多角形。
	color：多角形的顏色。
	thickness：多角形的邊線寬度，輸入負值或CV_FILLED代表填滿多角形。
	lineType：通道型態，可輸入8、4、CV_AA： 8->8通道連結。 4->4通道連結。 CV_AA->消除鋸齒(antialiased line)，消除顯示器畫面線邊緣的凹凸鋸齒。


OpenCV 畫文字字串
void putText(Mat& img, const string& text, Point org, int fontFace, double fontScale, Scalar color, int thickness=1, int lineType=8, bool bottomLeftOrigin=false)
	img：輸入圖，字串會畫在上面。
	text：輸出字串，OpenCV目前沒有支援中文文字顯現。
	org：文字左下角位置。
	fontFace：字體樣式。
	fontScale：字體大小。
	color：字串顏色。
	thickness：構成字串的線寬度。
	lineType：通道型態，有以下三種可選： 8：8通道連結。 4：4通道連結。 CV_AA：消除鋸齒(antialiased line)，消除顯示器畫面橢圓邊緣的凹凸鋸齒。

*/
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

		//-----------------------------------------

		Mat img(488, 400, CV_8UC3, Scalar(255, 255, 255));//建立彩色白底畫布

		line(img, Point(20, 40), Point(120, 140), Scalar(255, 9, 9), 3);
		rectangle(img, Point(150, 40), Point(250, 140), Scalar(0, 0, 255), -1);
		circle(img, Point(330, 90), 50, Scalar(9, 255, 9), -1);
		ellipse(img, Point(80, 280), Size(60, 48), 45, 9, 360, Scalar(255, 255, 9), 2);
		
		Point points[1][5];
		points[0][0] = Point(150, 279);
		points[0][1] = Point(190, 229);
		points[0][2] = Point(260, 255);
		points[0][3] = Point(224, 296);
		points[0][4] = Point(178, 316);
		const Point* ppt[1] = { points[0] };
		int npt[] = { 5 };
		polylines(img, ppt, npt, 1, 1, Scalar(0, 255, 255), 5);
		putText(img, string("OpenCv"), Point(280, 280), 0, 1, Scalar(0, 0, 0), 3);
		imshow("window", img);
		waitKey(0);
	}

	return 0;
}