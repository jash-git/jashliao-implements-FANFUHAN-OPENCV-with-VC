// dnn_googlenet.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
//#include <iostream>
#include <fstream>
#include "opencv.hpp"
#include "dnn.hpp"

using namespace std;
//using namespace cv;
cv::String model = "D:/models/googlenet/bvlc_googlenet.caffemodel"; // ģ��Ȩ���ļ�
cv::String config = "D:/models/googlenet/bvlc_googlenet.prototxt"; // ģ�������ļ�
cv::String framework = "caffe"; // ���ѧϰ���
cv::String label_file = "D:/models/googlenet/synset_words.txt"; // ImageNet��ǩ�ļ�
vector<cv::String> readLabels();

int main()
{
	// [1]����ͼ��
	cv::Mat image;
	image = cv::imread("space_shuttle.jpg");
	if (image.empty())
	{		
		printf("image loading error!\n");
		system("pause");
		return -1;
	}
	cv::imshow("image", image);
	cv::waitKey(33);

	// [2]����ģ��
	cv::dnn::Net net = cv::dnn::readNet(config, model, framework);
	if (net.empty())
	{
		printf("model loading error!\n");
		system("pause");
		return -1;
	}
	cv::Mat inputBlob = cv::dnn::blobFromImage(
		image, 
		1.0f, 
		cv::Size(224, 224), 
		cv::Scalar(104, 117, 123), 
		true, 
		false);

	// [3]ͼ����ࣨǰ�򴫲���
	cv::Mat prob;
	net.setInput(inputBlob, "data");
	prob = net.forward("prob");
	
	// [4]��ȡ�����������
	vector<cv::String> labels = readLabels();
	cv::Mat probMat = prob.reshape(1, 1);
	cv::Point classNumber;
	double classProb;
	cv::minMaxLoc(probMat, NULL, &classProb, NULL, &classNumber);
	int classidx = classNumber.x;
	printf("class: %s, probability: %.2f\n", labels.at(classidx).c_str(), classProb);
	
	// [5]��ʾ�ı�
	cv::putText(
		image, 
		labels.at(classidx), 
		cv::Point(30, 30), 
		cv::FONT_HERSHEY_COMPLEX, 
		1.0, 
		cv::Scalar(0, 0, 255), 
		2, 
		8);
	cv::imshow("Image Classification", image);
	cv::waitKey(0);


	// USE ClassificationModel
	cv::dnn::ClassificationModel classification_model(model, config);
	cv::dnn::ClassificationModel classification_model(net);
	classification_model.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
	classification_model.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);
	std::pair<int, float> result;
	result = classification_model.classify(image);
	int classID = result.first;
	float classScore = result.second;
	printf("class: %s, probability: %.2f\n", labels.at(classID).c_str(), classScore);
	cv::waitKey();


	return 0;
}

// ��ȡImageNet��ǩ�ļ�
std::vector<cv::String> readLabels()
{
	std::vector<cv::String> classNames;
	std::ifstream fp(label_file);
	if (!fp.is_open())
	{
		printf("could not open file...\n");
		exit(-1);
	}
	std::string name;
	while (!fp.eof())
	{
		std::getline(fp, name);
		if (name.length())
			classNames.push_back(name);
	}
	fp.close();
	return classNames;
}
