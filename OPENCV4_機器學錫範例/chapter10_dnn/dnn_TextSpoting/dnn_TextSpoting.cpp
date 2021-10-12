// dnn_TextSpoting.cpp : 定义控制台应用程序的入口点。
//

//https://github.com/opencv/opencv/blob/master/samples/dnn/scene_text_spotting.cpp

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <opencv.hpp>
#include <opencv2/dnn/dnn.hpp>

using namespace cv;
using namespace cv::dnn;

// 文本区域仿射变换预处理
void fourPointsTransform(const cv::Mat& frame, const cv::Point2f vertices[], cv::Mat& result);
bool sortPts(const cv::Point& p1, const cv::Point& p2);

int main()
{
	// [1]初始化参数
	// DB文本检测模型
	cv::String detModelPath = "D:/models/TextRecognitionModel_google/DB_TD500_resnet50.onnx";
	float binThresh = 0.3; 
	float polyThresh = 0.5;  
	double unclipRatio = 2.0; 
	uint maxCandidates = 200; 
	int height = 736; 
	int width = 736; 
	// CRNN文本识别模型
	cv::String recModelPath = "D:/models/TextRecognitionModel_google/crnn_cs_CN.onnx";
	cv::String vocPath = "D:/models/TextRecognitionModel_google/alphabet_3944.txt";
	int imreadRGB = 1;

	// [2]载入模型
	CV_Assert(!detModelPath.empty());
	cv::dnn::TextDetectionModel_DB detector(detModelPath);
	detector.setBinaryThreshold(binThresh)
		.setPolygonThreshold(polyThresh)
		.setUnclipRatio(unclipRatio)
		.setMaxCandidates(maxCandidates);

	CV_Assert(!recModelPath.empty());
	cv::dnn::TextRecognitionModel recognizer(recModelPath);

	// [3]载入词典
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

	// [4]设置检测参数
	double detScale = 1.0 / 255.0;
	cv::Size detInputSize = cv::Size(width, height);
	cv::Scalar detMean = cv::Scalar(122.67891434, 116.66876762, 104.00698793);
	detector.setInputParams(detScale, detInputSize, detMean);

	// [5]设置识别参数
	double recScale = 1.0 / 127.5;
	cv::Scalar recMean = Scalar(127.5);
	cv::Size recInputSize = Size(100, 32);
	recognizer.setInputParams(recScale, recInputSize, recMean);

	// 创建窗口
	static const std::string winName = "Text_Spotting";

	// [6]载入图像
	cv::Mat frame = cv::imread("acmilan.jpg");
	std::cout << frame.size << std::endl;

	// [7]推理
	std::vector< std::vector<cv::Point> > detResults;
	detector.detect(frame, detResults);

	if (detResults.size() > 0) {
		// 文本识别
		cv::Mat recInput;
		if (!imreadRGB) {
			cv::cvtColor(frame, recInput, cv::COLOR_BGR2GRAY);
		}
		else {
			recInput = frame;
		}
		std::vector< std::vector<Point> > contours;
		for (uint i = 0; i < detResults.size(); i++)
		{
			const auto& quadrangle = detResults[i];
			CV_CheckEQ(quadrangle.size(), (size_t)4, "");
			contours.emplace_back(quadrangle);
			std::vector<Point2f> quadrangle_2f;
			for (int j = 0; j < 4; j++)
				quadrangle_2f.emplace_back(quadrangle[j]);

			// 转换与裁剪图像
			cv::Mat cropped;
			fourPointsTransform(recInput, &quadrangle_2f[0], cropped);

			std::string recognitionResult = recognizer.recognize(cropped);
			std::cout << i << ": '" << recognitionResult << "'" << std::endl;
			cv::putText(frame, recognitionResult, quadrangle[3], cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
		}
		cv::polylines(frame, contours, true, cv::Scalar(0, 255, 0), 2);
	}
	else {
		std::cout << "No Text Detected." << std::endl;
	}
	cv::imshow(winName, frame);
	cv::waitKey();
	return 0;
}

// 文本区域仿射变换预处理
void fourPointsTransform(const cv::Mat& frame, const cv::Point2f vertices[], cv::Mat& result)
{
	const cv::Size outputSize = Size(100, 32);
	cv::Point2f targetVertices[4] = {
		cv::Point(0, outputSize.height - 1),
		cv::Point(0, 0),
		cv::Point(outputSize.width - 1, 0),
		cv::Point(outputSize.width - 1, outputSize.height - 1)
	};
	cv::Mat rotationMatrix = cv::getPerspectiveTransform(vertices, targetVertices);
	cv::warpPerspective(frame, result, rotationMatrix, outputSize);

#if 1
	cv::imshow("roi", result);
	cv::waitKey(33);
#endif
}

bool sortPts(const cv::Point& p1, const cv::Point& p2)
{
	return p1.x < p2.x;
}