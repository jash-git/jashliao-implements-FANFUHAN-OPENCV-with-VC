// Boosing.cpp : �������̨Ӧ�ó������ڵ㡣
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



	// 1.��ȡ����
	//const char *csv_file_name = argc >= 2 ? argv[1] : "D:/data/ml-data/mushroom/agaricus-lepiota.data";
	const char *csv_file_name = argc >= 2 ? argv[1] : "../mushroom/agaricus-lepiota.data";
	// 1.1 ��ȡCSV�����ļ�
	// �����÷�...
	cv::Ptr<TrainData> dataSet =
		TrainData::loadFromCSV(csv_file_name, // Input file name
			0, // �������ļ���ͷ����������
			0, // �����ı�ǩ�Ӵ��п�ʼ
			1, // �����������������Ӵ��п�ʼ
			"cat[0-22]" // All 23 columns are categorical
		);
	// Use defaults for delimeter (',') and missch ('?')ʹ��Ĭ�ϵġ�,���ָ�����

	// 1.2 ��֤���ݶ�ȡ�Ƿ���ȷ
	int n_samples = dataSet->getNSamples();
	if (n_samples == 0) {
		cerr << "��ȡ�ļ�����: " << csv_file_name << endl;
		exit(-1);
	}
	else {
		cout << "��" << csv_file_name << "�У���ȡ��" << n_samples << "������" << endl;
	}

	// 1.3 ����ѵ��������Լ�
	dataSet->setTrainTestSplitRatio(0.8, false); //��80%��20%�ı��������ݼ�Ϊѵ�����Ͳ��Լ�
	int n_train_samples = dataSet->getNTrainSamples();
	int n_test_samples = dataSet->getNTestSamples();
	cout << "Train Samples: " << n_train_samples << endl
		<< "Test  Samples: " << n_test_samples << endl;

	// 2.����AdaBoostģ��
	Ptr<Boost> boost;
	boost = Boost::create();

	// 3.����AdaBoostģ��
	//boost->setBoostType(Boost::GENTLE);
	boost->setBoostType(Boost::REAL);
	boost->setWeakCount(100);
	boost->setWeightTrimRate(0.95);
	boost->setMaxDepth(5);
	boost->setUseSurrogates(false);
	//boost->setPriors(Mat(priors));

	// 4.ѵ��AdaBoostģ��
	cout << "start training..." << endl;
	boost->train(dataSet);
	cout << "training success..." << endl;
	cout << endl;

	// 5.����
	cv::Mat results_train, results_test;
	float train_error = boost->calcError(dataSet, false, results_train);// use training data
	float test_error = boost->calcError(dataSet, true, results_test); // use test data
	std::vector<cv::String> names;
	dataSet->getNames(names);
	Mat flags = dataSet->getVarSymbolFlags();

	// 6.ͳ��������
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
			cout << "label: " << e_str << ", predict: " << r_str << " ��" << endl;
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

