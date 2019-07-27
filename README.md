### 相机内参标定

1. 通过CalibUI采集图像
标定图像一般采集15-20张左右，采集过程中注意变换标定板的各种姿态
2. 将采集到的图片放在CalibPic文件夹中
3. 进入build文件夹，打开终端，输入

```
./imagelist_creator ../config/imglistInternal.xml ../CalibPic/*
```


- 此步骤生成标定图片的列表，imagelist_creator是可执行文件名，第一个参数../config/imglistInternal.xml表示生成的文件列表的文件名，第二个参数../CalibPic/* 表示图片文件路径

- **生成的imglistInternal.xml在config文件夹中**

4. 修改../config/config.xml配置文件，对标定程序进行配置

- config.xml文件中设定了标定的各种配置


```
<?xml version="1.0"?>
<opencv_storage>
<Settings>
  <!-- Number of inner corners per a item row and column. (square, circle) -->
  <BoardSize_Width> 9</BoardSize_Width>
  <BoardSize_Height>6</BoardSize_Height>
  
  <!-- The size of a square in some user defined metric system (pixel, millimeter)-->
  <Square_Size>25</Square_Size>
  
  <!-- The type of input used for camera calibration. One of: CHESSBOARD CIRCLES_GRID ASYMMETRIC_CIRCLES_GRID -->
  <Calibrate_Pattern>"CHESSBOARD"</Calibrate_Pattern>
  
  <!-- The input to use for calibration. 
		To use an input camera -> give the ID of the camera, like "1"
		To use an input video  -> give the path of the input video, like "/tmp/x.avi"
		To use an image list   -> give the path to the XML or YAML file containing the list of the images, like "/tmp/circles_list.xml"
		-->
  <Input>"../config/imglistInternal.xml"</Input>
  <!--  If true (non-zero) we flip the input images around the horizontal axis.-->
  <Input_FlipAroundHorizontalAxis>0</Input_FlipAroundHorizontalAxis>
  
  <!-- Time delay between frames in case of camera. -->
  <Input_Delay>1000</Input_Delay>	
  
  <!-- How many frames to use, for calibration. -->
  <Calibrate_NrOfFrameToUse>20</Calibrate_NrOfFrameToUse>
  <!-- Consider only fy as a free parameter, the ratio fx/fy stays the same as in the input cameraMatrix. 
	   Use or not setting. 0 - False Non-Zero - True-->
  <Calibrate_FixAspectRatio> 1 </Calibrate_FixAspectRatio>
  <!-- If true (non-zero) tangential distortion coefficients  are set to zeros and stay zero.-->
  <Calibrate_AssumeZeroTangentialDistortion>1</Calibrate_AssumeZeroTangentialDistortion>
  <!-- If true (non-zero) the principal point is not changed during the global optimization.-->
  <Calibrate_FixPrincipalPointAtTheCenter> 1 </Calibrate_FixPrincipalPointAtTheCenter>
  
  <!-- The name of the output log file. -->
  <Write_outputFileName>"../config/camXbox.yml"</Write_outputFileName>
  <!-- If true (non-zero) we write to the output file the feature points.-->
  <Write_DetectedFeaturePoints>1</Write_DetectedFeaturePoints>
  <!-- If true (non-zero) we write to the output file the extrinsic camera parameters.-->
  <Write_extrinsicParameters>1</Write_extrinsicParameters>
  <!-- If true (non-zero) we show after calibration the undistorted images.-->
  <Show_UndistortedImage>1</Show_UndistortedImage>
 
</Settings>
</opencv_storage>
```


- 可以修改的地方


```
<Square_Size>25</Square_Size> 25表示标定棋盘格的边长为25mm
<Input>"../config/imglistInternal.xml"</Input> 此处配置文件列表的位置 即第3步中生成的文件列表文件
<Calibrate_NrOfFrameToUse>20</Calibrate_NrOfFrameToUse> 此处配置输入图片的数量
<Write_outputFileName>"../config/CamInternal.yml"</Write_outputFileName> 此处配置生成的相机内参数的文件路径和文件名
```



5. 仍然在build文件夹的终端中，输入



```
./camera_calibration ../config/config.xml
```
- 开启标定程序,生成相机内参文件：../config/CamInternal.yml









# Aruco码生成

## Opencv Version: 3.3

## Usage: create_marker [params] outfile 

	--bb (value:1)
		Number of bits in marker borders
	-d
		dictionary: DICT_4X4_50=0, DICT_4X4_100=1, DICT_4X4_250=2,DICT_4X4_1000=3, DICT_5X5_50=4, DICT_5X5_100=5, DICT_5X5_250=6, DICT_5X5_1000=7, DICT_6X6_50=8, DICT_6X6_100=9, DICT_6X6_250=10, DICT_6X6_1000=11, DICT_7X7_50=12,DICT_7X7_100=13, DICT_7X7_250=14, DICT_7X7_1000=15, DICT_ARUCO_ORIGINAL = 16
	--id
		Marker id in the dictionary
	--ms (value:200)
		Marker size in pixels
	--si (value:false)
		show generated image

	outfile (value:<none>)
		Output image


## example


```
./create_marker -d=10 --id=1 --ms=2000 ../markerGeneration/2000.png
```



- 含义:生成字典10里编号为1的Marker,像素大小为2000,输出位置为../markerGeneration/2000.png


# Aruco码位姿检测


```
./detect_markers -d=10 -c=../config/CamInternal.yml -l=0.16
```

- 含义:字典:10,相机内参路径:../config/CamInternal.yml,aruco码的边长16cm(0.16m)