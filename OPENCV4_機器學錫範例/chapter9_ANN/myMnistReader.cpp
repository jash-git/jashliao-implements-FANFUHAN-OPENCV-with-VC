#include "stdafx.h"
#include "myMnistReader.h"

int ConvertCharArrayToInt(unsigned char* array, int LengthOfArray)
{
	if (LengthOfArray < 0)
	{
		return -1;
	}
	int result = static_cast<signed int>(array[0]);
	for (int i = 1; i < LengthOfArray; i++)
	{
		result = (result << 8) + array[i];
	}
	return result;
}


/**
* 从打开的文件中读取数据
* 参数1：DataFile，数据文件
* 参数2：NumberOfData，图像或者标签数量
* 参数3：DataSizeInBytes，每个数据的长度
* 返回：Mat矩阵，每行1个数据
*/
cv::Mat ReadData(std::fstream& DataFile, int NumberOfData, int DataSizeInBytes)
{
	cv::Mat DataMat;
	// read the data if the file is opened.  
	if (DataFile.is_open())
	{
		int AllDataSizeInBytes = DataSizeInBytes * NumberOfData;
		unsigned char* TmpData = new unsigned char[AllDataSizeInBytes];
		DataFile.read((char *)TmpData, AllDataSizeInBytes);

		DataMat = cv::Mat(NumberOfData, DataSizeInBytes, CV_8UC1,
			TmpData).clone();
		delete[] TmpData;
		DataFile.close();
	}
	return DataMat;
}

/** 读取图像数据
* 参数1：FileName，图像数据文件
* 返回：Mat矩阵，每行1幅图像
*/
cv::Mat ReadImages(std::string& FileName)
{
	std::fstream File(FileName.c_str(), std::ios_base::in | std::ios_base::binary);

	if (!File.is_open())
	{
		return cv::Mat();
	}

	MNISTImageFileHeader FileHeader;
	File.read((char *)(&FileHeader), sizeof(FileHeader));

	int NumberOfImage = ConvertCharArrayToInt(FileHeader.NumberOfImages, 4);
	int ImageSizeInBytes = 28 * 28;
	return ReadData(File, NumberOfImage, ImageSizeInBytes);	
}


/** 读取标签数据
* 参数1：FileName，标签数据文件
* 返回：Mat矩阵，每行1个标签
*/
cv::Mat ReadLabels(std::string& FileName)
{
	std::fstream File(FileName.c_str(), std::ios_base::in | std::ios_base::binary);
	if (!File.is_open())
	{
		return cv::Mat();	}

	MNISTLabelFileHeader FileHeader;
	File.read((char *)(&FileHeader), sizeof(FileHeader));

	int NumberOfLabels = ConvertCharArrayToInt(FileHeader.NumberOfLabels, 4);
	int LabelSizeInBytes = 1;
	return ReadData(File, NumberOfLabels, LabelSizeInBytes);
}

/** 读取单幅图像数据
* 参数1：images，读取的图像
* 参数2：n，图像序号（n=1~60000）
* 返回：Mat类型的图像数据
*/
cv::Mat ReadSingleImage(cv::Mat &images, int n)
{
	int ImageSize = 28;
	cv::Mat singleImage;
	if (n >= 0)
	{
		cv::Mat temp;
		temp = images.rowRange(n, n + 1).clone();
		singleImage = temp.reshape(0, 28);
		return singleImage;
	}
	else
		return cv::Mat();
}

/** 将0~9的标签转换为[0,0,...,1]的向量形式
* 参数1：labelMat，存放标签的矩阵
* 返回：向量形式的标签矩阵
*/
cv::Mat CvtLabelData2Vec(cv::Mat &labelMat)
{
	int size = labelMat.rows;
	cv::Mat lableVec = cv::Mat(cv::Size(10, size), CV_32FC1);// vector rows = size, cols = 10;
	cv::Mat eyeMat = cv::Mat::eye(cv::Size(10, 10), CV_32FC1);

	for (int i = 0; i < size; i++) // ith row
	{
		switch ((int)labelMat.at<char>(i))
		{
		case 0:
			eyeMat.row(0).copyTo(lableVec.row(i));// 对labVec的第i行赋值
			break;
		case 1:
			eyeMat.row(1).copyTo(lableVec.row(i));
			break;
		case 2:
			eyeMat.row(2).copyTo(lableVec.row(i));
			break;
		case 3:
			eyeMat.row(3).copyTo(lableVec.row(i));
			break;
		case 4:
			eyeMat.row(4).copyTo(lableVec.row(i));
			break;
		case 5:
			eyeMat.row(5).copyTo(lableVec.row(i));
			break;
		case 6:
			eyeMat.row(6).copyTo(lableVec.row(i));
			break;
		case 7:
			eyeMat.row(7).copyTo(lableVec.row(i));
			break;
		case 8:
			eyeMat.row(8).copyTo(lableVec.row(i));
			break;
		case 9:
			eyeMat.row(9).copyTo(lableVec.row(i));
			break;
		default:
			break;
		}
	}
	return lableVec;
}

/** 获取0~9的预测结果
* 参数1：responesMat，使用predict()方法的预测结果
* 返回：ANN对单个样本的预测结果
*/
int getResponse(cv::Mat &responesMat)
{
	int minmaxIdx;
	//double *min, *max;
	cv::Point maxLoc;
	cv::minMaxLoc(responesMat, NULL, NULL, NULL, &maxLoc);
	return maxLoc.x;
}