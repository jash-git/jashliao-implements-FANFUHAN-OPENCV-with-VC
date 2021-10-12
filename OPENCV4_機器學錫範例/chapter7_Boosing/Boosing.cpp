// Boosing.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv.hpp>  
#include <opencv2/ml/ml.hpp>  
#include <iostream> 

using namespace cv;
using namespace cv::ml;
using namespace std;

int main(int argc, char *argv[])
{
	//int var_count = 16;
	//cv::Mat var_type(1, var_count + 2, CV_8U); // var_count is # features (16 here)
	//var_type.setTo(cv::Scalar::all(VAR_ORDERED));
	//var_type.at<uchar>(var_count) = var_type.at<uchar>(var_count + 1) = VAR_CATEGORICAL;



	// 1.读取数据
	//const char *csv_file_name = argc >= 2 ? argv[1] : "D:/data/ml-data/mushroom/agaricus-lepiota.data";
	const char *csv_file_name = argc >= 2 ? argv[1] : "../mushroom/agaricus-lepiota.data";
	// 1.1 读取CSV数据文件
	// 函数用法...
	cv::Ptr<TrainData> dataSet =
		TrainData::loadFromCSV(csv_file_name, // Input file name
			0, // 从数据文件开头跳过的行数
			0, // 样本的标签从此列开始
			1, // 样本输入特征向量从此列开始
			"cat[0-22]" // All 23 columns are categorical
		);
	// Use defaults for delimeter (',') and missch ('?')使用默认的“,”分割特征

	// 1.2 验证数据读取是否正确
	int n_samples = dataSet->getNSamples();
	if (n_samples == 0) {
		cerr << "读取文件错误: " << csv_file_name << endl;
		exit(-1);
	}
	else {
		cout << "从" << csv_file_name << "中，读取了" << n_samples << "个样本" << endl;
	}

	// 1.3 划分训练集与测试集
	dataSet->setTrainTestSplitRatio(0.8, false); //按80%和20%的比例将数据集为训练集和测试集
	int n_train_samples = dataSet->getNTrainSamples();
	int n_test_samples = dataSet->getNTestSamples();
	cout << "Train Samples: " << n_train_samples << endl
		<< "Test  Samples: " << n_test_samples << endl;

	// 2.创建AdaBoost模型
	Ptr<Boost> boost;
	boost = Boost::create();

	// 3.设置AdaBoost模型
	//boost->setBoostType(Boost::GENTLE);
	boost->setBoostType(Boost::REAL);
	boost->setWeakCount(100);
	boost->setWeightTrimRate(0.95);
	boost->setMaxDepth(5);
	boost->setUseSurrogates(false);
	//boost->setPriors(Mat(priors));

	// 4.训练AdaBoost模型
	cout << "start training..." << endl;
	boost->train(dataSet);
	cout << "training success..." << endl;
	cout << endl;

	// 5.测试
	cv::Mat results_train, results_test;
	float train_error = boost->calcError(dataSet, false, results_train);// use training data
	float test_error = boost->calcError(dataSet, true, results_test); // use test data
	std::vector<cv::String> names;
	dataSet->getNames(names);
	Mat flags = dataSet->getVarSymbolFlags();

	// 6.统计输出结果
	cv::Mat expected_responses = dataSet->getTestResponses();
	int t = 0, f = 0, total = 0;
	for (int i = 0; i < dataSet->getNTestSamples(); ++i) {
		float responses = results_test.at<float>(i, 0);
		float expected = expected_responses.at<float>(i, 0);
		cv::String r_str = names[(int)responses];
		cv::String e_str = names[(int)expected];
		if (responses == expected)
		{
			t++;
			cout << "label: " << e_str << ", predict: " << r_str << endl;
		}
		else
		{
			f++;
			cout << "label: " << e_str << ", predict: " << r_str << " ×" << endl;
		}
		total++;
	}
	cout << "Correct answer    = " << t << endl;
	cout << "Incorrect answer  = " << f << endl;
	cout << "Total test sample = " << total << endl;
	cout << "[AdaBoost] Correct answers  : " << (float(t) / total) << "" << endl;
	cout << "[AdaBoost] Incorrect answers: " << (float(f) / total) << "" << endl;
	cout << "[AdaBoost] Error on training data: " << train_error << "%" << endl;
	cout << "[AdaBoost] Error on test data: " << test_error << "%" << endl;
	system("pause");
	return 0;
}

