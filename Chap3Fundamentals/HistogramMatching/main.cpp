#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
int main()
{
    Mat inimage = imread("/Users/jiangshanchen/数字图像处理-姜/Chap3Fundamentals/histogram-equalization/4.tif");
    imshow("inimage" , inimage);
    Mat newimage;
    int rows =inimage.rows;
    int cols = inimage.cols* inimage.channels();
    int i,j;
    uchar *date;
    double r[256],p[256],sum[256];
    int end[256];
    sum[0]=0;
    newimage.create(rows, cols, inimage.type());
    for(i = 0; i < rows; i++)
    {
        date=inimage.ptr<uchar>(i);
        for(j = 0; j < cols; j++)
        {
            r[date[j]]++;
        }
    }
    for(i=0; i<256; i++)
    {
        p[i]=r[i]/(double)(rows*cols);
    }
    sum[0]=p[0];
    for (i=1; i<256; i++) {
        sum[i]=sum[i-1]+p[i];
    }
    for (i=0; i<256; i++) {
        sum[i]=sum[i]*255;
        end[i]=(int)(sum[i]+0.5);
    }
    for(i = 0; i < rows; i++)
    {
        date=inimage.ptr<uchar>(i);
        for(j = 0; j < cols; j++)
        {
            int result=end[date[j]];
            if (result==0) {
                date[j]=255;
            }else date[j]=result;
            
        }
    }
    imshow("newimage", inimage);
    imwrite("newimage_4.tif", inimage);
    waitKey(0);
    return 0;
}
