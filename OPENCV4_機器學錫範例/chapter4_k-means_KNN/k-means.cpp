// k-means.cpp : 定义控制台应用程序的入口点。
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
	Mat samples = img.reshape(0, img.cols*img.rows); // 图像转换成sampleCount行*3通道的矩阵
	printf("image  : h = %d, w = %d, c = %d\n", img.rows, img.cols, img.channels());
	
	//转换为CV_32FC3浮点型
	samples.convertTo(samples, CV_32FC3); // or CV_32F works (too)
	printf("samples: h = %d, w = %d, c = %d\n", samples.rows, samples.cols, samples.channels());

	//define criteria, number of clusters(K) 
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0);//终止条件
	int K = 4;   // 聚类类别数:4,8,16
	Mat labels;  // 聚类结果索引矩阵	
	Mat centers; // 聚类中心
	
	// 执行kmeans()
	double compactness = kmeans(samples, K, labels, criteria, 3, KMEANS_PP_CENTERS, centers);

	// 将聚类中心转为int型
	centers.convertTo(centers, CV_8UC3);
	// 按照聚类结果标签labels，对samples重新分配BGR值
	samples.convertTo(samples, CV_8UC3);
	cout << endl << "--- centers ---" << endl;
	cout << centers.at<Vec3b>(0, 0) << endl;
	cout << centers.at<Vec3b>(1, 0) << endl;
	cout << centers.at<Vec3b>(2, 0) << endl;
	cout << centers.at<Vec3b>(3, 0) << endl;

	cout << endl << "--- samples original ---" << endl;
	cout << samples.at<Vec3b>(1, 0) << endl; // 8U 类型的 RGB 彩色图像使用 <Vec3b>访问Mat像素值
	cout << samples.at<Vec3b>(100, 0) << endl;
	cout << samples.at<Vec3b>(1000, 0) << endl;

	cout << endl << "--- label ---" << endl;
	cout << labels.at<int>(1) << endl; // 8U 类型的 RGB 彩色图像使用 <Vec3b>访问Mat像素值
	cout << labels.at<int>(100) << endl;
	cout << labels.at<int>(1000) << endl;

	// 按label标签重新为samples赋值，实现色彩压缩
	for (int i = 0; i < labels.rows; i++)
	{
		int cluster = labels.at<int>(i);
		// Vec3b为OpenCV中CV_8UC3类型的RGB彩色图像数据类型
		samples.at<Vec3b>(i, 0) = centers.at<Vec3b>(cluster, 0);
	}
	
	cout << endl << "--- samples cluttered ---" << endl;
	cout << samples.at<Vec3b>(1, 0) << endl;
	cout << samples.at<Vec3b>(100, 0) << endl;
	cout << samples.at<Vec3b>(1000, 0) << endl;

	// 4.输出/显示聚类结果
	// 将samples转回img尺寸
	Mat img_out = samples.reshape(0, img.rows); // 图像转换成sampleCount行*3通道的矩阵
	cout << "Compactness: " << compactness << endl;
	imshow("image", img);
	imshow("clusters", img_out);
	// 保存图像
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
	// 1. 初始化参数
	const int MAX_CLUSTERS = 5; // 最大类别数
	Scalar colorTab[] =
	{
		Scalar(0, 0, 255),
		Scalar(0,255,0),
		Scalar(255,100,100),
		Scalar(255,0,255),
		Scalar(0,255,255)
	};
	Mat img(500, 500, CV_8UC3); // 新建画布
	img = Scalar::all(255);     // 将画布设置为白色
	RNG rng(12345);  //随机数产生器
	// 主循环
	for (;;)
	{
		// 初始化类别数
		int k, clusterCount = rng.uniform(2, MAX_CLUSTERS + 1); // 在[2, MAX_CLUSTERS + 1)区间，随机生成一个整数
		// 初始化样本数
		int i, sampleCount = rng.uniform(1, 1001); // 在[1, 1001)区间，随机生成一个整数
		Mat points(sampleCount, 1, CV_32FC2); //  输入样本矩阵：sampleCount行*1列，浮点型，2通道
		Mat labels; // 聚类结果索引矩阵
		clusterCount = MIN(clusterCount, sampleCount);  // 聚类类别数<样本数
		std::vector<Point2f> centers;
		cout << points.at<float>(0,0) << endl;
		cout << points.at<float>(10,0) << endl;
		cout << "---1---" << endl;
		// 2. 随机生成输入样本
		/* generate random sample from multigaussian distribution */
		for (k = 0; k < clusterCount; k++)
		{
			Point center;
			center.x = rng.uniform(0, img.cols);
			center.y = rng.uniform(0, img.rows);
			// 对样本points指定行进行赋值
			Mat pointChunk = points.rowRange(k*sampleCount / clusterCount,
				k == clusterCount - 1 ? sampleCount :
				(k + 1)*sampleCount / clusterCount);
			cout << points.at<float>(0, 0) << endl;
			cout << points.at<float>(10, 0) << endl;
			cout << "---2---" << endl;
			// rng.fill函数，会以center点为中心，产生高斯分布的随机点(位置点），并把位置点保存在矩阵pointChunk中。
			rng.fill(pointChunk, RNG::NORMAL, Scalar(center.x, center.y), Scalar(img.cols*0.05, img.rows*0.05));
		}
		//打乱points中的值，
		//第二个参数表示随机交换元素的数量的缩放因子，
		//总的交换次数dst.rows*dst.cols*iterFactor，
		//第三个参数是个随机发生器，决定选那两个元素交换。
		cout << points.at<float>(0, 0) << endl;
		cout << points.at<float>(10, 0) << endl;
		cout <<"---3---" << endl;
		randShuffle(points, 1, &rng);
		cout << points.at<float>(0, 0) << endl;
		cout << points.at<float>(10, 0) << endl;
		cout << "---4---" << endl;
		
		// 3. 执行k-means()算法
		// 输入：points为输入样本矩阵，每一行为一个样本
		// 输入：clusterCount为类别数
		// 输出：labels是一个一维矩阵，其size和points一样，存储每个输入样本执行kmeans算法后的类标签，值为0到clusterCount-1
		// 输入：TermCriteria()迭代终止条件：
		//		TermCriteria::COUNT：当迭代达到最大迭代次数时终止，参数为int max_Count=10
		//		TermCriteria::EPS：当迭代达到期望精度时终止，参数为double epsilon=1.0
		// 输出：centers中存放的是kmeans算法结束后每个类别的中心位置
		// 返回值：compactness聚类完成后的类别紧凑性度量值
		double compactness = kmeans(points, clusterCount, labels,
			TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0),
			3, KMEANS_PP_CENTERS, centers);

		// 4.绘制聚类结果
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
		// 5.输出/显示聚类结果
		cout << "Compactness: " << compactness << endl;
		imshow("clusters", img);
		char key = (char)waitKey();
		if (key == 27 || key == 'q' || key == 'Q') // 'ESC'
			break;
	}
	return 0;
}

#endif