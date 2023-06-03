#include "Cgraphic_math.h"



Cgraphic_math::Cgraphic_math()
{
	average_num = 13;
	median_num = 13;
}

Cgraphic_math::~Cgraphic_math()
{
	//delete img;
}

/*******************************************************************************
 * @Function:       // 获取背景图像
 * @Description:    // 获取均值或中值处理后得到的背景图像
 * @Input:          // void
 * @Output:         // 背景图像
 * @Return:         // 背景图像
*******************************************************************************/
Mat Cgraphic_math::getImage_back(void)
{
	return image_back;
}

/*******************************************************************************
 * @Function:       // 计算帧差图像
 * @Description:    // 利用输入image与中值或均值处理后的背景图像做差得到帧差
 * @Input:          // 需要做差的图像
 * @Output:         // 帧差
 * @Return:         // void
*******************************************************************************/
void Cgraphic_math::setDifImage(Mat image)
{
	image_dif = abs(image - image_back);
}


/*******************************************************************************
 * @Function:       // 均值处理图像
 * @Description:    // 计算多帧图像的均值得到背景图像
 * @Input:          // 需要处理的图像
 * @Output:         // 背景图像
 * @Return:         // void
*******************************************************************************/
void Cgraphic_math::images_average(Mat image)
{
	static int count = 0;
	float q1 = count / (count + 1.0);		//权重
	float q2 = 1 / (count + 1.0);

	//cvtColor(image, image, CV_BGR2GRAY);	//灰度

	//第一次执行需要初始化image_back
	if (count == 0)
	{
		image_back = image.clone();
	}

	//计算均值
	image_back = q1 * image_back + q2 * image;

	count++;

	//溢出
	if (count >= average_num)
	{
		count = 0;
	}
}

/*******************************************************************************
 * @Function:       // 获取帧差图像
 * @Description:    // 获取帧差图像
 * @Input:          // void
 * @Output:         // 无
 * @Return:         // 帧差图像
*******************************************************************************/
Mat Cgraphic_math::getDifImage(void)
{
	return image_dif;
}

/*******************************************************************************
 * @Function:       // 设置需要均值处理的帧数
 * @Description:    // 设置需要对需要进行均值的图像帧数
 * @Input:          // 帧数
 * @Output:         // 均值处理帧数
 * @Return:         // 无
*******************************************************************************/
void Cgraphic_math::setAverage_num(int num)
{
	average_num = num;
}

/*******************************************************************************
 * @Function:       // 插入排序算法
 * @Description:    // 对输入数组排序
 * @Input:          // arr:需要处理的数组，n:数组的长度
 * @Output:         // 排序完后的数组arr
 * @Return:         // 无
*******************************************************************************/
void InsertSort(int* arr, int n)
{
	for (int i = 0; i < n - 1; ++i)
	{
		//记录有序序列最后一个元素的下标
		int end = i;
		//待插入的元素
		int tem = arr[end + 1];
		//单趟排
		while (end >= 0)
		{
			//比插入的数大就向后移
			if (tem < arr[end])
			{
				arr[end + 1] = arr[end];
				end--;
			}
			//比插入的数小，跳出循环
			else
			{
				break;
			}
		}
		//tem放到比插入的数小的数的后面
		arr[end + 1] = tem;
		//代码执行到此位置有两种情况:
		//1.待插入元素找到应插入位置（break跳出循环到此）
		//2.待插入元素比当前有序序列中的所有元素都小（while循环结束后到此）
	}
}

/*******************************************************************************
 * @Function:       // 图像中值处理
 * @Description:    // 对多种图像相应像素点取中值，得到背景图像
 * @Input:          // image[]需要进行处理的图像数组
 * @Output:         // data_back背景图像
 * @Return:         // 无
*******************************************************************************/
void Cgraphic_math::images_median(Mat image[])
{
	int* arr = new int[median_num];
	
	if (image_back.empty())		//背景图像初始化
	{
		image_back = image[0].clone();
	}
	for (int i = 0; i < image[0].rows; i++)
	{
		for (int j = 0; j < image[0].cols; j++)
		{
			for (int n = 0; n < median_num; n++)
			{
				//获取第n张图像第i行的首地址
          	    uchar* data = image[n].ptr<uchar>(i);
				arr[n] = (int)data[j];
				if (n >= (median_num - 1))
				{
					//背景图像第i行首地址
					uchar* data_back = image_back.ptr<uchar>(i);
					InsertSort(arr, median_num);
					data_back[j] = (uchar)(arr[(median_num / 2)]);

					continue;
				}
				
			}
		}
	}

	delete[] arr;
}

/*******************************************************************************
 * @Function:       // 设置需要中值处理的帧数
 * @Description:    // 设置需要对需要进行中值的图像帧数
 * @Input:          // 帧数
 * @Output:         // 中值处理帧数
 * @Return:         // 无
*******************************************************************************/
void Cgraphic_math::setMedian_num(int num)
{
	median_num = num;
}
