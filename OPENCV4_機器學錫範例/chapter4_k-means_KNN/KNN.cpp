// KNN.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "opencv.hpp"
#include <iostream>

using namespace cv;
using namespace cv::ml;
using namespace std;

//#define CLASSIFIER
#define REGRESSION

// ����ѵ��������Լ��ĺ���
void generateDataSet(Mat &img, Mat &trainData, Mat &testData, Mat &trainLabel, Mat &testLabel, int train_rows=4);

#ifdef CLASSIFIER
int main()
{
	// 1.��ȡԭʼ����
	Mat img = imread("digits.png", 1); // ʹ��ͼƬ��ʽ��MNIST���ݼ������֣�
	cvtColor(img, img, CV_BGR2GRAY);
	
	// 2.����ѵ����
	// ����ѵ���������Լ���С
	int train_sample_count = 4000;
	int test_sample_count = 1000;
	int train_rows = 4; //  ÿ������ѵ����������4000/10��/100(����/��)=4
	Mat trainData, testData; // ����ѵ��������Լ�
	Mat trainLabel(train_sample_count, 1, CV_32FC1); // ����ѵ������ǩ
	Mat testLabel(test_sample_count, 1, CV_32FC1);   // �������Լ���ǩ
	// ����ѵ���������Լ����ǩ
	generateDataSet(img, trainData, testData, trainLabel, testLabel/*, train_rows*/);

	// 3.��������ʼ��KNNģ��
	cv::Ptr<cv::ml::KNearest> knn = cv::ml::KNearest::create(); // ����knnģ��
	int K = 5; // ��������ڽ���������
	knn->setDefaultK(K);
	knn->setIsClassifier(true); // ���ڷ���
	knn->setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE);

	// 4.ѵ��
	printf("��ʼѵ��...\n");
	//printf("trainData : rows, cols = %d, %d\n", trainData.rows, trainData.cols);
	//printf("trainLabel: rows, cols = %d, %d\n", trainLabel.rows, trainLabel.cols);
	knn->train(trainData, cv::ml::ROW_SAMPLE, trainLabel);
	printf("ѵ�����\n\n");

	// 5.����
	printf("��ʼ����...\n");
	Mat result;
	knn->findNearest(testData, K, result);
	//printf("test samples = %d\n", testData.rows);
	//printf("result rows  = %d\n", result.rows);
	// ����
	int count = 0;
	for (int i = 0; i < test_sample_count; i++)
	{
		int predict = int(result.at<float>(i));
		int actual = int(testLabel.at<float>(i));		
		if (predict == actual)
		{
			printf("label: %d, predict: %d\n", actual, predict);
			count++;			
		}
		else
			printf("label: %d, predict: %d ��\n", actual, predict);
	}
	printf("�������\n");
	// ������
	double accuracy = double(count) / double(test_sample_count);
	printf("K = %d\n", K);
	printf("accuracy = %.4f\n", accuracy);
	waitKey();
    return 0;
}
#endif

#ifdef REGRESSION
int main()
{
	// 1.��ȡԭʼ����
	Mat img = imread("digits.png", 1);
	cvtColor(img, img, CV_BGR2GRAY);

	// 2.����ѵ����
	// ����ѵ���������Լ���С
	int train_sample_count = 4000;
	int test_sample_count = 1000;
	int train_rows = 4; //  ÿ������ѵ����������4000/10��/100(����/��)=4
	Mat trainData, testData; // ����ѵ��������Լ�
	Mat trainLabel(train_sample_count, 1, CV_32FC1); // ����ѵ������ǩ
	Mat testLabel(test_sample_count, 1, CV_32FC1);   // �������Լ���ǩ
													 // ����ѵ���������Լ����ǩ
	generateDataSet(img, trainData, testData, trainLabel, testLabel/*, train_rows*/);

	// 3.��������ʼ��KNNģ��
	cv::Ptr<cv::ml::KNearest> knn = cv::ml::KNearest::create(); // ����knnģ��
	int K = 5; // ��������ڽ���������
	knn->setDefaultK(K);
	knn->setIsClassifier(false); // ���ڻع�
	knn->setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE);

	// 4.ѵ��
	printf("��ʼѵ��...\n");
	//printf("trainData : rows, cols = %d, %d\n", trainData.rows, trainData.cols);
	//printf("trainLabel: rows, cols = %d, %d\n", trainLabel.rows, trainLabel.cols);
	knn->train(trainData, cv::ml::ROW_SAMPLE, trainLabel);
	printf("ѵ�����\n\n");

	// 5.����
	printf("��ʼ����...\n");
	Mat result;
	knn->findNearest(testData, K, result);
	//printf("test samples = %d\n", testData.rows);
	//printf("result rows  = %d\n", result.rows);
	// ����
	int t = 0;
	int f = 0;
	for (int i = 0; i < test_sample_count; i++)
	{
		int predict = int(result.at<float>(i));
		int actual = int(testLabel.at<float>(i));
		if (predict == actual)
		{
			printf("label: %d, predict: %d\n", actual, predict);
			t++;
		}
		else
		{
			printf("label: %d, predict: %d ��\n", actual, predict);
			f++;
		}			
	}
	printf("�������\n");
	// ������
	float accuracy = (t * 1.0) / (t + f);
	printf("K = %d\n", K);
	printf("accuracy = %.4f\n", accuracy);
	waitKey();
	return 0;
}
#endif

/** @����ģ�͵�ѵ��������Լ�
	����1��img       �����룬�Ҷ�ͼ���ɹ̶��ߴ�Сͼƴ�ӳɵĴ�ͼ����ͬ����Сͼ����������
	����2��trainData �������ѵ������ά��Ϊ��ѵ�������� * ����������������CV_32FC3����
	����3��testData  ����������Լ���ά��Ϊ������������ * ����������������CV_32FC3����
	����4��trainLabel�������ѵ������ǩ��ά��Ϊ��ѵ�������� * 1��CV_32FC1����
	����4��testLabel ����������Լ���ǩ��ά��Ϊ������������ * 1��CV_32FC1����
	����5��train_rows�����룬����ѵ����������ռ������Ĭ��4������ѵ����1�����ڲ���
*/
void generateDataSet(Mat &img, Mat &trainData, Mat &testData, Mat &trainLabel, Mat &testLabel, int train_rows)
{
	// ��ʼ��ͼ������Ƭͼ����������
	int width_slice = 20;  // ����������Ƭͼ��Ŀ��
	int height_slice = 20; // ����������Ƭͼ��ĸ߶�
	int row_sample = 100;  // ÿ��������100��Сͼ
	int col_sample =  50;  // ÿ��������50��Сͼ
	int row_single_number = 5; // ��������ռ5��
	int test_rows = row_single_number - train_rows; // ����������ռ����

	Mat trainMat(train_rows * 20 *10, img.cols, CV_8UC1); // �������ѵ��ͼƬ
	trainMat = Scalar::all(0);
	Mat testMat(test_rows * 20 * 10, img.cols, CV_8UC1);  // ������в���ͼƬ
	testMat = Scalar::all(0);

	// ���ɲ��ԡ�ѵ����ͼ
	for (int i = 1; i <= 10 ; i++)
	{
		Mat tempTrainMat = img.rowRange((i - 1) * row_single_number * 20, (i * row_single_number - 1) * 20).clone();
		Mat tempTestMat  = img.rowRange((i * row_single_number - 1) * 20, (i * row_single_number) * 20).clone();
		imshow("temptrain", tempTrainMat);
		imshow("temptest",  tempTestMat);
		//printf("tempTrainMat(w, h) = %d, %d\n", tempTrainMat.cols, tempTrainMat.rows);
		//printf("tempTestMat (w, h) = %d, %d\n", tempTestMat.cols,  tempTestMat.rows);
		// train
		cv::Mat roi_train = trainMat(Rect(0, (i - 1) * train_rows * 20, tempTrainMat.cols, tempTrainMat.rows));
		Mat mask_train(roi_train.rows, roi_train.cols, roi_train.depth(), Scalar(1));
		// test
		cv::Mat roi_test = testMat(Rect(0, (i - 1) * test_rows * 20, tempTestMat.cols, tempTestMat.rows));
		Mat mask_test(roi_test.rows, roi_test.cols, roi_test.depth(), Scalar(1));
		// ��ȡ��ѵ�������зֱ��Ƶ�ѵ��ͼ�����ͼ��
		tempTrainMat.copyTo(roi_train, mask_train);
		tempTestMat.copyTo(roi_test, mask_test);
		//��ʾЧ��ͼ
		imshow("trainMat", trainMat);
		imshow("tesetMat", testMat);
		cv::waitKey(10);
	}
	// ���ͼ
	imwrite("trainMat.jpg", trainMat);
	imwrite("testMat.jpg", testMat);


	// ����ѵ������������
	printf("��ʼ����ѵ������������...\n");
	Rect roi;
	for (int i = 1; i <= col_sample; i++) // 50�У�1-50������ͼ��
	{
		//printf("��%d��: \n", i);
		for (int j = 1; j <= row_sample; j++) // 100�У�1-100������ͼ��
		{
			// ����Ϊѵ����
			Mat temp_single_num; // ��ȡһ������ͼ��
			// �ؼ����裺��ǰ��Ƭ���ֵ�λ������
			roi = Rect((j-1)*width_slice, (i-1)*height_slice, width_slice, height_slice); 
			temp_single_num = img(roi).clone(); // ע��˴���Ҫʹ�����.clone()��������ܸı���Ƭͼ����״������roi�ڴ���������
			//imshow("slice", temp_single_num);
			//waitKey(1);
			if (i % 5 != 0) 
			//{
				// ��ʼ�м�Ϊ1-4,6-9,11-14...46-49��Ϊ���Լ�
				// ������������Ƭ����������������Mat������
				trainData.push_back(temp_single_num.reshape(0, 1)); 
			//}
			else
			//{	// ��ʼ�м�Ϊ1����5,10,15...50��Ϊ���Լ�
				testData.push_back(temp_single_num.reshape(0, 1));  
			//}	
		}
	}
	trainData.convertTo(trainData, CV_32FC1);
	testData.convertTo(testData, CV_32FC1);
	printf("ѵ������������������\n\n");

	// ���ɱ�ǩ
	printf("��ʼ���ɱ�ǩ����...\n");
	for (int i = 1; i <= 10; i++)
	{		
		// train label
		Mat tmep_label_train = Mat::ones(train_rows * row_sample, 1, CV_32FC1); // ��ʱ��ŵ�ǰ��ǩ�ľ���
		tmep_label_train = tmep_label_train * (i - 1); // ��ǩ��0��ʼ
		Mat temp = trainLabel.rowRange((i - 1)* train_rows * row_sample, i * train_rows * row_sample);
		tmep_label_train.copyTo(temp); // ����ʱ��ǩ���Ƶ�trainLabel��Ӧ������Ϊǳ�������ı�temp���ı�trainLabel

		// test label
		Mat tmep_label_test = Mat::ones(test_rows * row_sample, 1, CV_32FC1);
		tmep_label_test = tmep_label_test * (i - 1);
		temp = testLabel.rowRange((i - 1)* test_rows * row_sample, i * test_rows * row_sample);
		tmep_label_test.copyTo(temp);
	}
	printf("��ǩ����������\n\n");
	//printf("trainLabel(1,400,401,800,801,4000) = %f, %f, %f, %f, %f, %f\n", trainLabel.at<float>(0), trainLabel.at<float>(399), trainLabel.at<float>(400), trainLabel.at<float>(799), trainLabel.at<float>(800), trainLabel.at<float>(3999));
	//printf("testLabel (1,100,101,200,201,1000) = %f, %f, %f, %f, %f, %f\n", testLabel.at<float>(0), testLabel.at<float>(99), testLabel.at<float>(100), testLabel.at<float>(199), testLabel.at<float>(200), testLabel.at<float>(999));
	//cv::waitKey();
}