// RandomTrees.cpp : �������̨Ӧ�ó������ڵ㡣
//

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
	const char *csv_file_name_train = "../Datasets/boston-house-prices/housing-train.csv";
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
	cv::Ptr<TrainData> dataSetTest = TrainData::loadFromCSV(csv_file_name_test, 0, -1, -1);
	int n_test_samples = dataSetTest->getNSamples();
	if (n_test_samples == 0) {
		cerr << "��ȡ�ļ�����: " << csv_file_name_test << endl;
		exit(-1);
	}
	else {
		cout << "��" << csv_file_name_test << "�У���ȡ��" << n_test_samples << "����������" << endl;
	}

	// 2.���������ģ��
	cv::Ptr<RTrees> forest = RTrees::create();

	// 3.���������
	forest->setActiveVarCount(0);
	forest->setCalculateVarImportance(true);
	forest->setTermCriteria(
		TermCriteria(
			TermCriteria::MAX_ITER + TermCriteria::EPS,
			100, 0.01));

	// 4.ѵ�������
	cout << "start training..." << endl;
	forest->train(dataSetTrain);
	cout << "training success!" << endl;

	// �����������������Ҫ��
	Mat var_importance = forest->getVarImportance();
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
	float MSE_train = forest->calcError(dataSetTrain,
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
		cout << "price: " << expected << ",\tpredict: " << responses << endl;
	/*	cout<< "price: " << expected << "\t" << responses << endl;*/
	}

	// ����RMSEָ��
	float RMSE_train = sqrt(square_error / total_train);

	// 6. ����ģ��
	forest->save("trained_forest.xml");

	// 7. ��ȡģ��
	forest->load("trained_forest.xml");

	// 8. ���Լ�����
	cv::Mat results_test;
	float MSE_test = forest->calcError(dataSetTest,
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
		cout << "price: " << expected << ",\tpredict: " << responses << endl;
		//cout << expected << "\t" << responses << endl;
	}
	// ����RMSEָ��
	float RMSE_test = sqrt(square_error / total_test);
	cout << "[random forest] train data RMSE  = " << RMSE_train << " k USD" << endl;
	cout << "[random forest] test  data RMSE  = " << RMSE_test << " k USD" << endl;
	cout << "[random forest] train data MSE   = " << MSE_train << endl;
	cout << "[random forest] test  data MSE   = " << MSE_test << endl;
	system("pause");
	return 0;
}
#endif

#ifdef _MUSROOM
int main(int argc, char *argv[])
{
	// 1.��ȡ����
	const char *csv_file_name = argc >= 2 ? argv[1] : "../Datasets/mushroom/agaricus-lepiota.data";
	// 1.1 ��ȡCSV�����ļ�
	// �����÷�...
	cv::Ptr<TrainData> dataSet_forest =
		TrainData::loadFromCSV(csv_file_name, // Input file name
			0, // �������ļ���ͷ����������
			0, // �����ı�ǩ�Ӵ��п�ʼ
			1, // �����������������Ӵ��п�ʼ
			"cat[0-22]" // All 23 columns are categorical
		);

	// 1.2 ��֤���ݶ�ȡ�Ƿ���ȷ
	int n_samples = dataSet_forest->getNSamples();
	int n_features = dataSet_forest->getNVars();
	cout << "ÿ�������� " << n_features << " ������" << endl;
	if (n_samples == 0) {
		cerr << "��ȡ�ļ�����: " << csv_file_name << endl;
		exit(-1);
	}
	else {
		cout << "��" << csv_file_name << "�У���ȡ��" << n_samples << "������" << endl;
	}

	// 1.3 ����ѵ��������Լ�
	dataSet_forest->setTrainTestSplitRatio(0.8, false); //��80%��20%�ı��������ݼ�Ϊѵ�����Ͳ��Լ�
	int n_train_samples = dataSet_forest->getNTrainSamples();
	int n_test_samples = dataSet_forest->getNTestSamples();
	cout << "Train Samples: " << n_train_samples << endl
		<< "Test Samples: " << n_test_samples << endl;

	// 2.���������ģ��
	cv::Ptr<RTrees> forest = RTrees::create();

	// 3.���������
	forest->setActiveVarCount(0); 
	forest->setCalculateVarImportance(true);
	//forest->setMaxDepth(10);//10
	//forest->setMinSampleCount(10);
	//forest->setRegressionAccuracy(0);
	//forest->setUseSurrogates(false);
	//forest->setMaxCategories(15);
	//forest->setPriors(Mat());
	forest->setTermCriteria(
		TermCriteria(
			TermCriteria::MAX_ITER + TermCriteria::EPS,
			100, 0.01));

	// 4.ѵ�������
	cout << "start training..." << endl;
	forest->train(dataSet_forest, 0);
	cout << "[random forest] training success." << endl;

	// Print variable importance
	Mat var_importance = forest->getVarImportance();
	if (!var_importance.empty())
	{
		double rt_imp_sum = sum(var_importance)[0];
		printf("var#\timportance (%%):\n");
		int i, n = (int)var_importance.total();// ���ؾ����Ԫ���ܸ���
		for (i = 0; i < n; i++)
			printf("%-2d\t%-4.1f\n", i, 100.f*var_importance.at<float>(i) / rt_imp_sum);
	}

	// 5.����
	cv::Mat results_train, results_test;
	float forest_train_error = forest->calcError(dataSet_forest, false, results_train);// use train data
	float forest_test_error  = forest->calcError(dataSet_forest, true, results_test); // use test data


	// 6.ͳ��������
	int t = 0, f = 0, total = 0;
	// random forest test:
	cv::Mat expected_responses_forest = dataSet_forest->getTestResponses(); // ��ȡ���Լ���ǩ
	std::vector<cv::String> names_forest;
	dataSet_forest->getNames(names_forest);
	for (int i = 0; i < dataSet_forest->getNTestSamples(); ++i) {
		float responses = results_test.at<float>(i, 0);
		float expected = expected_responses_forest.at<float>(i, 0);
		cv::String r_str = names_forest[(int)responses];
		cv::String e_str = names_forest[(int)expected];
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
	float forest_accuracy = (float(t) / total);
	float forest_error = (float(f) / total);

	cout << "[random forest] Correct answer rate  : " << forest_accuracy << "" << endl;
	cout << "[random forest] Incorrect answer rate: " << forest_error << "" << endl;
	cout << "[random forest] Error on training data: " << forest_train_error << "%" << endl;
	cout << "[random forest] Error on test data: " << forest_test_error << "%" << endl;
	system("pause");
	return 0;
}
#endif

