#ifndef YUCHULI_H
#define YUCHULI_H
#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include<opencv2\imgproc\imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include "math.h"
#include <iostream>
#include <vector>
#include <stack>
#include "histogram.h"
#include<QMessageBox>
using namespace cv;
using namespace std;
class yuchuli
{
private:
    Mat yimage;
    Mat zqimage;
    Mat frame;
public:
    yuchuli();
   // ~yuchuli();

    void setimage(Mat &image)
    {
        yimage=image;
    }

    void suoxiao(Mat &image)
    {
        resize(image, image, Size(image.cols / 3, image.rows / 3), 0, 0, INTER_LINEAR);
    }

    void huidu(Mat &image, Mat &result) //图像加权灰度化处理
    {

        for (int i = 0; i<image.rows; i++)
        {
            for (int j = 0; j<image.cols; j++)
            {
                result.at<uchar>(i, j) = 0.11*image.at<Vec3b>(i, j)[0] + 0.59*image.at<Vec3b>(i, j)[1] + 0.3*image.at<Vec3b>(i, j)[2];
            }

        }

    }

    Mat zhengqiang(Mat image)
    {
       histogram h;
       zqimage = h.stretch(image, 100);
       return zqimage;
    }

    Mat caise(Mat image)
    {
        frame = cvCreateImage(image.size(), IPL_DEPTH_8U, 3);
        cvtColor(image, frame, CV_GRAY2BGR);
        return frame;
    }

   void yclimage(Mat &image)
   {

       //Mat gray(image.size(), CV_8U, cv::Scalar(0));
       //huidu(image,gray);

       Mat dst;
       dst=zhengqiang(image);
       Mat cai;
       cai=caise(dst);
       image=cai;
   }


};

#endif // YUCHULI_H
