#ifndef FENGE_H
#define FENGE_H
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
#include"fenge.h"
using namespace cv;
using namespace std;


typedef struct _Feather
{
    int label;              // 连通域的label值
    int area;               // 连通域的面积
    int length;              //连通域周长
    double r;
    Rect boundingbox;       // 连通域的外接矩形框
} Feather;


class fenge
{
private:
    Mat result;
    Mat bgModel, fgModel;
    //cv::Rect rectangle(1, 1, Frame.cols - 2, Frame.rows - 2);
public:
    fenge();

    Mat gra(Mat frame)
    {
    cv::Rect rectangle(2, 2, frame.cols-4 , frame.rows - 4);
    cv::grabCut(frame,    //输入图像
            result,   //分段结果
            rectangle,// 包含前景的矩形
            bgModel, fgModel, // 前景、背景
            1,        // 迭代次数
            cv::GC_INIT_WITH_RECT); // 用矩形
    cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);
    dilate(result, result, cv::Mat());
    threshold(result, result, 127, 255, THRESH_BINARY);
    return result;


    }

    Mat graxiata(Mat frame)
    {
    cv::Rect rectangle(0, 50, frame.cols , frame.rows - 100);
    cv::grabCut(frame,    //输入图像
            result,   //分段结果
            rectangle,// 包含前景的矩形
            bgModel, fgModel, // 前景、背景
            1,        // 迭代次数
            cv::GC_INIT_WITH_RECT); // 用矩形
    cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);
    dilate(result, result, cv::Mat());
    threshold(result, result, 127, 255, THRESH_BINARY);
    return result;

    }

    /*
    Input:
    src: 待检测连通域的二值化图像
    Output:
    dst: 标记后的图像
    featherList: 连通域特征的清单
    return：
    连通域数量。
    */
    int bwLabel(Mat & src, Mat & dst, vector<Feather> & featherList)
    {
        int rows = src.rows;
        int cols = src.cols;

        int labelValue = 1;
        Point seed, neighbor;
        stack<Point> pointStack;    // 堆栈
        int length = 0;
        double r = 0;
        int area = 0;               // 用于计算连通域的面积
        int leftBoundary = 0;       // 连通域的左边界，即外接最小矩形的左边框，横坐标值，依此类推
        int rightBoundary = 0;
        int topBoundary = 0;
        Rect box;                   // 外接矩形框
        int bottomBoundary = 0;
        Feather feather;

        featherList.clear();    // 清除数组

        dst.release();
        dst = src.clone();
        int i;
        int j;
        for (i=0; i < rows; i++)
        {
            uchar *pRow = dst.ptr<uchar>(i);
            for (j=0; j < cols; j++)
            {
                if (pRow[j] == 255)
                {
                    length = 0;
                    r=0;
                    area = 0;
                    labelValue++;           // labelValue最大为254，最小为1.
                    seed = Point(j, i);     // Point（横坐标，纵坐标）
                    dst.at<uchar>(seed) = labelValue;
                    pointStack.push(seed);

                    area++;
                    leftBoundary = seed.x;
                    rightBoundary = seed.x;
                    topBoundary = seed.y;
                    bottomBoundary = seed.y;

                    while (!pointStack.empty())
                    {
                        neighbor = Point(seed.x + 1, seed.y);
                        if ((seed.x != (cols - 1)) && (dst.at<uchar>(neighbor) == 255))
                        {
                            dst.at<uchar>(neighbor) = labelValue;
                            pointStack.push(neighbor);

                            area++;
                            if (rightBoundary < neighbor.x)
                                rightBoundary = neighbor.x;
                            Point neighbor1= Point(neighbor.x , neighbor.y - 1);
                            Point neighbor2 = Point(neighbor.x, neighbor.y + 1);
                            Point neighbor3 = Point(neighbor.x + 1, neighbor.y);
                            Point neighbor4 = Point(neighbor.x - 1, neighbor.y);
                            if(neighbor.x>0&&neighbor.x<1111&&neighbor.y<641&&neighbor.y>0)
                            {
                                if (dst.at<uchar>(neighbor1) == 0) ++length;
                                if (dst.at<uchar>(neighbor2) == 0) ++length;
                                if (dst.at<uchar>(neighbor3) == 0) ++length;
                                if (dst.at<uchar>(neighbor4) == 0) ++length;
                            }

                        }

                        neighbor = Point(seed.x, seed.y + 1);
                        if ((seed.y != (rows - 1)) && (dst.at<uchar>(neighbor) == 255))
                        {
                            dst.at<uchar>(neighbor) = labelValue;
                            pointStack.push(neighbor);

                            area++;
                            if (bottomBoundary < neighbor.y)
                                bottomBoundary = neighbor.y;
                            Point neighbor1= Point(neighbor.x , neighbor.y - 1);
                            Point neighbor2 = Point(neighbor.x, neighbor.y + 1);
                            Point neighbor3 = Point(neighbor.x + 1, neighbor.y);
                            Point neighbor4 = Point(neighbor.x - 1, neighbor.y);
                            if(neighbor.x>0&&neighbor.x<1111&&neighbor.y<641&&neighbor.y>0)
                            {
                                if (dst.at<uchar>(neighbor1) == 0) ++length;
                                if (dst.at<uchar>(neighbor2) == 0) ++length;
                                if (dst.at<uchar>(neighbor3) == 0) ++length;
                                if (dst.at<uchar>(neighbor4) == 0) ++length;
                            }

                        }

                        neighbor = Point(seed.x - 1, seed.y);
                        if ((seed.x != 0) && (dst.at<uchar>(neighbor) == 255))
                        {
                            dst.at<uchar>(neighbor) = labelValue;
                            pointStack.push(neighbor);

                            area++;
                            if (leftBoundary > neighbor.x)
                                leftBoundary = neighbor.x;
                            Point neighbor1= Point(neighbor.x , neighbor.y - 1);
                            Point neighbor2 = Point(neighbor.x, neighbor.y + 1);
                            Point neighbor3 = Point(neighbor.x + 1, neighbor.y);
                            Point neighbor4 = Point(neighbor.x - 1, neighbor.y);
                            if(neighbor.x>0&&neighbor.x<1111&&neighbor.y<641&&neighbor.y>0)
                            {
                                if (dst.at<uchar>(neighbor1) == 0) ++length;
                                if (dst.at<uchar>(neighbor2) == 0) ++length;
                                if (dst.at<uchar>(neighbor3) == 0) ++length;
                                if (dst.at<uchar>(neighbor4) == 0) ++length;
                            }

                        }

                        neighbor = Point(seed.x, seed.y - 1);
                        if ((seed.y != 0) && (dst.at<uchar>(neighbor) == 255))
                        {
                            dst.at<uchar>(neighbor) = labelValue;
                            pointStack.push(neighbor);

                            area++;
                            if (topBoundary > neighbor.y)
                                topBoundary = neighbor.y;
                            Point neighbor1= Point(neighbor.x , neighbor.y - 1);
                            Point neighbor2 = Point(neighbor.x, neighbor.y + 1);
                            Point neighbor3 = Point(neighbor.x + 1, neighbor.y);
                            Point neighbor4 = Point(neighbor.x - 1, neighbor.y);
                            if(neighbor.x>0&&neighbor.x<1111&&neighbor.y<641&&neighbor.y>0)
                            {
                                if (dst.at<uchar>(neighbor1) == 0) ++length;
                                if (dst.at<uchar>(neighbor2) == 0) ++length;
                                if (dst.at<uchar>(neighbor3) == 0) ++length;
                                if (dst.at<uchar>(neighbor4) == 0) ++length;
                            }

                        }

                        seed = pointStack.top();
                        pointStack.pop();
                    }
                    box = Rect(leftBoundary, topBoundary, rightBoundary - leftBoundary, bottomBoundary - topBoundary);
                    if(area>=10&&area<10000)
                    {
                        //rectangle(src, box, 255);
                        feather.area = area;
                        feather.boundingbox = box;
                        feather.label = labelValue;
                        feather.length = length;
                        feather.r = (12.56*area) / (length*length);
                        featherList.push_back(feather);
                    }
                }
            }
        }

        return featherList.size();
    }









    int bwLabelt(Mat & src, Mat & dst, vector<Feather> & featherList)
    {
        int rows = src.rows;
        int cols = src.cols;

        int labelValue = 100;
        Point seed, neighbor;
        stack<Point> pointStack;    // 堆栈
        int length = 0;
        double r = 0;
        int area = 0;               // 用于计算连通域的面积
        int leftBoundary = 0;       // 连通域的左边界，即外接最小矩形的左边框，横坐标值，依此类推
        int rightBoundary = 0;
        int topBoundary = 0;
        Rect box;                   // 外接矩形框
        int bottomBoundary = 0;
        Feather feather;

        featherList.clear();    // 清除数组

        dst.release();
        dst = src.clone();
        int i;
        int j;
        for (i=0; i < rows; i++)
        {
            uchar *pRow = dst.ptr<uchar>(i);
            for (j=0; j < cols; j++)
            {
                if (pRow[j] == 255)
                {
                    length = 0;
                    r=0;
                    area = 0;
                    labelValue++;           // labelValue最大为254，最小为1.
                    seed = Point(j, i);     // Point（横坐标，纵坐标）
                    dst.at<uchar>(seed) = labelValue;
                    pointStack.push(seed);

                    area++;
                    leftBoundary = seed.x;
                    rightBoundary = seed.x;
                    topBoundary = seed.y;
                    bottomBoundary = seed.y;

                    while (!pointStack.empty())
                    {
                        neighbor = Point(seed.x + 1, seed.y);
                        if ((seed.x != (cols - 1)) && (dst.at<uchar>(neighbor) == 255))
                        {
                            dst.at<uchar>(neighbor) = labelValue;
                            pointStack.push(neighbor);

                            area++;
                            if (rightBoundary < neighbor.x)
                                rightBoundary = neighbor.x;
                            Point neighbor1= Point(neighbor.x , neighbor.y - 1);
                            Point neighbor2 = Point(neighbor.x, neighbor.y + 1);
                            Point neighbor3 = Point(neighbor.x + 1, neighbor.y);
                            Point neighbor4 = Point(neighbor.x - 1, neighbor.y);
                            if(neighbor.x>0&&neighbor.x<1111&&neighbor.y<641&&neighbor.y>0)
                            {
                                if (dst.at<uchar>(neighbor1) == 0) ++length;
                                if (dst.at<uchar>(neighbor2) == 0) ++length;
                                if (dst.at<uchar>(neighbor3) == 0) ++length;
                                if (dst.at<uchar>(neighbor4) == 0) ++length;
                            }

                        }

                        neighbor = Point(seed.x, seed.y + 1);
                        if ((seed.y != (rows - 1)) && (dst.at<uchar>(neighbor) == 255))
                        {
                            dst.at<uchar>(neighbor) = labelValue;
                            pointStack.push(neighbor);

                            area++;
                            if (bottomBoundary < neighbor.y)
                                bottomBoundary = neighbor.y;
                            Point neighbor1= Point(neighbor.x , neighbor.y - 1);
                            Point neighbor2 = Point(neighbor.x, neighbor.y + 1);
                            Point neighbor3 = Point(neighbor.x + 1, neighbor.y);
                            Point neighbor4 = Point(neighbor.x - 1, neighbor.y);
                            if(neighbor.x>0&&neighbor.x<1111&&neighbor.y<641&&neighbor.y>0)
                            {
                                if (dst.at<uchar>(neighbor1) == 0) ++length;
                                if (dst.at<uchar>(neighbor2) == 0) ++length;
                                if (dst.at<uchar>(neighbor3) == 0) ++length;
                                if (dst.at<uchar>(neighbor4) == 0) ++length;
                            }

                        }

                        neighbor = Point(seed.x - 1, seed.y);
                        if ((seed.x != 0) && (dst.at<uchar>(neighbor) == 255))
                        {
                            dst.at<uchar>(neighbor) = labelValue;
                            pointStack.push(neighbor);

                            area++;
                            if (leftBoundary > neighbor.x)
                                leftBoundary = neighbor.x;
                            Point neighbor1= Point(neighbor.x , neighbor.y - 1);
                            Point neighbor2 = Point(neighbor.x, neighbor.y + 1);
                            Point neighbor3 = Point(neighbor.x + 1, neighbor.y);
                            Point neighbor4 = Point(neighbor.x - 1, neighbor.y);
                            if(neighbor.x>0&&neighbor.x<1111&&neighbor.y<641&&neighbor.y>0)
                            {
                                if (dst.at<uchar>(neighbor1) == 0) ++length;
                                if (dst.at<uchar>(neighbor2) == 0) ++length;
                                if (dst.at<uchar>(neighbor3) == 0) ++length;
                                if (dst.at<uchar>(neighbor4) == 0) ++length;
                            }

                        }

                        neighbor = Point(seed.x, seed.y - 1);
                        if ((seed.y != 0) && (dst.at<uchar>(neighbor) == 255))
                        {
                            dst.at<uchar>(neighbor) = labelValue;
                            pointStack.push(neighbor);

                            area++;
                            if (topBoundary > neighbor.y)
                                topBoundary = neighbor.y;
                            Point neighbor1= Point(neighbor.x , neighbor.y - 1);
                            Point neighbor2 = Point(neighbor.x, neighbor.y + 1);
                            Point neighbor3 = Point(neighbor.x + 1, neighbor.y);
                            Point neighbor4 = Point(neighbor.x - 1, neighbor.y);
                            if(neighbor.x>0&&neighbor.x<1111&&neighbor.y<641&&neighbor.y>0)
                            {
                                if (dst.at<uchar>(neighbor1) == 0) ++length;
                                if (dst.at<uchar>(neighbor2) == 0) ++length;
                                if (dst.at<uchar>(neighbor3) == 0) ++length;
                                if (dst.at<uchar>(neighbor4) == 0) ++length;
                            }

                        }

                        seed = pointStack.top();
                        pointStack.pop();
                    }
                    box = Rect(leftBoundary, topBoundary, rightBoundary - leftBoundary, bottomBoundary - topBoundary);
                    if(area>=100)
                    {
                        //rectangle(src, box, 255);
                        feather.area = area;
                        feather.boundingbox = box;
                        feather.label = labelValue;

                        feather.length = length;
                        feather.r = (12.56*area) / (length*length);
                        featherList.push_back(feather);
                    }
                }
            }
        }

        return featherList.size();
    }
};

#endif // FENGE_H
