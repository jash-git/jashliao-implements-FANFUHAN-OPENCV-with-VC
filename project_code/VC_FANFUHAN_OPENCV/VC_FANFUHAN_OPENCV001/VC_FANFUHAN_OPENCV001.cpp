// VC_FANFUHAN_OPENCV001.cpp : �w�q�D���x���ε{�����i�J�I�C
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
	Mat image = imread("../../images/l_hires.jpg", IMREAD_GRAYSCALE);//IDE ���ո��|
	//Mat image = imread("../../../images/l_hires.jpg", IMREAD_GRAYSCALE);//������ ���ո��|

	if (image.empty()) {
		cout << "could not load image..." << endl;
		pause();
		return -1;
	}
	else
	{
		namedWindow("input", WINDOW_AUTOSIZE);
		imshow("input", image);
		imwrite("output.jpg", image);
		waitKey(0);
	}
	
    return 0;
}

