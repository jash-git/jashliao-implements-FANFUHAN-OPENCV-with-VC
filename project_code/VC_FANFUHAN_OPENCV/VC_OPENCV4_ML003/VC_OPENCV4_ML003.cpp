// VC_OPENCV4_ML003.cpp : 定義主控台應用程式的進入點。
//
/*
// Debug | x32
通用屬性
| C/C++
|	| 一般
|		| 其他 Include 目錄 -> ..\..\opencv411_x64\include
|
| 連結器
| 	|一一般
|		|  其他程式庫目錄 -> ..\..\opencv411_x64\lib
|
| 	|一輸入
|		| 其他相依性 -> opencv_world411d.lib;%(AdditionalDependencies)

// Releas | x64
組態屬性
| C/C++
|	| 一般
|		| 其他 Include 目錄 -> ..\..\opencv411_x64\include;%(AdditionalDependencies)
|
| 連結器
| 	|一般
|		| 其他程式庫目錄 -> ..\..\opencv411_x64\lib;%(AdditionalDependencies)
|
| 	|一輸入
|		| 其他相依性 -> opencv_world411.lib;%(AdditionalDependencies)

*/

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

//OPENCV4_ML03 ~ 支持向量機
//https://github.com/jash-git/CB_OpenCV249_ML/blob/master/CB_OpenCV249_ML03/main.cpp

void pause()
{
	printf("Press Enter key to continue...");
	fgetc(stdin);
}

int main()
{
	//60个训练样本
	double trainingData[60][4] = 
	{ 
		{ 5.1,3.5,1.4,0.2 },{ 4.9,3.0,1.4,0.2 },{ 4.7,3.2,1.3,0.2 },
		{ 4.6,3.1,1.5,0.2 },{ 5.0,3.6,1.4,0.2 },{ 5.4,3.9,1.7,0.4 },
		{ 4.6,3.4,1.4,0.3 },{ 5.0,3.4,1.5,0.2 },{ 4.4,2.9,1.4,0.2 },
		{ 4.9,3.1,1.5,0.1 },{ 5.4,3.7,1.5,0.2 },{ 4.8,3.4,1.6,0.2 },
		{ 4.8,3.0,1.4,0.1 },{ 4.3,3.0,1.1,0.1 },{ 5.8,4.0,1.2,0.2 },
		{ 5.7,4.4,1.5,0.4 },{ 5.4,3.9,1.3,0.4 },{ 5.1,3.5,1.4,0.3 },
		{ 5.7,3.8,1.7,0.3 },{ 5.1,3.8,1.5,0.3 },{ 7.0,3.2,4.7,1.4 },
		{ 6.4,3.2,4.5,1.5 },{ 6.9,3.1,4.9,1.5 },{ 5.5,2.3,4.0,1.3 },
		{ 6.5,2.8,4.6,1.5 },{ 5.7,2.8,4.5,1.3 },{ 6.3,3.3,4.7,1.6 },
		{ 4.9,2.4,3.3,1.0 },{ 6.6,2.9,4.6,1.3 },{ 5.2,2.7,3.9,1.4 },
		{ 5.0,2.0,3.5,1.0 },{ 5.9,3.0,4.2,1.5 },{ 6.0,2.2,4.0,1.0 },
		{ 6.1,2.9,4.7,1.4 },{ 5.6,2.9,3.6,1.3 },{ 6.7,3.1,4.4,1.4 },
		{ 5.6,3.0,4.5,1.5 },{ 5.8,2.7,4.1,1.0 },{ 6.2,2.2,4.5,1.5 },
		{ 5.6,2.5,3.9,1.1 },{ 6.3,3.3,6.0,2.5 },{ 5.8,2.7,5.1,1.9 },
		{ 7.1,3.0,5.9,2.1 },{ 6.3,2.9,5.6,1.8 },{ 6.5,3.0,5.8,2.2 },
		{ 7.6,3.0,6.6,2.1 },{ 4.9,2.5,4.5,1.7 },{ 7.3,2.9,6.3,1.8 },
		{ 6.7,2.5,5.8,1.8 },{ 7.2,3.6,6.1,2.5 },{ 6.5,3.2,5.1,2.0 },
		{ 6.4,2.7,5.3,1.9 },{ 6.8,3.0,5.5,2.1 },{ 5.7,2.5,5.0,2.0 },
		{ 5.8,2.8,5.1,2.4 },{ 6.4,3.2,5.3,2.3 },{ 6.5,3.0,5.5,1.8 },
		{ 7.7,3.8,6.7,2.2 },{ 7.7,2.6,6.9,2.3 },{ 6.0,2.2,5.0,1.5 }
	};
	Mat trainingDataMat(60, 4, CV_32FC1, trainingData);

	//训练样本所对应的类别，S表示setosa，V表示versicolor，R表示virginica
	int responses[60] = {   'S','S','S',
							'S','S','S',
							'S','S','S',
							'S','S','S',
							'S','S','S',
							'S','S','S',
							'S','S','V',
							'V','V','V',
							'V','V','V',
							'V','V','V',
							'V','V','V',
							'V','V','V',
							'V','V','V',
							'V','R','R',
							'R','R','R',
							'R','R','R',
							'R','R','R',
							'R','R','R',
							'R','R','R',
							'R','R','R' 
	};

	Mat labelsMat(60, 1, CV_32SC1, responses);//Mat responsesMat(60, 1, CV_32FC1, responses);

	//设置SVM参数
	Ptr<SVM> svm = SVM::create();    //创建一个分类器
	svm->setType(SVM::C_SVC);    //设置svm类型 //SVM类型为C-SVC
	svm->setKernel(SVM::RBF); //设置核函数; //核函数为高斯核函数
	svm->setDegree(0.5);
	svm->setGamma(8.0);//高斯核函数中的γ参数设置为8
	svm->setCoef0(1);
	svm->setNu(0.5);
	svm->setP(0);
	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 1000, 0.01));//迭代的终止条件
	svm->setC(10);//C参数设置为10

	//建立SVM模型
	Ptr<TrainData> tData = TrainData::create(trainingDataMat, ROW_SAMPLE, labelsMat);
	svm->train(tData);

	//预测样本数据
	double sampleData[4] = { 6.7, 3.1, 4.7, 1.5 };//{ 5.1,3.5,1.4,0.2 };//
	Mat testMat(1, 4, CV_32FC1, sampleData);
	float response = svm->predict(testMat);
	cout << endl << "result:  " << (char)response << endl;    //输出结果

	pause();
	return 0;
}
/*
//在opencv中的机器学习算法
//https://www.cnblogs.com/denny402/p/5032232.html

1、正态贝叶斯
// 创建贝叶斯分类器
Ptr<NormalBayesClassifier> model=NormalBayesClassifier::create();
// 设置训练数据
Ptr<TrainData> tData =TrainData::create(trainingDataMat, ROW_SAMPLE, labelsMat);
//训练分类器
model->train(tData);
//预测数据
float response = model->predict(testMat);


2、K最近邻
Ptr<KNearest> knn = KNearest::create();  //创建knn分类器
knn->setDefaultK(K);    //设定k值
knn->setIsClassifier(true);
// 设置训练数据
Ptr<TrainData> tData = TrainData::create(trainingDataMat, ROW_SAMPLE, labelsMat);
knn->train(tData);
float response = knn->predict(testMat);


3、支持向量机
Ptr<SVM> svm = SVM::create();    //创建一个分类器
svm->setType(SVM::C_SVC);    //设置svm类型
svm->setKernel(SVM::POLY); //设置核函数;
svm->setDegree(0.5);
svm->setGamma(1);
svm->setCoef0(1);
svm->setNu(0.5);
svm->setP(0);
svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER+TermCriteria::EPS, 1000, 0.01));
svm->setC(C);
Ptr<TrainData> tData = TrainData::create(trainingDataMat, ROW_SAMPLE, labelsMat);
svm->train(tData);
float response = svm->predict(testMat);


4、决策树： decision tree
Ptr<DTrees> dtree = DTrees::create();  //创建分类器
dtree->setMaxDepth(8);   //设置最大深度
dtree->setMinSampleCount(2);
dtree->setUseSurrogates(false);
dtree->setCVFolds(0); //交叉验证
dtree->setUse1SERule(false);
dtree->setTruncatePrunedTree(false);
Ptr<TrainData> tData = TrainData::create(trainingDataMat, ROW_SAMPLE, labelsMat);
dtree->train(tData);
float response = dtree->predict(testMat);


5、ADA Boost：adaboost
Ptr<Boost> boost = Boost::create();
boost->setBoostType(Boost::DISCRETE);
boost->setWeakCount(100);
boost->setWeightTrimRate(0.95);
boost->setMaxDepth(2);
boost->setUseSurrogates(false);
boost->setPriors(Mat());
Ptr<TrainData> tData = TrainData::create(trainingDataMat, ROW_SAMPLE, labelsMat);
boost->train(tData);
float response = boost->predict(testMat);


6、梯度提升决策树：gradient boosted trees
此算法在opencv3.0中被注释掉了，原因未知，因此此处提供一个老版本的算法。
GBTrees::Params params( GBTrees::DEVIANCE_LOSS, // loss_function_type
100, // weak_count
0.1f, // shrinkage
1.0f, // subsample_portion
2, // max_depth
false // use_surrogates )
);
Ptr<TrainData> tData = TrainData::create(trainingDataMat, ROW_SAMPLE, labelsMat);
Ptr<GBTrees> gbtrees = StatModel::train<GBTrees>(tData, params);
float response = gbtrees->predict(testMat);


7、随机森林：random forest
Ptr<RTrees> rtrees = RTrees::create();
rtrees->setMaxDepth(4);
rtrees->setMinSampleCount(2);
rtrees->setRegressionAccuracy(0.f);
rtrees->setUseSurrogates(false);
rtrees->setMaxCategories(16);
rtrees->setPriors(Mat());
rtrees->setCalculateVarImportance(false);
rtrees->setActiveVarCount(1);
rtrees->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 5, 0));
Ptr<TrainData> tData = TrainData::create(trainingDataMat, ROW_SAMPLE, labelsMat);
rtrees->train(tData);
float response = rtrees->predict(testMat);


8、人工神经网络：artificial neural networks
Ptr<ANN_MLP> ann = ANN_MLP::create();
ann->setLayerSizes(layer_sizes);
ann->setActivationFunction(ANN_MLP::SIGMOID_SYM, 1, 1);
ann->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER+TermCriteria::EPS, 300, FLT_EPSILON));
ann->setTrainMethod(ANN_MLP::BACKPROP, 0.001);
Ptr<TrainData> tData = TrainData::create(trainingDataMat, ROW_SAMPLE, labelsMat);
ann->train(tData);
float response = ann->predict(testMat);


9、EM算法：expectation-maximization
EM算法与前面的稍微有点不同，它需要创建很多个model,将trainingDataMat分成很多个modelSamples，每个modelSamples训练出一个model
训练核心代码为：
int nmodels = (int)labelsMat.size();
vector<Ptr<EM> > em_models(nmodels);
Mat modelSamples;
for( i = 0; i < nmodels; i++ )
{
const int componentCount = 3;
modelSamples.release();
for (j = 0; j < labelsMat.rows; j++)
{
if (labelsMat.at<int>(j,0)== i)
modelSamples.push_back(trainingDataMat.row(j));
}
// learn models
if( !modelSamples.empty() )
{
Ptr<EM> em = EM::create();
em->setClustersNumber(componentCount);
em->setCovarianceMatrixType(EM::COV_MAT_DIAGONAL);
em->trainEM(modelSamples, noArray(), noArray(), noArray());
em_models[i] = em;
}
}
*/