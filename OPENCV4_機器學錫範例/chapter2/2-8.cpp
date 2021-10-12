#include "stdafx.h"
#include "opencv.hpp"

int main()
{
    cv::VideoCapture cap;
    cap.open(0);
    int width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    std::cout << "cap(width, heigh): " << width << ", " << height << std::endl;
    cv::Mat frame, edge_img;
    cv::VideoWriter out;
    out.open(
        "my_video.avi", //输出文件名  
        CV_FOURCC('D', 'I', 'V', 'X'), //设置MPEG-4编码  
        30.0, //设置帧率 (FPS)  
        cv::Size(width, height), //设置单帧图片分辨率  
        false);  //false: 输入黑白图片; true: 输入彩色图片
    while (true) {
        cap >> frame;
        cv::resize(frame, frame, cv::Size(640, 480));
        cv::Canny(frame, edge_img, 100, 200);
        cv::imshow("original", frame);
        cv::imshow("edge", edge_img);
        out.write(edge_img);
        int c = cv::waitKey(5);
        if (c == 30 || c == 'q' || c == 'Q')
            break;
    }
    return 0;
}
