#ifndef MNISTREADER  
#define MNISTREADER  

#include <iostream>  
#include <fstream>  
#include <opencv.hpp>  

struct MNISTImageFileHeader
{
	unsigned char MagicNumber[4];
	unsigned char NumberOfImages[4];
	unsigned char NumberOfRows[4];
	unsigned char NumberOfColums[4];
};

struct MNISTLabelFileHeader
{
	unsigned char MagicNumber[4];
	unsigned char NumberOfLabels[4];
};

int ConvertCharArrayToInt(unsigned char* array, int LengthOfArray);
cv::Mat ReadData(std::fstream& DataFile, int NumberOfData, int DataSizeInBytes);
cv::Mat ReadImages(std::string& FileName);
cv::Mat ReadLabels(std::string& FileName);
cv::Mat ReadSingleImage(cv::Mat &images, int n);
cv::Mat CvtLabelData2Vec(cv::Mat &labelMat);
int getResponse(cv::Mat &responesMat);

#endif // MNISTREADER  