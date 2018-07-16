#include "myprogram.h"

//�ԻҶ�ͼ��ֵ��
void MyProgram::mythreshold(Mat &img, uchar T, bool flag = true)
{
	int n1 = img.rows;
	int nc = img.cols * img.channels();
	if (img.isContinuous())//�ж�ͼ���Ƿ�����
	{
		nc = nc * n1;
		n1 = 1;
	}
	for (int i = 0; i < n1; i++)
	{
		uchar *p = img.ptr<uchar>(i);
		for (int j = 0; j < nc; j++)
		{
			if (flag == true)
			{
				if (p[j] < T)
					p[j] = 0;
				else p[j] = 255;
			}
			if (flag == false)
			{
				if (p[j] > T)
					p[j] = 0;
				else p[j] = 255;
			}
		}
	}
}

//��ͨLBP����
void MyProgram::my_lbp(Mat &img, Mat &out)
{
	int rows = img.rows;
	int cols = img.cols;

	out = Mat(img.size(), img.type());

	for (int i = 1; i < rows - 1; i++)
	{
		uchar *p = img.ptr<uchar>(i);
		//uchar *p1 = img.ptr<uchar>(i - 1);
		//uchar *p2 = img.ptr<uchar>(i + 1);
		uchar *q = out.ptr<uchar>(i);

		for (int j = 1; j < cols - 1; j++)
		{
			uchar neighbor[8] = { 0 };
			neighbor[0] = p[j - 1 - img.step];
			neighbor[1] = p[j - img.step];
			neighbor[2] = p[j + 1 - img.step];
			neighbor[3] = p[j - 1];
			neighbor[4] = p[j + 1];
			neighbor[5] = p[j - 1 + img.step];
			neighbor[6] = p[j + img.step];
			neighbor[7] = p[j + 1 + img.step];

			int temp = 0;
			for (int k = 0; k <= 8; k++)
			{
				if (neighbor[k] > p[j])
				{
					temp += (1 << k);
				}
			}
			*(q + j) = temp;
		}
	}
}

/*
Բ��LBP����
radius:�뾶
count:��������ʱֻ֧��8��
*/
void MyProgram::my_lbp_circle(Mat &img, Mat &out, int radius, int count)
{
	int rows = img.rows;
	int cols = img.cols;

	out = Mat(img.size(), img.type());

	for (int i = radius; i < rows - radius; i++)
	{
		uchar *p = img.ptr<uchar>(i);
		uchar *q = out.ptr<uchar>(i);
		for (int j = radius; j < cols - radius; j++)
		{
			int temp = 0;
			for (int n = 0; n < count; n++)
			{
				float xx = static_cast<float>(radius * sin(2.0*CV_PI*n / static_cast<float>(count)));
				float yy = static_cast<float>(radius * cos(2.0*CV_PI*n / static_cast<float>(count)));

				// ��ȡ������ȡ����ֵ
				int fx = static_cast<int>(floor(xx));	//����ȡ��
				int fy = static_cast<int>(floor(yy));
				int cx = static_cast<int>(ceil(xx));	//����ȡ��
				int cy = static_cast<int>(ceil(yy));

				// С������
				float ty = yy - fy;
				float tx = xx - fx;

				float w1 = (1 - tx) * (1 - ty);	//���Ͻ�Ȩ��
				float w2 = tx * (1 - ty);		//���Ͻ�Ȩ��
				float w3 = (1 - tx) * ty;		//���½�Ȩ��
				float w4 = tx * ty;				//���½�Ȩ��

				float one = w1 * p[j - cx - cy * img.step] +
					w2 * p[j + fx - cy * img.step] +
					w3 * p[j - cx + fy * img.step] +
					w4 * p[j + fx + fy * img.step];

				//cout << "one = " << one << endl;
				//printf("p[j] = %d\n", p[j]);
				if (one < p[j])
				{
					temp += (1 << n);
				}
			}
			//cout << "temp = " << temp << endl;
			*(q + j) = temp;
		}
	}




}
