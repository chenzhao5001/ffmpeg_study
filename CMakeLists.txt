cmake_minimum_required(VERSION 3.23)
project(ffmpeg_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(ffmpeg_test main.cpp)

ADD_SUBDIRECTORY(haha) #如果不把子目录加入，会报错。
ADD_SUBDIRECTORY(hehe)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/haha") #要到haha目录，否则找不到
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/hehe")
target_link_libraries( # Specifies the target library.
        ffmpeg_test
        hehe
        haha)

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/output")
SET(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/output")
