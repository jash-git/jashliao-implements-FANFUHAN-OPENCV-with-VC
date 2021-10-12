// ANN.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "opencv.hpp"
#include "myMnistReader.h"
#include <fstream> 
#include <ctime> 

using namespace std;
using namespace cv;
using namespace ml;

void PrintfContainerElapseTime(char *pszContainerName, char *pszOperator, long lElapsetime)
{
	printf("%s 的 %s操作 用时 %d s\n", pszContainerName, pszOperator, lElapsetime/1000);
}


int main(int argc, _TCHAR* argv[])
{	
	// MNIST数据集的样本数
	const int NUMBER_OF_TRAIN_IMAGE = 60000;
	const int NUMBER_OF_TRAIN_LABEL = 60000;
	const int NUMBER_OF_TEST_IMAGE  = 10000;
	const int NUMBER_OF_TEST_LABEL  = 10000;
	// MNIST原始文件名
	std::string trainImageFile = "res\\train-images.idx3-ubyte";
	std::string trainLabelFile = "res\\train-labels.idx1-ubyte";
	std::string testImageFile  = "res\\t10k-images.idx3-ubyte";
	std::string testLabelFile  = "res\\t10k-labels.idx1-ubyte";
	// 读取MNIST数据 
	cv::Mat trainImageMat = ReadImages(trainImageFile);//将图像读到Mat中，每行一幅图像
	cv::Mat trainLabelMat = ReadLabels(trainLabelFile);//将图像读到Mat中，每列一个标签
	cv::Mat testImageMat  = ReadImages(testImageFile); //将图像读到Mat中，每行一幅图像
	cv::Mat testLabelMat  = ReadLabels(testLabelFile); //将图像读到Mat中，每列一个标签
	
	//cv::Mat trainImageMatUse = trainImageMat.rowRange(0, NUMBER_OF_TRAIN_IMAGE);//将图像读取到Mat中，每一行为一幅图像
	//cv::Mat trainLabelMatUse = trainLabelMat.rowRange(0, NUMBER_OF_TRAIN_IMAGE);//将图像读取到Mat中，每一列为一个标签
	//cv::Mat testImageMatUse = testImageMat.rowRange(0, NUMBER_OF_TEST_IMAGE); //将图像读取到Mat中，每一行为一幅图像
	//cv::Mat testLabelMatUse = testLabelMat.rowRange(0, NUMBER_OF_TEST_IMAGE); //将图像读取到Mat中，每一列为一个标签

	// 绘制一幅图像，查看数据读取是否正确
	bool draw_one_img = false;
	if (draw_one_img)
	{
		int n = 6;//read the nth image
		cv::Mat singleImage = ReadSingleImage(trainImageMat, n-1);// start from 0
		// 读训练集第6个标签（从0开始计数）
		char c_singleLabel = trainLabelMat.at<char>(n-1);
		cout << "the label of " << n << "th image is: " << (int)c_singleLabel << endl;// 将char强制转换成int型输出
		cv::imshow("image", singleImage);
		cv::waitKey();
	}

	// 准备训练集与测试集
	cv::Mat trainLabelMatVec, testLabelMatVec;// Vector形式的标签
	trainImageMat.convertTo(trainImageMat, CV_32F); // 要求使用CV_32F数据
	testImageMat.convertTo(testImageMat, CV_32F); // 要求使用CV_32F数据
	trainLabelMatVec = CvtLabelData2Vec(trainLabelMat); // 将label转换为10x1向量形式
	testLabelMatVec = CvtLabelData2Vec(testLabelMat); 
	
	// 打印前6组数据的标签
	if (1)
	{
		std::cout << std::endl;
		std::cout << "label 1 = " << trainLabelMat.row(0) << ": " << trainLabelMatVec.row(0) << std::endl;
		std::cout << "label 2 = " << trainLabelMat.row(1) << ": " << trainLabelMatVec.row(1) << std::endl;
		std::cout << "label 3 = " << trainLabelMat.row(2) << ": " << trainLabelMatVec.row(2) << std::endl;
		std::cout << "label 4 = " << trainLabelMat.row(3) << ": " << trainLabelMatVec.row(3) << std::endl;
		std::cout << "label 5 = " << trainLabelMat.row(4) << ": " << trainLabelMatVec.row(4) << std::endl;
		std::cout << "label 6 = " << trainLabelMat.row(5) << ": " << trainLabelMatVec.row(5) << std::endl << std::endl;
	}

	// 数据集转换
	Ptr<TrainData> trainData = TrainData::create(trainImageMat, ROW_SAMPLE, trainLabelMatVec);
	Ptr<TrainData> testData = TrainData::create(testImageMat, ROW_SAMPLE, testLabelMatVec);
	// 创建模型
	Ptr<cv::ml::ANN_MLP>  ANN_model = cv::ml::ANN_MLP::create();
	Ptr<cv::ml::ANN_MLP>  ANN_model_load = cv::ml::ANN_MLP::create();
	// 设置参数
	//cv::Mat layerSizes = (cv::Mat_<int>(1, 3) << 784, 10, 10); //3层：输入层，1层隐藏层和输出层，神经元分别为 784, 100, 10
	cv::Mat layerSizes = (cv::Mat_<int>(1, 4) << 784, 30, 20, 10); //4层：输入层，1层隐藏层和输出层，神经元分别为 784, 100, 10, 10
		
	ANN_model->setLayerSizes(layerSizes);
	ANN_model->setActivationFunction(ANN_MLP::SIGMOID_SYM,1,1);  //2.5, 1.0
	ANN_model->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 300, FLT_EPSILON));
	ANN_model->setTrainMethod(ANN_MLP::RPROP);
	
	// 训练
	bool bIsLoadFlag = false;
	bool bIsSelect = true;
	std::string slection = "";
	while (bIsSelect)
	{
		std::cout << "Do you want to load a pre-trained model? (Y/N) ";
		std::cin >> slection;
		if (slection == "y" || slection == "Y")
		{
			bIsLoadFlag = true;
			bIsSelect = false;
		}
		if (slection == "n" || slection == "N")
		{
			bIsLoadFlag = false;
			bIsSelect = false;
		}
	}

	if (!bIsLoadFlag)
	{
		// 计时开始
		clock_t clockBegin, clockEnd;
		clockBegin = clock();
		std::cout << "ANN trainning..." << std::endl << std::endl;
		ANN_model->train(trainData);// 训练要求标签维数等于输出层神经元个数，因此标签维数=10，为如下形式[0 0 0...1],...,[1 0 0 0...0]的向量形式
		std::cout << "-done" << std::endl << std::endl;
		clockEnd = clock();
		PrintfContainerElapseTime("ANN", "trainnig ", clockEnd - clockBegin);

		// 保存模型
		cv::FileStorage fs("model\\ann.yml", FileStorage::WRITE);
		if (fs.isOpened())
		{
			ANN_model->save("model\\ann.yml");
			fs.release();
		}
		else
			std::cout << "failed to open model file ann.yml" << std::endl << std::endl;
	}
	else
	{
		ANN_model_load = ANN_MLP::load("model\\ann.yml");
		if (ANN_model_load->isTrained())
			std::cout << "load ann model successfully!" << std::endl << std::endl;
		else
			std::cout << "load ann model failed!" << std::endl << std::endl;
	}

	// 测试
	std::cout << std::endl << "ANN testing..." << std::endl << std::endl;
	Mat responseMat;
	char c_singleLabel;
	int predictResult;
	int correctNum = 0;
	cv::Mat singleTestImage;
	std::string strLabel;
	std::string strPredict;
	stringstream stream;
	cv::Mat calcErrResults;

	bool dispFlag = false; // 显示每次预测的结果图像
	for (int i = 0; i < testImageMat.rows; i++)
	{
		if (!bIsLoadFlag)
			ANN_model->predict(testImageMat.row(i), responseMat);
		else
			ANN_model_load->predict(testImageMat.row(i), responseMat);
			
		c_singleLabel = testLabelMat.at<char>(i);//start from 0 

		// display result 
		if (dispFlag)
		{
			// predict result
			predictResult = getResponse(responseMat); // predict result in 0-9，此函数可以用calcError()函数取代
			stream.str("");// 清空
			stream << predictResult;
			strPredict = "predict: " + stream.str();
			// test label
			stream.str("");
			stream << (int)c_singleLabel;
			strLabel = "label   : " + stream.str();
			// display both
			singleTestImage = ReadSingleImage(testImageMat, i);
			cv::resize(singleTestImage, singleTestImage, cv::Size(), 12, 12);
			cv::putText(singleTestImage, strLabel, cv::Point(10, 20), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255), 1);
			cv::putText(singleTestImage, strPredict, cv::Point(10, 50), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255), 1);
			cv::imshow("prediction", singleTestImage);
			// printf result
			std::cout << "the test sample " << i << "   label  :  " << (int)c_singleLabel << std::endl;// 将char强制转换成int型输出
			std::cout << "the test sample " << i << "   predict:  " << predictResult << std::endl << std::endl;
			cv::waitKey();
		}
		else
		{
			// predict result
			predictResult = getResponse(responseMat); 
		}		
		if ((int)c_singleLabel == predictResult)
			correctNum++;
	}
	//if (!bIsLoadFlag)
	//	std::cout << "the number of traning sample is  " << NUMBER_OF_TRAIN_IMAGE << std::endl;
	std::cout << "the number of test sample is   " << NUMBER_OF_TEST_IMAGE << std::endl;
	std::cout << "the accuracy is                " << (double)correctNum / NUMBER_OF_TEST_IMAGE << std::endl << std::endl;
	
	system("pause");
	return 0;
}