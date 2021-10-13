// VC_OPENCV4_ML002.cpp : 定義主控台應用程式的進入點。
//
/*
// Debug | x32
通用屬性
| C/C++
|	| 一般
|		| 其他 Include 目錄 -> ..\..\opencv411_x64\include
|
| 連結器
| 	|一一般
|		|  其他程式庫目錄 -> ..\..\opencv411_x64\lib
|
| 	|一輸入
|		| 其他相依性 -> opencv_world411d.lib;%(AdditionalDependencies)

// Releas | x64
組態屬性
| C/C++
|	| 一般
|		| 其他 Include 目錄 -> ..\..\opencv411_x64\include;%(AdditionalDependencies)
|
| 連結器
| 	|一般
|		| 其他程式庫目錄 -> ..\..\opencv411_x64\lib;%(AdditionalDependencies)
|
| 	|一輸入
|		| 其他相依性 -> opencv_world411.lib;%(AdditionalDependencies)

*/

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

//OPENCV4_ML02 ~ K近鄰算法(KNN)
//https://github.com/jash-git/CB_OpenCV249_ML/blob/master/CB_OpenCV249_ML02/main.cpp

void pause()
{
	printf("Press Enter key to continue...");
	fgetc(stdin);
}

int main()
{
	float trainingData[24][2] = { { 4, 3 },{ 1, 3 },{ 3, 3 },{ 3, 7 },
	{ 3, 4 },{ 4, 1 },{ 1, 4 },{ 5, 6 },
	{ 3, 7 },{ 6, 2 },{ 4, 6 },{ 4, 4 },
	{ 5, 8 },{ 7, 8 },{ 7, 7 },{ 10, 5 },
	{ 7, 6 },{ 4, 10 },{ 9, 7 },{ 5, 4 },
	{ 8, 5 },{ 6, 6 },{ 7, 4 },{ 8, 8 } };
	Mat trainingDataCvMat = Mat(24, 2, CV_32FC1, trainingData);

	float responses[24] = { 'B','B','B','B','B','B','B','B','B','B',
		'G','G','G','G','G','G','G','G','G','G','G','G','G','G' };
	Mat responsesCvMat = Mat(24, 1, CV_32FC1, responses);

	//参数false表示分类问题
	cv::Ptr<cv::ml::KNearest> knn = cv::ml::KNearest::create();

	int K = 7;    //KNN算法的参数K值
	knn->setDefaultK(K);
	knn->setIsClassifier(true); // 用于分类
	knn->setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE);
	knn->train(trainingDataCvMat, cv::ml::ROW_SAMPLE, responsesCvMat);

	float myData[2] = { 6, 6 };//{ 4, 5 };
	Mat myDataCvMat = Mat(1, 2, CV_32FC1, myData);
	//nearests表示K个最邻近样本的响应值

	Mat result;
	float data=knn->findNearest(myDataCvMat, K, result);

	cout << (char)(data) << endl;

	pause();
	return 0;
}

