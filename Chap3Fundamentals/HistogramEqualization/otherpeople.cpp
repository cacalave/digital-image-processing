#include "opencv2/core.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define BYTE unsigned char
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
    //载入图片
    int i=0, j=0, temp=0;
    IplImage * img = cvLoadImage("/Users/jiangshanchen/数字图像处理-姜/Digital-Tangning/HistogramProcessing/OpenCV/LocalHistogramEqualization/origin.tif", CV_LOAD_IMAGE_GRAYSCALE);//图片路径
    int height = img->height;
    int width  = img->width;
    int step   = img->widthStep;
    uchar *data = (uchar*)img->imageData;
    float size = height*width;
    
    //直方图
    unsigned int hist[256] = {0};
    for (i=0; i<height; i++)
    {
        for (j=0; j<width; j++)
        {
            temp = data[i*step+j];
            hist[temp]++;
        }
    }
    //归一化直方图
    float histPDF[256] = {0};
    for (i=0; i<255; i++)
    {
        histPDF[i]=(float)hist[i]/size;
    }
    //累积直方图
    float histCDF[256] = {0};
    for (i=0; i<256; i++)
    {
        if (0==i) histCDF[i] = histPDF[i];
        else histCDF[i] = histCDF[i-1] + histPDF[i];
    }
    //直方图均衡化,映射
    int histEQU[256] = {0};
    for (i=0; i<256; i++)
    {
        histEQU[i] = (int)(255.0 * histCDF[i] + 0.5);
    }
    for (i=0; i<height; i++)
    {
        for (j=0; j<width; j++)
        {
            temp = data[i*step+j];
            data[i*step+j] = histEQU[temp];
        }
    }
    
    
    cvNamedWindow("demo", CV_WINDOW_AUTOSIZE);
    cvShowImage("demo", img);
    cvWaitKey(0);
    cvDestroyWindow("demo");
    cvReleaseImage(&img);
    return 0;
}