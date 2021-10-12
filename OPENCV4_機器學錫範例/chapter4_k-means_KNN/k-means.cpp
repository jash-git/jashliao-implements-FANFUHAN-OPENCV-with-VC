// k-means.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

//#define EXAMPLE1

int main()
{
	Mat img = imread("girl.jpg", 1);
	Mat samples = img.reshape(0, img.cols*img.rows); // ͼ��ת����sampleCount��*3ͨ���ľ���
	printf("image  : h = %d, w = %d, c = %d\n", img.rows, img.cols, img.channels());
	
	//ת��ΪCV_32FC3������
	samples.convertTo(samples, CV_32FC3); // or CV_32F works (too)
	printf("samples: h = %d, w = %d, c = %d\n", samples.rows, samples.cols, samples.channels());

	//define criteria, number of clusters(K) 
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0);//��ֹ����
	int K = 4;   // ���������:4,8,16
	Mat labels;  // ��������������	
	Mat centers; // ��������
	
	// ִ��kmeans()
	double compactness = kmeans(samples, K, labels, criteria, 3, KMEANS_PP_CENTERS, centers);

	// ����������תΪint��
	centers.convertTo(centers, CV_8UC3);
	// ���վ�������ǩlabels����samples���·���BGRֵ
	samples.convertTo(samples, CV_8UC3);
	cout << endl << "--- centers ---" << endl;
	cout << centers.at<Vec3b>(0, 0) << endl;
	cout << centers.at<Vec3b>(1, 0) << endl;
	cout << centers.at<Vec3b>(2, 0) << endl;
	cout << centers.at<Vec3b>(3, 0) << endl;

	cout << endl << "--- samples original ---" << endl;
	cout << samples.at<Vec3b>(1, 0) << endl; // 8U ���͵� RGB ��ɫͼ��ʹ�� <Vec3b>����Mat����ֵ
	cout << samples.at<Vec3b>(100, 0) << endl;
	cout << samples.at<Vec3b>(1000, 0) << endl;

	cout << endl << "--- label ---" << endl;
	cout << labels.at<int>(1) << endl; // 8U ���͵� RGB ��ɫͼ��ʹ�� <Vec3b>����Mat����ֵ
	cout << labels.at<int>(100) << endl;
	cout << labels.at<int>(1000) << endl;

	// ��label��ǩ����Ϊsamples��ֵ��ʵ��ɫ��ѹ��
	for (int i = 0; i < labels.rows; i++)
	{
		int cluster = labels.at<int>(i);
		// Vec3bΪOpenCV��CV_8UC3���͵�RGB��ɫͼ����������
		samples.at<Vec3b>(i, 0) = centers.at<Vec3b>(cluster, 0);
	}
	
	cout << endl << "--- samples cluttered ---" << endl;
	cout << samples.at<Vec3b>(1, 0) << endl;
	cout << samples.at<Vec3b>(100, 0) << endl;
	cout << samples.at<Vec3b>(1000, 0) << endl;

	// 4.���/��ʾ������
	// ��samplesת��img�ߴ�
	Mat img_out = samples.reshape(0, img.rows); // ͼ��ת����sampleCount��*3ͨ���ľ���
	cout << "Compactness: " << compactness << endl;
	imshow("image", img);
	imshow("clusters", img_out);
	// ����ͼ��
	stringstream ss;
	ss << K;
	string str = ss.str();
	string image_save_name = str + "_cluter.jpg";
	imwrite(image_save_name, img_out);
	waitKey();
	return 0;
}



#ifdef EXAMPLE1
int main()
{
	// 1. ��ʼ������
	const int MAX_CLUSTERS = 5; // ��������
	Scalar colorTab[] =
	{
		Scalar(0, 0, 255),
		Scalar(0,255,0),
		Scalar(255,100,100),
		Scalar(255,0,255),
		Scalar(0,255,255)
	};
	Mat img(500, 500, CV_8UC3); // �½�����
	img = Scalar::all(255);     // ����������Ϊ��ɫ
	RNG rng(12345);  //�����������
	// ��ѭ��
	for (;;)
	{
		// ��ʼ�������
		int k, clusterCount = rng.uniform(2, MAX_CLUSTERS + 1); // ��[2, MAX_CLUSTERS + 1)���䣬�������һ������
		// ��ʼ��������
		int i, sampleCount = rng.uniform(1, 1001); // ��[1, 1001)���䣬�������һ������
		Mat points(sampleCount, 1, CV_32FC2); //  ������������sampleCount��*1�У������ͣ�2ͨ��
		Mat labels; // ��������������
		clusterCount = MIN(clusterCount, sampleCount);  // ���������<������
		std::vector<Point2f> centers;
		cout << points.at<float>(0,0) << endl;
		cout << points.at<float>(10,0) << endl;
		cout << "---1---" << endl;
		// 2. ���������������
		/* generate random sample from multigaussian distribution */
		for (k = 0; k < clusterCount; k++)
		{
			Point center;
			center.x = rng.uniform(0, img.cols);
			center.y = rng.uniform(0, img.rows);
			// ������pointsָ���н��и�ֵ
			Mat pointChunk = points.rowRange(k*sampleCount / clusterCount,
				k == clusterCount - 1 ? sampleCount :
				(k + 1)*sampleCount / clusterCount);
			cout << points.at<float>(0, 0) << endl;
			cout << points.at<float>(10, 0) << endl;
			cout << "---2---" << endl;
			// rng.fill����������center��Ϊ���ģ�������˹�ֲ��������(λ�õ㣩������λ�õ㱣���ھ���pointChunk�С�
			rng.fill(pointChunk, RNG::NORMAL, Scalar(center.x, center.y), Scalar(img.cols*0.05, img.rows*0.05));
		}
		//����points�е�ֵ��
		//�ڶ���������ʾ�������Ԫ�ص��������������ӣ�
		//�ܵĽ�������dst.rows*dst.cols*iterFactor��
		//�����������Ǹ����������������ѡ������Ԫ�ؽ�����
		cout << points.at<float>(0, 0) << endl;
		cout << points.at<float>(10, 0) << endl;
		cout <<"---3---" << endl;
		randShuffle(points, 1, &rng);
		cout << points.at<float>(0, 0) << endl;
		cout << points.at<float>(10, 0) << endl;
		cout << "---4---" << endl;
		
		// 3. ִ��k-means()�㷨
		// ���룺pointsΪ������������ÿһ��Ϊһ������
		// ���룺clusterCountΪ�����
		// �����labels��һ��һά������size��pointsһ�����洢ÿ����������ִ��kmeans�㷨������ǩ��ֵΪ0��clusterCount-1
		// ���룺TermCriteria()������ֹ������
		//		TermCriteria::COUNT���������ﵽ����������ʱ��ֹ������Ϊint max_Count=10
		//		TermCriteria::EPS���������ﵽ��������ʱ��ֹ������Ϊdouble epsilon=1.0
		// �����centers�д�ŵ���kmeans�㷨������ÿ����������λ��
		// ����ֵ��compactness������ɺ���������Զ���ֵ
		double compactness = kmeans(points, clusterCount, labels,
			TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0),
			3, KMEANS_PP_CENTERS, centers);

		// 4.���ƾ�����
		for (i = 0; i < sampleCount; i++)
		{
			int clusterIdx = labels.at<int>(i);
			Point ipt = points.at<Point2f>(i);
			circle(img, ipt, 2, colorTab[clusterIdx], FILLED, LINE_AA);
		}
		for (i = 0; i < (int)centers.size(); ++i)
		{
			Point2f c = centers[i];
			circle(img, c, 40, colorTab[i], 1, LINE_AA);
		}
		// 5.���/��ʾ������
		cout << "Compactness: " << compactness << endl;
		imshow("clusters", img);
		char key = (char)waitKey();
		if (key == 27 || key == 'q' || key == 'Q') // 'ESC'
			break;
	}
	return 0;
}

#endif