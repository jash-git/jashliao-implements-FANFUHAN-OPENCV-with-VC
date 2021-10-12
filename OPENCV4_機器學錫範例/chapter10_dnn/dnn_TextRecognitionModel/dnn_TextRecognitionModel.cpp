// dnn_TextRecognitionModel.cpp : �������̨Ӧ�ó������ڵ㡣
//
// https://github.com/opencv/opencv/blob/master/samples/dnn/scene_text_recognition.cpp
// https://arxiv.org/abs/1507.05717
// https://www.cnblogs.com/wj-1314/p/9901029.html

#include "stdafx.h"
#include <iostream>
#include <fstream>

#include <opencv.hpp>
#include <opencv2/dnn/dnn.hpp>

using namespace cv;
using namespace cv::dnn;

cv::String convertForEval(cv::String &input); // ������Ԥ��ת��ΪСд����ɾ�������ַ�

int main()
{
	// [1]��ʼ����������
	// rcnn����Ȩ��.onnx�ļ�·��
	cv::String modelPath = "D:/models/TextRecognitionModel_google/crnn_cs.onnx";
	// ʶ��ʵ��·��
	cv::String vocPath = "D:/models/TextRecognitionModel_google/alphabet_36.txt";
	int imreadRGB = 1; // 0: �ԻҶ�ͼ��ʽ��ȡͼ��; 1: �Բ�ɫͼ��ʽ��ȡͼ��
	bool evaluate = false; // false: Ԥ�ⵥ��ͼ��; true: ʹ�û�׼��֤������
						   // ��׼��֤��·��
	cv::String evalDataPath = "D:/models/TextRecognitionModel_google/evaluation_data_rec";

	// [2]��������
	CV_Assert(!modelPath.empty());
	cv::dnn::TextRecognitionModel recognizer(modelPath);

	// [3]����ʵ�
	CV_Assert(!vocPath.empty());
	std::ifstream vocFile;
	vocFile.open(samples::findFile(vocPath));
	CV_Assert(vocFile.is_open());
	cv::String vocLine;
	std::vector<String> vocabulary;
	while (std::getline(vocFile, vocLine)) {
		vocabulary.push_back(vocLine);
	}
	recognizer.setVocabulary(vocabulary);
	recognizer.setDecodeType("CTC-greedy");

	// [3]���ò���
	double scale = 1.0 / 127.5;
	cv::Scalar mean = cv::Scalar(127.5, 127.5, 127.5);
	cv::Size inputSize = cv::Size(100, 32);
	recognizer.setInputParams(scale, inputSize, mean);

	if (evaluate) // ��׼��֤������
	{
		CV_Assert(!evalDataPath.empty());
		cv::String gtPath = evalDataPath + "/test_gts.txt";
		std::ifstream evalGts;
		evalGts.open(gtPath);
		CV_Assert(evalGts.is_open());

		cv::String gtLine;
		int cntRight = 0, cntAll = 0;
		cv::TickMeter timer;
		timer.reset();

		while (std::getline(evalGts, gtLine)) {
			size_t splitLoc = gtLine.find_first_of(' ');
			cv::String imgPath = evalDataPath + '/' + gtLine.substr(0, splitLoc);
			cv::String gt = gtLine.substr(splitLoc + 1);

			// [4]����
			cv::Mat frame = imread(samples::findFile(imgPath), imreadRGB);
			CV_Assert(!frame.empty());
			timer.start();
			std::string recognitionResult = recognizer.recognize(frame);
			cv::imshow("evaluate image", frame);
			std::cout << "Predition: '" << recognitionResult << "'" << std::endl;
			cv::waitKey();
			timer.stop();

			if (gt == convertForEval(recognitionResult))
				cntRight++;
			cntAll++;
		}
		std::cout << "Accuracy(%): " << (double)(cntRight) / (double)(cntAll) << std::endl;
		std::cout << "Average Inference Time(ms): " << timer.getTimeMilli() / (double)(cntAll) << std::endl;
	}
	else // ���Ե���ͼ��
	{
		// ��������
		static const std::string winName = "Input Cropped Image";
		// [1]����ͼ�񣨴˴����뾭��detectionģ�͵��ı����� 
		cv::Mat frame = cv::imread("acmilan_txt.jpg", imreadRGB);
		CV_Assert(!frame.empty());
		// [2]ʶ��
		std::string recognitionResult = recognizer.recognize(frame);
		cv::imshow(winName, frame);
		std::cout << "Predition: '" << recognitionResult << "'" << std::endl;
		cv::waitKey();
	}
	return 0;
}

// ��Ԥ��ת��ΪСд����ɾ�������ַ�
cv::String convertForEval(cv::String & input)
{
	cv::String output;
	for (uint i = 0; i < input.length(); i++) {
		char ch = input[i];
		if ((int)ch >= 97 && (int)ch <= 122) {
			output.push_back(ch);
		}
		else if ((int)ch >= 65 && (int)ch <= 90) {
			output.push_back((char)(ch + 32));
		}
		else {
			continue;
		}
	}
	return output;
}


//String convertForEval(cv::String &input);
//
//int main()
//{
//	// Path to a binary .onnx file contains trained CRNN text recognition model
//	cv::String modelPath = "D:/models/TextRecognitionModel_google/crnn_cs.onnx";
//	// Path to recognition vocabulary
//	cv::String vocPath = "D:/models/TextRecognitionModel_google/alphabet_36.txt"; // alphabet_36.txt
//	int imreadRGB = 1; // 0: imread with flags=IMREAD_GRAYSCALE; 1: imread with flags=IMREAD_COLOR.
//	bool evaluate = false; // false: predict with input images; true: evaluate on benchmarks.
//	cv::String evalDataPath = "D:/models/TextRecognitionModel_google/evaluation_data_rec"; // Path to benchmarks for evaluation
//						   
//	// Load the network
//	CV_Assert(!modelPath.empty());
//	cv::dnn::TextRecognitionModel recognizer(modelPath);
//
//	// Load vocabulary
//	CV_Assert(!vocPath.empty());
//	std::ifstream vocFile;
//	vocFile.open(samples::findFile(vocPath));
//	CV_Assert(vocFile.is_open());
//	String vocLine;
//	std::vector<String> vocabulary;
//	while (std::getline(vocFile, vocLine)) {
//		vocabulary.push_back(vocLine);
//	}
//	recognizer.setVocabulary(vocabulary);
//	recognizer.setDecodeType("CTC-greedy");
//
//	// Set parameters
//	double scale = 1.0 / 127.5;
//	Scalar mean = Scalar(127.5, 127.5, 127.5);
//	Size inputSize = Size(100, 32);
//	recognizer.setInputParams(scale, inputSize, mean);
//
//	if (evaluate)
//	{
//		// For evaluation
//		//String evalDataPath = parser.get<String>("evalDataPath");
//		CV_Assert(!evalDataPath.empty());
//		String gtPath = evalDataPath + "/test_gts.txt";
//		std::ifstream evalGts;
//		evalGts.open(gtPath);
//		CV_Assert(evalGts.is_open());
//
//		String gtLine;
//		int cntRight = 0, cntAll = 0;
//		TickMeter timer;
//		timer.reset();
//
//		while (std::getline(evalGts, gtLine)) {
//			size_t splitLoc = gtLine.find_first_of(' ');
//			String imgPath = evalDataPath + '/' + gtLine.substr(0, splitLoc);
//			String gt = gtLine.substr(splitLoc + 1);
//
//			// Inference
//			Mat frame = imread(samples::findFile(imgPath), imreadRGB);
//			CV_Assert(!frame.empty());
//			timer.start();
// 			std::string recognitionResult = recognizer.recognize(frame);
//			cv::imshow("evaluate image", frame);
//			std::cout << "Predition: '" << recognitionResult << "'" << std::endl;
//			cv::waitKey();
//			timer.stop();
//
//			if (gt == convertForEval(recognitionResult))
//				cntRight++;
//
//			cntAll++;
//		}
//		std::cout << "Accuracy(%): " << (double)(cntRight) / (double)(cntAll) << std::endl;
//		std::cout << "Average Inference Time(ms): " << timer.getTimeMilli() / (double)(cntAll) << std::endl;
//	}
//	else
//	{
//		// Create a window
//		static const std::string winName = "Input Cropped Image";
//		// Open an image file
//		// �˴����뾭��detectionģ�͵��ı�����
//		cv::Mat frame = cv::imread("acmilan_txt.jpg", imreadRGB);
//		CV_Assert(!frame.empty());
//
//		// Recognition
//		std::string recognitionResult = recognizer.recognize(frame);
//
//		imshow(winName, frame);
//		std::cout << "Predition: '" << recognitionResult << "'" << std::endl;
//		waitKey();
//	}
//
//	return 0;
//}
//
//// Convert the predictions to lower case, and remove other characters.
//// Only for Evaluation
//String convertForEval(String & input)
//{
//	String output;
//	for (uint i = 0; i < input.length(); i++) {
//		char ch = input[i];
//		if ((int)ch >= 97 && (int)ch <= 122) {
//			output.push_back(ch);
//		}
//		else if ((int)ch >= 65 && (int)ch <= 90) {
//			output.push_back((char)(ch + 32));
//		}
//		else {
//			continue;
//		}
//	}
//
//	return output;
//}

