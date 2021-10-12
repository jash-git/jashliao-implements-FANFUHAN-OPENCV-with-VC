#include "stdafx.h"
#include "opencv.hpp"

using namespace std;
int main()
{    
    cv::Point p1(1,2);
    cv::Point p2(3, 4);
    cout << "p1 = " << "(" << p1.x << ", " << p1.y << ")" <<  endl;
    cout << "p2 = " << "(" << p2.x << ", " << p2.y << ")" <<  endl << endl;

    cv::Point3f p3(1.1, 2.4, 3.6);
    cout << "p3.x = " << p3.x << endl;
    cout << "p3.y = " << p3.y << endl;
    cout << "p3.z = " << p3.z << endl<<endl;

    cv::Point3f p4(p3);
    cout << "p4.x = " << p4.x << endl;
    cout << "p4.y = " << p4.y << endl;
    cout << "p4.z = " << p4.z << endl<<endl;

    //计算
    cv::Point p = p1 + p2;
    cout << "p1 + p2 =  " << "(" << p.x << ", " << p.y << ")" << endl;
    cout << "p1 . p2 = " << p1.dot(p2) << endl;
    cout << "p3×p4 = " << p3.cross(p4) << endl << endl;

    cv::Rect2i rect(0,0,3,3);
    cout << "rect" << rect << endl;
    cout << "p1.inside(rect)  = " << p1.inside(rect) << endl;
    cout << "p2.inside(rect)  = " << p2.inside(rect) << endl;
    system("PAUSE");
    return 0;
}
