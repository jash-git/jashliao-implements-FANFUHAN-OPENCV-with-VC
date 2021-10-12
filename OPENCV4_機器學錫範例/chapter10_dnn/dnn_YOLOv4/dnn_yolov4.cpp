// dnn_yolov4.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\dnn.hpp>
#include<fstream>
#include<iostream>

using namespace std;
// ���������
void postProcess(
	cv::dnn::Net &net,
	cv::Mat& frame,
	const vector<cv::Mat>& outs,
	vector<cv::Rect> &boxes,
	vector<int> &classIds,
	vector<int> &indices,
	double confThreshold,
	double nmsThreshold
);

// �����ƽ��
void drawPred(
	cv::Mat &frame,
	vector<cv::Rect> &boxes,
	vector<int> &classIds,
	vector<int> &indices,
	vector<string> &classNamesVec);

// ��������
bool USE_IMAGE = true;  // true: ����ͼ��; false: ������Ƶ
bool USE_YOLOv4 = true; // true: YOLOv4;   false: YOLOv4_tiny
float confidenceThreshold = 0.3; // ���Ŷ�����
float nmsThreshold = 0.2; 		  // ����MNS����

int main()
{
	// [1]ģ���ļ�·������
	cv::String model, config;
	if (USE_YOLOv4)
	{
		model = "D:/models/yolov4/yolov4.weights"; // ģ��Ȩ���ļ�
		config = "D:/models/yolov4/yolov4.cfg";    // ģ�������ļ� 
	}
	else // use yolov4-tiny
	{
		model = "D:/models/yolov4/yolov4-tiny.weights";
		config = "D:/models/yolov4/yolov4-tiny.cfg";
	}
	cv::String framework = "Darknet";                     // ���ѧϰ���
	cv::String label_file = "D:/models/yolov4/coco.names";// ����ǩ�ļ�

														  //[2] �������
	ifstream classNamesFile(label_file);
	vector<string> classNamesVec;
	if (classNamesFile.is_open())
	{
		string className = "";
		while (std::getline(classNamesFile, className))
		{
			classNamesVec.push_back(className);
		}
	}
	// [3]����ģ��
	cv::dnn::Net net = cv::dnn::readNet(config, model, framework);

	// [4]������ͼ��
	cv::Mat frame;
	cv::Mat inputBlob;
	if (USE_IMAGE)
	{
		frame = cv::imread("car.jpg"); //office
		cv::imshow("src", frame);
		cv::waitKey(33);
		inputBlob = cv::dnn::blobFromImage(frame, 1.0 / 255, cv::Size(608, 608), cv::Scalar());
		net.setInput(inputBlob);

		// [5] ģ������
		//��ȡδ���������
		std::vector<cv::String> outNames = net.getUnconnectedOutLayersNames();
		std::vector<cv::Mat> outs;
		// ǰ�򴫲�
		net.forward(outs, outNames);
		// [6]�������
		vector<cv::Rect> boxes;
		vector<int> classIds;
		vector<int> indices;
		postProcess(net, frame, outs, boxes, classIds, indices, confidenceThreshold, nmsThreshold);
		// [7]��ʾ���
		drawPred(frame, boxes, classIds, indices, classNamesVec);
		cv::imshow("dst", frame);
		cv::waitKey(0);
	}
	else // ������Ƶ
	{
		cv::VideoCapture cap;
		cap.open(0); // web camera
					 //cap.open("HighwayIII_Original_sequence.avi"); // video
		cap >> frame;
		while (1)
		{
			cap >> frame;
			// Stop the program if reached end of video
			if (frame.empty()) {
				cout << "Done processing !!!" << endl;
				cv::waitKey(3000);
				break;
			}
			inputBlob = cv::dnn::blobFromImage(frame, 1.0 / 255, cv::Size(608, 608), cv::Scalar());
			net.setInput(inputBlob);

			// [5] ģ������
			//��ȡδ���������
			std::vector<cv::String> outNames = net.getUnconnectedOutLayersNames();
			std::vector<cv::Mat> outs;
			// ǰ�򴫲�
			net.forward(outs, outNames);

			// [6]�������
			vector<cv::Rect> boxes;
			vector<int> classIds;
			vector<int> indices;
			postProcess(net, frame, outs, boxes, classIds, indices, confidenceThreshold, nmsThreshold);
			// [7]��ʾ���
			drawPred(frame, boxes, classIds, indices, classNamesVec);
			cv::imshow("dst", frame);
			if (cv::waitKey(1) == 27) break;
		}
	}
	return 0;
}

// ���������
// Remove the bounding boxes with low confidence using non-maxima suppression
void postProcess(
	cv::dnn::Net &net,
	cv::Mat& frame,
	const vector<cv::Mat>& outs,
	vector<cv::Rect> &boxes,
	vector<int> &classIds,
	vector<int> &indices,
	double confThreshold,
	double nmsThreshold)
{
	float* data;
	cv::Mat scores; // ���Ŷȷ���	
	vector<float> confidences;
	int centerX, centerY, width, height, left, top;

	double confidence;
	cv::Point classIdPoint;

	//�ҳ����е�Ŀ�꼰��λ��
	for (size_t i = 0; i < outs.size(); ++i) {
		data = (float*)outs[i].data;
		for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
		{
			scores = outs[i].row(j).colRange(5, outs[i].cols);
			cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
			if (confidence > confidenceThreshold)
			{
				centerX = (int)(data[0] * frame.cols);
				centerY = (int)(data[1] * frame.rows);
				width = (int)(data[2] * frame.cols);
				height = (int)(data[3] * frame.rows);
				left = centerX - width / 2;
				top = centerY - height / 2;
				classIds.push_back(classIdPoint.x);
				confidences.push_back((float)confidence);
				boxes.push_back(cv::Rect(left, top, width, height));
			}
		}
	}
	// ��ȡ����ʱ��
	vector<double> layersTimes;
	double freq = cv::getTickFrequency() / 1000;
	double t = net.getPerfProfile(layersTimes) / freq;
	string label = cv::format("YOLO v4: inference time for a frame : %.2f ms", t);
	cv::putText(frame, label, cv::Point(15, 15), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0, 0, 255));
	cv::dnn::NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
}

// ���Ƽ����
// Draw the predicted bounding box
void drawPred(
	cv::Mat &frame,
	vector<cv::Rect> &boxes,
	vector<int> &classIds,
	vector<int> &indices,
	vector<string> &classNamesVec)
{
	cv::Scalar rectColor, textColor; //box �� text ����ɫ
	cv::Rect box, textBox;
	int idx; //�������
	cv::String className;
	cv::Size labelSize;
	for (size_t i = 0; i < indices.size(); ++i)
	{
		idx = indices[i];
		className = classNamesVec[classIds[idx]];

		labelSize = cv::getTextSize(className, cv::FONT_HERSHEY_COMPLEX, 0.5, 1, 0);
		box = boxes[idx];
		textBox = cv::Rect(cv::Point(box.x - 1, box.y),
			cv::Point(box.x + labelSize.width, box.y - labelSize.height));
		rectColor = cv::Scalar(idx * 11 % 256, idx * 22 % 256, idx * 33 % 256);
		textColor = cv::Scalar(255 - idx * 11 % 256, 255 - idx * 22 % 256, 255 - idx * 33 % 256);

		cv::rectangle(frame, box, rectColor, 2, 8, 0);
		cv::rectangle(frame, textBox, rectColor, -1, 8, 0);
		cv::putText(frame, className.c_str(), cv::Point(box.x, box.y - 2), cv::FONT_HERSHEY_SIMPLEX, 0.5, textColor, 1, 8);
	}
}

// Get max scores with corresponding indices.
//    scores: a set of scores.
//    threshold: only consider scores higher than the threshold.
//    top_k: if -1, keep all; otherwise, keep at most top_k.
//    score_index_vec: store the sorted (score, index) pair.
inline void GetMaxScoreIndex(const std::vector<float>& scores, const float threshold, const int top_k,
	std::vector<std::pair<float, int> >& score_index_vec)
{
	CV_DbgAssert(score_index_vec.empty());
	// Generate index score pairs.
	for (size_t i = 0; i < scores.size(); ++i)
	{
		if (scores[i] > threshold)
		{
			score_index_vec.push_back(std::make_pair(scores[i], i));
		}
	}

	// Sort the score pair according to the scores in descending order
	std::stable_sort(score_index_vec.begin(), score_index_vec.end(),
		SortScorePairDescend<int>);

	// Keep top_k scores if needed.
	if (top_k > 0 && top_k < (int)score_index_vec.size())
	{
		score_index_vec.resize(top_k);
	}
}

// Do non maximum suppression given bboxes and scores.
// Inspired by Piotr Dollar's NMS implementation in EdgeBox.
//    bboxes: a set of bounding boxes.
//    scores: a set of corresponding confidences.
//    score_threshold: a threshold used to filter detection results.
//    nms_threshold: a threshold used in non maximum suppression.
//    top_k: if not > 0, keep at most top_k picked indices.
//    indices: the kept indices of bboxes after nms.
template <typename BoxType>
inline void NMSFast_(
	const std::vector<BoxType>& bboxes,
	const std::vector<float>& scores, 
	const float score_threshold,
	const float nms_threshold, 
	const float eta, const int top_k,
	std::vector<int>& indices, 
	float(*computeOverlap)(const BoxType&, const BoxType&))
{
	CV_Assert(bboxes.size() == scores.size());

	// Get top_k scores (with corresponding indices).
	std::vector<std::pair<float, int> > score_index_vec;
	GetMaxScoreIndex(scores, score_threshold, top_k, score_index_vec);

	// Do nms.
	float adaptive_threshold = nms_threshold;
	indices.clear();
	for (size_t i = 0; i < score_index_vec.size(); ++i) {
		const int idx = score_index_vec[i].second;
		bool keep = true;
		for (int k = 0; k < (int)indices.size() && keep; ++k) {
			const int kept_idx = indices[k];
			float overlap = computeOverlap(bboxes[idx], bboxes[kept_idx]);
			keep = overlap <= adaptive_threshold;
		}
		if (keep)
			indices.push_back(idx);
		if (keep && eta < 1 && adaptive_threshold > 0.5) {
			adaptive_threshold *= eta;
		}
	}
}