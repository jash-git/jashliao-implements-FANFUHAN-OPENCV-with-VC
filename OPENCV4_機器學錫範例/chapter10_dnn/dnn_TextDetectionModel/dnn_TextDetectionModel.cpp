// dnn_TextDetectionModel.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <opencv.hpp>
#include <opencv2/dnn/dnn.hpp>

using namespace cv;
using namespace cv::dnn;

/* 参考文献
[1] Real-time Scene Text Detection with Differentiable Binarization[C]. CVPR. 2019.
"Download links are provided in doc/tutorials/dnn/dnn_text_spotting/dnn_text_spotting.markdown";
*/


static void split(const std::string& s, char delimiter, std::vector<std::string>& elems)
{
	elems.clear();
	size_t prev_pos = 0;
	size_t pos = 0;
	while ((pos = s.find(delimiter, prev_pos)) != std::string::npos)
	{
		elems.emplace_back(s.substr(prev_pos, pos - prev_pos));
		prev_pos = pos + 1;
	}
	if (prev_pos < s.size())
		elems.emplace_back(s.substr(prev_pos, s.size() - prev_pos));
}

int main()
{
	// 初始化参数	
	bool evaluate = false; // 运行模式：false:预测单张图像; true: 基准数据集评估 evaluate on benchmarks
	// 初始化参数
	// 二进制.onnx文件的路径，包含训练好的DB检测器模型
	//cv::String modelPath = "D:/models/TextRecognitionModel_google/DB_TD500_resnet18.onnx"; 
	cv::String modelPath = "D:/models/TextRecognitionModel_google/DB_TD500_resnet50.onnx";
	float binThresh = 0.3;    // Confidence threshold of the binary map 二值图的置信度阈值
	float polyThresh = 0.5;   // Confidence threshold of polygons 多边形的置信度阈值
	double unclipRatio = 2.0; // 检测到的文本区域的未压缩比率，该比率确定输出大小。 通常设置为2.0。
	uint maxCandidates = 200; // // 输出结果的最大数量
	int height = 736; // 模型输入图像的高度，32的整数倍
	int width = 736;  // 模型输入图像的宽度，32的整数倍

	// Load the network
	CV_Assert(!modelPath.empty());
	cv::dnn::TextDetectionModel_DB detector(modelPath);
	detector.setBinaryThreshold(binThresh)
		.setPolygonThreshold(polyThresh)
		.setUnclipRatio(unclipRatio)
		.setMaxCandidates(maxCandidates);

	double scale = 1.0 / 255.0;
	cv::Size inputSize = Size(width, height);
	cv::Scalar mean = Scalar(122.67891434, 116.66876762, 104.00698793);
	detector.setInputParams(scale, inputSize, mean);

	// Create a window
	static const std::string winName = "TextDetectionModel";

	if (evaluate) {
		// for evaluation 验证集
		// Path to benchmarks for evaluation 基准数据集的路径
		cv::String evalDataPath = "D:/models/TextRecognitionModel_google/evaluation_data_det/TD500";
		cv::String testListPath = evalDataPath + "/test_list.txt";
		std::ifstream testList;
		testList.open(testListPath);
		CV_Assert(testList.is_open());

		// Create a window for showing groundtruth
		static const std::string winNameGT = "GT";

		cv::String testImgPath;
		while (std::getline(testList, testImgPath)) {
			cv::String imgPath = evalDataPath + "/test_images/" + testImgPath;
			std::cout << "Image Path: " << imgPath << std::endl;

			cv::Mat frame = cv::imread(samples::findFile(imgPath), IMREAD_COLOR);
			CV_Assert(!frame.empty());
			cv::Mat src = frame.clone();

			// Inference
			std::vector<std::vector<Point>> results;
			detector.detect(frame, results);
			// 绘制检测结果
			cv::polylines(frame, results, true, Scalar(0, 255, 0), 3); // thinkness 2
			// resize frame
			if (frame.cols > 1024)
			{
				cv::resize(frame, frame, cv::Size(), 0.3, 0.3);
			}
			cv::imshow(winName, frame);

			// load groundtruth
			String imgName = testImgPath.substr(0, testImgPath.length() - 4);
			String gtPath = evalDataPath + "/test_gts/" + imgName + ".txt";
			// std::cout << gtPath << std::endl;
			std::ifstream gtFile;
			gtFile.open(gtPath);
			CV_Assert(gtFile.is_open());

			std::vector<std::vector<Point>> gts;
			cv::String gtLine;
			while (std::getline(gtFile, gtLine)) {
				size_t splitLoc = gtLine.find_last_of(',');
				cv::String text = gtLine.substr(splitLoc + 1);
				if (text == "###\r" || text == "1") {
					// ignore difficult instances
					continue;
				}
				gtLine = gtLine.substr(0, splitLoc);

				std::vector<std::string> v;
				split(gtLine, ',', v);

				std::vector<int> loc;
				std::vector<Point> pts;
				for (auto && s : v) {
					loc.push_back(atoi(s.c_str()));
				}
				for (size_t i = 0; i < loc.size() / 2; i++) {
					pts.push_back(Point(loc[2 * i], loc[2 * i + 1]));
				}
				gts.push_back(pts);
			}
			// 绘制真值
			cv::polylines(src, gts, true, Scalar(0, 255, 0), 3); // thinkness 2
			// resize
			if (src.cols > 1024)
			{
				cv::resize(src, src, cv::Size(), 0.3, 0.3);
			}
			cv::imshow(winNameGT, src);
			cv::waitKey();
		}
	}
	else {
		// Open an image file
		// 此处读取的是经过detection模型获得的文本区域
		cv::Mat frame = cv::imread("acmilan.jpg");
		CV_Assert(!frame.empty());
		
		// Detect
		std::vector<std::vector<Point>> results;
		detector.detect(frame, results);

		cv::polylines(frame, results, true, Scalar(0, 255, 0), 3);
		if (frame.cols > 1024)
		{
			cv::resize(frame, frame, cv::Size(), 0.4, 0.4);
		}
		cv::imshow(winName, frame);
		cv::waitKey();
	}
	return 0;
}
