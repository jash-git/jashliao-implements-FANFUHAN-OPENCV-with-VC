// VC_FANFUHAN_OPENCV012.cpp : 定義主控台應用程式的進入點。
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
	// 打开摄像头
	// VideoCapture capture(0);
	// 打开视频文件
	VideoCapture capture;
	capture.open("../../images/vtest.avi");////影片讀取
	if (!capture.isOpened())
	{
		cout << "could not load video.." << endl;
		pause();
		return -1;
	}
	else
	{
		
		Size S = Size((int)capture.get(CAP_PROP_FRAME_WIDTH), (int)capture.get(CAP_PROP_FRAME_HEIGHT));////影片畫面大小
		int fps = capture.get(CAP_PROP_FPS);//抓取影片每秒張數
		cout << "capture Width:" << S.width <<"\tHeight:"<<S.height<< endl;
		cout << "capture fps: " << fps << endl;

		VideoWriter writer("test.mp4", cv::VideoWriter::fourcc('D', 'I', 'V', 'X'), fps, S, true);


		Mat frame;
		while (capture.read(frame)) {
			imshow("input", frame);//顯示影面每一格的畫面
			writer.write(frame);//將每一格的畫面寫入檔案
			char c = waitKey(50);
			if (c == 27) //ESC
			{
				break;
			}
		}
		capture.release();
		writer.release();

		waitKey(0);
	}

	return 0;
}
