// SVM.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "opencv.hpp"

using namespace cv;
using namespace cv::ml;
using namespace std;

// ͼ�����
cv::Mat deskew(cv::Mat& img);
// ��������ͼ��
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

// ����HOG�������ݼ�
void generateDataSet(Mat &img, vector<Mat> &trainDataVec, vector<Mat> &testDataVec, vector<int> &trainLabel, vector<int> &testLabel, int train_rows, bool HOG_flag);
void convert_to_ml(const vector< Mat > & train_samples, Mat& trainData);



int main()
{
	// 1.��ȡԭʼ����
	cv::Mat img = imread("digits.png", 1);
	cvtColor(img, img, CV_BGR2GRAY);
	// 2.������ͼ
	cv::Mat img_deskewed = img.clone();
	img_deskewed = deskewBigImage(img);
	//cv::imwrite("digits_deskewed.png", img_deskewed);
	//cv::imshow("img_deskewed", img_deskewed);
	//cv::waitKey();
	// 3.����ѵ����
	// ����ѵ���������Լ���С
	int train_sample_count = 4000;
	int test_sample_count = 1000;
	int train_rows = 4; //  ÿ������ѵ����������4000/10��/100(����/��)=4
	cv::Mat trainHOGData, testHOGData, trainRawData, testRawData; // ����ѵ��������Լ�
	vector<cv::Mat> trainHOGDataVec, testHOGDataVec, trainRawDataVec, testRawDataVec;
	// ����ѵ���������Լ����ǩ
	vector<int> trainHOGLabel, testHOGLabel, trainRawLabel, testRawLabel;
	generateDataSet(img_deskewed, trainHOGDataVec, testHOGDataVec, trainHOGLabel, testHOGLabel, train_rows, true);
	generateDataSet(img_deskewed, trainRawDataVec, testRawDataVec, trainRawLabel, testRawLabel, train_rows, false);

	// 2.2����SVM������
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
	// ѵ��Train SVM on training data 
	convert_to_ml(trainHOGDataVec, trainHOGData);
	convert_to_ml(testHOGDataVec, testHOGData);
	convert_to_ml(trainRawDataVec, trainRawData);
	convert_to_ml(testRawDataVec, testRawData);

	printf("��ʼѵ��hog+svm...\n");
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
	//printf("��ʼѵ��raw svm...\n");
	svm_raw->train(trainRawData, cv::ml::ROW_SAMPLE, trainRawLabel);
	
	double optC = svm->getC();
	double optGamma = svm->getGamma();
	//int optDegree = svm->getDegree();
	printf("ѵ�����,svm_hog���Ų���C = %f,Gamma = %f\n\n",optC, optGamma);

	double optCsvm_raw = svm_raw->getC();
	double optGammasvm_raw = svm_raw->getGamma();
	//int optDegree = svm->getDegree();
	printf("ѵ�����,svm_raw���Ų���C = %f,Gamma = %f\n\n", optCsvm_raw, optGammasvm_raw);
	//printf("ѵ�����,���Ų���:C = %f, Gamma = %f, Degree = %d\n\n", optC, optGamma, optDegree);
	//system("PAUSE");
	// Save trained model 
	//svm->save("digits_hog_svm_xx_model.yml");
	//svm_raw->save("digits_raw_svm_model.yml");
	// ����Test on a held out test set
	cv::Mat result, result_raw;
	printf("��ʼ����...\n");
	svm->predict(testHOGData, result);

	// ������
	// ����
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
			//printf("label: %d, predict: %d ��\n", actual, predict);
			f++;
		}
	}
	printf("HOG SVM ������ɣ�\n");
	// ������

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
			//printf("label: %d, predict: %d ��\n", actual, predict);
			f++;
		}
	}
	printf("Raw SVM �������: \n");
	// ������
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

// ��������ͼ��
cv::Mat deskewBigImage(cv::Mat& img)
{
	int digit_image_width = 20;
	int digit_image_height = 20;
	int big_image_width = img.cols;
	int big_image_height = img.rows;
	int digit_per_rows = big_image_width / digit_image_width;   // ÿ���ַ���100
	int digit_per_cols = big_image_height / digit_image_height; // ÿ���ַ���50
	printf("digit_rows = %d, digit_cols = %d \n", digit_per_rows, digit_per_cols);
	
	cv::Mat deskewed_image = img.clone();// ����ͼ��
	for (int j = 0; j < digit_per_cols; j++) // ����ÿ��y:0-50
	{
		//printf("j = %d \n", j);
		for (int i = 0; i < digit_per_rows; i++)// ����ÿ��x:0-100
		{			
			//printf("i = %d, j = %d \n", i, j);
			cv::Mat temp_digit,deskewed_digit;
			cv::Rect roi;
			// ��ȡ����ͼ�� x,y,w,h
			roi = cv::Rect(i*digit_image_width,j*digit_image_height, digit_image_width, digit_image_height);
			//cout << "roi = "<<roi << endl;
			temp_digit = deskewed_image(roi);
			
			// ƫбУ��
			deskewed_digit = deskew(temp_digit);
			//cv::imshow("before", temp_digit);
			//cv::imshow("after", deskewed_digit);
			//cv::waitKey(20);
			// ������ͼ�У������Ǳ������������ͼ
			deskewed_digit.copyTo(deskewed_image(roi));
		}
	}
	// ���ͼ
	cv::imwrite("digits_deskewed.png", deskewed_image);
	return deskewed_image;
}

/** @����ģ�͵�ѵ��������Լ�
����1��img       �����룬�Ҷ�ͼ���ɹ̶��ߴ�Сͼƴ�ӳɵĴ�ͼ����ͬ����Сͼ����������
����2��trainDataVec�������ѵ������ά��Ϊ��ѵ�������� * ����������������CV_32F����
����3��testDataVec����������Լ���ά��Ϊ������������ * ����������������CV_32F����
����4��trainLabel�������ѵ������ǩ��ά��Ϊ��ѵ�������� * 1��int������
����4��testLabel ����������Լ���ǩ��ά��Ϊ������������ * 1��int������
����5��train_rows�����룬����ѵ����������ռ������Ĭ��4������ѵ����1�����ڲ���
����6��HOG_flag�����룬true:��ȡHOG��������Ϊ����������false:ֱ��ʹ��ͼ��ԭʼ������Ϊ��������
*/
void generateDataSet(Mat &img, vector<Mat> &trainDataVec, vector<Mat> &testDataVec, vector<int> &trainLabel, vector<int> &testLabel, int train_rows, bool HOG_flag)
{
	// ��ʼ��ͼ������Ƭͼ����������
	int width_slice = 20;  // ����������Ƭͼ��Ŀ��
	int height_slice = 20; // ����������Ƭͼ��ĸ߶�
	int row_sample = 100;  // ÿ��������100��Сͼ
	int col_sample = 50;   // ÿ��������50��Сͼ
	int row_single_number = 5; // ��������ռ5��
	int test_rows = row_single_number - train_rows; // ����������ռ����

	Mat trainMat(train_rows * 20 * 10, img.cols, CV_8UC1); // �������ѵ��ͼƬ
	trainMat = Scalar::all(0);
	Mat testMat(test_rows * 20 * 10, img.cols, CV_8UC1);  // ������в���ͼƬ
	testMat = Scalar::all(0);

	// ���ɲ��ԡ�ѵ����ͼ
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
		// ��ȡ��ѵ�������зֱ��Ƶ�ѵ��ͼ�����ͼ��
		tempTrainMat.copyTo(roi_train, mask_train);
		tempTestMat.copyTo(roi_test, mask_test);
		//��ʾЧ��ͼ
		//imshow("trainHOGMat", trainMat);
		//imshow("tesetHOGMat", testMat);
		//cv::waitKey(10);
	}
	// ���ͼ
	//imwrite("trainHOGMat.jpg", trainMat);
	//imwrite("testHOGMat.jpg", testMat);

	// ����ѵ������������
	printf("��ʼ����ѵ������������...\n");
	Rect roi;
	for (int i = 1; i <= col_sample; i++) // 50�У�1-50������ͼ��
	{
		//printf("��%d��: \n", i);
		for (int j = 1; j <= row_sample; j++) // 100�У�1-100������ͼ��
		{
			// ����Ϊѵ����
			Mat temp_single_num; // ��ȡһ������ͼ��
								 // �ؼ����裺��ǰ��Ƭ���ֵ�λ������
			roi = Rect((j-1)*width_slice, (i-1)*height_slice, width_slice, height_slice);
			temp_single_num = img(roi).clone(); // ע��˴���Ҫʹ�����.clone()��������ܸı���Ƭͼ����״������roi�ڴ���������
			//imshow("slice", temp_single_num);
			//waitKey();
			if (i % 5 != 0)
			{
				// ��ʼ�м�Ϊ1-4,6-9,11-14...46-49��Ϊ���Լ�
				// ������������Ƭ����������������Mat������
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
			{	// ��ʼ�м�Ϊ1����5,10,15...50��Ϊ���Լ�
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
	printf("ѵ������������������\n\n");

	// ���ɱ�ǩ
	printf("��ʼ���ɱ�ǩ����...\n");
	// ѵ������train_rows=4�У���������=5-train_rows=1��
	// 4 rows 0 (400��0), 4 rows 1(400��1), ... 4 rows 9(400��9)
	//trainLabel.assign(train_rows*row_sample*10, 0);
	for (int i = 0; i < 10; i++)
	{
		trainLabel.insert(trainLabel.begin() + i * 400, 400, i);// c.insert(pos,n,elem); ��posλ�ò���n��elem���ݡ��޷���ֵ��
		testLabel.insert(testLabel.begin() + i * 100, 100, i);
	}
	printf("��ǩ����������\n\n");

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
