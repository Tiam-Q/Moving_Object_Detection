#ifndef _CGRAPHIC_MATH_H
#define _CGRAPHIC_MATH_H

#include <opencv2/opencv.hpp>
#include<iostream> 
#include<string.h>

using namespace std;
using namespace cv;


/*************************************************************************
* @abstract				 Cgraphic_math类,实现对多帧图像进行均值或中值处理，
						 得到背景图像，最后帧差计算实现对移动物体的检测
* @author				 2131277807@qq.com
* @since				 opencv3.4.4
**************************************************************************/
class Cgraphic_math
{
private:
	Mat image_back;			//背景图像
	Mat image_dif;		    //侦差图像
	int average_num;		//多少帧取一次平均

	int median_num;			//多少帧取中值

public:
	Cgraphic_math();				//构造函数
	~Cgraphic_math();				//析构函数

	Mat getImage_back(void);		//获取背景图像
	Mat getDifImage(void);			//获取帧差
	void setDifImage(Mat image);	//帧差计算

	void images_average(Mat image);	//均值处理
	void setAverage_num(int num);	//设置均值处理帧数

	void images_median(Mat image[]);//中值处理
	void setMedian_num(int num);	//设置中值处理帧数
};



#endif




