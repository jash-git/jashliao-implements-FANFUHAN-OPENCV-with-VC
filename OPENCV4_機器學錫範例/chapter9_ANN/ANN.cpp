// ANN.cpp : �������̨Ӧ�ó������ڵ㡣
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
	printf("%s �� %s���� ��ʱ %d s\n", pszContainerName, pszOperator, lElapsetime/1000);
}


int main(int argc, _TCHAR* argv[])
{	
	// MNIST���ݼ���������
	const int NUMBER_OF_TRAIN_IMAGE = 60000;
	const int NUMBER_OF_TRAIN_LABEL = 60000;
	const int NUMBER_OF_TEST_IMAGE  = 10000;
	const int NUMBER_OF_TEST_LABEL  = 10000;
	// MNISTԭʼ�ļ���
	std::string trainImageFile = "res\\train-images.idx3-ubyte";
	std::string trainLabelFile = "res\\train-labels.idx1-ubyte";
	std::string testImageFile  = "res\\t10k-images.idx3-ubyte";
	std::string testLabelFile  = "res\\t10k-labels.idx1-ubyte";
	// ��ȡMNIST���� 
	cv::Mat trainImageMat = ReadImages(trainImageFile);//��ͼ�����Mat�У�ÿ��һ��ͼ��
	cv::Mat trainLabelMat = ReadLabels(trainLabelFile);//��ͼ�����Mat�У�ÿ��һ����ǩ
	cv::Mat testImageMat  = ReadImages(testImageFile); //��ͼ�����Mat�У�ÿ��һ��ͼ��
	cv::Mat testLabelMat  = ReadLabels(testLabelFile); //��ͼ�����Mat�У�ÿ��һ����ǩ
	
	//cv::Mat trainImageMatUse = trainImageMat.rowRange(0, NUMBER_OF_TRAIN_IMAGE);//��ͼ���ȡ��Mat�У�ÿһ��Ϊһ��ͼ��
	//cv::Mat trainLabelMatUse = trainLabelMat.rowRange(0, NUMBER_OF_TRAIN_IMAGE);//��ͼ���ȡ��Mat�У�ÿһ��Ϊһ����ǩ
	//cv::Mat testImageMatUse = testImageMat.rowRange(0, NUMBER_OF_TEST_IMAGE); //��ͼ���ȡ��Mat�У�ÿһ��Ϊһ��ͼ��
	//cv::Mat testLabelMatUse = testLabelMat.rowRange(0, NUMBER_OF_TEST_IMAGE); //��ͼ���ȡ��Mat�У�ÿһ��Ϊһ����ǩ

	// ����һ��ͼ�񣬲鿴���ݶ�ȡ�Ƿ���ȷ
	bool draw_one_img = false;
	if (draw_one_img)
	{
		int n = 6;//read the nth image
		cv::Mat singleImage = ReadSingleImage(trainImageMat, n-1);// start from 0
		// ��ѵ������6����ǩ����0��ʼ������
		char c_singleLabel = trainLabelMat.at<char>(n-1);
		cout << "the label of " << n << "th image is: " << (int)c_singleLabel << endl;// ��charǿ��ת����int�����
		cv::imshow("image", singleImage);
		cv::waitKey();
	}

	// ׼��ѵ��������Լ�
	cv::Mat trainLabelMatVec, testLabelMatVec;// Vector��ʽ�ı�ǩ
	trainImageMat.convertTo(trainImageMat, CV_32F); // Ҫ��ʹ��CV_32F����
	testImageMat.convertTo(testImageMat, CV_32F); // Ҫ��ʹ��CV_32F����
	trainLabelMatVec = CvtLabelData2Vec(trainLabelMat); // ��labelת��Ϊ10x1������ʽ
	testLabelMatVec = CvtLabelData2Vec(testLabelMat); 
	
	// ��ӡǰ6�����ݵı�ǩ
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

	// ���ݼ�ת��
	Ptr<TrainData> trainData = TrainData::create(trainImageMat, ROW_SAMPLE, trainLabelMatVec);
	Ptr<TrainData> testData = TrainData::create(testImageMat, ROW_SAMPLE, testLabelMatVec);
	// ����ģ��
	Ptr<cv::ml::ANN_MLP>  ANN_model = cv::ml::ANN_MLP::create();
	Ptr<cv::ml::ANN_MLP>  ANN_model_load = cv::ml::ANN_MLP::create();
	// ���ò���
	//cv::Mat layerSizes = (cv::Mat_<int>(1, 3) << 784, 10, 10); //3�㣺����㣬1�����ز������㣬��Ԫ�ֱ�Ϊ 784, 100, 10
	cv::Mat layerSizes = (cv::Mat_<int>(1, 4) << 784, 30, 20, 10); //4�㣺����㣬1�����ز������㣬��Ԫ�ֱ�Ϊ 784, 100, 10, 10
		
	ANN_model->setLayerSizes(layerSizes);
	ANN_model->setActivationFunction(ANN_MLP::SIGMOID_SYM,1,1);  //2.5, 1.0
	ANN_model->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 300, FLT_EPSILON));
	ANN_model->setTrainMethod(ANN_MLP::RPROP);
	
	// ѵ��
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
		// ��ʱ��ʼ
		clock_t clockBegin, clockEnd;
		clockBegin = clock();
		std::cout << "ANN trainning..." << std::endl << std::endl;
		ANN_model->train(trainData);// ѵ��Ҫ���ǩά�������������Ԫ��������˱�ǩά��=10��Ϊ������ʽ[0 0 0...1],...,[1 0 0 0...0]��������ʽ
		std::cout << "-done" << std::endl << std::endl;
		clockEnd = clock();
		PrintfContainerElapseTime("ANN", "trainnig ", clockEnd - clockBegin);

		// ����ģ��
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

	// ����
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

	bool dispFlag = false; // ��ʾÿ��Ԥ��Ľ��ͼ��
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
			predictResult = getResponse(responseMat); // predict result in 0-9���˺���������calcError()����ȡ��
			stream.str("");// ���
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
			std::cout << "the test sample " << i << "   label  :  " << (int)c_singleLabel << std::endl;// ��charǿ��ת����int�����
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