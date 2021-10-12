// dnn_GOTURN.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>  // need contrib!

using namespace cv;
using namespace std;

int main()
{
	// ����������
	// goturn.caffemodel��goturn.prototxt�����������ļ�Ŀ¼
	cv::Ptr<cv::Tracker> tracker = cv::TrackerGOTURN::create();

	// ��ȡ��Ƶ�ļ�
	cv::VideoCapture video("TH1.mp4");
	if (!video.isOpened())
	{
		cout << "load video file error!" << endl;
		return 0;
	}

	// ��ȡ����ʾ��һ֡
	cv::Mat frame;
	video >> frame;
	cv::resize(frame, frame, cv::Size(), 0.5, 0.5, INTER_CUBIC);
	cv::imshow("Tracking", frame);
	// �����ʼ��boundibg box
	cv::Rect2d bbox;
	bbox = selectROI("Tracking", frame, false);

	// ʹ��bbox��ʼ��������
	tracker->init(frame, bbox);
	int frame_count = 0;
	while (video.read(frame))
	{
		cv::resize(frame, frame, cv::Size(), 0.5, 0.5, INTER_CUBIC);
		// ������ʱ��
		double timer = (double)getTickCount();
		// ���¸�����
		bool ret = tracker->update(frame, bbox);
		// ����֡�ʣ�Frames per second (FPS)
		float fps = getTickFrequency() / ((double)getTickCount() - timer);
		if (ret)
		{
			// ���ٳɹ������Ƹ��ٿ�
			cv::rectangle(frame, bbox, cv::Scalar(255, 176, 30), 2, 1);
		}
		else
		{
			// ����ʧ��ʱ��ʾ
			cv::putText(frame, "Tracking failure detected", cv::Point(100, 80), cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(104,200,55), 2);
		}

		// ��ͼ���ϱ�Ǹ����㷨
		cv::putText(frame, "GOTURN Tracker", cv::Point(20, 20), cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(104, 200, 55), 2);
		// ��ͼ������ʾFPS��֡�ʣ�
		cv::putText(frame, "FPS : " + to_string(int(fps)), cv::Point(20, 50), cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(104, 200, 55), 2);
		// ��ͼ������ʾ֡��
		cv::putText(frame, "frame: " + to_string(++frame_count), cv::Point(120, 50), cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(104, 200, 55),2);
		// ��ʾͼ��
		cv::imshow("Tracking", frame);
		// ����ESC���˳�
		if (cv::waitKey(1) == 27) break;
	}

	return 0;
}
