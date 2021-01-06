cmake_minimum_required(VERSION 3.16)
project(new)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(new
        anomaly_detection_util.cpp
        anomaly_detection_util.h
        SimpleAnomalyDetector.cpp
        SimpleAnomalyDetector.h
        HybridAnomalyDetector.cpp
        HybridAnomalyDetector.h
        timeseries.h
        timeseries.cpp
        CLI.cpp
        CLI.h
        commands.h
        AnomalyDetector.h
        minCircle.cpp
        minCircle.h
        MainTrain.cpp
        MainEX4.cpp)

