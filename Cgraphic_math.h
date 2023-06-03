#ifndef _CGRAPHIC_MATH_H
#define _CGRAPHIC_MATH_H

#include <opencv2/opencv.hpp>
#include<iostream> 
#include<string.h>

using namespace std;
using namespace cv;


/*************************************************************************
* @abstract				 Cgraphic_math��,ʵ�ֶԶ�֡ͼ����о�ֵ����ֵ����
						 �õ�����ͼ�����֡�����ʵ�ֶ��ƶ�����ļ��
* @author				 2131277807@qq.com
* @since				 opencv3.4.4
**************************************************************************/
class Cgraphic_math
{
private:
	Mat image_back;			//����ͼ��
	Mat image_dif;		    //���ͼ��
	int average_num;		//����֡ȡһ��ƽ��

	int median_num;			//����֡ȡ��ֵ

public:
	Cgraphic_math();				//���캯��
	~Cgraphic_math();				//��������

	Mat getImage_back(void);		//��ȡ����ͼ��
	Mat getDifImage(void);			//��ȡ֡��
	void setDifImage(Mat image);	//֡�����

	void images_average(Mat image);	//��ֵ����
	void setAverage_num(int num);	//���þ�ֵ����֡��

	void images_median(Mat image[]);//��ֵ����
	void setMedian_num(int num);	//������ֵ����֡��
};



#endif




