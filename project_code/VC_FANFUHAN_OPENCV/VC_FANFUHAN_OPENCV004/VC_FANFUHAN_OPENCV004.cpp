// VC_FANFUHAN_OPENCV004.cpp : 定義主控台應用程式的進入點。
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
		namedWindow("input");
		imshow("input", src);

		int height = src.rows;
		int width = src.cols;
		int ch = src.channels();

		//*
		Mat color_reverse = Mat::zeros(src.size(), src.type());
		Mat OnlyRed = Mat::zeros(src.size(), src.type());
		Mat OnlyGreen = Mat::zeros(src.size(), src.type());
		Mat OnlyBlue = Mat::zeros(src.size(), src.type());

		// 直接读取图像像素,將圖片顏色反轉
		for (int row = 0; row < height; ++row) {
			for (int col = 0; col < width; ++col) {
				if (ch == 3) {
					Vec3b bgr = src.at<Vec3b>(row, col);

					Vec3b bgrreverse;
					Vec3b bgrRed;
					Vec3b bgrGreen;
					Vec3b bgrBlue;

					bgrreverse[0] = 255 - bgr[0];//依序取出藍色，並反轉
					bgrreverse[1] = 255 - bgr[1];//依序取出綠色，並反轉
					bgrreverse[2] = 255 - bgr[2];//依序取出紅色，並反轉

					bgrRed[0] = 0;
					bgrRed[1] = 0;
					bgrRed[2] = bgr[2];;

					bgrGreen[0] = 0;
					bgrGreen[1] = bgr[1];;
					bgrGreen[2] = 0;

					bgrBlue[0] = bgr[0];;
					bgrBlue[1] = 0;
					bgrBlue[2] = 0;

					color_reverse.at<Vec3b>(row, col) = bgrreverse;
					OnlyRed.at<Vec3b>(row, col) = bgrRed;
					OnlyGreen.at<Vec3b>(row, col) = bgrGreen;
					OnlyBlue.at<Vec3b>(row, col) = bgrBlue;
				}
				else if (ch == 1) {
					int gray = src.at<uchar>(row, col);
					color_reverse.at<uchar>(row, col) = 255 - gray;
				}
			}
		}
		namedWindow("color_reverse");
		imshow("color_reverse", color_reverse);

		namedWindow("OnlyRed");
		imshow("OnlyRed", OnlyRed);

		namedWindow("OnlyGreen");
		imshow("OnlyGreen", OnlyGreen);

		namedWindow("OnlyBlue");
		imshow("OnlyBlue", OnlyBlue);
		//*/

		/*
		// 指针读取
		Mat result = Mat::zeros(src.size(), src.type());
		Mat OnlyRed = Mat::zeros(src.size(), src.type());
		Mat OnlyGreen = Mat::zeros(src.size(), src.type());
		Mat OnlyBlue = Mat::zeros(src.size(), src.type());
		int blue = 0, green = 0, red = 0;
		int gray;
		for (int row = 0; row < height; ++row) {
			// curr_row为第row行的首地址，遍历时，前三个字节表示的是第一个像素的BGR值，
			// 注意BGR值顺序，接下来三个字节是第二个像素的值。
			uchar *curr_row = src.ptr<uchar>(row);
			uchar *result_row = result.ptr<uchar>(row);
			uchar *OnlyRed_row = OnlyRed.ptr<uchar>(row);
			uchar *OnlyGreen_row = OnlyGreen.ptr<uchar>(row);
			uchar *OnlyBlue_row = OnlyBlue.ptr<uchar>(row);
			for (int col = 0; col < width; ++col) {
				if (ch == 3) {
					blue = *curr_row++;
					green = *curr_row++;
					red = *curr_row++;

					*result_row++ = 255 - blue;
					*result_row++ = 255 - green;
					*result_row++ = 255 - red;

					*OnlyRed_row++ = 0;
					*OnlyRed_row++ = 0;
					*OnlyRed_row++ = red;

					*OnlyGreen_row++ = 0;
					*OnlyGreen_row++ = green;
					*OnlyGreen_row++ = 0;

					*OnlyBlue_row++ = blue;
					*OnlyBlue_row++ = 0;
					*OnlyBlue_row++ = 0;
				}
				else if (ch == 1) {
					gray = *curr_row++;
					*result_row++ = gray;
				}
			}
		}

		namedWindow("result");
		imshow("result", result);

		namedWindow("OnlyRed");
		imshow("OnlyRed", OnlyRed);

		namedWindow("OnlyGreen");
		imshow("OnlyGreen", OnlyGreen);

		namedWindow("OnlyBlue");
		imshow("OnlyBlue", OnlyBlue);
		//*/

		waitKey(0);
	}

	return 0;
}
