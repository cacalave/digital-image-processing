#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <math.h>
using namespace cv;
using namespace std;
int main()
{
    Mat inimage = imread("/Users/jiangshanchen/数字图像处理-姜/Chap3Fundamentals/3.2.4Piecewise-LinearTransformationFunction-JiangShanchen/contrast-stretching/Fig0310(b)(washed_out_pollen_image).tif");
    int rows =inimage.rows;
    int cols =inimage.cols;
    Mat sumimage,;
    Scalar sum;
    sumimage.create(rows, cols, inimage.type());
    for (int k=0; k<rows; k++) {
        for (int l =0; l<cols; l++) {
            sum.val[0]+=inimage.at<Vec3b>(k,l)[0];
            sum.val[1]+=inimage.at<Vec3b>(k,l)[1];
            sum.val[2]+=inimage.at<Vec3b>(k,l)[2];
        }
    }
    for (int k=0; k<rows; k++) {
        for (int l =0; l<cols; l++) {
            sumimage.at<Vec3b>(k,l)[0]=sum.val[0]/(rows*cols);
            sumimage.at<Vec3b>(k,l)[1]=sum.val[1]/(rows*cols);
            sumimage.at<Vec3b>(k,l)[2]=sum.val[2]/(rows*cols);
            if (inimage.at<Vec3b>(k,l)[0]>sumimage.at<Vec3b>(k,l)[0])
                inimage.at<Vec3b>(k,l)[0]=255;
            else inimage.at<Vec3b>(k,l)[0]=0;
            if (inimage.at<Vec3b>(k,l)[1]>sumimage.at<Vec3b>(k,l)[1])
                inimage.at<Vec3b>(k,l)[1]=255;
            else inimage.at<Vec3b>(k,l)[1]=0;
            if (inimage.at<Vec3b>(k,l)[2]>sumimage.at<Vec3b>(k,l)[2])
                inimage.at<Vec3b>(k,l)[2]=255;
            else inimage.at<Vec3b>(k,l)[2]=0;
        }
    }
    imshow("result", inimage);
    imwrite("result.jpg", inimage);
    waitKey(0);
    return 0;
}
