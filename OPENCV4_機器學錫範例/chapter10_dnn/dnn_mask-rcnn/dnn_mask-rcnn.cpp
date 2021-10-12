// dnn_mask-rcnn.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv.hpp>
#include <opencv2\dnn.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>

using namespace std;
using namespace cv;
using namespace dnn;

// Give the configuration and weight files for the model
// 设置模型权重、网络结构与类别标签文件的路径
cv::String model = "D:/models/mask_rcnn_inception_v2/frozen_inference_graph.pb";
cv::String config = "D:/models/mask_rcnn_inception_v2/mask_rcnn_inception_v2_coco_2018_01_28.pbtxt";
string classesFile = "D:/models/mask_rcnn_inception_v2/mscoco_labels.names";


// Initialize the parameters
// 初始化参数
float confThreshold = 0.6; // Confidence threshold 置信度阈值
float maskThreshold = 0.3; // Mask threshold 蒙版阈值

vector<string> classes;
vector<cv::Scalar> colors;

// Draw the predicted bounding box
// 绘制分割结果函数
void drawPred(cv::Mat& frame, int classId, float conf, cv::Rect box, cv::Mat& objectMask);

// Postprocess the neural network's output for each frame
// 网络推理结果后处理函数
void postProcess(cv::Mat& frame, const vector<Mat>& outs);

int main()
{
	// Load names of classes
	// 载入类别标签
	ifstream classFptr(classesFile.c_str());
	string line;
	while (getline(classFptr, line)) classes.push_back(line);

	// Load the colors
	// 载入绘图颜色文件
	string colorsFile = "D:/models/mask_rcnn_inception_v2/colors.txt";
	ifstream colorFptr(colorsFile.c_str());
	while (getline(colorFptr, line)) {
		char* pEnd;
		double r, g, b;
		r = strtod(line.c_str(), &pEnd);
		g = strtod(pEnd, NULL);
		b = strtod(pEnd, NULL);
		colors.push_back(cv::Scalar(r, g, b, 255.0));
	}

	// Load the network
	// 载入模型
	cv::dnn::Net net = readNetFromTensorflow(model, config);
	net.setPreferableBackend(DNN_BACKEND_OPENCV);
	net.setPreferableTarget(DNN_TARGET_CPU);

	// Open a video file or an image file or a camera stream.
	string str, outputFile;
	//cv::VideoCapture cap;
	//cap.open("test.mp4");
	cv::Mat image, blob;

	// get frame from the video
	// 读取测试图像
	image = cv::imread("carandmotorcycle.jpg"); //hourse carandmotorcycle
	if (image.empty()) {
		cout << "load image failed!" << outputFile << endl;
		system("PAUSE");
		return 0;
	}
	cv::imshow("Mask R-CNN in OpenCV", image);
	cv::waitKey(1);

	// Create a 4D blob from a frame.
	// 从图像创建4D blob
	cv::dnn::blobFromImage(image, blob, 1.0, Size(image.cols, image.rows), Scalar(), true, false);

	// Sets the input to the network
	// 设置网络输入
	net.setInput(blob);

	// Runs the forward pass to get output from the output layers
	// 前向推理获取结果
	std::vector<String> outNames(2);
	outNames[0] = "detection_out_final";
	outNames[1] = "detection_masks";
	vector<cv::Mat> outs;
	net.forward(outs, outNames);

	// Extract the bounding box and mask for each of the detected objects
	// 从推理结果中提取boundding box和mask蒙版
	postProcess(image, outs);

	// display efficiency information.
	// 显示网络推理耗时
	// The function getPerfProfile returns the overall time for inference(t) and the timings for each of the layers
	vector<double> layersTimes;
	double freq = getTickFrequency() / 1000;
	double t = net.getPerfProfile(layersTimes) / freq;
	string label = format("Mask-RCNN: inference time for a frame : %.2f ms", t);
	cv::putText(image, label, cv::Point(15, 20), cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(0, 0, 255));
	// display the result
	// 显示结果图像
	cv::imshow("Mask R-CNN in OpenCV", image);
	cv::waitKey();
	//// Process frames.
	//while (0)
	//{
	//	// get frame from the video
	//	cap >> frame;

	//	// Stop the program if reached end of video
	//	if (frame.empty()) {
	//		cout << "Done processing !!!" << endl;
	//		cout << "Output file is stored as " << outputFile << endl;
	//		cv::waitKey(3000);
	//		break;
	//	}
	//	// Create a 4D blob from a frame.
	//	cv::dnn::blobFromImage(frame, blob, 1.0, Size(frame.cols, frame.rows), Scalar(), true, false);
	//	//blobFromImage(frame, blob);

	//	//Sets the input to the network
	//	net.setInput(blob);

	//	// Runs the forward pass to get output from the output layers
	//	std::vector<String> outNames(2);
	//	outNames[0] = "detection_out_final";
	//	outNames[1] = "detection_masks";
	//	vector<cv::Mat> outs;
	//	net.forward(outs, outNames);

	//	// Extract the bounding box and mask for each of the detected objects
	//	postProcess(frame, outs);

	//	// Put efficiency information. The function getPerfProfile returns the overall time for inference(t) and the timings for each of the layers(in layersTimes)
	//	vector<double> layersTimes;
	//	double freq = getTickFrequency() / 1000;
	//	double t = net.getPerfProfile(layersTimes) / freq;
	//	string label = format("Mask-RCNN on 2.5 GHz Intel Core i7 CPU, Inference time for a frame : %0.0f ms", t);
	//	cv::putText(frame, label, cv::Point(0, 15), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 0, 255));

	//	// Write the frame with the detection boxes
	//	cv::Mat detectedFrame;
	//	frame.convertTo(detectedFrame, CV_8U);
	//	cv::imshow("Mask R-CNN in OpenCV", frame);
	//}
	//cap.release();
	return 0;
}

// For each frame, extract the bounding box and mask for each detected object
void postProcess(cv::Mat& frame, const vector<cv::Mat>& outs)
{
	cv::Mat outDetections = outs[0];
	cv::Mat outMasks = outs[1];

	// Output size of masks is NxCxHxW where
	// 输出masks的维度为N*C*H*W:
	// N - number of detected boxes
	// C - number of classes (excluding background)
	// HxW - segmentation shape
	const int numDetections = outDetections.size[2];
	const int numClasses = outMasks.size[1];

	outDetections = outDetections.reshape(1, outDetections.total() / 7);
	for (int i = 0; i < numDetections; ++i)
	{
		float score = outDetections.at<float>(i, 2);
		if (score > confThreshold)
		{
			// Extract the bounding box
			// 提取bounding box
			int classId = static_cast<int>(outDetections.at<float>(i, 1));
			int left = static_cast<int>(frame.cols * outDetections.at<float>(i, 3));
			int top = static_cast<int>(frame.rows * outDetections.at<float>(i, 4));
			int right = static_cast<int>(frame.cols * outDetections.at<float>(i, 5));
			int bottom = static_cast<int>(frame.rows * outDetections.at<float>(i, 6));

			left = max(0, min(left, frame.cols - 1));
			top = max(0, min(top, frame.rows - 1));
			right = max(0, min(right, frame.cols - 1));
			bottom = max(0, min(bottom, frame.rows - 1));
			cv::Rect box = cv::Rect(left, top, right - left + 1, bottom - top + 1);

			// Extract the mask for the object
			// 提取mask
			cv::Mat objectMask(outMasks.size[2], outMasks.size[3], CV_32F, outMasks.ptr<float>(i, classId));

			// Draw bounding box, colorize and show the mask on the image
			// 绘制bounding box与分割mask
			drawPred(frame, classId, score, box, objectMask);
		}
	}
}

// Draw the predicted bounding box, colorize and show the mask on the image
void drawPred(cv::Mat& frame, int classId, float conf, cv::Rect box, cv::Mat& objectMask)
{
	// Draw a rectangle displaying the bounding box
	// 绘制bounding box
	cv::rectangle(frame, cv::Point(box.x, box.y), cv::Point(box.x + box.width, box.y + box.height), cv::Scalar(255, 178, 50), 3);

	// Get the label for the class name and its confidence
	// 生成类别与置信度标签
	string label = format("%.2f", conf);
	if (!classes.empty())
	{
		CV_Assert(classId < (int)classes.size());
		label = classes[classId] + ":" + label;
	}

	// Display the label at the top of the bounding box
	// 设置类别与置信度标签的尺寸与颜色
	int baseLine;
	cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
	box.y = max(box.y, labelSize.height);
	cv::Scalar color = colors[classId%colors.size()];

	// Resize the mask, threshold, color and apply it on the image
	// 根据门限maskThreshold生成mask蒙版
	cv::resize(objectMask, objectMask, cv::Size(box.width, box.height));
	cv::Mat mask = (objectMask > maskThreshold);
	cv::Mat coloredRoi = (0.3 * color + 0.7 * frame(box));
	coloredRoi.convertTo(coloredRoi, CV_8UC3);

	// Draw the contours on the image
	// 绘制分割轮廓
	vector<cv::Mat> contours;
	cv::Mat hierarchy;
	mask.convertTo(mask, CV_8U);
	cv::findContours(mask, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	cv::drawContours(coloredRoi, contours, -1, color, 5, LINE_8, hierarchy, 100);
	coloredRoi.copyTo(frame(box), mask);

	// 绘制类别与置信度标签
	cv::rectangle(frame, cv::Point(box.x, box.y - round(1.5*labelSize.height)), cv::Point(box.x + round(1.5*labelSize.width), box.y + baseLine), color, FILLED);
	cv::Scalar textColor = cv::Scalar(255, 255, 255) - color;
	cv::putText(frame, label, cv::Point(box.x, box.y), cv::FONT_HERSHEY_SIMPLEX, 0.6, textColor, 1);
}
