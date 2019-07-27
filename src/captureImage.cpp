#include <unistd.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <cstdio>
 
using namespace cv;
using namespace std;
 
#define WIDTH 640
#define HEIGHT 480

int main() 
{
	char key = 0;
    VideoCapture capture(0);
    Mat camImage;
    int i = 1;
    if (!capture.isOpened())
    {
        cout<<"can not open the camera"<<endl; cin.get(); exit(1);
    }
    // capture.set(CAP_PROP_FRAME_WIDTH, WIDTH);
    // capture.set(CAP_PROP_FRAME_HEIGHT, HEIGHT);
	string pathName = "../CalibPic/calib_";
	string formatName = ".png";
	string num;
	string fileName;
 
	while (capture.read(camImage))   //循环读取摄像画面帧capture >> cam
    {
        int w, h ;
        w= camImage.cols;  //获取相机画面宽高
        h= camImage.rows;      
        imshow("cam",camImage);        
        key = waitKey(10);
        if(key == 'c' || key == 'C') //按c键采集图像
        {
			num = to_string(i);
            while (num.size() < 2) num = "0" + num;
            // num.append(2-num.size(),'0');
            fileName = pathName + num + formatName;
            imwrite(fileName, camImage);
            cout<<"Image: "<<i<<" capture ok!"<<endl; //每次截取成功打印一次，图片保存在工程的编译目录下
            ++i;
        }
        if (key == 'q' || key == 'Q')//按q键退出 ，27为Esc键
        {
             break;
        }
    }
	return 0;
 
}