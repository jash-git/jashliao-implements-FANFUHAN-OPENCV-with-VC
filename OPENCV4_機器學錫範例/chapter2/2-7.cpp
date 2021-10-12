#include "stdafx.h"
#include "opencv.hpp"

int main()
{
    cv::VideoCapture cap;
    cap.open(0);
    cv::Mat frame, edge_img;
    while(true) {
        cap >> frame;        
        cv::Canny(frame, edge_img,100,200);
        cv::imshow("original", frame);
        cv::imshow("edge", edge_img);
        int c = cv::waitKey(5);
        if (c == 27 || c == 'q' || c == 'Q')
            break;
    }
    return 0;
}
