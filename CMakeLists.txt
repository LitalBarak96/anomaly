cmake_minimum_required(VERSION 3.16)
project(new)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(new
        anomaly_detection_util.cpp
        anomaly_detection_util.h
        MainTrain.cpp)
