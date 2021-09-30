// VC_FANFUHAN_OPENCV014.cpp : �w�q�D���x���ε{�����i�J�I�C
//
/*
// Debug | x32
�q���ݩ�
| C/C++
|	| �@��
|		| ��L Include �ؿ� -> C:\opencv\build\include
|
| �s����
| 	|�@�@��
|		|  ��L�{���w�ؿ� -> C:\opencv\build\x64\vc15\lib
|
| 	|�@��J
|		| ��L�̩ۨ� -> opencv_world411d.lib;%(AdditionalDependencies)

// Releas | x64
�պA�ݩ�
| C/C++
|	| �@��
|		| ��L Include �ؿ� -> C:\opencv\build\include
|
| �s����
| 	|�@��
|		| ��L�{���w�ؿ� -> C:\opencv\build\x64\vc15\lib
|
| 	|�@��J
|		| ��L�̩ۨ� -> opencv_world411.lib;%(AdditionalDependencies)

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

	if (src_bgr.empty())
	{
		cout << "could not load image.." << endl;
		pause();
		return -1;
	}
	else
	{
		imshow("input_bgr", src_bgr);

		int h = src_bgr.rows;//���o�Ϲ����e�ؤo
		int w = src_bgr.cols;
		float fx = 0.0, fy = 0.0;//�إ߰_�l�I
		Mat dst = Mat::zeros(src_bgr.size(), src_bgr.type());//�إ߹w�]���ťյe��
		Size S00(w * 2, h * 2);//�إߩ�j��ؤo
		Size S01(w * 0.5, h * 0.5);//�إ��Y�p��ؤo

		resize(src_bgr, dst, S00, fx, fy, INTER_NEAREST);
		imshow("INTER_NEAREST", dst);

		resize(src_bgr, dst, S00, fx, fy, INTER_LINEAR);
		imshow("INTER_LINEAR", dst);

		resize(src_bgr, dst, S00, fx, fy, INTER_CUBIC);
		imshow("INTER_CUBIC", dst);

		resize(src_bgr, dst, S00, fx, fy, INTER_LANCZOS4);
		imshow("INTER_LANCZOS4", dst);

		resize(src_bgr, dst, S01, fx, fy, INTER_LINEAR);
		imshow("INTER_LINEAR01", dst);
		waitKey(0);

	}

	return 0;
}