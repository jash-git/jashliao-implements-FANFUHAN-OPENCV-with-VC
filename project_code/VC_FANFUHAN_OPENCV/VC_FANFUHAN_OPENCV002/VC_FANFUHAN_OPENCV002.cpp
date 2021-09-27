// VC_FANFUHAN_OPENCV002.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include "stdafx.h"
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
	Mat src = imread("../../images/l_hires.jpg");//IDE ���ո��|
	//Mat src = imread("../../../images/l_hires.jpg");//������ ���ո��|

	if (src.empty()) {
		cout << "could not load image..." << endl;
		pause();
		return -1;
	}
	else
	{
		namedWindow("input");
		imshow("input", src);

		Mat gray,hsv;
		/*
		COLOR_BGR2GRAY = 6 �m����Ƕ�
		COLOR_GRAY2BGR = 8 �ǫ���m��m��
		COLOR_BGR2HSV = 40 RGB��HSV
		COLOR_HSV2BGR = 54 HSV��RGB
		*/
		cvtColor(src, gray, COLOR_BGR2GRAY);
		cvtColor(src, hsv, COLOR_BGR2HSV);
		
		namedWindow("output gray");
		imshow("output gray", gray);
		
		namedWindow("output hsv");
		imshow("output hsv", hsv);

		imwrite("gray.jpg", gray);
		imwrite("hsv.jpg", hsv);

		waitKey(0);
	}

    return 0;
}

