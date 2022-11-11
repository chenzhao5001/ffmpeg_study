cmake_minimum_required(VERSION 3.23)
project(ffmpeg_test)
set(CMAKE_CXX_STANDARD 11)



ADD_SUBDIRECTORY(haha) #如果不把子目录加入，会报错。(引入包含CMakeList的目录)
ADD_SUBDIRECTORY(hehe)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/haha") #要到haha目录，否则找不到
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/hehe")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/ffmpeg/include")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/sdl/include")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/glfw/include")


link_directories(${PROJECT_SOURCE_DIR}/ffmpeg/lib)
link_directories(${PROJECT_SOURCE_DIR}/sdl/lib)
link_directories(${PROJECT_SOURCE_DIR}/glfw/lib)

#这里我调了很久，add_executable 要在 link_directories后面
add_executable(ffmpeg_test
        main.cpp
        util/io_test.cpp
        util/io_test.h
        util/audio_control.cpp
        util/audio_control.h
        util/codec.cpp
        util/codec.h
        player/newPlay.cpp
        player/newPlay.h
        player/openglPlayer.cpp
        player/openglPlayer.h
        window/windowControl.cpp
        window/windowControl.h)



target_link_libraries( # Specifies the target library.
        ffmpeg_test
        avcodec.lib
        avutil.lib
        avformat.lib
        SDL2.lib
        glfw3.lib
        hehe
        haha)

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/output")
SET(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/output")
