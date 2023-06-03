/*****************************************************************
*
*                       .::::.
*                     .::::::::.
*                    :::::::::::
*                 ..:::::::::::'
*              '::::::::::::'
*                .::::::::::
*           '::::::::::::::..
*                ..::::::::::::.
*              ``::::::::::::::::
*               ::::``:::::::::'        .:::.
*              ::::'   ':::::'       .::::::::.
*            .::::'      ::::     .:::::::'::::.
*           .:::'       :::::  .:::::::::' ':::::.
*          .::'        :::::.:::::::::'      ':::::.
*         .::'         ::::::::::::::'         ``::::.
*     ...:::           ::::::::::::'              ``::.
*    ```` ':.          ':::::::::'                  ::::..
*                       '.:::::'                    ':'````.. 
*****************************************************************/
/****************************************************************
* @日期：2023年06月03日
* @作者：2131277807@qq..com
* @环境：Visual Studio2019   OpenCV3.4.4
* @描述：帧差法移动检测，使用求多帧图像的均值和中值，得到视频背景，
*		 当前图像减去背景得到帧差图像，利用帧差图像可找到移动物体。
* @需要改进：均值得到的效果不理想，
*****************************************************************/



#include <opencv2/opencv.hpp>  
#include<iostream>  
#include "Cgraphic_math.h"


using namespace std;
using namespace cv;


#define		num		19
#define		type    1		//0:以均值的方式
							//1:以中值的方式



int main()
{
	VideoCapture test_video;
	int count = 0;

	//读取视频
	test_video.open("C:\\Users\\Tiam\\Desktop\\Moving_Object_Detection\\video\\test.avi");
	
	//读取帧数、帧率
	int FrameCount = test_video.get(cv::CAP_PROP_FRAME_COUNT);
	int fps = test_video.get(cv::CAP_PROP_FPS);

	//单帧图像
	Mat frame;
	Mat frame_gray;
	Cgraphic_math graphic;
	graphic.setAverage_num(INT_MAX);

	//图像数组
	Mat image[num];
	Mat img;
	Mat img_gray;
	//填入中值处理的帧数
	graphic.setMedian_num(num);
	//初始化
	for (int i = 0; i < num; i++)
	{
		test_video.read(img);
		cvtColor(img, img_gray, CV_BGR2GRAY);
		
		image[i] = img_gray.clone();
	}
	//中值处理得到背景
	graphic.images_median(image);


	while (count < (FrameCount-num))	//前面读取了num帧需要减去
	{
		test_video.read(frame);
		cvtColor(frame, frame_gray, CV_BGR2GRAY);

		if (type == 0)
		{
			//均值处理得到背景
			graphic.images_average(frame_gray);
			graphic.setDifImage(frame_gray);
		}
		else
		{
			//中值处理得到背景
			graphic.setDifImage(frame_gray);
		}
			

		//二值化
		threshold(graphic.getDifImage(), graphic.getDifImage(), 50, 255, THRESH_BINARY);
		vector<vector<Point>> contours;
		//寻找中心
		findContours(graphic.getDifImage(), contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
		for (int i = 0; i < contours.size(); i++)
		{
			if ((contours[i].size() > 75)& (contours[i].size() < 150))
			{
				//寻找区域
				Rect roi = boundingRect(Mat(contours[i]));
				rectangle(frame, roi, Vec3b(0, 0, 255), 2);
			}

		}


		cv::imshow("video", frame);		//显示
		
		cv::waitKey(fps);

		count++;
	}

	destroyAllWindows();
}

