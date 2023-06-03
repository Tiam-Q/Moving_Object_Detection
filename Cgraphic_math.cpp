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
 * @Function:       // ��ȡ����ͼ��
 * @Description:    // ��ȡ��ֵ����ֵ�����õ��ı���ͼ��
 * @Input:          // void
 * @Output:         // ����ͼ��
 * @Return:         // ����ͼ��
*******************************************************************************/
Mat Cgraphic_math::getImage_back(void)
{
	return image_back;
}

/*******************************************************************************
 * @Function:       // ����֡��ͼ��
 * @Description:    // ��������image����ֵ���ֵ�����ı���ͼ������õ�֡��
 * @Input:          // ��Ҫ�����ͼ��
 * @Output:         // ֡��
 * @Return:         // void
*******************************************************************************/
void Cgraphic_math::setDifImage(Mat image)
{
	image_dif = abs(image - image_back);
}


/*******************************************************************************
 * @Function:       // ��ֵ����ͼ��
 * @Description:    // �����֡ͼ��ľ�ֵ�õ�����ͼ��
 * @Input:          // ��Ҫ�����ͼ��
 * @Output:         // ����ͼ��
 * @Return:         // void
*******************************************************************************/
void Cgraphic_math::images_average(Mat image)
{
	static int count = 0;
	float q1 = count / (count + 1.0);		//Ȩ��
	float q2 = 1 / (count + 1.0);

	//cvtColor(image, image, CV_BGR2GRAY);	//�Ҷ�

	//��һ��ִ����Ҫ��ʼ��image_back
	if (count == 0)
	{
		image_back = image.clone();
	}

	//�����ֵ
	image_back = q1 * image_back + q2 * image;

	count++;

	//���
	if (count >= average_num)
	{
		count = 0;
	}
}

/*******************************************************************************
 * @Function:       // ��ȡ֡��ͼ��
 * @Description:    // ��ȡ֡��ͼ��
 * @Input:          // void
 * @Output:         // ��
 * @Return:         // ֡��ͼ��
*******************************************************************************/
Mat Cgraphic_math::getDifImage(void)
{
	return image_dif;
}

/*******************************************************************************
 * @Function:       // ������Ҫ��ֵ�����֡��
 * @Description:    // ������Ҫ����Ҫ���о�ֵ��ͼ��֡��
 * @Input:          // ֡��
 * @Output:         // ��ֵ����֡��
 * @Return:         // ��
*******************************************************************************/
void Cgraphic_math::setAverage_num(int num)
{
	average_num = num;
}

/*******************************************************************************
 * @Function:       // ���������㷨
 * @Description:    // ��������������
 * @Input:          // arr:��Ҫ��������飬n:����ĳ���
 * @Output:         // ������������arr
 * @Return:         // ��
*******************************************************************************/
void InsertSort(int* arr, int n)
{
	for (int i = 0; i < n - 1; ++i)
	{
		//��¼�����������һ��Ԫ�ص��±�
		int end = i;
		//�������Ԫ��
		int tem = arr[end + 1];
		//������
		while (end >= 0)
		{
			//�Ȳ��������������
			if (tem < arr[end])
			{
				arr[end + 1] = arr[end];
				end--;
			}
			//�Ȳ������С������ѭ��
			else
			{
				break;
			}
		}
		//tem�ŵ��Ȳ������С�����ĺ���
		arr[end + 1] = tem;
		//����ִ�е���λ�����������:
		//1.������Ԫ���ҵ�Ӧ����λ�ã�break����ѭ�����ˣ�
		//2.������Ԫ�رȵ�ǰ���������е�����Ԫ�ض�С��whileѭ�������󵽴ˣ�
	}
}

/*******************************************************************************
 * @Function:       // ͼ����ֵ����
 * @Description:    // �Զ���ͼ����Ӧ���ص�ȡ��ֵ���õ�����ͼ��
 * @Input:          // image[]��Ҫ���д����ͼ������
 * @Output:         // data_back����ͼ��
 * @Return:         // ��
*******************************************************************************/
void Cgraphic_math::images_median(Mat image[])
{
	int* arr = new int[median_num];
	
	if (image_back.empty())		//����ͼ���ʼ��
	{
		image_back = image[0].clone();
	}
	for (int i = 0; i < image[0].rows; i++)
	{
		for (int j = 0; j < image[0].cols; j++)
		{
			for (int n = 0; n < median_num; n++)
			{
				//��ȡ��n��ͼ���i�е��׵�ַ
          	    uchar* data = image[n].ptr<uchar>(i);
				arr[n] = (int)data[j];
				if (n >= (median_num - 1))
				{
					//����ͼ���i���׵�ַ
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
 * @Function:       // ������Ҫ��ֵ�����֡��
 * @Description:    // ������Ҫ����Ҫ������ֵ��ͼ��֡��
 * @Input:          // ֡��
 * @Output:         // ��ֵ����֡��
 * @Return:         // ��
*******************************************************************************/
void Cgraphic_math::setMedian_num(int num)
{
	median_num = num;
}
