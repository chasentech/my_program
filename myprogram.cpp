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