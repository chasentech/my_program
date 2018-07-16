#ifndef _MYPROGRAM_H_
#define _MYPROGRAM_H_

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class MyProgram
{
private:
	Mat img_origion;
	Mat img_show;

public:
	void mythreshold(Mat &img, uchar T, bool flag = true);
	void my_lbp(Mat &img, Mat &out);
	void my_lbp_circle(Mat &img, Mat &out, int radius, int count);

};

#endif
