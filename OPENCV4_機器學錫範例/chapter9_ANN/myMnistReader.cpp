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
* �Ӵ򿪵��ļ��ж�ȡ����
* ����1��DataFile�������ļ�
* ����2��NumberOfData��ͼ����߱�ǩ����
* ����3��DataSizeInBytes��ÿ�����ݵĳ���
* ���أ�Mat����ÿ��1������
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

/** ��ȡͼ������
* ����1��FileName��ͼ�������ļ�
* ���أ�Mat����ÿ��1��ͼ��
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


/** ��ȡ��ǩ����
* ����1��FileName����ǩ�����ļ�
* ���أ�Mat����ÿ��1����ǩ
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

/** ��ȡ����ͼ������
* ����1��images����ȡ��ͼ��
* ����2��n��ͼ����ţ�n=1~60000��
* ���أ�Mat���͵�ͼ������
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

/** ��0~9�ı�ǩת��Ϊ[0,0,...,1]��������ʽ
* ����1��labelMat����ű�ǩ�ľ���
* ���أ�������ʽ�ı�ǩ����
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
			eyeMat.row(0).copyTo(lableVec.row(i));// ��labVec�ĵ�i�и�ֵ
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

/** ��ȡ0~9��Ԥ����
* ����1��responesMat��ʹ��predict()������Ԥ����
* ���أ�ANN�Ե���������Ԥ����
*/
int getResponse(cv::Mat &responesMat)
{
	int minmaxIdx;
	//double *min, *max;
	cv::Point maxLoc;
	cv::minMaxLoc(responesMat, NULL, NULL, NULL, &maxLoc);
	return maxLoc.x;
}