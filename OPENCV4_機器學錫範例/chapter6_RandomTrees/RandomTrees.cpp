// RandomTrees.cpp : 定义控制台应用程序的入口点。
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
	// 1.读取数据
	// 1.1 读取训练集
	const char *csv_file_name_train = "../Datasets/boston-house-prices/housing-train.csv";
	cv::Ptr<TrainData> dataSetTrain =
		TrainData::loadFromCSV(csv_file_name_train, // Input file name
			0, // 从数据文件开头跳过的行数
			-1, // 样本标签于此列开始，-1时样本标签为最后一列
			-1 //  样本标签于此列结束，-1时为上一个参数所在列	
		);
	// 验证数据读取是否正确
	int n_train_samples = dataSetTrain->getNSamples();
	if (n_train_samples == 0) {
		cerr << "读取文件错误: " << csv_file_name_train << endl;
		exit(-1);
	}
	else {
		cout << "从" << csv_file_name_train << "中，读取了" << n_train_samples << "个训练样本" << endl;
	}
	// 1.2 读取测试集
	const char *csv_file_name_test = "../boston-house-prices/housing-test.csv";
	cv::Ptr<TrainData> dataSetTest = TrainData::loadFromCSV(csv_file_name_test, 0, -1, -1);
	int n_test_samples = dataSetTest->getNSamples();
	if (n_test_samples == 0) {
		cerr << "读取文件错误: " << csv_file_name_test << endl;
		exit(-1);
	}
	else {
		cout << "从" << csv_file_name_test << "中，读取了" << n_test_samples << "个测试样本" << endl;
	}

	// 2.创建随机树模型
	cv::Ptr<RTrees> forest = RTrees::create();

	// 3.设置随机树
	forest->setActiveVarCount(0);
	forest->setCalculateVarImportance(true);
	forest->setTermCriteria(
		TermCriteria(
			TermCriteria::MAX_ITER + TermCriteria::EPS,
			100, 0.01));

	// 4.训练随机树
	cout << "start training..." << endl;
	forest->train(dataSetTrain);
	cout << "training success!" << endl;

	// 输出样本特征属性重要性
	Mat var_importance = forest->getVarImportance();
	if (!var_importance.empty())
	{
		double rt_imp_sum = sum(var_importance)[0];
		printf("var#\timportance (%%):\n");
		int i, n = (int)var_importance.total();// 返回矩阵的元素总个数
		for (i = 0; i < n; i++)
			printf("%-2d\t%-4.1f\n", i, 100.f*var_importance.at<float>(i) / rt_imp_sum);
	}

	// 5. 训练集精度
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

	// 计算RMSE指标
	float RMSE_train = sqrt(square_error / total_train);

	// 6. 保存模型
	forest->save("trained_forest.xml");

	// 7. 读取模型
	forest->load("trained_forest.xml");

	// 8. 测试集精度
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
	// 计算RMSE指标
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
	// 1.读取数据
	const char *csv_file_name = argc >= 2 ? argv[1] : "../Datasets/mushroom/agaricus-lepiota.data";
	// 1.1 读取CSV数据文件
	// 函数用法...
	cv::Ptr<TrainData> dataSet_forest =
		TrainData::loadFromCSV(csv_file_name, // Input file name
			0, // 从数据文件开头跳过的行数
			0, // 样本的标签从此列开始
			1, // 样本输入特征向量从此列开始
			"cat[0-22]" // All 23 columns are categorical
		);

	// 1.2 验证数据读取是否正确
	int n_samples = dataSet_forest->getNSamples();
	int n_features = dataSet_forest->getNVars();
	cout << "每个样本有 " << n_features << " 个特征" << endl;
	if (n_samples == 0) {
		cerr << "读取文件错误: " << csv_file_name << endl;
		exit(-1);
	}
	else {
		cout << "从" << csv_file_name << "中，读取了" << n_samples << "个样本" << endl;
	}

	// 1.3 划分训练集与测试集
	dataSet_forest->setTrainTestSplitRatio(0.8, false); //按80%和20%的比例将数据集为训练集和测试集
	int n_train_samples = dataSet_forest->getNTrainSamples();
	int n_test_samples = dataSet_forest->getNTestSamples();
	cout << "Train Samples: " << n_train_samples << endl
		<< "Test Samples: " << n_test_samples << endl;

	// 2.创建随机树模型
	cv::Ptr<RTrees> forest = RTrees::create();

	// 3.设置随机树
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

	// 4.训练随机树
	cout << "start training..." << endl;
	forest->train(dataSet_forest, 0);
	cout << "[random forest] training success." << endl;

	// Print variable importance
	Mat var_importance = forest->getVarImportance();
	if (!var_importance.empty())
	{
		double rt_imp_sum = sum(var_importance)[0];
		printf("var#\timportance (%%):\n");
		int i, n = (int)var_importance.total();// 返回矩阵的元素总个数
		for (i = 0; i < n; i++)
			printf("%-2d\t%-4.1f\n", i, 100.f*var_importance.at<float>(i) / rt_imp_sum);
	}

	// 5.测试
	cv::Mat results_train, results_test;
	float forest_train_error = forest->calcError(dataSet_forest, false, results_train);// use train data
	float forest_test_error  = forest->calcError(dataSet_forest, true, results_test); // use test data


	// 6.统计输出结果
	int t = 0, f = 0, total = 0;
	// random forest test:
	cv::Mat expected_responses_forest = dataSet_forest->getTestResponses(); // 获取测试集标签
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
			cout << "label: " << e_str << ", predict: " << r_str << " ×" << endl;
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

