// SVM.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "opencv.hpp"

using namespace cv;
using namespace cv::ml;
using namespace std;

// 图像矫正
cv::Mat deskew(cv::Mat& img);
// 矫正所有图像
cv::Mat deskewBigImage(cv::Mat& img);
HOGDescriptor hog(
	Size(20, 20), //winSize
	Size(10, 10), //blocksize
	Size(5, 5), //blockStride,
	Size(10, 10), //cellSize,
	9, //nbins,
	1, //derivAper,
	-1, //winSigma,
	0, //histogramNormType,
	0.2, //L2HysThresh,
	1,//gammal correction,
	64,//nlevels=64
	1);//Use signed gradients 

// 生成HOG特征数据集
void generateDataSet(Mat &img, vector<Mat> &trainDataVec, vector<Mat> &testDataVec, vector<int> &trainLabel, vector<int> &testLabel, int train_rows, bool HOG_flag);
void convert_to_ml(const vector< Mat > & train_samples, Mat& trainData);



int main()
{
	// 1.读取原始数据
	cv::Mat img = imread("digits.png", 1);
	cvtColor(img, img, CV_BGR2GRAY);
	// 2.矫正大图
	cv::Mat img_deskewed = img.clone();
	img_deskewed = deskewBigImage(img);
	//cv::imwrite("digits_deskewed.png", img_deskewed);
	//cv::imshow("img_deskewed", img_deskewed);
	//cv::waitKey();
	// 3.制作训练集
	// 设置训练集、测试集大小
	int train_sample_count = 4000;
	int test_sample_count = 1000;
	int train_rows = 4; //  每类用于训练的行数，4000/10类/100(样本/行)=4
	cv::Mat trainHOGData, testHOGData, trainRawData, testRawData; // 申明训练集与测试集
	vector<cv::Mat> trainHOGDataVec, testHOGDataVec, trainRawDataVec, testRawDataVec;
	// 生成训练集、测试集与标签
	vector<int> trainHOGLabel, testHOGLabel, trainRawLabel, testRawLabel;
	generateDataSet(img_deskewed, trainHOGDataVec, testHOGDataVec, trainHOGLabel, testHOGLabel, train_rows, true);
	generateDataSet(img_deskewed, trainRawDataVec, testRawDataVec, trainRawLabel, testRawLabel, train_rows, false);

	// 2.2创建SVM分类器
	// Set up SVM for OpenCV 3
	Ptr<SVM> svm = SVM::create();
	Ptr<SVM> svm_raw = SVM::create();
	// Set SVM type
	//svm->setType(SVM::C_SVC);
	//svm_raw->setType(SVM::C_SVC);
	// Set SVM Kernel to Radial Basis Function (RBF) 
	svm->setKernel(SVM::RBF);//LINEAR
	svm_raw->setKernel(SVM::RBF);
	// Set parameter C
	svm->setC(10);//12.5
	svm_raw->setC(10);

	// Set parameter Gamma
	svm->setGamma(0.5);//RBF
	//svm->setGamma(1);
	//svm->setCoef0(0);
	//svm->setDegree(2);
	//svm->setCoef0(0);
	//svm_raw->setCoef0(0);
	svm_raw->setGamma(0.5);
	//svm_raw->setDegree(2);
	// 训练Train SVM on training data 
	convert_to_ml(trainHOGDataVec, trainHOGData);
	convert_to_ml(testHOGDataVec, testHOGData);
	convert_to_ml(trainRawDataVec, trainRawData);
	convert_to_ml(testRawDataVec, testRawData);

	printf("开始训练hog+svm...\n");
	//======================== trainAuto =============================
	//RBF
	//svm->setKernel(SVM::RBF);
	//Ptr<ParamGrid> Cgrid = SVM::getDefaultGridPtr(SVM::C);
	//Ptr<ParamGrid> gammaGrid = SVM::getDefaultGridPtr(SVM::GAMMA);
	//cv::ml::ParamGrid mannualCgrid(
	//	6.0, // minVal
	//	12.0, // maxVal
	//	1.5); // logSetp
	//Ptr<ParamGrid> mannualCgridPtr = &mannualCgrid;

	Ptr<ParamGrid>  artificalCgrid; 
	// Creates a ParamGrid Ptr that can be given to the SVM::trainAuto method. 
	artificalCgrid->create(
		6.0, // minVal
		12.0, // maxVal
		1.5 // logSetp
	);

	//svm->trainAuto(trainHOGData, 
	//	ROW_SAMPLE,
	//	trainHOGLabel,  
	//	10,   // KFold
	//	Cgrid, // or Cgrid
	//	gammaGrid// GAMMA
	//);

	//POLY
	//svm->setKernel(SVM::POLY);
	//Ptr<ParamGrid> Cgrid = SVM::getDefaultGridPtr(SVM::C);
	//Ptr<ParamGrid> gammaGrid = SVM::getDefaultGridPtr(SVM::GAMMA);
	//Ptr<ParamGrid> degreeGrid = SVM::getDefaultGridPtr(SVM::DEGREE);
	//svm->setDegree(2);
	//svm->trainAuto(trainHOGData,
	//	ROW_SAMPLE,
	//	trainHOGLabel,
	//	10,   // KFold
	//	Cgrid, // C
	//	gammaGrid,// GAMMA
	//	degreeGrid// DEGREE
	//);

	svm->train(trainHOGData, cv::ml::ROW_SAMPLE, trainHOGLabel);
	//printf("开始训练raw svm...\n");
	svm_raw->train(trainRawData, cv::ml::ROW_SAMPLE, trainRawLabel);
	
	double optC = svm->getC();
	double optGamma = svm->getGamma();
	//int optDegree = svm->getDegree();
	printf("训练完成,svm_hog最优参数C = %f,Gamma = %f\n\n",optC, optGamma);

	double optCsvm_raw = svm_raw->getC();
	double optGammasvm_raw = svm_raw->getGamma();
	//int optDegree = svm->getDegree();
	printf("训练完成,svm_raw最优参数C = %f,Gamma = %f\n\n", optCsvm_raw, optGammasvm_raw);
	//printf("训练完成,最优参数:C = %f, Gamma = %f, Degree = %d\n\n", optC, optGamma, optDegree);
	//system("PAUSE");
	// Save trained model 
	//svm->save("digits_hog_svm_xx_model.yml");
	//svm_raw->save("digits_raw_svm_model.yml");
	// 测试Test on a held out test set
	cv::Mat result, result_raw;
	printf("开始测试...\n");
	svm->predict(testHOGData, result);

	// 输出结果
	// 精度
	int t = 0, f = 0;	
	for (int i = 0; i < test_sample_count; i++)
	{		
		int predict = int(result.at<float>(i));
		int actual = testHOGLabel[i]; // 2020.2.15
		if (predict == actual)
		{
			//printf("label: %d, predict: %d\n", actual, predict);
			t++;
		}
		else
		{
			//printf("label: %d, predict: %d ×\n", actual, predict);
			f++;
		}
	}
	printf("HOG SVM 测试完成：\n");
	// 输出结果

	float accuracy = (t * 1.0) / (t + f);
	printf("total predict %d samples\n",t+f);
	printf("correct = %d\n", t);
	printf("error = %d\n", f);
	printf("accuracy = %.4f\n", accuracy);
	//system("PAUSE");
	// Raw svm
	svm_raw->predict(testRawData, result_raw);
	t = 0;
	f = 0;
	for (int i = 0; i < test_sample_count; i++)
	{
		//printf("result_raw(i) = %f\n",result_raw.at<float>(i));
		int predict = int(result_raw.at<float>(i));
		int actual = testRawLabel[i]; // 2020.2.15
		if (predict == actual)
		{
			//printf("label: %d, predict: %d\n", actual, predict);
			t++;
		}
		else
		{
			//printf("label: %d, predict: %d ×\n", actual, predict);
			f++;
		}
	}
	printf("Raw SVM 测试完成: \n");
	// 输出结果
	accuracy = (t * 1.0) / (t + f);
	printf("total predict %d samples\n", t + f);
	printf("correct = %d\n", t);
	printf("error = %d\n", f);
	printf("accuracy = %.4f\n", accuracy);
	system("PAUSE");
    return 0;
}


cv::Mat deskew(cv::Mat& img)
{
	cv::Moments m = moments(img);
	bool affineFlags = WARP_INVERSE_MAP | INTER_LINEAR;
	int SZ = img.rows;
	if (abs(m.mu02) < 1e-2)
	{
		// No deskewing needed. 
		return img.clone();
	}
	// Calculate skew based on central momemts. 
	double skew = m.mu11 / m.mu02;
	//printf("skew1 = %f\n", skew);
	// Calculate affine transform to correct skewness. 
	cv::Mat warpMat = (cv::Mat_<double>(2, 3) << 1, -skew, 0.5*SZ*skew, 0, 1, 0);
	cv::Mat imgOut = cv::Mat::zeros(img.rows, img.cols, img.type());
	cv::warpAffine(img, imgOut, warpMat, imgOut.size());
	cv::Moments m_after = moments(imgOut);
	skew = m_after.mu11 / m_after.mu02;
	//printf("skew2 = %f\n\n", skew);
	return imgOut;
}

// 矫正所有图像
cv::Mat deskewBigImage(cv::Mat& img)
{
	int digit_image_width = 20;
	int digit_image_height = 20;
	int big_image_width = img.cols;
	int big_image_height = img.rows;
	int digit_per_rows = big_image_width / digit_image_width;   // 每行字符数100
	int digit_per_cols = big_image_height / digit_image_height; // 每列字符数50
	printf("digit_rows = %d, digit_cols = %d \n", digit_per_rows, digit_per_cols);
	
	cv::Mat deskewed_image = img.clone();// 拷贝图像
	for (int j = 0; j < digit_per_cols; j++) // 遍历每列y:0-50
	{
		//printf("j = %d \n", j);
		for (int i = 0; i < digit_per_rows; i++)// 遍历每行x:0-100
		{			
			//printf("i = %d, j = %d \n", i, j);
			cv::Mat temp_digit,deskewed_digit;
			cv::Rect roi;
			// 获取单张图像 x,y,w,h
			roi = cv::Rect(i*digit_image_width,j*digit_image_height, digit_image_width, digit_image_height);
			//cout << "roi = "<<roi << endl;
			temp_digit = deskewed_image(roi);
			
			// 偏斜校正
			deskewed_digit = deskew(temp_digit);
			//cv::imshow("before", temp_digit);
			//cv::imshow("after", deskewed_digit);
			//cv::waitKey(20);
			// 贴到大图中：如果是潜拷贝则无需贴图
			deskewed_digit.copyTo(deskewed_image(roi));
		}
	}
	// 存大图
	cv::imwrite("digits_deskewed.png", deskewed_image);
	return deskewed_image;
}

/** @生成模型的训练集与测试集
参数1：img       ，输入，灰度图像，由固定尺寸小图拼接成的大图，不同类别的小图像依次排列
参数2：trainDataVec，输出，训练集，维度为：训练样本数 * 单个样本特征数，CV_32F类型
参数3：testDataVec，输出，测试集，维度为：测试样本数 * 单个样本特征数，CV_32F类型
参数4：trainLabel，输出，训练集标签，维度为：训练样本数 * 1，int型向量
参数4：testLabel ，输出，测试集标签，维度为：测试样本数 * 1，int型向量
参数5：train_rows，输入，用于训练的样本所占行数，默认4行用于训练，1行用于测试
参数6：HOG_flag，输入，true:提取HOG描述子作为特征向量，false:直接使用图像原始像素作为特征向量
*/
void generateDataSet(Mat &img, vector<Mat> &trainDataVec, vector<Mat> &testDataVec, vector<int> &trainLabel, vector<int> &testLabel, int train_rows, bool HOG_flag)
{
	// 初始化图像中切片图与其他参数
	int width_slice = 20;  // 单个数字切片图像的宽度
	int height_slice = 20; // 单个数字切片图像的高度
	int row_sample = 100;  // 每行样本数100幅小图
	int col_sample = 50;   // 每列样本数50幅小图
	int row_single_number = 5; // 单个数字占5行
	int test_rows = row_single_number - train_rows; // 测试样本所占行数

	Mat trainMat(train_rows * 20 * 10, img.cols, CV_8UC1); // 存放所有训练图片
	trainMat = Scalar::all(0);
	Mat testMat(test_rows * 20 * 10, img.cols, CV_8UC1);  // 存放所有测试图片
	testMat = Scalar::all(0);

	// 生成测试、训练大图
	for (int i = 1; i <= 10; i++)
	{
		Mat tempTrainMat = img.rowRange((i - 1) * row_single_number * 20, (i * row_single_number - 1) * 20).clone();
		Mat tempTestMat = img.rowRange((i * row_single_number - 1) * 20, (i * row_single_number) * 20).clone();
		//imshow("tempHOGtrain", tempTrainMat);
		//imshow("tempHOGtest", tempTestMat);
		//printf("tempTrainMat(w, h) = %d, %d\n", tempTrainMat.cols, tempTrainMat.rows);
		//printf("tempTestMat (w, h) = %d, %d\n", tempTestMat.cols,  tempTestMat.rows);
		// train
		cv::Mat roi_train = trainMat(Rect(0, (i - 1) * train_rows * 20, tempTrainMat.cols, tempTrainMat.rows));
		Mat mask_train(roi_train.rows, roi_train.cols, roi_train.depth(), Scalar(1));
		// test
		cv::Mat roi_test = testMat(Rect(0, (i - 1) * test_rows * 20, tempTestMat.cols, tempTestMat.rows));
		Mat mask_test(roi_test.rows, roi_test.cols, roi_test.depth(), Scalar(1));
		// 提取的训练测试行分别复制到训练图与测试图中
		tempTrainMat.copyTo(roi_train, mask_train);
		tempTestMat.copyTo(roi_test, mask_test);
		//显示效果图
		//imshow("trainHOGMat", trainMat);
		//imshow("tesetHOGMat", testMat);
		//cv::waitKey(10);
	}
	// 存大图
	//imwrite("trainHOGMat.jpg", trainMat);
	//imwrite("testHOGMat.jpg", testMat);

	// 生成训练、测试数据
	printf("开始生成训练、测试数据...\n");
	Rect roi;
	for (int i = 1; i <= col_sample; i++) // 50行：1-50行数字图像
	{
		//printf("第%d行: \n", i);
		for (int j = 1; j <= row_sample; j++) // 100列：1-100列数字图像
		{
			// 第行为训练集
			Mat temp_single_num; // 读取一个数字图像
								 // 关键步骤：当前切片数字的位置区域
			roi = Rect((j-1)*width_slice, (i-1)*height_slice, width_slice, height_slice);
			temp_single_num = img(roi).clone(); // 注意此处需要使用深拷贝.clone()，后面才能改变切片图的形状，否则roi内存区域不连续
			//imshow("slice", temp_single_num);
			//waitKey();
			if (i % 5 != 0)
			{
				// 起始行记为1-4,6-9,11-14...46-49行为测试集
				// 将单个数字切片拉成向量连续放入Mat容器中
				if (HOG_flag)
				{
					vector<float> descriptors;
					hog.compute(temp_single_num, descriptors);
					trainDataVec.push_back(Mat(descriptors).clone());
				}					
				else
					trainDataVec.push_back(temp_single_num.reshape(0, 1));
			}
			else
			{	// 起始行记为1，第5,10,15...50行为测试集
				//testData.push_back(descriptors_mat);
				if (HOG_flag)
				{
					vector<float> descriptors;
					hog.compute(temp_single_num, descriptors);
					testDataVec.push_back(Mat(descriptors).clone());
				}
				else
					testDataVec.push_back(temp_single_num.reshape(0, 1));				
			}	
		}
	}
	//trainData.convertTo(trainData, CV_32FC1);
	//testData.convertTo(testData, CV_32FC1);
	printf("训练、测试数据已生成\n\n");

	// 生成标签
	printf("开始生成标签数据...\n");
	// 训练数据train_rows=4行，测试数据=5-train_rows=1行
	// 4 rows 0 (400个0), 4 rows 1(400个1), ... 4 rows 9(400个9)
	//trainLabel.assign(train_rows*row_sample*10, 0);
	for (int i = 0; i < 10; i++)
	{
		trainLabel.insert(trainLabel.begin() + i * 400, 400, i);// c.insert(pos,n,elem); 在pos位置插入n个elem数据。无返回值。
		testLabel.insert(testLabel.begin() + i * 100, 100, i);
	}
	printf("标签数据已生成\n\n");

	//printf("trainLabel(1,400,401,800,801,4000) = %f, %f, %f, %f, %f, %f\n", trainLabel.at<float>(0), trainLabel.at<float>(399), trainLabel.at<float>(400), trainLabel.at<float>(799), trainLabel.at<float>(800), trainLabel.at<float>(3999));
	//printf("testLabel (1,100,101,200,201,1000) = %f, %f, %f, %f, %f, %f\n", testLabel.at<float>(0), testLabel.at<float>(99), testLabel.at<float>(100), testLabel.at<float>(199), testLabel.at<float>(200), testLabel.at<float>(999));
	//cv::waitKey();
}


/*
* Convert training/testing set to be used by OpenCV Machine Learning algorithms.
* TrainData is a matrix of size (#samples x max(#cols,#rows) per samples), in 32FC1.
* Transposition of samples are made if needed.
*/
void convert_to_ml(const vector< Mat > & train_samples, Mat& trainData)
{
	//--Convert data
	const int rows = (int)train_samples.size();
	const int cols = (int)std::max(train_samples[0].cols, train_samples[0].rows);
	Mat tmp(1, cols, CV_32FC1); //< used for transposition if needed
	trainData = Mat(rows, cols, CV_32FC1);
	for (size_t i = 0; i < train_samples.size(); ++i)
	{
		CV_Assert(train_samples[i].cols == 1 || train_samples[i].rows == 1);
		if (train_samples[i].cols == 1)
		{
			transpose(train_samples[i], tmp);
			tmp.copyTo(trainData.row((int)i));
		}
		else if (train_samples[i].rows == 1)
		{
			train_samples[i].copyTo(trainData.row((int)i));
		}
	}
}
