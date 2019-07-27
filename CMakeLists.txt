cmake_minimum_required(VERSION 3.0)
project(ArucoGenerationDetection)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV 3.0.0 REQUIRED)
# find_package(Eigen3 REQUIRED)

#生成marker
add_executable(generateChessboard ./src/generateChessboard.cpp)
target_link_libraries(generateChessboard ${OpenCV_LIBRARIES})

add_executable(create_marker ./src/create_marker.cpp)
target_link_libraries(create_marker ${OpenCV_LIBRARIES})

#采集标定相机内参的图像
add_executable(captureImage ./src/captureImage.cpp)
target_link_libraries(captureImage ${OpenCV_LIBRARIES})
#根据采集的图像生成列表
add_executable(imagelist_creator ./src/imagelist_creator.cpp)
target_link_libraries(imagelist_creator ${OpenCV_LIBRARIES})
#标定相机内参
add_executable(camera_calibration ./src/camera_calibration.cpp)
target_link_libraries(camera_calibration ${OpenCV_LIBRARIES})
#识别aruco码
add_executable(detect_markers ./src/detect_markers_33.cpp)
target_link_libraries(detect_markers ${OpenCV_LIBRARIES})