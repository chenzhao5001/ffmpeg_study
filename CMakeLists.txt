cmake_minimum_required(VERSION 3.23)
project(ffmpeg_test)
set(CMAKE_CXX_STANDARD 14)
set(lib_src_DIR ${PROJECT_SOURCE_DIR}/ffmpeg/lib)



ADD_SUBDIRECTORY(haha) #如果不把子目录加入，会报错。(引入包含CMakeList的目录)
ADD_SUBDIRECTORY(hehe)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/haha") #要到haha目录，否则找不到
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/hehe")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/ffmpeg/include")


link_directories(${PROJECT_SOURCE_DIR}/ffmpeg/lib)
add_executable(ffmpeg_test main.cpp util/io_test.cpp util/io_test.h util/audio_control.cpp util/audio_control.h)  #这里我调了很久，add_executable 要在 link_directories后面



target_link_libraries( # Specifies the target library.
        ffmpeg_test
        avcodec.lib
        avutil.lib
        avformat.lib
        hehe
        haha)

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/output")
SET(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/output")
