// Creating and training a decision tree

#include "stdafx.h"
#include <opencv.hpp>  
#include <opencv2/ml/ml.hpp>  
#include <iostream> 

#define _MUSROOM  
//#define _BOSTON

using namespace std;
using namespace cv;
using namespace cv::ml;


#ifdef _BOSTON
int main(int argc, char *argv[]) {
	// 1.��ȡ����
	// 1.1 ��ȡѵ����
	const char *csv_file_name_train = "../boston-house-prices/housing-train.csv";
	cv::Ptr<TrainData> dataSetTrain =
		TrainData::loadFromCSV(csv_file_name_train, // Input file name
			0, // �������ļ���ͷ����������
			-1, // ������ǩ�ڴ��п�ʼ��-1ʱ������ǩΪ���һ��
			-1 //  ������ǩ�ڴ��н�����-1ʱΪ��һ������������	
		);
	// ��֤���ݶ�ȡ�Ƿ���ȷ
	int n_train_samples = dataSetTrain->getNSamples();
	if (n_train_samples == 0) {
		cerr << "��ȡ�ļ�����: " << csv_file_name_train << endl;
		exit(-1);
	}
	else {
		cout << "��" << csv_file_name_train << "�У���ȡ��" << n_train_samples << "��ѵ������" << endl;
	}
	// 1.2 ��ȡ���Լ�
	const char *csv_file_name_test = "../boston-house-prices/housing-test.csv";
	cv::Ptr<TrainData> dataSetTest = TrainData::loadFromCSV(csv_file_name_test,	0, -1, -1);
	int n_test_samples = dataSetTest->getNSamples();
	if (n_test_samples == 0) {
		cerr << "��ȡ�ļ�����: " << csv_file_name_test << endl;
		exit(-1);
	}
	else {
		cout << "��" << csv_file_name_test << "�У���ȡ��" << n_test_samples << "����������" << endl;
	}

	// 2.����������ģ��
	cv::Ptr<RTrees> dtree = RTrees::create();

	// 3.����ģ�Ͳ���
	dtree->setMaxDepth(15);//15
	dtree->setMinSampleCount(2);//2
	dtree->setRegressionAccuracy(0.01f);
	dtree->setUseSurrogates(false /* true */);
	dtree->setCalculateVarImportance(true); // ����������Ҫ�Լ���
	//dtree->setMaxCategories(15);
	dtree->setCVFolds(0 /*10*/); // 
	dtree->setUse1SERule(true/*true*/);
	dtree->setTruncatePrunedTree(true);

	// 4.ѵ��������
	cout << "start training..." << endl;
	dtree->train(dataSetTrain);
	cout << "training success!" << endl;

	// �����������������Ҫ��
	Mat var_importance = dtree->getVarImportance();
	if (!var_importance.empty())
	{
		double rt_imp_sum = sum(var_importance)[0];
		printf("var#\timportance (%%):\n");
		int i, n = (int)var_importance.total();// ���ؾ����Ԫ���ܸ���
		for (i = 0; i < n; i++)
			printf("%-2d\t%-4.1f\n", i, 100.f*var_importance.at<float>(i) / rt_imp_sum);
	}

	// 5. ѵ��������
	cv::Mat train_results;
	float MSE_train = dtree->calcError(dataSetTrain,
		false, // use train data
		train_results);
	cv::Mat expected_responses = dataSetTrain->getResponses();
	int total_train = 0;
	float square_error = 0.0;
	cout << endl << "--- train set --- " << endl;
	for (int i = 0; i < expected_responses.rows; ++i) {
		float responses = train_results.at<float>(i, 0);
		float expected = expected_responses.at<float>(i, 0);
		square_error += (expected - responses) * (expected - responses);
		total_train++;
		//cout << "price: " << expected << ",\tpredict: " << responses << endl;
		cout << expected << "\t" << responses << endl;
	}
	// ����RMSEָ��
	float RMSE_train = sqrt(square_error / total_train);

	// 6. ����ģ��
	dtree->save("trained_dtree.xml");

	// 7. ��ȡģ��
	dtree->load("trained_dtree.xml");

	// 8. ���Լ�����
	cv::Mat results_test;
	float MSE_test = dtree->calcError(dataSetTest,
		true, // use train data: now it is test data actually
		results_test);
	cv::Mat expected_responses_test = dataSetTest->getResponses();
	//cout << expected_responses_test.size() << endl;
	int total_test = 0;
	square_error = 0.0;
	cout << endl << "--- test set --- " << endl;
	for (int i = 0; i < expected_responses_test.rows; ++i) {
		float responses = results_test.at<float>(i, 0);
		float expected = expected_responses_test.at<float>(i, 0);
		square_error += (expected - responses) * (expected - responses);
		total_test++;
		//cout << "price: " << expected << ",\tpredict: " << responses << endl;
		cout <<  expected << "\t" << responses << endl;
	}
	// ����RMSEָ��
	float RMSE_test = sqrt(square_error / total_test);
	cout << "train data RMSE  = " << RMSE_train << " k USD" << endl;
	cout << "test  data RMSE  = " << RMSE_test  << " k USD" << endl;
	cout << "train data MSE   = " << MSE_train << endl;
	cout << "test  data MSE   = " << MSE_test << endl;
	system("pause");
	return 0;
}
#endif


#ifdef _MUSROOM
int main(int argc, char *argv[]) {
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
	dataSet->setTrainTestSplitRatio(0.9, false); //��90%��10%�ı��������ݼ�Ϊѵ�����Ͳ��Լ�
	int n_train_samples = dataSet->getNTrainSamples();
	int n_test_samples = dataSet->getNTestSamples();
	cout << "Train Samples: " << n_train_samples << endl
		<<  "Test  Samples: " << n_test_samples << endl;

	// 2.����������ģ��
	cv::Ptr<RTrees> dtree = RTrees::create();
	
	// 3.����ģ�Ͳ���
	// 3.1 ���������Ҫ������
	// Set up priors to penalize "poisonous" 10x as much as "edible"
	//float _priors[] = { 1.0, 10.0 };
	//cv::Mat priors(1, 2, CV_32F, _priors);
	dtree->setMaxDepth(10);//10
	dtree->setMinSampleCount(10);//10
	dtree->setRegressionAccuracy(0.01f);
	dtree->setUseSurrogates(false /* true */);
	dtree->setMaxCategories(15);
	dtree->setCVFolds(1 /*10*/); // nonzero causes core dump
	dtree->setUse1SERule(false/*true*/);
	dtree->setTruncatePrunedTree(true);
	//dtree->setPriors( priors );
	dtree->setPriors(cv::Mat()); // ignore priors for now...
								 // Now train the model
								 // NB: we are only using the "train" part of the data set
	
	// 4.ѵ��������
	cout << "start training..." << endl;
	dtree->train(dataSet);
	cout << "training success." << endl;

	// 5.����
	cv::Mat results_train, results_test;
	float train_error = dtree->calcError(dataSet, false, results_train);// use training data
	float test_error = dtree->calcError(dataSet, true, results_test); // use test data
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
	cout << "[Decision Tree] Correct answers  : " << (float(t) / total) << ""<< endl;
	cout << "[Decision Tree] Incorrect answers: " << (float(f) / total) << "" << endl;
	cout << "[Decision Tree] Error on training data: " << train_error << "%" << endl;
	cout << "[Decision Tree] Error on test data: " << test_error << "%" << endl;
	system("pause");
	return 0;
}
#endif
