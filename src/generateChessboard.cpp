//编程环境：VS2013, X64，OpenCV3.0.0  
#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

int main(){
	//单位转换  
	int dot_per_inch = 96;  //我的电脑是96DPI(dot per inch）  
	double cm_to_inch = 0.3937; //1cm=0.3937inch  
	double inch_to_cm = 2.54;   //1inch = 2.54cm  
	double inch_per_dot = 1.0 / 96.0;

	//自定义标定板  
	double blockSize_cm = 2.5; //方格尺寸：边长2.5cm的正方形  
	int blockNum = 8; //8*8个方格  


	int blockSize = (int)(blockSize_cm / inch_to_cm *dot_per_inch);
	cout << blockSize << endl;

	int imageSize = blockSize * blockNum;
	cout << imageSize << endl;
	Mat chessBoard(imageSize, imageSize, CV_8UC3, Scalar::all(0));
	unsigned char color = 0;

	for (int i = 0; i < imageSize; i = i + blockSize){
		color = ~color;
		for (int j = 0; j < imageSize; j = j + blockSize){
			Mat ROI = chessBoard(Rect(i, j, blockSize, blockSize));
			ROI.setTo(Scalar::all(color));
			color = ~color;
		}
	}
	imshow("Chess board", chessBoard);
	imwrite("../markerGeneration/chessBoard.jpg", chessBoard);
	cvWaitKey(3000);
	return 0;
}
