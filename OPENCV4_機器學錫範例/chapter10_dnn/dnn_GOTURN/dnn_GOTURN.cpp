// dnn_GOTURN.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>  // need contrib!

using namespace cv;
using namespace std;

int main()
{
	// 创建跟踪器
	// goturn.caffemodel和goturn.prototxt拷贝至程序文件目录
	cv::Ptr<cv::Tracker> tracker = cv::TrackerGOTURN::create();

	// 读取视频文件
	cv::VideoCapture video("TH1.mp4");
	if (!video.isOpened())
	{
		cout << "load video file error!" << endl;
		return 0;
	}

	// 读取并显示第一帧
	cv::Mat frame;
	video >> frame;
	cv::resize(frame, frame, cv::Size(), 0.5, 0.5, INTER_CUBIC);
	cv::imshow("Tracking", frame);
	// 定义初始化boundibg box
	cv::Rect2d bbox;
	bbox = selectROI("Tracking", frame, false);

	// 使用bbox初始化跟踪器
	tracker->init(frame, bbox);
	int frame_count = 0;
	while (video.read(frame))
	{
		cv::resize(frame, frame, cv::Size(), 0.5, 0.5, INTER_CUBIC);
		// 启动计时器
		double timer = (double)getTickCount();
		// 更新跟踪器
		bool ret = tracker->update(frame, bbox);
		// 计算帧率：Frames per second (FPS)
		float fps = getTickFrequency() / ((double)getTickCount() - timer);
		if (ret)
		{
			// 跟踪成功：绘制跟踪框
			cv::rectangle(frame, bbox, cv::Scalar(255, 176, 30), 2, 1);
		}
		else
		{
			// 跟踪失败时提示
			cv::putText(frame, "Tracking failure detected", cv::Point(100, 80), cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(104,200,55), 2);
		}

		// 在图像上标记跟踪算法
		cv::putText(frame, "GOTURN Tracker", cv::Point(20, 20), cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(104, 200, 55), 2);
		// 在图像上显示FPS（帧率）
		cv::putText(frame, "FPS : " + to_string(int(fps)), cv::Point(20, 50), cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(104, 200, 55), 2);
		// 在图像上显示帧数
		cv::putText(frame, "frame: " + to_string(++frame_count), cv::Point(120, 50), cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(104, 200, 55),2);
		// 显示图像
		cv::imshow("Tracking", frame);
		// 按下ESC键退出
		if (cv::waitKey(1) == 27) break;
	}

	return 0;
}
