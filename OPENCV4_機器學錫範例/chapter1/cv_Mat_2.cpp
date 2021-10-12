#include "stdafx.h"
#include "opencv.hpp"

using namespace std;
int main()    
{
    cv::Mat m0 = cv::Mat::eye(3, 3, CV_8UC1);
    cv::Mat m1 = cv::Mat::ones(3, 3, CV_8UC1);

    cout << "m0 = " << endl << m0 << endl << endl;
    cout << "m1 = " << endl << m1 << endl << endl;
    cout << "m0 + m1 = " << endl << m0 + m1 << endl << endl;
    cout << "(m1 .* m2) = " << endl << (m1.mul(m2)) << endl << endl;
    cout << "(m1 ./ m2) = " << endl << (m1 / m2) << endl << endl;
    cout << "m0 < m1 = " << endl << (m0 < m1) << endl << endl;
    cout << "m0 <= m1 = " << endl << (m0 <= m1) << endl << endl;
    system("pause");
    return 0;
